#include "CMOS_6502.h"

//-------------------------------------------------------------------------------------------------------------------------------//
Instruction::Instruction(Addressing m, std::string s, uint8_t c, bool l, void(CMOS_6502::*f)(Addressing, uint16_t)) : mode(m), opstring(s), cycles(c), legal(l), func(f){};
//-------------------------------------------------------------------------------------------------------------------------------//





void  CMOS_6502::buildInstructionSet(){


    
    instructionSet.push_back(Instruction(IMPLIED             , std::string("BRK"), 7, true , &CMOS_6502::BRK));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("ORA"), 6, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("SLO"), 8, false, &CMOS_6502::SLO));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("NOP"), 3, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("ORA"), 3, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("ASL"), 5, true , &CMOS_6502::ASL));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("SLO"), 5, false, &CMOS_6502::SLO));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("PHP"), 3, true , &CMOS_6502::PHP));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ORA"), 2, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(ACCUMULATOR         , std::string("ASL"), 2, true , &CMOS_6502::ASL));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ANC"), 2, false, &CMOS_6502::ANC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ORA"), 4, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ASL"), 6, true , &CMOS_6502::ASL));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("SLO"), 6, false, &CMOS_6502::SLO));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BPL"), 2, true , &CMOS_6502::BPL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("ORA"), 5, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("SLO"), 8, false, &CMOS_6502::SLO));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ORA"), 4, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ASL"), 6, true , &CMOS_6502::ASL));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("SLO"), 6, false, &CMOS_6502::SLO));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("CLC"), 2, true , &CMOS_6502::CLC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("ORA"), 4, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("SLO"), 7, false, &CMOS_6502::SLO));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ORA"), 4, true , &CMOS_6502::ORA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ASL"), 7, true , &CMOS_6502::ASL));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("SLO"), 7, false, &CMOS_6502::SLO));

    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("JSR"), 6, true , &CMOS_6502::JSR));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("AND"), 6, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("RLA"), 8, false, &CMOS_6502::RLA));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("BIT"), 3, true , &CMOS_6502::BIT));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("AND"), 3, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("RLO"), 5, true , &CMOS_6502::ROL));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("RLA"), 5, false, &CMOS_6502::RLA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("PLP"), 4, true , &CMOS_6502::PLP));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("AND"), 2, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(ACCUMULATOR         , std::string("ROL"), 2, true , &CMOS_6502::ROL));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ANC"), 2, false, &CMOS_6502::ANC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("BIT"), 4, true , &CMOS_6502::BIT));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("AND"), 4, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ROL"), 6, true , &CMOS_6502::ROL));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("RLA"), 6, false, &CMOS_6502::RLA));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BMI"), 2, true , &CMOS_6502::BMI));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("AND"), 5, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("RLA"), 8, false, &CMOS_6502::RLA));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("AND"), 4, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ROL"), 6, true , &CMOS_6502::ROL));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("RLA"), 6, false, &CMOS_6502::RLA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("SEC"), 2, true , &CMOS_6502::SEC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("AND"), 4, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("RLA"), 7, false, &CMOS_6502::RLA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("AND"), 4, true , &CMOS_6502::AND));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ROL"), 7, true , &CMOS_6502::ROL));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("RLA"), 7, false, &CMOS_6502::RLA));

    instructionSet.push_back(Instruction(IMPLIED             , std::string("RTI"), 6, true , &CMOS_6502::RTI));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("EOR"), 6, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("SRE"), 8, false, &CMOS_6502::SRE));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("NOP"), 3, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("EOR"), 3, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("LSR"), 5, true , &CMOS_6502::LSR));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("SRE"), 5, false, &CMOS_6502::SRE));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("PHA"), 3, true , &CMOS_6502::PHA));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("EOR"), 2, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(ACCUMULATOR         , std::string("LSR"), 2, true , &CMOS_6502::LSR));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ALR"), 2, false, &CMOS_6502::ALR));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("JMP"), 3, true , &CMOS_6502::JMP));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("EOR"), 4, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("LSR"), 6, true , &CMOS_6502::LSR));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("SRE"), 6, false, &CMOS_6502::SRE));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BVC"), 2, true , &CMOS_6502::BVC));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("EOR"), 5, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("SRE"), 8, false, &CMOS_6502::SRE));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("EOR"), 4, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("LSR"), 6, true , &CMOS_6502::LSR));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("SRE"), 6, false, &CMOS_6502::SRE));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("CLI"), 2, true , &CMOS_6502::CLI));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("EOR"), 4, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("SRE"), 7, false, &CMOS_6502::SRE));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("EOR"), 4, true , &CMOS_6502::EOR));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("LSR"), 7, true , &CMOS_6502::LSR));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("SRE"), 7, false, &CMOS_6502::SRE));

    instructionSet.push_back(Instruction(IMPLIED             , std::string("RTS"), 6, true , &CMOS_6502::RTS));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("ADC"), 6, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("RRA"), 8, false, &CMOS_6502::RRA));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("NOP"), 3, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("ADC"), 3, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("ROR"), 5, true , &CMOS_6502::ROR));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("RRA"), 5, false, &CMOS_6502::RRA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("PLA"), 4, true , &CMOS_6502::PLA));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ADC"), 2, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ACCUMULATOR         , std::string("ROR"), 2, true , &CMOS_6502::ROR));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("ARR"), 2, false, &CMOS_6502::ARR));
    instructionSet.push_back(Instruction(INDIRECT            , std::string("JMP"), 5, true , &CMOS_6502::JMP));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ADC"), 4, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ROR"), 6, true , &CMOS_6502::ROR));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("RRA"), 6, false, &CMOS_6502::RRA));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BVS"), 2, true , &CMOS_6502::BVS));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("ADC"), 5, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("RRA"), 8, false, &CMOS_6502::RRA));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ADC"), 4, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ROR"), 6, true , &CMOS_6502::ROR));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("RRA"), 6, false, &CMOS_6502::RRA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("SEI"), 2, true , &CMOS_6502::SEI));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("ADC"), 4, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("RRA"), 7, false, &CMOS_6502::RRA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ADC"), 4, true , &CMOS_6502::ADC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ROR"), 7, true , &CMOS_6502::ROR));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("RRA"), 7, false, &CMOS_6502::RRA));

    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("STA"), 6, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("SAX"), 6, false, &CMOS_6502::SAX));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("STY"), 3, true , &CMOS_6502::STY));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("STA"), 3, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("STX"), 3, true , &CMOS_6502::STX));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("SAX"), 3, false, &CMOS_6502::SAX));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("DEY"), 2, true , &CMOS_6502::DEY));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TXA"), 2, true , &CMOS_6502::TXA));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("XAA"), 2, false, &CMOS_6502::XAA));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("STY"), 4, true , &CMOS_6502::STY));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("STA"), 4, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("STX"), 4, true , &CMOS_6502::STX));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("SAX"), 4, false, &CMOS_6502::SAX));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BCC"), 2, true , &CMOS_6502::BCC));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("STA"), 6, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("AHX"), 6, false, &CMOS_6502::AHX));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("STY"), 4, true , &CMOS_6502::STY));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("STA"), 4, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_Y , std::string("STX"), 4, true , &CMOS_6502::STX));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_Y , std::string("SAX"), 4, false, &CMOS_6502::SAX));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TYA"), 2, true , &CMOS_6502::TYA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("STA"), 5, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TXS"), 2, true , &CMOS_6502::TXS));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("TAS"), 5, false, &CMOS_6502::TAS));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("SHY"), 5, false, &CMOS_6502::SHY));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("STA"), 5, true , &CMOS_6502::STA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("SHX"), 5, false, &CMOS_6502::SHX));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("AHX"), 5, false, &CMOS_6502::AHX));

    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("LDY"), 2, true , &CMOS_6502::LDY));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("LDA"), 5, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("LDX"), 0, true , &CMOS_6502::LDX));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("LAX"), 5, false, &CMOS_6502::LAX));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("LDY"), 4, true , &CMOS_6502::LDY));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("LDX"), 4, true , &CMOS_6502::LDX));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("LAX"), 4, false, &CMOS_6502::LAX));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TAY"), 2, true , &CMOS_6502::TAY));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TAX"), 2, true , &CMOS_6502::TAX));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("LAX"), 4, false, &CMOS_6502::LAX));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("LDY"), 4, true , &CMOS_6502::LDY));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("LDX"), 4, true , &CMOS_6502::LDX));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("LAX"), 4, false, &CMOS_6502::LAX));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BCS"), 2, true , &CMOS_6502::BCS));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("LDA"), 5, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("LAX"), 5, false, &CMOS_6502::LAX));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("LDY"), 4, true , &CMOS_6502::LDY));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_Y , std::string("LDX"), 4, true , &CMOS_6502::LDX));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_Y , std::string("LAX"), 4, false, &CMOS_6502::LAX));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("CLV"), 2, true , &CMOS_6502::CLV));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("TSX"), 2, true , &CMOS_6502::TSX));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("LAS"), 4, false, &CMOS_6502::LAS));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("LDY"), 4, true , &CMOS_6502::LDY));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("LDA"), 4, true , &CMOS_6502::LDA));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("LDX"), 4, true , &CMOS_6502::LDX));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("LAX"), 4, false, &CMOS_6502::LAX));

    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("CPY"), 2, true , &CMOS_6502::CPY));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("CMP"), 6, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("DCP"), 8, false, &CMOS_6502::DCP));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("CPY"), 3, true , &CMOS_6502::CPY));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("CMP"), 3, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("DEC"), 5, true , &CMOS_6502::DEC));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("DCP"), 5, false, &CMOS_6502::DCP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("INY"), 2, true , &CMOS_6502::INY));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("CMP"), 2, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("DEX"), 2, true , &CMOS_6502::DEX));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("AXS"), 2, false, &CMOS_6502::AXS));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("CPY"), 4, true , &CMOS_6502::CPY));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("CMP"), 4, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("DEC"), 6, true , &CMOS_6502::DEC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("DCP"), 6, false, &CMOS_6502::DCP));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BNE"), 2, true , &CMOS_6502::BNE));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("CMP"), 5, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("DCP"), 8, false, &CMOS_6502::DCP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("CMP"), 4, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("DEC"), 6, true , &CMOS_6502::DEC));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("DCP"), 6, false, &CMOS_6502::DCP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("CLD"), 2, true , &CMOS_6502::CLD));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("CMP"), 4, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("DCP"), 7, false, &CMOS_6502::DCP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("CMP"), 4, true , &CMOS_6502::CMP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("DEC"), 7, true , &CMOS_6502::DEC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("DCP"), 7, false, &CMOS_6502::DCP));

    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("CPX"), 2, true , &CMOS_6502::CPX));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("SBC"), 6, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(X_INDEXED           , std::string("ISC"), 8, false, &CMOS_6502::ISC));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("CPX"), 3, true , &CMOS_6502::CPX));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("SBC"), 3, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("INC"), 5, true , &CMOS_6502::INC));
    instructionSet.push_back(Instruction(ZERO_PAGE           , std::string("ISC"), 5, false, &CMOS_6502::ISC));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("INX"), 2, true , &CMOS_6502::INX));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("SBC"), 2, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("NOP"), 2, true , &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("SBC"), 2, false, &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("CPX"), 4, true , &CMOS_6502::CPX));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("SBC"), 4, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("INC"), 6, true , &CMOS_6502::INC));
    instructionSet.push_back(Instruction(ABSOLUTE            , std::string("ISC"), 6, false, &CMOS_6502::ISC));

    instructionSet.push_back(Instruction(RELATIVE            , std::string("BEQ"), 2, true , &CMOS_6502::BEQ));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("SBC"), 5, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("KIL"), 0, false, &CMOS_6502::KIL));
    instructionSet.push_back(Instruction(INDEXED_Y           , std::string("ISC"), 8, false, &CMOS_6502::ISC));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("SBC"), 4, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("INC"), 6, true , &CMOS_6502::INC));
    instructionSet.push_back(Instruction(ZERO_PAGE_INDEXED_X , std::string("ISC"), 6, false, &CMOS_6502::ISC));
    instructionSet.push_back(Instruction(IMPLIED             , std::string("SED"), 2, true , &CMOS_6502::SED));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("SBC"), 4, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(IMMEDIATE           , std::string("NOP"), 2, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_Y  , std::string("ISC"), 7, false, &CMOS_6502::ISC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false, &CMOS_6502::NOP));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("SBC"), 4, true , &CMOS_6502::SBC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("INC"), 7, true , &CMOS_6502::INC));
    instructionSet.push_back(Instruction(ABSOLUTE_INDEXED_X  , std::string("ISC"), 7, false, &CMOS_6502::ISC));


};

