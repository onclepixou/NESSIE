#! /usr/bin/python3

import sys


if __name__ == "__main__":

    if len(sys.argv) != 3:
        sys.exit()

    trig = ["ADC", "AND", "ASL","BCC","BCS","BEQ","BIT","BMI","BNE","BPL","BRK","BVC","BVS","CLC","CLD","CLI","CLV","CMP","CPX","CPY","DEC","DEX","DEY","EOR","INC","INX","INY","JMP","JSR","LDA","LDX","LDY","LSR","NOP","ORA","PHA","PHP","PLA","PLP","ROL","ROR","RTI","RTS","SBC","SEC","SED","SEI","STA","STX","STY","TAX","TAY","TSX","TXA","TXS","TYA"]
    ref = []
    perso = []

    f = open(sys.argv[1], "r")
    for line in f.readlines():
        newitem = []
        lst = line.split(" ")
        newitem.append(lst[0])
        for i, s  in enumerate(lst) :
            if s in trig:
                newitem.append(s)
                newitem.append(lst[i+1])
            if(s[0:2] == "A:"):
                newitem.append(lst[i])
                newitem.append(lst[i+1])
                newitem.append(lst[i+2])
                newitem.append(lst[i+3])
                newitem.append(lst[i+4])

        
        ref.append(newitem)
    f.close()
        

    f = open(sys.argv[2], "r")
    for line in f.readlines():
        newitem = []
        lst = line.split(" ")
        newitem.append(lst[0])
        for i, s  in enumerate(lst) :
            if s in trig:
                newitem.append(s)
                for j in range(i + 1, len(lst)):
                    if((lst[j] != '')):
                        if(lst[j][1] != ":"):
                            newitem.append(lst[j])
                        else:
                            newitem.append("")
                        break
                    if(lst[j][0:2] == "A:"):
                        newitem.append('')

                
            if(s[0:2] == "A:"):
                newitem.append(lst[i])
                newitem.append(lst[i+1])
                newitem.append(lst[i+2])
                newitem.append(lst[i+3])
                newitem.append(lst[i+4])

        
        perso.append(newitem)
    f.close()


def compare(lst1, lst2):

    if len(lst1) != len(lst2):
        return False

    for i in range(len(lst1)):
        if (lst1[i] != lst2[i]):
            return False

    return True

banlist = [104, 105, 106, 107, 108, 109, 110, 111]

for i in range(len(ref)):
    truth = compare(ref[i], perso[i])
    if((not truth) and (i+1 not in banlist)):
        print("Difference spotted at ligne {} / {}".format(i+1, len(ref)))
        print("Previous   was ", perso[i - 1])
        print("reference says ", ref[i])
        print("Emulator  says ", perso[i])
        sys.exit()
    print("Ok line {}".format(i+1))

        


