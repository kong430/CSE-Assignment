#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of data words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000

#define ADD 0
#define NOR 1
#define LW 2
#define SW 3
#define BEQ 4
#define JALR 5 /* JALR will not implemented for this project */
#define HALT 6
#define NOOP 7

#define NOOPINSTRUCTION 0x1c00000

typedef struct IFIDStruct
{
	int instr;
	int pcPlus1;
} IFIDType;

typedef struct IDEXStruct
{
	int instr;
	int pcPlus1;
	int readRegA;
	int readRegB;
	int offset;
} IDEXType;

typedef struct EXMEMStruct
{
	int instr;
	int branchTarget;
	int aluResult;
	int readRegB;
} EXMEMType;

typedef struct MEMWBStruct
{
	int instr;
	int writeData;
} MEMWBType;

typedef struct WBENDStruct
{
	int instr;
	int writeData;
} WBENDType;

typedef struct stateStruct
{
	int pc;
	int instrMem[NUMMEMORY];
	int dataMem[NUMMEMORY];
	int reg[NUMREGS];
	int numMemory;
	IFIDType IFID;
	IDEXType IDEX;
	EXMEMType EXMEM;
	MEMWBType MEMWB;
	WBENDType WBEND;
	int cycles; /* number of cycles run so far */
} stateType;

void initState(stateType *state, FILE *filePtr);
void showInitState(stateType *state, FILE *filePtr);
void stage_IF(stateType *newState, stateType *state);
void stage_ID(stateType *newState, stateType *state);
void stage_EX(stateType *newState, stateType *state);
void stage_MEM(stateType *newState, stateType *state);
void stage_WB(stateType *newState, stateType *state);
int convertNum(int num);
int isHazard(stateType *state);
void forward(stateType *state);

void printState(stateType *statePtr);
int field0(int instruction);
int field1(int instruction);
int field2(int instruction);
int opcode(int instruction);
void printInstruction(int instr);

int main(int argc, char *argv[])
{
	FILE *filePtr;
	stateType state;
	stateType newState;

	if ( argc != 2 )
	{
		printf("error: usage: %s <machine-code file>\n", argv[0]);
		exit(1);
	}

	filePtr = fopen(argv[1], "r");

	if ( filePtr == NULL )
	{
		printf("error: can't open file %s", argv[1]);
		perror("fopen");
		exit(1);
	}

	initState(&state, filePtr);

	char line[MAXLINELENGTH];

	/* show initial mem state */
	for ( state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++ )
	{
		if ( sscanf(line, "%d", state.dataMem + state.numMemory) != 1 )
		{
			printf("error in reading address %d\n", state.numMemory);
			exit(1);
		}

		printf("memory[%d]=%d\n", state.numMemory, state.dataMem[state.numMemory]);
	}

	printf("%d memory words\n", state.numMemory);
	printf("\tinstruction memory:\n");

	/* show instruction memory */
	for ( int i = 0; i < state.numMemory; i++ )
	{
		state.instrMem[i] = state.dataMem[i];
		printf("\t\tinstrMem[ %d ] ", i);
		printInstruction(state.instrMem[i]);
	}

	/* write comments to understand easily */
	while ( 1 )
	{
		printState(&state);
		/* check for halt */
		if ( opcode(state.MEMWB.instr) == HALT )
		{
			printf("machine halted\n");
			printf("total of %d cycles executed\n", state.cycles);
			exit(0);
		}

		/* newState is the state of the machine
		at the end of a cycle */
		newState = state;
		newState.cycles++;

		/* --------------------- IF stage --------------------- */
		stage_IF(&newState, &state);
		/* --------------------- ID stage --------------------- */
		stage_ID(&newState, &state);
		/* --------------------- EX stage --------------------- */
		stage_EX(&newState, &state);
		/* --------------------- MEM stage -------------------- */
		stage_MEM(&newState, &state);
		/* --------------------- WB stage --------------------- */
		stage_WB(&newState, &state);

		state = newState;

		/* this is the last statement before end of the loop.

		It marks the end of the cycle and updates the

		current state with the values calculated in this cycle */
	}

	return 0;
}