//-------------------------------------------------------------------------------------------------------------------------------//

CMOS_6502::CMOS_6502(const Cartridge& c): cart(c) {
    
    X = 0; 
    Y = 0; 
    A = 0;
    S = 0xFD; 
    P = 0x24;

    info = cart.getMappingInfo();
    pc = info.pcStart;

    RAM = (uint8_t*)calloc(RAMSIZE, sizeof(uint8_t));
    memset(RAM, (uint8_t)0, RAMSIZE * sizeof(uint8_t));

    buildInstructionSet();


    loadProgram();
    uint16_t tmp = RAM[0xFFFC] + (RAM[0xFFFD] << 8);
    printf("Essai reset : %04X\n", tmp);
}

CMOS_6502::~CMOS_6502(){
    free(RAM);
}

//-------------------------------------------------------------------------------------------------------------------------------//

void CMOS_6502::loadProgram(){

    size_t actualSize = cart.PRG_size()/ 8;
    size_t maxSize = info.PRGBankEnd - info.PRGBankStart + 1;

    if(actualSize <= maxSize)
        memcpy(&RAM[info.PRGBankStart], cart.PRG(), maxSize * sizeof(uint8_t));

    else
        throw(std::string("Memory mapping failed"));
    
    return;
}


void CMOS_6502::fetch(){
    nextOpc = RAM[pc];
    printf("%02X\n", nextOpc); 
    deb.offset = pc;
    deb.ops = getOpName(nextOpc);
    return;
}

