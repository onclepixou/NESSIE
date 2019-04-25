#include "Disassembler.h"
//-------------------------------------------------------------------------------------------------------------------------------//
Instruction::Instruction(Addressing m, std::string s, uint8_t c, bool l) : mode(m), opstring(s), cycles(c), legal(l){};
//-------------------------------------------------------------------------------------------------------------------------------//
Operation::Operation(Instruction ins, uint16_t of): m(ins.mode), ops(ins.opstring), c(ins.cycles), l(ins.legal), offset(of) {}
//-------------------------------------------------------------------------------------------------------------------------------//

ImmOp::ImmOp(Instruction ins, size_t of, uint8_t a1) : Operation(ins, of), arg1(a1){}

void ImmOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s   #$%02X", ops.c_str(), arg1 ); 
   if(!l){
       printf("%*c;Illegal OPcode %s",15,' ', ops.c_str());
   }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
AbsOp::AbsOp(Instruction ins, size_t of, uint16_t a) : Operation(ins, of), arg1(a){}

void AbsOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s  $%04X", ops.c_str(), arg1 ); 
    if(!l){
       printf("%*c;Illegal OPcode %s",15,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
ZpOp::ZpOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void ZpOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s    $%02X", ops.c_str(), arg1 ); 
    if(!l){
       printf("%*c;Illegal OPcode %s",15,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
ImpOp::ImpOp(Instruction ins, size_t of) : Operation(ins, of){}

void ImpOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s ", ops.c_str()); 
    if(!l){
       printf("%*c;Illegal OPcode %s",21,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
IndOp::IndOp(Instruction ins, size_t of, uint16_t a) : Operation(ins, of), arg1(a){}

void IndOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s  $%04X", ops.c_str(), arg1 );
    if(!l){
       printf("%*c;Illegal OPcode %s",15,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
AbsxOp::AbsxOp(Instruction ins, size_t of, uint16_t a) : Operation(ins, of), arg1(a){}

void AbsxOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s  $%04X , X", ops.c_str(), arg1 );
   if(!l){
       printf("%*c;Illegal OPcode %s",11,' ', ops.c_str());
   }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
AbsyOp::AbsyOp(Instruction ins, size_t of, uint16_t a) : Operation(ins, of), arg1(a){}

void AbsyOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s  $%04X , Y", ops.c_str(), arg1 );
   if(!l){
       printf("%*c;Illegal OPcode %s",11,' ', ops.c_str());
   }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
ZpxOp::ZpxOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void ZpxOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s    $%02X , X", ops.c_str(), arg1 );
    if(!l){
       printf("%*c;Illegal OPcode %s",11,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
ZpyOp::ZpyOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void ZpyOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s    $%02X , Y", ops.c_str(), arg1 ); 
    if(l){
       printf("%*c;Illegal OPcode %s",11,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
IndxOp::IndxOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void IndxOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s   ($%02X , X)", ops.c_str(), arg1 ); 
    if(!l){
       printf("%*c;Illegal OPcode %s",10,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
IndyOp::IndyOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void IndyOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s   ($%02X), Y", ops.c_str(), arg1 ); 
    if(!l){
       printf("%*c;Illegal OPcode %s",11,' ', ops.c_str());
    }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
RelOp::RelOp(Instruction ins, size_t of, uint8_t a) : Operation(ins, of), arg1(a){}

void RelOp::prettyPrint(){
   printf("%04lX :    ", offset);
   printf("%s    $%02X", ops.c_str(), arg1 );
   if(!l){
       printf("%*c;Illegal OPcode %s",15,' ', ops.c_str());
   }
   printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------//
AccOp::AccOp(Instruction ins, size_t of) : Operation(ins, of){}

void AccOp::prettyPrint(){
    printf("%04lX :    ", offset);
    printf("%s ", ops.c_str()); 
    if(!l){
       printf("%*c;Illegal OPcode %s",21,' ', ops.c_str());
    }
   printf("\n");
}

//-------------------------------------------------------------------------------------------------------------------------------//

Disassembler::Disassembler(std::string name) : cart(Cartridge(name)){

    pcStart = cart.getMappingInfo().pcStart;
    buildInstructionSet();
    loadPRGBank();
    printHeader();
    printProgram();

}

Disassembler::~Disassembler(){
    for(size_t i = 0; i < program.size(); i++){
        delete program[i];
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//

void Disassembler::loadPRGBank(){

    uint16_t a;
    uint8_t* ptr = cart.PRG();
    uint8_t* start = ptr;
    MappingInfo info = cart.getMappingInfo();
    uint16_t end = info.PRGBankEnd - info.PRGBankStart;

    while((ptr-start) < end){
        a = 0;
        uint8_t opc = *ptr;
        Addressing add = getAddressing(opc);
        std::string opname = getOpName(opc);

        switch (add){

            case IMMEDIATE:
                program.push_back(new ImmOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case ABSOLUTE :
                a = ptr[1] + (ptr[2] << 8);
                program.push_back(new AbsOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), a));
                ptr+=2;
                break;

            case ZERO_PAGE :
                program.push_back(new ZpOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case IMPLIED :
                program.push_back(new ImpOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart)));
                break;

            case INDIRECT :
                a = ptr[1] + (ptr[2] << 8);
                program.push_back(new IndOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), a));
                ptr+=2;
                break;

            case ABSOLUTE_INDEXED_X :
                a = ptr[1] + (ptr[2] << 8);
                program.push_back(new AbsxOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), a));
                ptr+=2;
                break;

            case ABSOLUTE_INDEXED_Y :
                a = ptr[1] + (ptr[2] << 8);
                program.push_back(new AbsyOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), a));
                ptr+=2;
                break;

            case ZERO_PAGE_INDEXED_X :
                program.push_back(new ZpxOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case ZERO_PAGE_INDEXED_Y :
                program.push_back(new ZpyOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case X_INDEXED :
                program.push_back(new IndxOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case INDEXED_Y :
                program.push_back(new IndyOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case RELATIVE :
                program.push_back(new RelOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart), ptr[1]));
                ptr++;
                break;

            case ACCUMULATOR :
                program.push_back(new AccOp(instructionSet.at(opc), (size_t)(ptr - cart.PRG() + pcStart)));
                break;

            default:
                break;

        }
        ptr++;
    }

    return;
}

void Disassembler::buildInstructionSet(){

    
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x00, Instruction(IMPLIED             , std::string("BRK"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x01, Instruction(X_INDEXED           , std::string("ORA"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x02, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x03, Instruction(X_INDEXED           , std::string("SLO"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x04, Instruction(ZERO_PAGE           , std::string("NOP"), 3, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x05, Instruction(ZERO_PAGE           , std::string("ORA"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x06, Instruction(ZERO_PAGE           , std::string("ASL"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x07, Instruction(ZERO_PAGE           , std::string("SLO"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x08, Instruction(IMPLIED             , std::string("PHP"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x09, Instruction(IMMEDIATE           , std::string("ORA"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0a, Instruction(ACCUMULATOR         , std::string("ASL"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0b, Instruction(IMMEDIATE           , std::string("ANC"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0c, Instruction(ABSOLUTE            , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0d, Instruction(ABSOLUTE            , std::string("ORA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0e, Instruction(ABSOLUTE            , std::string("ASL"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x0f, Instruction(ABSOLUTE            , std::string("SLO"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x10, Instruction(RELATIVE            , std::string("BPL"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x11, Instruction(INDEXED_Y           , std::string("ORA"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x12, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x13, Instruction(INDEXED_Y           , std::string("SLO"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x14, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x15, Instruction(ZERO_PAGE_INDEXED_X , std::string("ORA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x16, Instruction(ZERO_PAGE_INDEXED_X , std::string("ASL"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x17, Instruction(ZERO_PAGE_INDEXED_X , std::string("SLO"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x18, Instruction(IMPLIED             , std::string("CLC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x19, Instruction(ABSOLUTE_INDEXED_Y  , std::string("ORA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1a, Instruction(IMPLIED             , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1b, Instruction(ABSOLUTE_INDEXED_Y  , std::string("SLO"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1c, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1d, Instruction(ABSOLUTE_INDEXED_X  , std::string("ORA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1e, Instruction(ABSOLUTE_INDEXED_X  , std::string("ASL"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x1f, Instruction(ABSOLUTE_INDEXED_X  , std::string("SLO"), 7, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x20, Instruction(ABSOLUTE            , std::string("JSR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x21, Instruction(X_INDEXED           , std::string("AND"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x22, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x23, Instruction(X_INDEXED           , std::string("RLA"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x24, Instruction(ZERO_PAGE           , std::string("BIT"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x25, Instruction(ZERO_PAGE           , std::string("AND"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x26, Instruction(ZERO_PAGE           , std::string("RLO"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x27, Instruction(ZERO_PAGE           , std::string("RLA"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x28, Instruction(IMPLIED             , std::string("PLP"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x29, Instruction(IMMEDIATE           , std::string("AND"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2a, Instruction(ACCUMULATOR         , std::string("ROL"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2b, Instruction(IMMEDIATE           , std::string("ANC"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2c, Instruction(ABSOLUTE            , std::string("BIT"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2d, Instruction(ABSOLUTE            , std::string("AND"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2e, Instruction(ABSOLUTE            , std::string("ROL"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x2f, Instruction(ABSOLUTE            , std::string("RLA"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x30, Instruction(RELATIVE            , std::string("BMI"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x31, Instruction(INDEXED_Y           , std::string("AND"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x32, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x33, Instruction(INDEXED_Y           , std::string("RLA"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x34, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x35, Instruction(ZERO_PAGE_INDEXED_X , std::string("AND"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x36, Instruction(ZERO_PAGE_INDEXED_X , std::string("ROL"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x37, Instruction(ZERO_PAGE_INDEXED_X , std::string("RLA"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x38, Instruction(IMPLIED             , std::string("SEC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x39, Instruction(ABSOLUTE_INDEXED_Y  , std::string("AND"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3a, Instruction(IMPLIED             , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3b, Instruction(ABSOLUTE_INDEXED_Y  , std::string("RLA"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3c, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3d, Instruction(ABSOLUTE_INDEXED_X  , std::string("AND"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3e, Instruction(ABSOLUTE_INDEXED_X  , std::string("ROL"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x3f, Instruction(ABSOLUTE_INDEXED_X  , std::string("RLA"), 7, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x40, Instruction(IMPLIED             , std::string("RTI"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x41, Instruction(X_INDEXED           , std::string("EOR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x42, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x43, Instruction(X_INDEXED           , std::string("SRE"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x44, Instruction(ZERO_PAGE           , std::string("NOP"), 3, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x45, Instruction(ZERO_PAGE           , std::string("EOR"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x46, Instruction(ZERO_PAGE           , std::string("LSR"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x47, Instruction(ZERO_PAGE           , std::string("SRE"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x48, Instruction(IMPLIED             , std::string("PHA"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x49, Instruction(IMMEDIATE           , std::string("EOR"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4a, Instruction(ACCUMULATOR         , std::string("LSR"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4b, Instruction(IMMEDIATE           , std::string("ALR"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4c, Instruction(ABSOLUTE            , std::string("JMP"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4d, Instruction(ABSOLUTE            , std::string("EOR"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4e, Instruction(ABSOLUTE            , std::string("LSR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x4f, Instruction(ABSOLUTE            , std::string("SRE"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x50, Instruction(RELATIVE            , std::string("BVC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x51, Instruction(INDEXED_Y           , std::string("EOR"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x52, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x53, Instruction(INDEXED_Y           , std::string("SRE"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x54, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x55, Instruction(ZERO_PAGE_INDEXED_X , std::string("EOR"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x56, Instruction(ZERO_PAGE_INDEXED_X , std::string("LSR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x57, Instruction(ZERO_PAGE_INDEXED_X , std::string("SRE"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x58, Instruction(IMPLIED             , std::string("CLI"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x59, Instruction(ABSOLUTE_INDEXED_Y  , std::string("EOR"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5a, Instruction(IMPLIED             , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5b, Instruction(ABSOLUTE_INDEXED_Y  , std::string("SRE"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5c, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5d, Instruction(ABSOLUTE_INDEXED_X  , std::string("EOR"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5e, Instruction(ABSOLUTE_INDEXED_X  , std::string("LSR"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x5f, Instruction(ABSOLUTE_INDEXED_X  , std::string("SRE"), 7, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x60, Instruction(IMPLIED             , std::string("RTS"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x61, Instruction(X_INDEXED           , std::string("ADC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x62, Instruction(X_INDEXED           , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x63, Instruction(X_INDEXED           , std::string("RRA"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x64, Instruction(ZERO_PAGE           , std::string("NOP"), 3, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x65, Instruction(ZERO_PAGE           , std::string("ADC"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x66, Instruction(ZERO_PAGE           , std::string("ROR"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x67, Instruction(ZERO_PAGE           , std::string("RRA"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x68, Instruction(IMPLIED             , std::string("PLA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x69, Instruction(IMMEDIATE           , std::string("ADC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6a, Instruction(ACCUMULATOR         , std::string("ROR"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6b, Instruction(IMMEDIATE           , std::string("ARR"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6c, Instruction(INDIRECT            , std::string("JMP"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6d, Instruction(ABSOLUTE            , std::string("ADC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6e, Instruction(ABSOLUTE            , std::string("ROR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x6f, Instruction(ABSOLUTE            , std::string("RRA"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x70, Instruction(RELATIVE            , std::string("BVS"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x71, Instruction(INDEXED_Y           , std::string("ADC"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x72, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x73, Instruction(INDEXED_Y           , std::string("RRA"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x74, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x75, Instruction(ZERO_PAGE_INDEXED_X , std::string("ADC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x76, Instruction(ZERO_PAGE_INDEXED_X , std::string("ROR"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x77, Instruction(ZERO_PAGE_INDEXED_X , std::string("RRA"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x78, Instruction(IMPLIED             , std::string("SEI"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x79, Instruction(ABSOLUTE_INDEXED_Y  , std::string("ADC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7a, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7b, Instruction(ABSOLUTE_INDEXED_Y  , std::string("RRA"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7c, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7d, Instruction(ABSOLUTE_INDEXED_X  , std::string("ADC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7e, Instruction(ABSOLUTE_INDEXED_X  , std::string("ROR"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x7f, Instruction(ABSOLUTE_INDEXED_X  , std::string("RRA"), 7, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x80, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x81, Instruction(X_INDEXED           , std::string("STA"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x82, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x83, Instruction(X_INDEXED           , std::string("SAX"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x84, Instruction(ZERO_PAGE           , std::string("STY"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x85, Instruction(ZERO_PAGE           , std::string("STA"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x86, Instruction(ZERO_PAGE           , std::string("STX"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x87, Instruction(ZERO_PAGE           , std::string("SAX"), 3, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x88, Instruction(IMPLIED             , std::string("DEY"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x89, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8a, Instruction(IMPLIED             , std::string("TXA"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8b, Instruction(IMMEDIATE           , std::string("XAA"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8c, Instruction(ABSOLUTE            , std::string("STY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8d, Instruction(ABSOLUTE            , std::string("STA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8e, Instruction(ABSOLUTE            , std::string("STX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x8f, Instruction(ABSOLUTE            , std::string("SAX"), 4, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0x90, Instruction(RELATIVE            , std::string("BCC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x91, Instruction(INDEXED_Y           , std::string("STA"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x92, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x93, Instruction(INDEXED_Y           , std::string("AHX"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x94, Instruction(ZERO_PAGE_INDEXED_X , std::string("STY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x95, Instruction(ZERO_PAGE_INDEXED_X , std::string("STA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x96, Instruction(ZERO_PAGE_INDEXED_Y , std::string("STX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x97, Instruction(ZERO_PAGE_INDEXED_Y , std::string("SAX"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x98, Instruction(IMPLIED             , std::string("TYA"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x99, Instruction(ABSOLUTE_INDEXED_Y  , std::string("STA"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9a, Instruction(IMPLIED             , std::string("TXS"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9b, Instruction(ABSOLUTE_INDEXED_Y  , std::string("TAS"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9c, Instruction(ABSOLUTE_INDEXED_X  , std::string("SHY"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9d, Instruction(ABSOLUTE_INDEXED_X  , std::string("STA"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9e, Instruction(ABSOLUTE_INDEXED_X  , std::string("SHX"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0x9f, Instruction(ABSOLUTE_INDEXED_X  , std::string("AHX"), 5, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa0, Instruction(IMMEDIATE           , std::string("LDY"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa1, Instruction(X_INDEXED           , std::string("LDA"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa2, Instruction(IMMEDIATE           , std::string("LDX"), 0, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa3, Instruction(X_INDEXED           , std::string("LAX"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa4, Instruction(ZERO_PAGE           , std::string("LDY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa5, Instruction(ZERO_PAGE           , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa6, Instruction(ZERO_PAGE           , std::string("LDX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa7, Instruction(ZERO_PAGE           , std::string("LAX"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa8, Instruction(IMPLIED             , std::string("TAY"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xa9, Instruction(IMMEDIATE           , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xaa, Instruction(IMPLIED             , std::string("TAX"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xab, Instruction(IMMEDIATE           , std::string("LAX"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xac, Instruction(ABSOLUTE            , std::string("LDY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xad, Instruction(ABSOLUTE            , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xae, Instruction(ABSOLUTE            , std::string("LDX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xaf, Instruction(ABSOLUTE            , std::string("LAX"), 4, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb0, Instruction(RELATIVE            , std::string("BCS"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb1, Instruction(INDEXED_Y           , std::string("LDA"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb2, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb3, Instruction(INDEXED_Y           , std::string("LAX"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb4, Instruction(ZERO_PAGE_INDEXED_X , std::string("LDY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb5, Instruction(ZERO_PAGE_INDEXED_X , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb6, Instruction(ZERO_PAGE_INDEXED_Y , std::string("LDX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb7, Instruction(ZERO_PAGE_INDEXED_Y , std::string("LAX"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb8, Instruction(IMPLIED             , std::string("CLV"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xb9, Instruction(ABSOLUTE_INDEXED_Y  , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xba, Instruction(IMPLIED             , std::string("TSX"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xbb, Instruction(ABSOLUTE_INDEXED_Y  , std::string("LAS"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xbc, Instruction(ABSOLUTE_INDEXED_X  , std::string("LDY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xbd, Instruction(ABSOLUTE_INDEXED_X  , std::string("LDA"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xbe, Instruction(ABSOLUTE_INDEXED_Y  , std::string("LDX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xbf, Instruction(ABSOLUTE_INDEXED_Y  , std::string("LAX"), 4, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc0, Instruction(IMMEDIATE           , std::string("CPY"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc1, Instruction(X_INDEXED           , std::string("CMP"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc2, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc3, Instruction(X_INDEXED           , std::string("DCP"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc4, Instruction(ZERO_PAGE           , std::string("CPY"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc5, Instruction(ZERO_PAGE           , std::string("CMP"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc6, Instruction(ZERO_PAGE           , std::string("DEC"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc7, Instruction(ZERO_PAGE           , std::string("DCP"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc8, Instruction(IMPLIED             , std::string("INY"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xc9, Instruction(IMMEDIATE           , std::string("CMP"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xca, Instruction(IMPLIED             , std::string("DEX"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xcb, Instruction(IMMEDIATE           , std::string("AXS"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xcc, Instruction(ABSOLUTE            , std::string("CPY"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xcd, Instruction(ABSOLUTE            , std::string("CMP"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xce, Instruction(ABSOLUTE            , std::string("DEC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xcf, Instruction(ABSOLUTE            , std::string("DCP"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd0, Instruction(RELATIVE            , std::string("BNE"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd1, Instruction(INDEXED_Y           , std::string("CMP"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd2, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd3, Instruction(INDEXED_Y           , std::string("DCP"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd4, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd5, Instruction(ZERO_PAGE_INDEXED_X , std::string("CMP"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd6, Instruction(ZERO_PAGE_INDEXED_X , std::string("DEC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd7, Instruction(ZERO_PAGE_INDEXED_X , std::string("DCP"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd8, Instruction(IMPLIED             , std::string("CLD"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xd9, Instruction(ABSOLUTE_INDEXED_Y  , std::string("CMP"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xda, Instruction(IMPLIED             , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xdb, Instruction(ABSOLUTE_INDEXED_Y  , std::string("DCP"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xdc, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xdd, Instruction(ABSOLUTE_INDEXED_X  , std::string("CMP"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xde, Instruction(ABSOLUTE_INDEXED_X  , std::string("DEC"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xdf, Instruction(ABSOLUTE            , std::string("DCP"), 7, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe0, Instruction(IMMEDIATE           , std::string("CPX"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe1, Instruction(X_INDEXED           , std::string("SBC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe2, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe3, Instruction(X_INDEXED           , std::string("ISC"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe4, Instruction(ZERO_PAGE           , std::string("CPX"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe5, Instruction(ZERO_PAGE           , std::string("SBC"), 3, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe6, Instruction(ZERO_PAGE           , std::string("INC"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe7, Instruction(ZERO_PAGE           , std::string("ISC"), 5, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe8, Instruction(IMPLIED             , std::string("INX"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xe9, Instruction(IMMEDIATE           , std::string("SBC"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xea, Instruction(IMPLIED             , std::string("NOP"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xeb, Instruction(IMMEDIATE           , std::string("SBC"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xec, Instruction(ABSOLUTE            , std::string("CPX"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xed, Instruction(ABSOLUTE            , std::string("SBC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xee, Instruction(ABSOLUTE            , std::string("INC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xef, Instruction(ABSOLUTE            , std::string("ISC"), 6, false)));

    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf0, Instruction(RELATIVE            , std::string("BEQ"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf1, Instruction(INDEXED_Y           , std::string("SBC"), 5, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf2, Instruction(IMPLIED             , std::string("KIL"), 0, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf3, Instruction(INDEXED_Y           , std::string("ISC"), 8, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf4, Instruction(ZERO_PAGE_INDEXED_X , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf5, Instruction(ZERO_PAGE_INDEXED_X , std::string("SBC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf6, Instruction(ZERO_PAGE_INDEXED_X , std::string("INC"), 6, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf7, Instruction(ZERO_PAGE_INDEXED_X , std::string("ISC"), 6, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf8, Instruction(IMPLIED             , std::string("SED"), 2, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xf9, Instruction(ABSOLUTE_INDEXED_Y  , std::string("SBC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xfa, Instruction(IMMEDIATE           , std::string("NOP"), 2, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xfb, Instruction(ABSOLUTE_INDEXED_Y  , std::string("ISC"), 7, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xfc, Instruction(ABSOLUTE_INDEXED_X  , std::string("NOP"), 4, false)));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xfd, Instruction(ABSOLUTE_INDEXED_X  , std::string("SBC"), 4, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xfe, Instruction(ABSOLUTE_INDEXED_X  , std::string("INC"), 7, true )));
    instructionSet.insert(std::pair<uint8_t, Instruction> (0xff, Instruction(ABSOLUTE_INDEXED_X  , std::string("ISC"), 7, false)));

    return ;
};

Addressing Disassembler::getAddressing(uint8_t opc){
    return (instructionSet.at(opc).mode);
}

std::string Disassembler::getOpName(uint8_t opc){
    return (instructionSet.at(opc).opstring);  
}

bool Disassembler::getLegality(uint8_t opc){
    return (instructionSet.at(opc).legal);  
}

void Disassembler::printHeader(){
    printf("--------------------------------------------------------------------------------------------------\n");
    std::cout << "Game Name              : " << cart.Name << std::endl;
    std::cout << "Number of 8k PRG banks : " << (unsigned)cart.headerFile.PRG_size << std::endl;
    std::cout << "Number of 4k CHR banks : " << (unsigned)cart.headerFile.CHR_size << std::endl;
    std::cout << std::endl;
    std::string mirror = cart.headerFile.mirroring ? "Vertical" : "Horizontal";
    std::cout << "Mirroring              : " << mirror << std::endl;
    std::cout << "Battery memory         : " << (cart.headerFile.hasBatteryRAM ? std::string("true") : std::string("false")) << std::endl;
    std::cout << "Trainer                : " << (cart.headerFile.hasTrainer ? std::string("true") : std::string("false")) << std::endl;
    std::cout << "VRAM                   : " << (cart.headerFile.hasVRAM ? std::string("enabled") : std::string("disabled")) << std::endl;
    std::cout << std::endl;
    std::cout << "Mapper version         : " << (unsigned)cart.headerFile.mapper << std::endl;
    std::cout << "SubMapper version      : " << (unsigned)cart.headerFile.submapper << std::endl;
    std::cout << std::endl;

    std::string console;
    switch(cart.headerFile.console){
        case 0 :
            console = "NES";
            break;

        case 1 :
            console = "VS_SYSTEM";
            break;

        case 2 :
            console = "PLAYCHOICE_10";
            break;

        case 3 :
            console = "EXTENDED";
            break;
    }

    std::string region;
    switch(cart.headerFile.version){
        case 0 :
            region = "NTSC";
            break;

        case 1 :
            console = "PAL";
            break;

        case 2 :
            console = "MULTI_REGION";
            break;

        case 3 :
            console = "DENDY";
            break;
    }

    std::cout << "Console                : " << console << std::endl;
    std::cout << "Region                 : " << region << std::endl;
    std::cout << "NES2.0 header style    : " << (cart.headerFile.hasNes2 ? std::string("true") : std::string("false")) << std::endl;
    std::cout << std::endl;
    std::cout << "PRG_RAM_size           : " << (unsigned)cart.headerFile.PRG_RAM_size   << std::endl; 
    std::cout << "PRG_NVRAM_size         : " << (unsigned)cart.headerFile.PRG_NVRAM_size << std::endl; 
    std::cout << "CHR_RAM_size           : " << (unsigned)cart.headerFile.CHR_RAM_size   << std::endl; 
    std::cout << "CHR_NVRAM_size         : " << (unsigned)cart.headerFile.CHR_NVRAM_size << std::endl;
    std::cout << std::endl;
    if(cart.headerFile.console == VS_SYSTEM){
        std::cout << "VS PPU version         : " << (unsigned)cart.headerFile.VS_PPU << std::endl;
        std::cout << "VS Hardware version    : " << (unsigned)cart.headerFile.VS_Hardware << std::endl;
    }
    if(cart.headerFile.console == EXTENDED){
        std::cout << "Extended type          : " << (unsigned)cart.headerFile.extendedType << std::endl;  
    }
    std::cout << std::endl;
        std::cout << "Miscellaneous Rom      : " << (unsigned)cart.headerFile.miscRom << std::endl; 
        std::cout << "Expansion device       : " << (unsigned)cart.headerFile.expansionDevice << std::endl; 
    printf("--------------------------------------------------------------------------------------------------\n");
}


void Disassembler::printProgram(){
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("------------------------\n");
    printf("Start of PRG section : |\n");
    printf("------------------------\n");
    for(size_t i = 0; i < program.size(); i++){
        program[i]->prettyPrint();
    }
    printf("------------------------\n");
    printf("End of PRG section :   |\n");
    printf("------------------------\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    return;
}

void Disassembler::dumpCHRBanks(){
    return;
}
//-------------------------------------------------------------------------------------------------------------------------------//