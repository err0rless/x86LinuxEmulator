#include <stdio.h>
#include <stdlib.h>

// STRUCT OF VIRTUAL-PROCESSOR
typedef struct VIRTUAL_REGISTER
{
	long eax;
	long ebx;
	long ecx;
	long edx;
	long esi;
	long edi;
	long ebp;
	long esp;
	void *eip;
} Vreg;

// STRUCT OF INSTRUCTION
typedef struct INSTRUCTION_ELEMENTS
{
	char insOpcode;
	char opTypes;
	long operand1;
	long operand2;
} InsElement;

// OPERAND TYPE DEFINES
#define IMM      0x10
#define REGISTER 0x20
#define MEMORY   0x30
#define PMEMORY  0x40

// REGISTER DEFINES
#define EAX 0x00
#define EBX 0x01
#define ECX 0x02
#define EDX 0x03
#define ESI 0x04
#define EDI 0x05
#define EBP 0x06
#define ESP 0x07
#define EIP 0x08

// TPYE OF OPERANDS
#define OP1_REG 0x10
#define OP1_IMM 0x20
#define OP1_MEM 0x30

#define OP2_REG 0x01
#define OP2_IMM 0x02
#define OP2_MEM 0x03

#define OPERAND_SINGLE 0xff

void mov(char type, Vreg *v, InsElement *ins);
void intt(char type, Vreg *v, InsElement *ins);