void CMOS_6502::decode(){
    uint16_t tmp;
    nextFunc = getFnc(nextOpc);
    nextMode = getAddressing(nextOpc);
    deb.mode = nextMode;
    
    switch(nextMode){ 
        case IMMEDIATE:
            nextArg = RAM[++pc];
            break;

        case ABSOLUTE :
            nextArg = RAM[++pc] + (RAM[++pc] << 8);
            break;

        case ZERO_PAGE :
            nextArg = RAM[++pc];
            break;

        case IMPLIED :
            nextArg = 0;
            break;

        case INDIRECT :
            nextArg = RAM[++pc] + (RAM[++pc] << 8);
            break;

        case ABSOLUTE_INDEXED_X :
            nextArg = RAM[++pc] + (RAM[++pc] << 8) + X;
            break;

        case ABSOLUTE_INDEXED_Y :
            nextArg = RAM[++pc] + (RAM[++pc] << 8) + Y;
            break;

        case ZERO_PAGE_INDEXED_X :
            nextArg = RAM[++pc] + X;
            break;

        case ZERO_PAGE_INDEXED_Y :
            nextArg = RAM[++pc] + Y;
            break;

        case X_INDEXED :
            tmp = RAM[++pc] + X;
            nextArg = tmp + (tmp << 8);
            break;

        case INDEXED_Y :
            tmp = RAM[++pc];
            nextArg = RAM[tmp] + (RAM[tmp + 1] << 8) + Y;
            break;

        case RELATIVE :
            nextArg = pc + (int8_t)RAM[++pc] + 2;
            break;

        case ACCUMULATOR :
            nextArg = 0;
            break;

        default:
            break;
    }
    pc ++;
    return;
}



