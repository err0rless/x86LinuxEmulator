#/bin/bash
clear

gcc -c *.c -std=c11

#python generateOpcodes.py > opcode.tmp
#objcopy --add-section .VCODE=opcode.tmp handler.o

gcc -o main *.o

rm -rf *.o
#rm -rf opcode.tmp