void
initState(stateType *state, FILE *filePtr)
{
	char line[MAXLINELENGTH];

	/* initialize registers */
	for ( int i = 0; i < NUMREGS; i++ )
		state->reg[i] = 0;

	/* initialize cycle, PC, pipeline registers */
	state->cycles = 0;
	state->pc = 0;

	state->IFID.instr = NOOPINSTRUCTION;
	state->IFID.pcPlus1 = 0;

	state->IDEX.instr = NOOPINSTRUCTION;
	state->IDEX.pcPlus1 = 0;
	state->IDEX.readRegA = 0;
	state->IDEX.readRegB = 0;
	state->IDEX.offset = 0;

	state->EXMEM.instr = NOOPINSTRUCTION;
	state->EXMEM.branchTarget = 0;
	state->EXMEM.aluResult = 0;
	state->EXMEM.readRegB = 0;

	state->MEMWB.instr = NOOPINSTRUCTION;
	state->MEMWB.writeData = 0;

	state->WBEND.instr = NOOPINSTRUCTION;
	state->WBEND.writeData = 0;
}

void stage_IF(stateType *newState, stateType *state)
{
	newState->pc++;
	newState->IFID.instr = state->instrMem[state->pc];
	newState->IFID.pcPlus1 = state->pc + 1;
}

void stage_ID(stateType *newState, stateType *state)
{
	int regA = field0(state->IFID.instr);
	int regB = field1(state->IFID.instr);
	int offset = convertNum(field2(state->IFID.instr));

	/* if hazard happens, stall the cycle */
	if ( isHazard(state) )
	{
		newState->pc = state->pc;

		newState->IFID.instr = state->IFID.instr;
		newState->IFID.pcPlus1 = state->pc;

		newState->IDEX.pcPlus1 = 0;
		newState->IDEX.readRegA = 0;
		newState->IDEX.readRegB = 0;
		newState->IDEX.offset = 0;
		newState->IDEX.instr = NOOPINSTRUCTION;
	}
	else
	{
		newState->IDEX.readRegA = state->reg[regA];
		newState->IDEX.readRegB = state->reg[regB];
		newState->IDEX.pcPlus1 = state->IFID.pcPlus1;
		newState->IDEX.offset = offset;
		newState->IDEX.instr = state->IFID.instr;
	}
}

void stage_EX(stateType *newState, stateType *state)
{
	int op = opcode(state->IDEX.instr);

	newState->EXMEM.instr = state->IDEX.instr;
	newState->EXMEM.branchTarget = state->IDEX.pcPlus1 + state->IDEX.offset;

	forward(state);

	switch ( op )
	{
	case ADD:
		newState->EXMEM.aluResult = state->IDEX.readRegA + state->IDEX.readRegB;
		break;
	case NOR:
		newState->EXMEM.aluResult = ~(state->IDEX.readRegA | state->IDEX.readRegB);
		break;
	case LW:
	case SW:
		newState->EXMEM.aluResult = state->IDEX.readRegA + state->IDEX.offset;
		break;
	case BEQ:
		newState->EXMEM.aluResult = state->IDEX.readRegA - state->IDEX.readRegB;
		break;
	case HALT:
		newState->MEMWB.instr = HALT;
		break;
	case NOOP:
		newState->MEMWB.instr = NOOP;
		break;
	default:
		break;
	}

	newState->EXMEM.readRegB = state->IDEX.readRegB;
}

