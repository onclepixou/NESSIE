#include "NES_emulator.h"

bool parseArg(int argc, char** argv){
    if(argc != 2){
        std::cout << "Bad CLI argument specified" << std::endl;
        std::cout << "Expected filename " << std::endl;
        return false; 
    }
    return true;
}

int main(int argc, char** argv){

    Cartridge cart(argv[1]);
    CMOS_6502 proc(cart);
    proc.play();
    
    

    return EXIT_SUCCESS;
}
