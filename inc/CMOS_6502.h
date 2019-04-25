#ifndef CMOS_6502_H
#define CMOS_6502_H

#include <iostream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <vector>
#include <string>


#include "Cartridge.h"

#define RAMSIZE (0xFFFF + 1)

// Declaration 
class CMOS_6502;
//------------------------//

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
    void (CMOS_6502::*func)(Addressing, uint16_t);

    Instruction(Addressing m, std::string s, uint8_t c, bool l, void(CMOS_6502::*f)(Addressing, uint16_t));

}Instruction;


class Debugger{
    public:
        std::string ops;
        uint16_t arg;
        Addressing mode;
        uint16_t offset;

        uint8_t A;
        uint8_t X;
        uint8_t Y;
        uint8_t P;
        uint8_t S;

        void trace();

};

class CMOS_6502{
    private:

        // Registers
        int8_t X;
        int8_t Y;
        int8_t A;
        int8_t S;
        int8_t P;   // NV#BDIZC
        uint16_t pc;

        // Game to be played
        Cartridge cart;

        // Internals
        MappingInfo info;
        std::vector<Instruction> instructionSet;
        Debugger deb;

        // Parameters for next execution
        void (CMOS_6502::*nextFunc)(Addressing, uint16_t);
        Addressing nextMode;
        uint16_t nextArg;
        uint8_t nextOpc;
        
        // Memory
        uint8_t* RAM;
        
        void loadProgram();
        void buildInstructionSet();

        void fetch();
        void decode();
        void execute();

        // Logic and arithmetic operations
        void ORA(Addressing mode, uint16_t arg1);
        void AND(Addressing mode, uint16_t arg1);
        void EOR(Addressing mode, uint16_t arg1);
        void ADC(Addressing mode, uint16_t arg1);
        void SBC(Addressing mode, uint16_t arg1);
        void CMP(Addressing mode, uint16_t arg1);
        void CPX(Addressing mode, uint16_t arg1);
        void CPY(Addressing mode, uint16_t arg1);
        void DEC(Addressing mode, uint16_t arg1);
        void DEX(Addressing mode, uint16_t arg1);
        void DEY(Addressing mode, uint16_t arg1);
        void INC(Addressing mode, uint16_t arg1);
        void INX(Addressing mode, uint16_t arg1);
        void INY(Addressing mode, uint16_t arg1);
        void ASL(Addressing mode, uint16_t arg1);
        void ROL(Addressing mode, uint16_t arg1);
        void LSR(Addressing mode, uint16_t arg1);
        void ROR(Addressing mode, uint16_t arg1);

        // Move operations
        void LDA(Addressing mode, uint16_t arg1);
        void STA(Addressing mode, uint16_t arg1);
        void LDX(Addressing mode, uint16_t arg1);
        void STX(Addressing mode, uint16_t arg1);
        void LDY(Addressing mode, uint16_t arg1);
        void STY(Addressing mode, uint16_t arg1);
        void TAX(Addressing mode, uint16_t arg1);
        void TXA(Addressing mode, uint16_t arg1);
        void TAY(Addressing mode, uint16_t arg1);
        void TYA(Addressing mode, uint16_t arg1);
        void TSX(Addressing mode, uint16_t arg1);
        void TXS(Addressing mode, uint16_t arg1);
        void PLA(Addressing mode, uint16_t arg1);
        void PHA(Addressing mode, uint16_t arg1);
        void PLP(Addressing mode, uint16_t arg1);
        void PHP(Addressing mode, uint16_t arg1);

        // JMP/Flag operations
        void BPL(Addressing mode, uint16_t arg1);
        void BMI(Addressing mode, uint16_t arg1);
        void BVC(Addressing mode, uint16_t arg1);
        void BVS(Addressing mode, uint16_t arg1);
        void BCC(Addressing mode, uint16_t arg1);
        void BCS(Addressing mode, uint16_t arg1);
        void BNE(Addressing mode, uint16_t arg1);
        void BEQ(Addressing mode, uint16_t arg1);
        void BRK(Addressing mode, uint16_t arg1);
        void RTI(Addressing mode, uint16_t arg1);
        void JSR(Addressing mode, uint16_t arg1);
        void RTS(Addressing mode, uint16_t arg1);
        void JMP(Addressing mode, uint16_t arg1);
        void BIT(Addressing mode, uint16_t arg1);
        void CLC(Addressing mode, uint16_t arg1);
        void SEC(Addressing mode, uint16_t arg1);
        void CLD(Addressing mode, uint16_t arg1);
        void SED(Addressing mode, uint16_t arg1);
        void CLI(Addressing mode, uint16_t arg1);
        void SEI(Addressing mode, uint16_t arg1);
        void CLV(Addressing mode, uint16_t arg1);
        void NOP(Addressing mode, uint16_t arg1);

        // Illegal operations
        void SLO(Addressing mode, uint16_t arg1);
        void RLA(Addressing mode, uint16_t arg1);
        void SRE(Addressing mode, uint16_t arg1);
        void RRA(Addressing mode, uint16_t arg1);
        void SAX(Addressing mode, uint16_t arg1);
        void LAX(Addressing mode, uint16_t arg1);
        void DCP(Addressing mode, uint16_t arg1);
        void ISC(Addressing mode, uint16_t arg1);
        void ANC(Addressing mode, uint16_t arg1);
        void ALR(Addressing mode, uint16_t arg1);
        void ARR(Addressing mode, uint16_t arg1);
        void XAA(Addressing mode, uint16_t arg1);
        void AXS(Addressing mode, uint16_t arg1);
        void AHX(Addressing mode, uint16_t arg1);
        void SHY(Addressing mode, uint16_t arg1);
        void SHX(Addressing mode, uint16_t arg1);
        void TAS(Addressing mode, uint16_t arg1);
        void LAS(Addressing mode, uint16_t arg1);
        void KIL(Addressing mode, uint16_t arg1);


        // Stack operations
        uint8_t pullStack();
        void    pushStack(uint8_t); 

        // Flags setter
        void SetNegative(bool);
        void SetOverflow(bool);
        void SetBrk(bool);
        void SetDecimal(bool);
        void SetIrq(bool);
        void SetZero(bool);
        void SetCarry(bool);


        // Flag getter
        bool Negative();
        bool Overflow();
        bool Brk();
        bool Decimal();
        bool Irq();
        bool Zero();
        bool Carry();
        

    public:

        CMOS_6502(const Cartridge& c);
        ~CMOS_6502();
        
        void play();

        Addressing getAddressing(uint8_t opc);
        std::string getOpName(uint8_t opc);
        void (CMOS_6502::*getFnc(uint8_t opc))(Addressing, uint16_t);


};






#endif