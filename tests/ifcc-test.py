#!/usr/bin/env python3

# This scripts runs GCC as well as IFCC on each test-case provided and compares the results.
#
# input: the test-cases are specified either as individual
#         command-line arguments, or as part of a directory tree
#
# output: 
#
# The script is divided in three distinct steps:
# - in the ARGPARSE step, we understand the command-line arguments
# - in the PREPARE step, we copy all our test-cases into a single directory tree
# - in the TEST step, we actually run GCC and IFCC on each test-case
#
#

import argparse
import os
import shutil
import sys
import subprocess
import asyncio
from pathlib import Path
import filecmp

######################################################################################
# ARGPARSE step: make sense of our command-line arguments

argparser = argparse.ArgumentParser(
    description="Compile multiple programs with both GCC and IFCC, run them, and compare the results.",
    epilog=""
)

argparser.add_argument('input', metavar='PATH', nargs='+', help='For each path given:'
                                                                + ' if it\'s a file, use this file;'
                                                                + ' if it\'s a directory, use all *.c files in this subtree')

argparser.add_argument('-d', '--debug', action="count", default=0,
                       help='Increase quantity of debugging messages (only useful to debug the test script itself)')
argparser.add_argument('-v', '--verbose', action="count", default=0,
                       help='Increase verbosity level. You can use this option multiple times.')
argparser.add_argument('-w', '--wrapper', metavar='PATH',
                       help='Invoke your compiler through the shell script at PATH. (default: `ifcc-wrapper.sh`)')

args = argparser.parse_args()

if args.debug >= 2:
    print('debug: command-line arguments ' + str(args))

orig_cwd = os.getcwd()
if "ifcc-test-output" in orig_cwd:
    print('error: cannot run from within the output directory')
    exit(1)

if os.path.isdir('ifcc-test-output'):
    # cleanup previous output directory
    subprocess.call('rm -rf ifcc-test-output', shell=True)
os.mkdir('ifcc-test-output')

# Then we process the inputs arguments i.e. filenames or subtrees
inputfilenames = []
for path in args.input:
    path = os.path.normpath(path)  # collapse redundant slashes etc.
    if os.path.isfile(path):
        if path[-2:] == '.c':
            inputfilenames.append(path)
        else:
            print("error: incorrect filename suffix (should be '.c'): " + path)
            exit(1)
    elif os.path.isdir(path):
        for dirpath, dirnames, filenames in os.walk(path):
            inputfilenames += [dirpath + '/' + name for name in filenames if name[-2:] == '.c']
    else:
        print("error: cannot read input path `" + path + "'")
        sys.exit(1)

# debug: after treewalk
if args.debug:
    print("debug: list of files after tree walk:", " ".join(inputfilenames))

# sanity check
if len(inputfilenames) == 0:
    print("error: found no test-case in: " + " ".join(args.input))
    sys.exit(1)

# Here we check that  we can actually read the files.  Our goal is to
# fail as early as possible when the CLI arguments are wrong.
for inputfilename in inputfilenames:
    try:
        f = open(inputfilename, "r")
        f.close()
    except Exception as e:
        print("error: " + e.args[1] + ": " + inputfilename)
        sys.exit(1)

# Last but not least: we now locate the "wrapper script" that we will
# use to invoke ifcc
if args.wrapper:
    wrapper = os.path.realpath(os.getcwd() + "/" + args.wrapper)
else:
    wrapper = os.path.dirname(os.path.realpath(__file__)) + "/ifcc-wrapper.sh"

if not os.path.isfile(wrapper):
    print("error: cannot find " + os.path.basename(wrapper) + " in directory: " + os.path.dirname(wrapper))
    exit(1)

if args.debug:
    print("debug: wrapper path: " + wrapper)

######################################################################################
# PREPARE step: copy all test-cases under ifcc-test-output

jobs = []

for inputfilename in inputfilenames:
    if args.debug >= 2:
        print("debug: PREPARING " + inputfilename)

    if 'ifcc-test-output' in os.path.realpath(inputfilename):
        print('error: input filename is within output directory: ' + inputfilename)
        exit(1)

    # each test-case gets copied and processed in its own subdirectory:
    # ../somedir/subdir/file.c becomes ./ifcc-test-output/somedir-subdir-file/input.c
    subdir = 'ifcc-test-output/' + inputfilename.strip("./")[:-2].replace('/', '-')
    os.mkdir(subdir)
    shutil.copyfile(inputfilename, subdir + '/input.c')
    jobs.append(Path(subdir))

