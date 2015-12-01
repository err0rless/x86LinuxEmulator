#include <stdio.h>
#include <stdlib.h>
#include "Virtual.h"

void setOpcode(void (*insList[0xff])(char type, Vreg *v, InsElement ins))
{
	insList[0x00] = mov;
	insList[0x0a] = intt;
	insList[0x0b] = inc;
	insList[0x0c] = dec;
	insList[0x0d] = cmp;
}

void chkReg(long value, Vreg *v)
{
	if (value < 0 || value > 7)
	{
		pError("Invalid Register Value\n", v);
	}
}

void pError(const char *eMsg, Vreg *v)
{
	char eipMsg[32];
	sprintf(eipMsg, "Error occured at 0x%x\n", (int)v->eip);

	write(2, eipMsg, strlen(eipMsg));
	write(2, eMsg, strlen(eMsg));
	exit(1);
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
		chkReg(ins.operand1, v);
		v->reg[tm1] = v->reg[ins.operand1];
		break;
	case OP1_IMM:
		v->reg[tm1] = ins.operand1;
		break;
	case OP1_MEM:
		v->reg[tm1] = *(int *)ins.operand1;
		break;
	default:
		pError("mov::Invalid Operand type\n", v);
		break;
	}

	switch (OP2_TYPE)
	{
	case OP2_IMM:
		pError("mov::Invalid Operand type\n", v);
	case OP2_REG:
		chkReg(ins.operand2, v);
		v->reg[ins.operand2] = v->reg[tm1];
		break;
	case OP2_MEM:
		*(int *)ins.operand2 = v->reg[tm1];
		break;
	default:
		pError("mov::Invalid Operand type\n", v);
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

	__asm__
	(	"mov %0, %%eax\n\t"
		"mov %1, %%edx\n\t"
		"mov %2, %%ecx\n\t"
		"mov %3, %%ebx\n\t"
		"int $0x80"
		: /* No outputs */
		: "m"(v->reg[eax]), "m"(v->reg[edx]), "m"(v->reg[ecx]), "m"(v->reg[ebx])
	);

	v->eip += 6;
}

void inc(char type, Vreg *v, InsElement ins)
{
	char SINGLE_OP_TYPE = type & 0x0f;

	switch (SINGLE_OP_TYPE)
	{
	case SINGLE_REG:
		chkReg(ins.operand1, v);
		v->reg[(int)ins.operand1] += 1;
		break;
	case SINGLE_MEMORY:
		*(int *)ins.operand1 += 1;
		break;
	default:
		pError("inc::Invalid Single Operand's Type\n", v);
		break;
	}

	v->eip += 6;
}

void dec(char type, Vreg *v, InsElement ins)
{
	char SINGLE_OP_TYPE = type & 0x0f;

	switch (SINGLE_OP_TYPE)
	{
	case SINGLE_REG:
		chkReg(ins.operand1, v);
		v->reg[(int)ins.operand1] -= 1;
		break;
	case SINGLE_MEMORY:
		*(int *)ins.operand1 -= 1;
		break;
	default:
		pError("dec::Invalid Single Operand's Type\n", v);
		break;
	}

	v->eip += 6;
}

void cmp(char type, Vreg *v, InsElement ins)
{
	char OP1_TYPE = type & 0xf0;
	char OP2_TYPE = type & 0x0f;

	switch (OP1_TYPE)
	{
	case OP1_REG:
		chkReg(ins.operand1, v);
		v->reg[tm1] = v->reg[ins.operand1];
		break;
	case OP1_IMM:
		v->reg[tm1] = ins.operand1;
		break;
	case OP1_MEM:
		v->reg[tm1] = *(int *)ins.operand1;
		break;
	default:
		pError("cmp::Invalid Operand type\n", v);
		break;
	}

	switch (OP2_TYPE)
	{
	case OP2_REG:
		chkReg(ins.operand2, v);
		v->flag[ZF] = !(v->reg[tm1] == v->reg[ins.operand2]);
		break;
	case OP2_IMM:
		v->flag[ZF] = !(v->reg[tm1] == ins.operand2);
		break;
	case OP2_MEM:
		v->flag[ZF] = !(v->reg[tm1] == *(int *)ins.operand2);
		break;
	default:
		pError("cmp::Invalid Operand2 type\n", v);
		break;
	}

	v->eip += 10;
}