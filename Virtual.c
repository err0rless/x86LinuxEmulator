#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

void setOpcode(void (*insList[0xff])(char type, Vreg *v, InsElement ins))
{
	insList[0x00] = mov;
	insList[0x0a] = intt;
	insList[0x0b] = inc;
	insList[0x0c] = dec;
}

void pError(const char *eMsg)
{
	return write(2, eMsg, strlen(eMsg));
}

void mov(char type, Vreg *v, InsElement ins)
{
	char OP1_TYPE = type & 0xf0;
	char OP2_TYPE = type & 0x0f;

	printf("ins.operand1 : %ld\n", ins.operand1);
	printf("ins.operand2 : %ld\n\n", ins.operand2);

	switch (OP1_TYPE)
	{
	case OP1_REG:
		// not yet
		break;

	case OP1_IMM:

		switch (OP2_TYPE)
		{
		case OP2_IMM:
			// not yet
			break;
		case OP2_REG:

			switch ((int)ins.operand2)
			{
			case EAX:
				v->eax = ins.operand1; break;
			case EBX:
				v->ebx = ins.operand1; break;
			case ECX:
				v->ecx = ins.operand1; break;
			case EDX:
				v->edx = ins.operand1; break;
			case ESI:
				v->esi = ins.operand1; break;
			case EDI:
				v->edi = ins.operand1; break;
			case EBP:
				v->ebp = ins.operand1; break;
			case ESP: 
				v->esp = ins.operand1; break;
			case EIP:
				pError("register EIP is not writable");
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

	// sizeof (opcode + type + operand1 + operand2);
	v->eip += 10;
}

void intt(char type, Vreg *v, InsElement ins)
{
	printf("in intt eax : 0x%lx\n", v->eax);
	printf("in intt ebx : 0x%lx\n", v->ebx);
	printf("in intt ecx : 0x%lx\n", v->ecx);
	printf("in intt edx : 0x%lx\n\n", v->edx);

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


void inc(char type, Vreg *v, InsElement ins)
{
	printf("in inc...\n");

	switch ((int)ins.operand1)
	{
	case EAX:
		v->eax += 1; break;
	case EBX:
		v->ebx += 1; break;
	case ECX:
		v->ecx += 1; break;
	case EDX:
		v->edx += 1; break;
	case ESI:
		v->esi += 1; break;
	case EDI:
		v->edi += 1; break;
	default: break;
	}

	v->eip += 6;
}

void dec(char type, Vreg *v, InsElement ins)
{
	printf("in dec...\n");

	switch((int)ins.operand1)
	{
	case EAX:
		v->eax -= 1; break;
	case EBX:
		v->ebx -= 1; break;
	case ECX:
		v->ecx -= 1; break;
	case EDX:
		v->edx -= 1; break;
	case ESI:
		v->esi -= 1; break;
	case EDI:
		v->edi -= 1; break;
	default: break;
	}

	v->eip += 6;
}