# eliminate duplicate paths from the 'jobs' list
unique_jobs = []
for j in jobs:
    if not j in unique_jobs:
        unique_jobs.append(j)
jobs = sorted(unique_jobs)
# debug: after deduplication
if args.debug:
    print("debug: list of test-cases after deduplication:", " ".join(map(str, jobs)))

######################################################################################
# TEST step: actually compile all test-cases with both compilers


semaphore = asyncio.Semaphore(10)


def test_result(ok: bool, job_path: Path, message: str = None):
    print(f"TEST-CASE: {job_path}")
    print(f"TEST {'OK' if ok else 'FAIL'}{ f' ({message})' if message else ''}")
    return ok


async def job(p: Path, semaphore: asyncio.Semaphore):

    async with semaphore:

        # Reference compiler = GCC
        gcc_comp = await asyncio.create_subprocess_exec(
            "gcc", "-S", "-o",
            p / "asm-gcc.s",
            p / "input.c",
            stderr=(p / "gcc-compile.txt").open("w")
        )
        # IFCC compiler
        ifcc_comp = await asyncio.create_subprocess_exec(
            Path.cwd() /"ifcc", p / "input.c",
            stdout=(p / "asm-ifcc.s").open("w"),
            stderr=(p / "ifcc-compile.txt").open("w")
        )
        await gcc_comp.wait()
        await ifcc_comp.wait()

        # ifcc correctly rejects invalid program -> test-case ok
        if gcc_comp.returncode != 0 and ifcc_comp.returncode != 0:
            return test_result(True, p, "both failed")

        # ifcc wrongly accepts invalid program -> error
        if gcc_comp.returncode != 0 and ifcc_comp.returncode == 0:
            return test_result(False, p, "your compiler accepts an invalid program")

        # ifcc wrongly rejects valid program -> error
        if gcc_comp.returncode == 0 and ifcc_comp.returncode != 0:
            ok = test_result(False, p, "your compiler rejects a valid program")
            if args.verbose:
                print((p / "ifcc-compile.txt").read_text())
            return ok

        # ifcc accepts to compile valid program -> let's link it
        gcc_link = await asyncio.create_subprocess_exec(
            "gcc", "-o",
            p / "exe-gcc",
            p / "asm-gcc.s",
            stderr=(p / "gcc-link.txt").open("w")
        )
        ifcc_link = await asyncio.create_subprocess_exec(
            "gcc", "-o",
            p / "exe-ifcc",
            p / "asm-ifcc.s",
            stderr=(p / "ifcc-link.txt").open("w")
        )
        await gcc_link.wait()
        await ifcc_link.wait()

        if ifcc_link.returncode:
            ok = test_result(False, p, "your compiler produces incorrect assembly")
            if args.verbose:
                print((p / "ifcc-link.txt").read_text())
            return ok

        # both compilers  did produce an  executable, so now we  run both
        # these executables and compare the results.
        gcc_out = p / "gcc-execute.txt"
        ifcc_out = p / "ifcc-execute.txt"
        gcc_exec = await asyncio.create_subprocess_exec(
            p / "exe-gcc",
            stdout=gcc_out.open("w")
        )
        ifcc_exec = await asyncio.create_subprocess_exec(
            p / "exe-ifcc",
            stdout=ifcc_out.open("w")
        )
        await gcc_exec.wait()
        await ifcc_exec.wait()

        if gcc_exec.returncode != ifcc_exec.returncode:
            return test_result(False, p, "different return codes at execution")

        if not filecmp.cmp(gcc_out, ifcc_out):
            ok = test_result(False, p, "different stdout at execution")
            if args.verbose:
                print("GCC:")
                print(gcc_out.read_text())
                print("IFCC:")
                print(ifcc_out.read_text())
            return ok

        # last but not least
        return test_result(True, p)


async def main():
    res = await asyncio.gather(*(job(j, semaphore) for j in jobs))
    return res.count(False)


failed = asyncio.run(main())

print("-------")
if failed:
    print(f"{failed} test{'s' if failed > 1 else ''} failed")
else:
    print("All tests passed")