void stage_MEM(stateType *newState, stateType *state)
{
	int op = opcode(state->EXMEM.instr);

	newState->MEMWB.instr = state->EXMEM.instr;

	switch ( op )
	{
	case ADD:
	case NOR:
		newState->MEMWB.writeData = state->EXMEM.aluResult;
		break;
	case BEQ:
		if ( !state->EXMEM.aluResult )
		{
			newState->pc = state->EXMEM.branchTarget;

			newState->IFID.instr = NOOPINSTRUCTION;
			newState->IFID.pcPlus1 = 0;

			newState->IDEX.instr = NOOPINSTRUCTION;
			newState->IDEX.pcPlus1 = 0;
			newState->IDEX.readRegA = 0;
			newState->IDEX.readRegB = 0;
			newState->IDEX.offset = 0;

			newState->EXMEM.instr = NOOPINSTRUCTION;
			newState->EXMEM.branchTarget = 0;
			newState->EXMEM.aluResult = 0;
			newState->EXMEM.readRegB = 0;
		}
		break;
	case LW:
		newState->MEMWB.writeData = state->dataMem[state->EXMEM.aluResult];
		break;
	case SW:
		newState->dataMem[state->EXMEM.aluResult] = state->EXMEM.readRegB;
		break;
	case NOOP:
	case HALT:
		break;
	default:
		break;
	}
}

void stage_WB(stateType *newState, stateType *state)
{
	int op = opcode(state->MEMWB.instr);
	int dest;

	newState->WBEND.instr = state->MEMWB.instr;
	newState->WBEND.writeData = state->MEMWB.writeData;

	if ( op == ADD || op == NOR )
	{
		dest = field2(state->MEMWB.instr);
		newState->reg[dest] = state->MEMWB.writeData;
	}
	else if ( op == LW )
	{
		dest = field1(state->MEMWB.instr);
		newState->reg[dest] = state->MEMWB.writeData;
	}
	else if ( op == JALR )
	{
		printf("Not accepted instruction.\n");
		exit(1);
	}
}

int isHazard(stateType *state)
{
	int prevop = opcode(state->IDEX.instr);
	int curop = opcode(state->IFID.instr);

	int regA = field0(state->IFID.instr);
	int regB = field1(state->IFID.instr);
	int dest = field1(state->IDEX.instr);

	if ( prevop == LW )
	{
		switch ( curop )
		{
		case ADD:
		case NOR:
		case BEQ:
			/* if current instr uses load's dest reg */
			if ( regA == dest || regB == dest )
				return 1;
			break;
		case LW:
		case SW:
			if ( regA == dest )
				return 1;
			break;
		default:
			break;
		}
	}

	return 0;
}

void forward(stateType *state)
{
	int curop = opcode(state->IDEX.instr);
	int prevop = opcode(state->WBEND.instr);
	int dest;

	switch ( curop )
	{
	case HALT:
	case NOOP:
		return;
	}

	switch ( prevop )
	{
	case ADD:
	case NOR:
		dest = field2(state->WBEND.instr);
		if ( field0(state->IDEX.instr) == dest )
			state->IDEX.readRegA = state->WBEND.writeData;
		if ( field1(state->IDEX.instr) == dest )
			state->IDEX.readRegB = state->WBEND.writeData;
		break;
	case LW:
		dest = field1(state->WBEND.instr);
		if ( field0(state->IDEX.instr) == dest )
			state->IDEX.readRegA = state->WBEND.writeData;
		if ( field1(state->IDEX.instr) == dest )
			state->IDEX.readRegB = state->WBEND.writeData;
		break;
	default:
		break;
	}

	prevop = opcode(state->MEMWB.instr);

	switch ( prevop )
	{
	case ADD:
	case NOR:
		dest = field2(state->MEMWB.instr);
		if ( field0(state->IDEX.instr) == dest )
			state->IDEX.readRegA = state->MEMWB.writeData;
		if ( field1(state->IDEX.instr) == dest )
			state->IDEX.readRegB = state->MEMWB.writeData;
		break;
	case LW:
		dest = field1(state->MEMWB.instr);
		if ( field0(state->IDEX.instr) == dest )
			state->IDEX.readRegA = state->MEMWB.writeData;
		if ( field1(state->IDEX.instr) == dest )
			state->IDEX.readRegB = state->MEMWB.writeData;
		break;
	default:
		break;
	}

	prevop = opcode(state->EXMEM.instr);

	switch ( prevop )
	{
	case ADD:
	case NOR:
		dest = field2(state->EXMEM.instr);
		if ( field0(state->IDEX.instr) == dest )
			state->IDEX.readRegA = state->EXMEM.aluResult;
		if ( field1(state->IDEX.instr) == dest )
			state->IDEX.readRegB = state->EXMEM.aluResult;
		break;
	default:
		break;
	}
}

