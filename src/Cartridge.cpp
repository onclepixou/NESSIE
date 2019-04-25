#include "Cartridge.h"


// Cartridge static methods
    FILE* Cartridge::getFileHandle(std::string  filename){
        FILE* romFile = fopen(filename.c_str(), "rb");
        if( !romFile)
            return nullptr;
        return romFile;
    }



    MappingInfo Cartridge::getMappingInfo(){

        MappingInfo info;
        info.hasCHR = (headerFile.CHR_size > 0) ? true : false; 

        switch(headerFile.mapper){
            case 0 :
                info.pcStart = 0xC000;
                info.PRGBankStart = 0xC000;
                info.PRGBankEnd = 0xFFFF;
                return info;
                break;

            case 4 :
                info.pcStart = 0x8000;
                info.PRGBankStart = 0x8000;
                info.PRGBankEnd = 0xFFFF;
                info.CHRBankStart = 0x0;
                info.CHRBankEnd = 0x1FFF;
                break;
                
            default :
                throw(std::string("Unsupported mapper") + std::to_string(headerFile.mapper));
                return info;
                break;
        }
        return info;
    }
//----------------------------------------------------------------------------------------//

// Cartridge Constructor / Destructor
    Cartridge::Cartridge(std::string filename){
        try{
            FILE* romFile =  Cartridge::getFileHandle(filename);

            if(!romFile)
                throw std::string("Failed opening romFile");

            Name = filename.c_str();
            loadRom(romFile);
        }


        catch(std::string& erro) {
            std::cerr << erro << std::endl;
        }

    }

    Cartridge::Cartridge(const Cartridge& rhs): Name(rhs.Name){

        headerFile = rhs.headerFile;

        trainer_size = rhs.trainer_size;
        PRG_RomData_size = rhs.PRG_RomData_size;
        CHR_RomData_size = rhs.CHR_RomData_size;
        PlayChoice_IROM_size = rhs.PlayChoice_IROM_size;
        PlayChoice_PROM_Data_size = rhs.PlayChoice_PROM_Data_size;
        PlayChoice_PROM_Counter_size = rhs.PlayChoice_PROM_Counter_size;;


        Trainer_Data = (uint8_t*)calloc(trainer_size, sizeof(uint8_t));
        memcpy(Trainer_Data, rhs.Trainer_Data, trainer_size);

        PRG_RomData  = (uint8_t*)calloc(PRG_RomData_size, sizeof(uint8_t));
        memcpy(PRG_RomData, rhs.PRG_RomData,PRG_RomData_size);

        CHR_RomData  = (uint8_t*)calloc(CHR_RomData_size, sizeof(uint8_t));
        memcpy(CHR_RomData, rhs.CHR_RomData,CHR_RomData_size);

        PlayChoice_IROM = (uint8_t*)calloc(PlayChoice_IROM_size, sizeof(uint8_t));
        memcpy(PlayChoice_IROM, rhs.PlayChoice_IROM,PlayChoice_IROM_size);

        PlayChoice_PROM_Data = (uint8_t*)calloc(PlayChoice_PROM_Data_size , sizeof(uint8_t));
        memcpy(PlayChoice_PROM_Data, rhs.PlayChoice_PROM_Data, PlayChoice_PROM_Data_size);

        PlayChoice_PROM_Counter = (uint8_t*)calloc(PlayChoice_PROM_Counter_size, sizeof(uint8_t));
        memcpy(PlayChoice_PROM_Counter, rhs.PlayChoice_PROM_Counter, PlayChoice_PROM_Counter_size);   

    }

    Cartridge::~Cartridge(){

        if(Trainer_size() != 0)
            free(Trainer_Data);

        if(PRG_size() != 0)
            free(PRG_RomData);

        if(CHR_size() != 0)
            free(CHR_RomData);

        if(PIROM_size() != 0)
            free(PlayChoice_IROM);

        if(PROMd_size() != 0)
            free(PlayChoice_PROM_Data);

        if(PROMc_size() != 0)
            free(PlayChoice_PROM_Counter);
    }
//----------------------------------------------------------------------------------------//