void CMOS_6502::execute(){
    deb.arg = nextArg;
    deb.A = A;
    deb.X = X;
    deb.Y = Y;
    deb.P = P;
    deb.S = S;
    deb.trace();
    (this->*nextFunc)(nextMode, nextArg);
    return;
}

void CMOS_6502::play(){
    bool keepgoing = true;
    int max = 0;
    while(keepgoing){
        fetch();
        decode();
        execute();
        max ++;
        keepgoing = (max <= 8990) ? true : false; 
    }
    return;
}

Addressing CMOS_6502::getAddressing(uint8_t opc){
    return (instructionSet[opc].mode);
}

std::string CMOS_6502::getOpName(uint8_t opc){
    return (instructionSet[opc].opstring);  
}

void (CMOS_6502::*CMOS_6502::getFnc(uint8_t opc))(Addressing, uint16_t) {
    return (instructionSet[opc].func);  
}


//------------------------------------------------------------------------------------------------------//
void CMOS_6502::SetNegative(bool b){
    if(b){
        P|= 0x80;
        return;
    }

    P&= 0x7F;
    return;
}

void CMOS_6502::SetOverflow(bool b){
    if(b){
        P|= 0x40;
        return;
    }
    P&= 0XBF;
    return;
}

void CMOS_6502::SetBrk(bool b){
    if(b){
        P|= 0x10;
        return;
    }
    P&= 0XEF;
    return;
}

void CMOS_6502::SetDecimal(bool b){
    if(b){
        P|= 0x08;
        return;
    }
    P&= 0XF7;
    return;
}

void CMOS_6502::SetIrq(bool b){
    if(b){
        P|= 0x04;
        return;
    }
    P&= 0XFB;
    return;
}

void CMOS_6502::SetZero(bool b){
    if(b){
        P|= 0x02;
        return;
    }

    P&= 0xFD;
    return;
}

void CMOS_6502::SetCarry(bool b){
    if(b){
        P|= 0x01;
        return;
    }

    P&= 0xFE;
    return;
}
//------------------------------------------------------------------------------------------------------//

bool CMOS_6502::Negative(){
    return (P & 0x80);
}

bool CMOS_6502::Overflow(){
    return (P & 0x40);
}

bool CMOS_6502::Brk(){
    return (P & 0x10);   
}

bool CMOS_6502::Decimal(){
    return (P & 0x08);
}
bool CMOS_6502::Irq(){
    return (P & 0x04);
}

bool CMOS_6502::Zero(){
    return (P & 0x2);   
}

bool CMOS_6502::Carry(){
    return (P & 0x01);
}

//-------------------------------------------------------------------------------------------------------------------------------//

void CMOS_6502::ORA(Addressing mode, uint16_t arg1){

    if(mode == IMMEDIATE)
        A|= (arg1 & 0xFF);
    else
        A|= RAM[arg1];

    SetNegative(A & 0x80);
    SetZero(!(A & 0xFF));

    return ;
}


