# config.mk contains the paths to antlr4 etc.
# Each student should have a config.mk corresponding to her system.
# Examples are  ubuntu.mk, DI.mk, fedora.mk
# Then config.mk should be in the .gitignore of your project
ifeq ($(wildcard makefiles/config.mk),)
	include makefiles/DI.mk
else
	include makefiles/config.mk
endif

CC=g++
CCFLAGS=-g -c -std=c++17 -I$(ANTLRINC) -Wno-attributes # -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDFLAGS=-g

SRC_DIR = src
BUILD_DIR = build
GENERATED_DIR = $(SRC_DIR)/generated
TEST_OUTPUT = ifcc-test-output
EXE = ifcc

default: all
all: $(EXE)

##########################################
# automatically find source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# form object file names
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# generated objects
GENERATED_OBJECTS=\
	$(BUILD_DIR)/ifccBaseVisitor.o \
	$(BUILD_DIR)/ifccLexer.o \
	$(BUILD_DIR)/ifccVisitor.o \
	$(BUILD_DIR)/ifccParser.o \

##########################################
# link together all pieces of our compiler
$(EXE): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJECTS) $(GENERATED_OBJECTS) $(ANTLRLIB) -o $(EXE)

##########################################
# compile our hand-written C++ code: main(), Visitors, etc.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(GENERATED_OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) -MMD -o $@ $<

##########################################
# compile all the antlr-generated C++
$(BUILD_DIR)/%.o: $(GENERATED_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) -MMD -o $@ $<

# automagic dependency management: `gcc -MMD` generates all the .d files for us
-include $(BUILD_DIR)/*.d
$(BUILD_DIR)/%.d:

##########################################
# generate the C++ implementation of our Lexer/Parser/Visitor
$(GENERATED_DIR)/ifccLexer.cpp: $(GENERATED_DIR)/ifccParser.cpp
$(GENERATED_DIR)/ifccVisitor.cpp: $(GENERATED_DIR)/ifccParser.cpp
$(GENERATED_DIR)/ifccBaseVisitor.cpp: $(GENERATED_DIR)/ifccParser.cpp
$(GENERATED_DIR)/ifccParser.cpp: ifcc.g4
	@mkdir -p $(GENERATED_DIR)
	$(ANTLR) -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED_DIR) ifcc.g4

# prevent automatic cleanup of "intermediate" files like ifccLexer.cpp etc
.PRECIOUS: $(GENERATED_DIR)/ifcc%.cpp

##########################################
# view the parse tree in a graphical window

# Usage: `make gui FILE=path/to/your/file.c`
FILE ?= tests/testfiles/1_return42.c

gui:
	@mkdir -p $(GENERATED_DIR) $(BUILD_DIR)
	$(ANTLR) -Dlanguage=Java -o $(GENERATED_DIR) ifcc.g4
	javac -cp $(ANTLRJAR) -d $(BUILD_DIR) $(GENERATED_DIR)/*.java
	java -cp $(ANTLRJAR):$(BUILD_DIR) org.antlr.v4.gui.TestRig $(EXE) axiom -gui $(FILE)

##########################################
# run tests
test: $(EXE)
	python3 ifcc-test.py tests

##########################################
# delete all machine-generated files
clean:
	rm -rf $(BUILD_DIR) $(GENERATED_DIR) $(TEST_OUTPUT)
	rm -f $(EXE)

##########################################
# documentation
doc:
	doxygen
	xdg-open html/index.html
