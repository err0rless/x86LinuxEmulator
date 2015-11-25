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

unsigned int pError(const char *eMsg)
{
	return write(2, eMsg, strlen(eMsg));
}

void mov(char type, Vreg *v, InsElement ins)
{
	char OP1_TYPE = type & 0xf0;
	char OP2_TYPE = type & 0x0f;

	printf("ins.operand1 : %ld\n", ins.operand1);
	printf("ins.operand2 : %ld\n\n", ins.operand2);

	if (OP2_TYPE == OP2_IMM)
	{
		pError("mov::Invalid Operand2 OP2_IMM");
		return ;
	}

	switch (OP1_TYPE)
	{
	case OP1_REG:
		switch (OP2_TYPE)
		{
		case OP2_REG:
			v->reg[(int)ins.operand2] = v->reg[(int)ins.operand1];
			break;
		case OP2_MEM:
			*(ins.operand2) = v->reg[(int)ins.operand1];
			break;
		default: 
			pError("mov::Invalid Operand2's type");
			break;
		}
		break;

	case OP1_IMM:
		switch (OP2_TYPE)
		{
		case OP2_REG:
			v->reg[(int)ins.operand2] = ins.operand1;
			break;
		case OP2_MEM:
			*(ins.operand2) = ins.operand1;
			break;
		default: 
			pError("mov::Invalid Operand2's type");
			break;
		}
		break;

	case OP1_MEM:
		switch (OP2_TYPE)
		{
		case OP2_REG:
			v->reg[(int)ins.operand2] = *(ins.operand1);
			break;
		case OP2_MEM:
			*(ins.operand2) = *(ins.operand1);
			break;
		default: 
			pError("mov::Invalid Operand2's type");
			break;
		}
		break;
	}

	// sizeof (opcode + type + operand1 + operand2);
	v->eip += 10;
}

void intt(char type, Vreg *v, InsElement ins)
{
	printf("in intt eax : 0x%lx\n", v->reg[eax]);
	printf("in intt ebx : 0x%lx\n", v->reg[ebx]);
	printf("in intt ecx : 0x%lx\n", v->reg[ecx]);
	printf("in intt edx : 0x%lx\n\n", v->reg[edx]);

	char int_num[30];

	switch (type & 0x0f)
	{
	case SINGLE_IMM:
	case SINGLE_PMEMORY:
		strcpy(int_num, "$");
		break;
	case SINGLE_REG:
		strcpy(int_num, "%%");
		break;
	default: 
		pError("intt::Invalid Operand1's type");
		break;
	}
	
	sprintf(int_num, "%s%d\n\t", int_num, ins.operand1);

	char assm[1024];
	strcpy(assm, "mov %0, %%eax\n\t");
	strcat(assm, "mov %1, %%edx\n\t");
	strcat(assm, "mov %2, %%ecx\n\t");
	strcat(assm, "mov %3, %%ebx\n\t");
	strcat(assm, int_num);

	__asm__
	(	assm,
		: /* No outputs */
		: "m"(v->reg[eax]), "m"(v->reg[edx]), "m"(v->reg[ecx]), "m"(v->reg[ebx])
	);

	v->eip += 6;
}

void inc(char type, Vreg *v, InsElement ins)
{
	printf("in inc...\n");

	v->reg[(int)ins.operand1] += 1;

	v->eip += 6;
}

void dec(char type, Vreg *v, InsElement ins)
{
	printf("in dec...\n");

	v->reg[(int)ins.operand1] -= 1;

	v->eip += 6;
}