void CMOS_6502::AND(Addressing mode, uint16_t arg1){

    if(mode == IMMEDIATE)
        A&= (arg1 & 0xFF);
    else
        A&= RAM[arg1];

    SetNegative(A & 0x80);
    SetZero(!(A & 0xFF));
    return ;
}

void CMOS_6502::EOR(Addressing mode, uint16_t arg1){


    if(mode == IMMEDIATE)
        A^= (arg1 & 0xFF);
    else
        A^= RAM[arg1];

    SetNegative(A & 0x80);
    SetZero(!(A & 0xFF));

    return ;
}

void CMOS_6502::ADC(Addressing mode, uint16_t arg1){
  
    uint8_t m;

    if(mode == IMMEDIATE)
        m = arg1;
    else
        m = RAM[arg1];

    uint16_t tmp = A + m + Carry();

    SetZero(!(tmp & 0xFF));

    if(Decimal()){

        if(((A & 0xF ) + (m & 0xF) + Carry()) > 0x9){
            tmp += 0x6;
        }

        SetNegative(tmp & 0x80);
        SetOverflow((A^tmp) & (m ^ tmp) & (0x80) );

        if (tmp > 0x99){
            tmp += 0x60;
        }

        SetCarry(tmp > 0x99);
    }

    else{
        SetNegative(tmp & 0x80);
        SetCarry(tmp > 0xFF);
        SetOverflow((A^tmp) & (m ^ tmp) & (0x80) );
    }



    A = tmp & 0xFF;


    return ;
}

void CMOS_6502::SBC(Addressing mode, uint16_t arg1){

  
    uint8_t m;

    if(mode == IMMEDIATE)
        m = arg1;
    else
        m = RAM[arg1];

    uint16_t tmp = A - m - !Carry();

    SetZero(!(tmp & 0xFF));
    SetNegative(tmp & 0x80);
    SetOverflow((A^tmp) & (m ^ tmp) & (0x80) );

    if(Decimal()){

        if(((A & 0xF ) - !Carry()) < (m & 0xF)){
            tmp -= 0x6;
        }

        if (tmp > 0x99){
            tmp -= 0x60;
        }
    }

    SetCarry(tmp < 0x100);

    A = tmp & 0xFF;
   

    return ;
}

void CMOS_6502::CMP(Addressing mode, uint16_t arg1){

    uint8_t m;

    if(mode == IMMEDIATE)
        m = arg1;
    else
        m = RAM[arg1];

    uint16_t tmp = A - m;

    SetZero(!(tmp & 0xFF));
    SetNegative(tmp & 0x80);
    SetCarry(tmp < 0x100);

    return;
}

void CMOS_6502::CPX(Addressing mode, uint16_t arg1){

    uint8_t m;

    if(mode == IMMEDIATE)
        m = arg1;
    else
        m = RAM[arg1];

    uint16_t tmp = X - m;

    SetZero(!(tmp & 0xFF));
    SetNegative(tmp & 0x80);
    SetCarry(tmp < 0x100);

    return;
}

void CMOS_6502::CPY(Addressing mode, uint16_t arg1){

    uint8_t m;

    if(mode == IMMEDIATE)
        m = arg1;
    else
        m = RAM[arg1];

    uint16_t tmp = Y - m;

    SetZero(!(tmp & 0xFF));
    SetNegative(tmp & 0x80);
    SetCarry(tmp < 0x100);

    return;
}

void CMOS_6502::DEC(Addressing mode, uint16_t arg1){
    uint8_t tmp = RAM[arg1];
    tmp -= 1;
    SetNegative(tmp & 0x80);
    SetZero(!(tmp & 0xFF));
    RAM[arg1] = tmp;

    return;
}

void CMOS_6502::DEX(Addressing mode, uint16_t arg1){
    X -= 1;
    SetNegative(X & 0x80);
    SetZero(!(X & 0xFF));

    return;
}

void CMOS_6502::DEY(Addressing mode, uint16_t arg1){
    Y -= 1;
    SetNegative(Y & 0x80);
    SetZero(!(Y & 0xFF));

    return;
}

void CMOS_6502::INC(Addressing mode, uint16_t arg1){
    uint8_t tmp = RAM[arg1];
    tmp += 1;
    SetNegative(tmp & 0x80);
    SetZero(!(tmp & 0xFF));
    RAM[arg1] = tmp;

    return;
}

void CMOS_6502::INX(Addressing mode, uint16_t arg1){
    X += 1;
    SetNegative(X & 0x80);
    SetZero(!(X & 0xFF));

    return;
}

void CMOS_6502::INY(Addressing mode, uint16_t arg1){
    Y += 1;
    SetNegative(Y & 0x80);
    SetZero(!(Y & 0xFF));

    return;
}

