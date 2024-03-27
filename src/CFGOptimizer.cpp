#include "CFGOptimizer.h"

void CFGOptimizer::optimization()
{
    for (auto bb : cfg->bbs)
    {
        for (Instr *instr : bb->instrs)
        {
            if (checkInstr(instr, bb))
            {
                optimization();
                break;
            }
        }
    }
}

bool CFGOptimizer::checkInstr(Instr *instr, BasicBlock *actualbb)
{
    bool modified = false;
    int addr1 = -1;
    int addr2 = -1;
    int destAddr = -1;
    bool isDivideOrModulo = false;

    if (AddInstr *addInstr = dynamic_cast<AddInstr *>(instr))
    {
        addr1 = addInstr->term1;
        addr2 = addInstr->term2;
        destAddr = addInstr->dest;
    }
    else if (SubInstr *subInstr = dynamic_cast<SubInstr *>(instr))
    {
        addr1 = subInstr->term1;
        addr2 = subInstr->term2;
        destAddr = subInstr->dest;
    }
    else if (MulInstr *mulInstr = dynamic_cast<MulInstr *>(instr))
    {
        addr1 = mulInstr->factor1;
        addr2 = mulInstr->factor2;
        destAddr = mulInstr->dest;
    }
    else if (DivInstr *divInstr = dynamic_cast<DivInstr *>(instr))
    {
        addr1 = divInstr->numerator;
        addr2 = divInstr->denominator;
        destAddr = divInstr->dest;
        isDivideOrModulo = true;
    }
    else if (ModInstr *modInstr = dynamic_cast<ModInstr *>(instr))
    {
        addr1 = modInstr->numerator;
        addr2 = modInstr->denominator;
        destAddr = modInstr->dest;
        isDivideOrModulo = true;
    }
    else if (BitInstr *bitInstr = dynamic_cast<BitInstr *>(instr))
    {
        addr1 = bitInstr->term1;
        addr2 = bitInstr->term2;
        destAddr = bitInstr->dest;
    }

    if (const_index.find(addr1) != const_index.end() && const_index.find(addr2) != const_index.end())
    {
        if (isDivideOrModulo && const_index[addr2] == 0)
        {
            divide_or_modulo.insert(const_index[addr1]);
        }
        else
        {
            updateCFG(addr1, addr2, destAddr, actualbb, instr);
            modified = true;
        }
    }
    return modified;
}

void CFGOptimizer::updateCFG(int addr1, int addr2, int destAddr, BasicBlock *actualbb, Instr *instr)
{
    // créer la nouvelle instruction const
    ConstInstr *constInstr1 = dynamic_cast<ConstInstr *>(instr_index[addr1]);
    ConstInstr *constInstr2 = dynamic_cast<ConstInstr *>(instr_index[addr2]);

    int result;

    if (AddInstr *addInstr = dynamic_cast<AddInstr *>(instr))
    {
        result = constInstr1->value + constInstr2->value;
    }
    else if (SubInstr *subInstr = dynamic_cast<SubInstr *>(instr))
    {
        result = constInstr1->value - constInstr2->value;
    }
    else if (MulInstr *mulInstr = dynamic_cast<MulInstr *>(instr))
    {
        result = constInstr1->value * constInstr2->value;
    }
    else if (DivInstr *divInstr = dynamic_cast<DivInstr *>(instr))
    {
        result = constInstr1->value / constInstr2->value;
    }
    else if (ModInstr *modInstr = dynamic_cast<ModInstr *>(instr))
    {
        result = constInstr1->value % constInstr2->value;
    }
    else if (NegInstr *negInstr = dynamic_cast<NegInstr *>(instr))
    {
        result = -constInstr1->value;
    }
    else if (BitInstr *bitInstr = dynamic_cast<BitInstr *>(instr))
    {
        switch (bitInstr->bitOp)
        {
        case BitInstr::And:
            result = constInstr1->value & constInstr2->value;
            break;
        case BitInstr::Or:
            result = constInstr1->value | constInstr2->value;
            break;
        case BitInstr::Xor:
            result = constInstr1->value ^ constInstr2->value;
            break;
        }
    }
    else
    {
        // Le cas par défaut si l'instruction n'est d'aucun type connu
    }

    ConstInstr *constInstruction = new ConstInstr(result, destAddr);
    const_index[destAddr] = result;
    instr_index[destAddr] = constInstruction;

    // supprimer les deux instructions const
    actualbb->delete_instr(constInstr1);
    actualbb->delete_instr(constInstr2);
    // remplacer l'intruction add par la nouvelle instruction const
    actualbb->replace_instr(instr, constInstruction);
}

void CFGOptimizer::divideOrModuloByZero()
{
    for (int i : divide_or_modulo)
    {
        cerr << "Error: Division or modulo by zero with value " << i << endl;
    }
}