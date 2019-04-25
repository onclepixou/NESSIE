#include "NES_dasm.h"

bool parseArg(int argc, char** argv){
    if(argc != 2){
        std::cout << "Bad CLI argument specified" << std::endl;
        std::cout << "Expected filename " << std::endl;
        return false; 
    }
    return true;
}

int main(int argc, char** argv){

    if(parseArg(argc, argv)){
        try{
            Disassembler disasm(argv[1]);
        }
        catch(std::string& s){
            std::cerr << s << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "Disassembling done !" << std::endl;
    return EXIT_SUCCESS;
}