void CMOS_6502::ASL(Addressing mode, uint16_t arg1){
    if(mode != ACCUMULATOR){

        uint8_t tmp = RAM[arg1];
        SetCarry(tmp & 0x80);
        tmp <<= 1;
        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        RAM[arg1] = tmp;
    }

    else{
        uint8_t tmp = A;
        SetCarry(tmp & 0x80);
        tmp <<= 1;
        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        A= tmp;      
    }

    return;
}

void CMOS_6502::ROL(Addressing mode, uint16_t arg1){
    
    if(mode != ACCUMULATOR){

        uint8_t tmp = RAM[arg1];
        uint8_t oldCarry = Carry() ? 0x1 : 0;
        SetCarry(tmp & 0x80);

        tmp <<= 1;
        tmp |= oldCarry;

        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        RAM[arg1] = tmp;
    }

    else{
        uint8_t tmp = A;
        uint8_t oldCarry = Carry() ? 0x1 : 0;
        SetCarry(tmp & 0x80);

        tmp <<= 1;
        tmp |= oldCarry;

        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        A = tmp;
    }

    return;
}

void CMOS_6502::LSR(Addressing mode, uint16_t arg1){

    if(mode != ACCUMULATOR){  

        uint8_t tmp = RAM[arg1];
        SetCarry(tmp & 0x01);
        tmp >>= 1;
        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        RAM[arg1] = tmp;
    }

    else{

        uint8_t tmp = A;
        SetCarry(tmp & 0x01);
        tmp >>= 1;
        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        A = tmp;
    }
    
    return;
}

void CMOS_6502::ROR(Addressing mode, uint16_t arg1){

    if(mode != ACCUMULATOR){  

        uint16_t tmp = RAM[arg1];
        if(Carry()) tmp |= 0x100;
        SetCarry(tmp & 0x01);
        tmp >>= 1;
        tmp |= 0xFF;

        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        RAM[arg1] = tmp;
    }

    else{

        uint16_t tmp = A;
        if(Carry()) tmp |= 0x100;
        SetCarry(tmp & 0x01);
        tmp >>= 1;
        tmp |= 0xFF;

        SetNegative(tmp & 0x80);
        SetZero(!(tmp & 0xFF));
        A = tmp;
    }
    

    return;
}

void CMOS_6502::LDA(Addressing mode, uint16_t arg1){
  

    if(mode == IMMEDIATE)
        A = arg1;
    else
        A = RAM[arg1];

    SetNegative( A & 0x80 );
    SetZero(!( A & 0xFF));
    return;
}

void CMOS_6502::STA(Addressing mode, uint16_t arg1){
    RAM[arg1] = A;
    return;
}

void CMOS_6502::LDX(Addressing mode, uint16_t arg1){

    if(mode == IMMEDIATE)
        X = arg1;
    else
        X = RAM[arg1];

    SetNegative( X & 0x80 );
    SetZero(!( X & 0xFF));
    return;
}

void CMOS_6502::STX(Addressing mode, uint16_t arg1){
    RAM[arg1] = X;
    return;
}

void CMOS_6502::LDY(Addressing mode, uint16_t arg1){

    if(mode == IMMEDIATE)
        Y = arg1;
    else
        Y = RAM[arg1];

    SetNegative( Y & 0x80 );
    SetZero(!( Y & 0xFF));
    return;
}

void CMOS_6502::STY(Addressing mode, uint16_t arg1){
    RAM[arg1] = Y;
    return;
}

void CMOS_6502::TAX(Addressing mode, uint16_t arg1){
    X = A;
    SetNegative( X & 0x80 );
    SetZero(!( X & 0xFF));
    return;
}

void CMOS_6502::TXA(Addressing mode, uint16_t arg1){
    A = X;
    SetNegative( A & 0x80 );
    SetZero(!( A & 0xFF));
    return;
}

void CMOS_6502::TAY(Addressing mode, uint16_t arg1){
    Y = A;
    SetNegative( Y & 0x80 );
    SetZero(!( Y & 0xFF));
    return;
}

void CMOS_6502::TYA(Addressing mode, uint16_t arg1){
    A = Y;
    SetNegative( A & 0x80 );
    SetZero(!( A & 0xFF));
    return;
}

void CMOS_6502::TSX(Addressing mode, uint16_t arg1){
    X = S;
    SetNegative( X & 0x80 );
    SetZero(!( X & 0xFF));
    return;
}

void CMOS_6502::TXS(Addressing mode, uint16_t arg1){
    S = X;
    return;
}

uint8_t CMOS_6502::pullStack(){

    if(S == 0xFF)
        S = 0x00;
    else
        S++;

    return RAM[0x100 + S]; 
}

void CMOS_6502::pushStack(uint8_t v){
    RAM[S + 0x100] = v;

    if(S == 0x00)
        S = 0xFF;
    else
        S--;
}

