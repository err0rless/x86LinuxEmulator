#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

char str[] = "Hello, World!\n";

int main(void)
{
	Vreg *v = malloc(sizeof(Vreg));
	InsElement ins;

	void (*insList[0xff])(char type, Vreg *v, InsElement ins);
	setOpcode(insList);

	void *stack  = malloc(1024);
	void *vmcode = malloc(1024);

	memcpy(\
	vmcode,  "\x00\x21\x04\x00\x00\x00\x00\x00\x00\x00" // mov $0x04, %eax
	         "\x0b\xff\x01\x00\x00\x00"                 // inc %ebx ; ebx = 1
	         "\x00\x21\x34\xa0\x04\x08\x02\x00\x00\x00" // mov $pstr, %ecx
	         "\x00\x21\x0f\x00\x00\x00\x03\x00\x00\x00" // mov $0x0f, %edx
	         "\x0a\xff\x80\x00\x00\x00"                 // int $0x80 (write pstr)
	         "\x0c\xff\x00\x00\x00\x00"                 // dec %eax
	         "\x0c\xff\x00\x00\x00\x00"                 // dec %eax
	         "\x0c\xff\x00\x00\x00\x00"                 // dec %eax
	         "\x0a\xff\x80\x00\x00\x00"                 // int $0x80 (exit(1))
	         , 66);

	v->reg[eax] = 0;
	v->reg[ebx] = 0;
	v->reg[ecx] = 0;
	v->reg[edx] = 0;
	v->reg[esi] = 0;
	v->reg[edi] = 0;
	v->reg[ebp] = 0;
	v->reg[esp] = 0;
	v->eip = vmcode;

	for (int i = 0; i <= 9; i++)
	{
		memcpy(&ins, v->eip, 2);
		memcpy(&ins.operand1, v->eip+2, 4);
		memcpy(&ins.operand2, v->eip+6, 4);

		printf("ins.insOpcode = %d\n", ins.insOpcode);
		printf("ins.opTypes   = 0x%x\n", ins.opTypes);

		insList[ins.insOpcode](ins.opTypes, v, ins);	
	}

	return 0;
}