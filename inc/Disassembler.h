#ifndef DASM_H
#define DASM_H

#include <iostream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <vector>
#include <string>

#include "Cartridge.h"

// Addressing mode
typedef enum Addressing{   
    IMMEDIATE,
    ABSOLUTE,
    ZERO_PAGE,
    IMPLIED,
    INDIRECT,
    ABSOLUTE_INDEXED_X,
    ABSOLUTE_INDEXED_Y,
    ZERO_PAGE_INDEXED_X,
    ZERO_PAGE_INDEXED_Y,
    X_INDEXED,
    INDEXED_Y,
    RELATIVE,
    ACCUMULATOR
} Addressing;


typedef struct Instruction{
    Addressing mode;
    std::string opstring;
    uint8_t  cycles;
    bool legal;

    Instruction(Addressing , std::string , uint8_t , bool );

}Instruction;

class Operation{
    public:

        size_t offset;
        Addressing m;
        std::string ops;
        uint8_t  c;
        bool l;
    
        virtual void prettyPrint() =0;
        Operation(Instruction, uint16_t);

};

class ImmOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        ImmOp(Instruction, size_t, uint8_t);
};

class AbsOp : public Operation{
    public:
        uint16_t arg1;
        void prettyPrint();
        AbsOp(Instruction, size_t, uint16_t);
};

class ZpOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        ZpOp(Instruction, size_t, uint8_t);
};

class ImpOp : public Operation{
    public:
        void prettyPrint();
        ImpOp(Instruction, size_t);
};

class IndOp : public Operation{
    public:
        uint16_t arg1;
        void prettyPrint();
        IndOp(Instruction, size_t, uint16_t);
};

class AbsxOp : public Operation{
    public:
        uint16_t arg1;
        void prettyPrint();
        AbsxOp(Instruction, size_t, uint16_t);
};

class AbsyOp : public Operation{
    public:
        uint16_t arg1;
        void prettyPrint();
        AbsyOp(Instruction, size_t, uint16_t);
};

class ZpxOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        ZpxOp(Instruction, size_t, uint8_t);
};

class ZpyOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        ZpyOp(Instruction, size_t, uint8_t);
};

class IndxOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        IndxOp(Instruction, size_t, uint8_t);
};

class IndyOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        IndyOp(Instruction, size_t, uint8_t);
};

class RelOp : public Operation{
    public:
        uint8_t arg1;
        void prettyPrint();
        RelOp(Instruction, size_t, uint8_t);
};

class AccOp : public Operation{
    public:
        void prettyPrint();
        AccOp(Instruction, size_t);
};

class Disassembler{
private: 

    Cartridge cart;
    std::vector<Operation*> program;
    std::map<uint8_t, Instruction> instructionSet;
    uint16_t pcStart;
    
    

public:
    Disassembler(std::string name);
    ~Disassembler();

    void buildInstructionSet();
    void loadPRGBank();
    void printHeader();
    void dumpCHRBanks();
    void printProgram();

    Addressing getAddressing(uint8_t opc);
    std::string getOpName(uint8_t opc);
    bool getLegality(uint8_t opc);

};
#endif