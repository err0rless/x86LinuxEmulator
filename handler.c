#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

char str1[] = "Hello, World!\n";
char str2[] = "This isn't :)\n";

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
	         "\x0b\xf0\x01\x00\x00\x00"                 // inc %ebx ; ebx = 1
	         "\x00\x21\x3c\xb0\x04\x08\x02\x00\x00\x00" // mov $str1, %ecx
	         "\x00\x21\x0f\x00\x00\x00\x0b\x00\x00\x00" // mov $0x0f, %edx
	         "\x0a\xf1\x80\x00\x00\x00"                 // int $0x80 (write str1)
	         "\x00\x21\x4b\xb0\x04\x08\x02\x00\x00\x00" // mov $str2, %ecx
	         "\x0a\xf1\x80\x00\x00\x00"                 // int $0x80 (write str2)
	         , 58);

	for (int i = 0; i <= 7; i++)
		v->reg[i] = 0;
	for (int i =  0; i <= 10; i++)
		v->flag[i] = 0;

	v->eip = vmcode;

	for (int i = 0; i <= 6; i++)
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