int convertNum(int num)
{
	if ( num & (1 << 15) )
		num -= (1 << 16);

	return num;
}

void printState(stateType *statePtr)
{
	int i;
	printf("\n@@@\nstate before cycle %d starts\n", statePtr->cycles);
	printf("\tpc %d\n", statePtr->pc);
	printf("\tdata memory:\n");

	for ( i = 0; i<statePtr->numMemory; i++ )
		printf("\t\tdataMem[ %d ] %d\n", i, statePtr->dataMem[i]);

	printf("\tregisters:\n");
	for ( i = 0; i<NUMREGS; i++ )
		printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);

	printf("\tIFID:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->IFID.instr);
	printf("\t\tpcPlus1 %d\n", statePtr->IFID.pcPlus1);

	printf("\tIDEX:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->IDEX.instr);
	printf("\t\tpcPlus1 %d\n", statePtr->IDEX.pcPlus1);
	printf("\t\treadRegA %d\n", statePtr->IDEX.readRegA);
	printf("\t\treadRegB %d\n", statePtr->IDEX.readRegB);
	printf("\t\toffset %d\n", statePtr->IDEX.offset);

	printf("\tEXMEM:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->EXMEM.instr);
	printf("\t\tbranchTarget %d\n", statePtr->EXMEM.branchTarget);
	printf("\t\taluResult %d\n", statePtr->EXMEM.aluResult);
	printf("\t\treadRegB %d\n", statePtr->EXMEM.readRegB);

	printf("\tMEMWB:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->MEMWB.instr);
	printf("\t\twriteData %d\n", statePtr->MEMWB.writeData);

	printf("\tWBEND:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->WBEND.instr);
	printf("\t\twriteData %d\n", statePtr->WBEND.writeData);
}

int field0(int instruction)
{
	return((instruction >> 19) & 0x7);
}

int field1(int instruction)
{
	return((instruction >> 16) & 0x7);
}

int field2(int instruction)
{
	return(instruction & 0xFFFF);
}

int opcode(int instruction)
{
	return(instruction >> 22);
}


void printInstruction(int instr)
{
	char opcodeString[10];
	if ( opcode(instr) == ADD )
	{
		strcpy(opcodeString, "add");
	}
	else if ( opcode(instr) == NOR )
	{
		strcpy(opcodeString, "nor");
	}
	else if ( opcode(instr) == LW )
	{
		strcpy(opcodeString, "lw");
	}
	else if ( opcode(instr) == SW )
	{
		strcpy(opcodeString, "sw");
	}
	else if ( opcode(instr) == BEQ )
	{
		strcpy(opcodeString, "beq");
	}
	else if ( opcode(instr) == JALR )
	{
		strcpy(opcodeString, "jalr");
	}
	else if ( opcode(instr) == HALT )
	{
		strcpy(opcodeString, "halt");
	}
	else if ( opcode(instr) == NOOP )
	{
		strcpy(opcodeString, "noop");
	}
	else
	{
		strcpy(opcodeString, "data");
	}
	printf("%s %d %d %d\n", opcodeString, field0(instr), field1(instr), field2(instr));
}
