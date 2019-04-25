
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include <cstdio>

#define PRG_UNIT 0x4000
#define CHR_UNIT 0x2000
#define TRAINER_UNIT 0x200
#define PLAYCHOICE_INST_ROM 0x2000

// Mirroring type
typedef enum MirrorType{
    H_MIRROR,
    V_MIRROR
} MirrorType;

// Console model
typedef enum ConsoleType{
    NES,
    VS_SYSTEM,
    PLAYCHOICE_10,
    EXTENDED
} ConsoleType;

// Game region
typedef enum Region{   
    NTSC,
    PAL,
    MULTI_REGION,
    DENDY
} Region;

typedef struct{
    bool hasCHR;

    uint16_t pcStart;

    uint16_t PRGBankStart;
    uint16_t PRGBankEnd;

    uint16_t CHRBankStart;
    uint16_t CHRBankEnd;

}MappingInfo;

typedef struct{
    uint8_t     PRG_size;           // number of PRG banks
    uint8_t     CHR_size;           // number of CHR banks

    MirrorType  mirroring;          // mirroring type
    bool        hasBatteryRAM;      // battery packed Ram inside cartridge ?
    bool        hasTrainer;         // trainer section ?
    bool        hasVRAM;            // four screen VRAM instead of mirroring ?

    uint16_t    mapper;             // cartridge mapper reference 
    uint8_t     submapper;          // cartridge submapper reference
    
    ConsoleType console;            // Console type
    bool        hasNes2;            // Nes2.0 ?

    size_t      PRG_RAM_size;       // volatile  PRG RAM on chip
    size_t      PRG_NVRAM_size;     // Non volatile PRG RAM on chip
    size_t      CHR_RAM_size;       // volatile CHR RAM on chip
    size_t      CHR_NVRAM_size;     // Non volatile CHR RAM on chip

    Region      version;            // Region

    uint8_t     VS_PPU;             // PPU version when Console is VS_SYSTEM
    uint8_t     VS_Hardware;        // Hardware version when Console is VS_SYSTEM 
    uint8_t     extendedType;       // Extended console version when Console is EXTENDED

    uint8_t     miscRom;            // Number of miscellaneous ROM
    uint8_t     expansionDevice;    // Default expansion device

} header_t;




class Cartridge{
    private:
        std::string Name;
        header_t headerFile;

        uint8_t* Trainer_Data;                // Specific Rom Section
        uint8_t* PRG_RomData;                 // Specific Rom Section
        uint8_t* CHR_RomData;                 // Specific Rom Section
        uint8_t* PlayChoice_IROM;             // Specific Rom Section
        uint8_t* PlayChoice_PROM_Data;        // Specific Rom Section
        uint8_t* PlayChoice_PROM_Counter;     // Specific Rom Section

        size_t  trainer_size;                 // Associated Section Size
        size_t  PRG_RomData_size;             // Associated Section Size
        size_t  CHR_RomData_size;             // Associated Section Size
        size_t  PlayChoice_IROM_size;         // Associated Section Size
        size_t  PlayChoice_PROM_Data_size;    // Associated Section Size
        size_t  PlayChoice_PROM_Counter_size; // Associated Section Size


        void loadRom(FILE* romFile);         // open romFile to fill header and load data sections
        friend class Disassembler;

    public:

        // Class constructor
        Cartridge(std::string filename);     // Creates Cartridge object with input .nes file 
        Cartridge(const Cartridge& rhs);     // Copy constructor
        ~Cartridge();

        // getter
        uint8_t* Trainer();
        uint8_t* PRG();
        uint8_t* CHR();
        uint8_t* PIROM();
        uint8_t* PROMd();
        uint8_t* PROMc();

        size_t Trainer_size();
        size_t PRG_size();
        size_t CHR_size();
        size_t PIROM_size();
        size_t PROMd_size();
        size_t PROMc_size();
        
        // Class method
        static FILE* getFileHandle(std::string  filename);    // opens a file
        MappingInfo getMappingInfo();


};
#endif