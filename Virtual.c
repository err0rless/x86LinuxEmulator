#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

void mov(char type, Vreg *v, InsElement *ins)
{
	char OP1_TYPE = type & 0xf0;
	char OP2_TYPE = type & 0x0f;

	long op1, op2;

	memcpy(&op1, v->eip+2, 4);
	memcpy(&op2, v->eip+6, 4);

	printf("op1 : %ld\n", op1);
	printf("op2 : %ld\n", op2);

	switch (OP1_TYPE)
	{
	case OP1_REG:
		// not yet
		break;

	case OP1_IMM:
		printf("inmov In mov in OP1_IMM\n");

		switch (OP2_TYPE)
		{
		case OP2_IMM:
			// not yet
			break;
		case OP2_REG:
			printf("in mov ins op2 : %ld\n", op2);

			switch ((int)op2)
			{
			case EAX:
				v->eax = op1; 
				printf("test::%ld %ld\n", v->eax, op1);
				break;
			case EBX:
				v->ebx = op1; break;
			case ECX:
				v->ecx = op1; break;
			case EDX:
				v->edx = op1; break;
			case ESI:
			case EDI:
			case EBP:
			case ESP: 
			default: break; // not yet
			}
			
			break;
		case OP2_MEM:
			// not yet
			break;
		}
		break;

	case OP1_MEM:
		// not yet
		break;
	}

	v->eip += 10;
}

void intt(char type, Vreg *v, InsElement *ins)
{
	printf("in intt eax : %ld\n", v->eax);
	printf("in intt ebx : %ld\n", v->ebx);
	printf("in intt ecx : %ld\n", v->ecx);
	printf("in intt edx : %ld\n", v->edx);

	__asm__
	(
		"mov %0, %%eax\n\t"
		"mov %1, %%edx\n\t"
		"mov %2, %%ecx\n\t"
		"mov %3, %%ebx\n\t"
		"int $0x80"
		: /* No outputs */
		: "m"(v->eax), "m"(v->edx), "m"(v->ecx), "m"(v->ebx)
	);

	v->eip += 6;
}
