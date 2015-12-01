#include <stdio.h>
#include <stdlib.h>

// STRUCT OF VIRTUAL-PROCESSOR
typedef struct VIRTUAL_REGISTER
{
	long reg[8];   // general registers eax ... esp
	long flag[11]; // status flag registers CF ... OF
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

// GENERAL REGISTER DEFINES
#define EAX 0x00
#define EBX 0x01
#define ECX 0x02
#define EDX 0x03
#define ESI 0x04
#define EDI 0x05
#define EBP 0x06
#define ESP 0x07
#define EIP 0x08
#define TM1 0x09
#define TM2 0x0a

#define eax 0x00
#define ebx 0x01
#define ecx 0x02
#define edx 0x03
#define esi 0x04
#define edi 0x05
#define ebp 0x06
#define esp 0x07
// eip...
#define tm1 0x09
#define tm2 0x0a

// FLAG REGISTER DEFINES
#define CF 0x00
#define PF 0x01
#define AF 0x02
#define ZF 0x03
#define SF 0x04
#define TF 0x05
#define IF 0x06
#define DF 0x07
#define OF 0x08

// TPYE OF OPERANDS
#define OP1_REG 0x10
#define OP1_IMM 0x20
#define OP1_MEM 0x30

#define OP2_REG 0x01
#define OP2_IMM 0x02
#define OP2_MEM 0x03

#define OPERAND_SINGLE 0xf0
#define SINGLE_REG     0x00
#define SINGLE_IMM     0x01
#define SINGLE_MEMORY  0x02

// error, print handler
void pError(const char *eMsg, Vreg *v);
void chkReg(long value, Vreg *vs);

// INSTRUCTION HANDLERS
void mov (char type, Vreg *v, InsElement ins);
void intt(char type, Vreg *v, InsElement ins);
void inc (char type, Vreg *v, InsElement ins);
void dec (char type, Vreg *v, InsElement ins);
void cmp (char type, Vreg *v, InsElement ins);