#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

char str[] = "Hello, World!\n";

int main(void)
{
	Vreg *v = malloc(sizeof(Vreg));
	InsElement *ins = malloc(sizeof(InsElement));

	void *stack  = malloc(1024);
	void *vmcode = malloc(1024);

	memcpy(\
	vmcode,  "\x00\x21\x04\x00\x00\x00\x00\x00\x00\x00"
			 "\x00\x21\x01\x00\x00\x00\x01\x00\x00\x00"
			 "\x00\x21\x30\xa0\x04\x08\x02\x00\x00\x00"
			 "\x00\x21\x0f\x00\x00\x00\x03\x00\x00\x00"
			 "\x0a\xff\x80\x00\x00\x00", 46);

	v->eax = 0;
	v->ebx = 0;
	v->ecx = 0;
	v->edx = 0;
	v->esi = 0;
	v->edi = 0;
	v->ebp = stack;
	v->esp = stack;
	v->eip = vmcode;

	for (int i = 0; i <= 4; i++)
	{
		ins = v->eip;

		if (ins->insOpcode == 0)
		{
			mov(ins->opTypes, v, ins);
		}
		else
		{
			intt(ins->opTypes, v, ins);
		}
	}

	return 0;
}
