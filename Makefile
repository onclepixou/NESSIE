CC=g++

SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin

LINCDIR = inc
INCDIR= -I $(LINCDIR) -I /usr/include -I /usr/local/include


CFLAGS=  -std=c++11 -g $(INCDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(LINCDIR)/*.h)
NESMU_DEP  := obj/CMOS_6502.o obj/Cartridge.o obj/NESMU.o
DASM_DEP   := obj/Cartridge.o obj/DasmTool.o obj/Disassembler.o



$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ 


NESMU:$(NESMU_DEP)
	$(CC) $(CFLAGS)  -o $(BINDIR)/$@ $^ 

Dasm:$(DASM_DEP)
	$(CC) $(CFLAGS)  -o $(BINDIR)/$@  $^ 


.PHONY: clean

clean :
	rm $(OBJDIR)/*.o