// Cartridge class method
    void Cartridge::loadRom(FILE* romFile){                          

        //-------------------------------------------------------------------------//
        u_char* header = (u_char*)calloc(16, sizeof(u_char));
        header_t* info = (header_t*) calloc(1, sizeof(header_t));

        fseek(romFile,0, SEEK_SET);
        fread(header, sizeof(u_char), 16, romFile);

        memcpy(&(info->PRG_size), header+4, sizeof(uint8_t));
        memcpy(&(info->CHR_size), header+5, sizeof(uint8_t));

        uint8_t flag6;
        memcpy(&(flag6), header+6, sizeof(uint8_t));
        info->mirroring = (flag6 & 0x1) ? V_MIRROR : H_MIRROR;
        info->hasBatteryRAM   = (flag6 & 0x2) ? true : false;
        info->hasTrainer      = (flag6 & 0x4) ? true : false;
        info->hasVRAM         = (flag6 & 0x8) ? true : false;
        info->mapper          = (flag6 & 0xF0) >> 4;

        uint8_t flag7;
        memcpy(&(flag7), header+7, sizeof(uint8_t));
        switch (flag7 & 0x3)
        {
            case 0:
                info->console = NES;
                break;
            case 1:
                info->console = VS_SYSTEM;
                break;
            case 2:
                info->console = PLAYCHOICE_10;
                break;

            default:
            info->console = EXTENDED;
                break;
        }
        info->hasNes2 = (((flag7 & 0xC) >> 2) == 2) ? true : false;
        info->mapper += (flag7 & 0xF0);

        uint8_t flag8;
        memcpy(&(flag8), header+8, sizeof(uint8_t));
        info->mapper   += ((flag8 & 0x0F) << 8);
        info->submapper = ((flag8 & 0xF0) >> 4);

        uint8_t flag9;
        memcpy(&(flag9), header+9, sizeof(uint8_t));
        info->PRG_size += ((flag9 & 0x0F) << 4);
        info->CHR_size += ((flag9 & 0xF0) << 4);

        uint8_t flag10;
        memcpy(&(flag10), header+10, sizeof(uint8_t));
        info->PRG_RAM_size = (flag10 & 0xF) ? (64 << (flag10 & 0xF))  : 0;
        info->PRG_NVRAM_size = (flag10 & 0xF0) ? (64 << (flag10 & 0xF0))  : 0;

        uint8_t flag11;
        memcpy(&(flag11), header+11, sizeof(uint8_t));
        info->CHR_RAM_size = (flag11 & 0xF) ? (64 << (flag11 & 0xF))  : 0;
        info->CHR_NVRAM_size = (flag11 & 0xF0) ? (64 << (flag11 & 0xF0))  : 0;

        uint8_t flag12;
        memcpy(&(flag12), header+12, sizeof(uint8_t));
        switch (flag12 & 0x3)
        {
            case 0:
                info->version = NTSC;
                break;
            case 1:
                info->version = PAL;
                break;
            case 2:
                info->version = MULTI_REGION;
                break;

            default:
                info->version = DENDY;
                break;
        }

        uint8_t flag13;
        if(info->console == VS_SYSTEM){
            memcpy(&(flag13), header+13, sizeof(uint8_t));
            info->VS_PPU = flag13 & 0x0F;
            info->VS_Hardware = ((flag13 & 0x0F) >> 4);
        }

        if(info->console == EXTENDED){
            memcpy(&(flag13), header+13, sizeof(uint8_t));
            info->extendedType = flag13 & 0x0F;
        }

        uint8_t flag14;
        memcpy(&(flag14), header+14, sizeof(uint8_t));
        info->miscRom = (flag14 & 0x3);

        uint8_t flag15;
        memcpy(&(flag15), header+15, sizeof(uint8_t));
        info->expansionDevice = (flag15 & 0x3F);


        headerFile = *info;

        //-------------------------------------------------------------------------//

        if(info->hasTrainer){
            Trainer_Data = (uint8_t*)calloc(0x200, sizeof(uint8_t));
            fseek(romFile, 0x10 , SEEK_SET);
            fread(Trainer_Data, sizeof(uint8_t), TRAINER_UNIT, romFile);
        }
        trainer_size = info->hasTrainer * TRAINER_UNIT;

        PRG_RomData = (uint8_t*)calloc(headerFile.PRG_size * PRG_UNIT , sizeof(uint8_t));
        fread(PRG_RomData, sizeof(uint8_t), headerFile.PRG_size * PRG_UNIT, romFile);
        PRG_RomData_size =  headerFile.PRG_size * PRG_UNIT;

        CHR_RomData = (uint8_t*)calloc(headerFile.CHR_size * CHR_UNIT, sizeof(uint8_t));
        fread(CHR_RomData, sizeof(uint8_t), headerFile.CHR_size * CHR_UNIT, romFile);
        CHR_RomData_size = headerFile.CHR_size * CHR_UNIT;


        if(headerFile.console == PLAYCHOICE_10){
            PlayChoice_IROM         = (uint8_t*)calloc(PLAYCHOICE_INST_ROM, sizeof(uint8_t));
            PlayChoice_PROM_Data    = (uint8_t*)calloc(0x10, sizeof(uint8_t));
            PlayChoice_PROM_Counter = (uint8_t*)calloc(0x10, sizeof(uint8_t));
            fread(PlayChoice_IROM, sizeof(uint8_t), PLAYCHOICE_INST_ROM, romFile);
            fread(PlayChoice_PROM_Data, sizeof(uint8_t), 0x10, romFile);
            fread(PlayChoice_PROM_Counter, sizeof(uint8_t), 0x10, romFile);
            PlayChoice_IROM_size =  PLAYCHOICE_INST_ROM;       
            PlayChoice_PROM_Data_size    =  0X10;
            PlayChoice_PROM_Counter_size =  0X10;
        }
        else{
            PlayChoice_IROM_size =  0;       
            PlayChoice_PROM_Data_size    = 0;
            PlayChoice_PROM_Counter_size = 0; 
        }


        //-------------------------------------------------------------------------//

        free(info);
        free(header);
        fclose(romFile);

    }


//----------------------------------------------------------------------------------------// 


// Getter/Setter
    uint8_t* Cartridge::Trainer(){return Trainer_Data;}
    uint8_t* Cartridge::PRG(){return PRG_RomData;}
    uint8_t* Cartridge::CHR(){return CHR_RomData;}
    uint8_t* Cartridge::PIROM(){return PlayChoice_IROM;}
    uint8_t* Cartridge::PROMd(){return PlayChoice_PROM_Data;}
    uint8_t* Cartridge::PROMc(){return PlayChoice_PROM_Counter;}

    size_t Cartridge::Trainer_size(){return trainer_size;}
    size_t Cartridge::PRG_size(){return PRG_RomData_size;}
    size_t Cartridge::CHR_size(){return CHR_RomData_size;}
    size_t Cartridge::PIROM_size(){return PlayChoice_IROM_size;}
    size_t Cartridge::PROMd_size(){return PlayChoice_PROM_Data_size;}
    size_t Cartridge::PROMc_size(){return PlayChoice_PROM_Counter_size;}
//----------------------------------------------------------------------------------------// 