void CMOS_6502::PLA(Addressing mode, uint16_t arg1){


    A = pullStack();   // BIZARRE

    SetNegative( A & 0x80 );
    SetZero(!( A & 0xFF));

    return;
}

void CMOS_6502::PHA(Addressing mode, uint16_t arg1){

    pushStack(A);
    return;
}

void CMOS_6502::PLP(Addressing mode, uint16_t arg1){

    P = pullStack();
    P|= 0x20;
    return;
}

void CMOS_6502::PHP(Addressing mode, uint16_t arg1){

    pushStack(P);
    return;
}

void CMOS_6502::BPL(Addressing mode, uint16_t arg1){

    if(!Negative()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BMI(Addressing mode, uint16_t arg1){
    if(Negative()){
        pc = arg1;
    }

    return;    
}

void CMOS_6502::BVC(Addressing mode, uint16_t arg1){
    if(!Overflow()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BVS(Addressing mode, uint16_t arg1){
    if(Overflow()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BCC(Addressing mode, uint16_t arg1){
    if(!Carry()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BCS(Addressing mode, uint16_t arg1){
    if(Carry()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BNE(Addressing mode, uint16_t arg1){
    if(!Zero()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BEQ(Addressing mode, uint16_t arg1){
    if(Zero()){
        pc = arg1;
    }

    return;
}

void CMOS_6502::BRK(Addressing mode, uint16_t arg1){
    pc++;
    pushStack((pc >> 8) & 0xFF);
    pushStack(pc & 0xFF);
    pushStack(P);
    pc = (RAM[0xFFFF] << 8) + RAM[0xFFFE];

    SetBrk(true);
    SetIrq(true);

    return;
}

void CMOS_6502::RTI(Addressing mode, uint16_t arg1){
    P = pullStack();
    uint8_t lo = pullStack();
    uint8_t hi = pullStack();
    pc = (hi << 8) | lo;
    return;
}

void CMOS_6502::JSR(Addressing mode, uint16_t arg1){
    pc --;
    pushStack((pc >> 8) & 0xFF);
    pushStack(pc & 0xFF);
    pc = arg1;
    return;
}

void CMOS_6502::RTS(Addressing mode, uint16_t arg1){

    uint8_t lo = pullStack();
    uint8_t hi = pullStack();
    pc = (hi << 8) | lo;
    pc++;
    return;
}

void CMOS_6502::JMP(Addressing mode, uint16_t arg1){
    pc = arg1;
    return;
}

void CMOS_6502::BIT(Addressing mode, uint16_t arg1){
    uint8_t m = RAM[arg1];
    uint8_t res = A & m;
    SetNegative(m & 0x80);
    SetOverflow(m & 0x40);
    SetZero(!res);
    return;
}

void CMOS_6502::CLC(Addressing mode, uint16_t arg1){
    SetCarry(false);
    return;
}

void CMOS_6502::SEC(Addressing mode, uint16_t arg1){
    SetCarry(true);
    return;
}

void CMOS_6502::CLD(Addressing mode, uint16_t arg1){
    SetDecimal(false);
    return;
}

void CMOS_6502::SED(Addressing mode, uint16_t arg1){
    SetDecimal(true);
    return;
}

void CMOS_6502::CLI(Addressing mode, uint16_t arg1){
    SetIrq(false);
    return;
}

void CMOS_6502::SEI(Addressing mode, uint16_t arg1){
    SetIrq(true);
    return;
}

void CMOS_6502::CLV(Addressing mode, uint16_t arg1){
    SetOverflow(false);
    return;
}

void CMOS_6502::NOP(Addressing mode, uint16_t arg1){
    return;
}

void CMOS_6502::SLO(Addressing mode, uint16_t arg1){
    ASL(mode, arg1);
    ORA(mode, arg1);
    return;
}

void CMOS_6502::RLA(Addressing mode, uint16_t arg1){
    ROL(mode, arg1);
    AND(mode, arg1);
    return;
}

void CMOS_6502::SRE(Addressing mode, uint16_t arg1){
    LSR(mode, arg1);
    EOR(mode, arg1);
    return;
}

void CMOS_6502::RRA(Addressing mode, uint16_t arg1){
    ROR(mode, arg1);
    ADC(mode, arg1);
    return;
}

void CMOS_6502::SAX(Addressing mode, uint16_t arg1){
    RAM[arg1] = (A & X);
    return;
}

void CMOS_6502::LAX(Addressing mode, uint16_t arg1){
    LDA(mode, arg1);
    LDX(mode, arg1);
    return;
}

void CMOS_6502::DCP(Addressing mode, uint16_t arg1){
    DEC(mode, arg1);
    CMP(mode, arg1);
    return;
}

void CMOS_6502::ISC(Addressing mode, uint16_t arg1){
    INC(mode, arg1);
    SBC(mode, arg1);
    return;
}

void CMOS_6502::ANC(Addressing mode, uint16_t arg1){
    AND(IMMEDIATE, arg1);
    SetCarry(A & 0x80);
    return;
}

void CMOS_6502::ALR(Addressing mode, uint16_t arg1){
    AND(IMMEDIATE, arg1);
    LSR(ACCUMULATOR, arg1);
    return;
}

void CMOS_6502::ARR(Addressing mode, uint16_t arg1){
    AND(IMMEDIATE, arg1);
    ROR(ACCUMULATOR, arg1);
    SetCarry(A & 0x40);
    SetOverflow((A & 0x40) ^ (A & 0x20));
    return;
}

void CMOS_6502::XAA(Addressing mode, uint16_t arg1){
    A = X;
    AND(IMMEDIATE, arg1);
    return;
}

void CMOS_6502::AXS(Addressing mode, uint16_t arg1){
    X = ((X & A) - arg1);
    SetNegative(X & 0x80);
    SetCarry(X & 0x40);
    SetZero(!(X & 0xFF));
    return;
}

void CMOS_6502::AHX(Addressing mode, uint16_t arg1){
    RAM[arg1] = A & X & RAM[(arg1 >> 8) & 0xFF] + 0x1;
    return; 
}

void CMOS_6502::SHY(Addressing mode, uint16_t arg1){
    RAM[arg1] = Y & RAM[(arg1 >> 8) & 0xFF] + 0x1;
    return; 
}

void CMOS_6502::SHX(Addressing mode, uint16_t arg1){
    RAM[arg1] = X & RAM[(arg1 >> 8) & 0xFF] + 0x1;
    return; 
}

void CMOS_6502::TAS(Addressing mode, uint16_t arg1){
    pushStack(A & X);
    AHX(mode, arg1);
    return;
}

void CMOS_6502::LAS(Addressing mode, uint16_t arg1){
    uint8_t tmp = RAM[arg1] & RAM[0x1];
    std::cout << "LAS ça s'est mal passé" << std::endl;
    return;
}

void CMOS_6502::KIL(Addressing mode, uint16_t arg1){
    //std::cout << "Terminated after kill" << std::endl;
    //exit(0);
    return;
}

//-------------------------------------------------------------------------------------------------------------------------------//

void Debugger::trace(){
   char buffer[1000];

   sprintf(buffer, "%04lX : ", offset);
   std::string offsetPart(buffer);

   memset(buffer, 0, 1000 * sizeof(char));

   switch(mode){ 
        case IMMEDIATE:
            sprintf(buffer,"%s   #$%02X", ops.c_str(), arg ); 
            break;

        case ABSOLUTE :
            sprintf(buffer, "%s  $%04X", ops.c_str(), arg ); 
            break;

        case ZERO_PAGE :
            sprintf(buffer, "%s    $%02X", ops.c_str(), arg ); 
            break;

        case IMPLIED :
            sprintf(buffer, "%s ", ops.c_str(), arg); 
            break;

        case INDIRECT :
            sprintf(buffer, "%s  $%04X", ops.c_str(), arg);
            break;

        case ABSOLUTE_INDEXED_X :
            sprintf(buffer, "%s  $%04X , X", ops.c_str(), arg );
            break;

        case ABSOLUTE_INDEXED_Y :
            sprintf(buffer, "%s  $%04X , Y", ops.c_str(), arg);
            break;

        case ZERO_PAGE_INDEXED_X :
            sprintf(buffer, "%s    $%02X , X", ops.c_str(), arg);
            break;

        case ZERO_PAGE_INDEXED_Y :
            sprintf(buffer, "%s    $%02X , Y", ops.c_str(), arg); 
            break;

        case X_INDEXED :
            sprintf(buffer, "%s   ($%02X , X)", ops.c_str(), arg);
            break;

        case INDEXED_Y :
            sprintf(buffer, "%s   ($%02X), Y", ops.c_str(), arg); 
            break;

        case RELATIVE :
            sprintf(buffer, "%s    $%02X", ops.c_str(), arg);
            break;

        case ACCUMULATOR :
            sprintf(buffer, "%s ", ops.c_str()); 
            break;

        default:
            break;
    }

    std::string operation(buffer);

    memset(buffer, 0, 1000 * sizeof(char));

    sprintf(buffer, "A:%02X X:%02X Y:%02X P:%02X SP:%02X ", A, X, Y, P, S);
    std::string dump(buffer);

    std::cout << offsetPart << std::string(15 - offsetPart.size(), ' ') << operation << 
        std::string(30 - operation.size(), ' ') << dump << std::endl;
    return;
}

