#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000
typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int num);

int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if(argc != 2)
    {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }
    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL)
    {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    state.pc = 0;
    for (int i=0;i<NUMREGS;i++)
    {
        state.reg[i] = 0;
    }

    /* read in the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL;
            state.numMemory++)
    {
        if (sscanf(line, "%d", state.mem+state.numMemory) != 1)
        {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    int opcode, regA, regB, dest, offset;
    int count;
 
    while (1)
    {
        printState(&state);
    
        int mchTmp = state.mem[state.pc];
        opcode = (mchTmp >> 22) & 7;
        regA = (mchTmp >> 19) & 7;
        regB = (mchTmp >> 16) & 7;
        dest = mchTmp & 7;
        offset = convertNum(mchTmp & 0x0000FFFF);
        
	    //add
	    if (opcode == 0)
	    {
	    	state.reg[dest] = state.reg[regA] + state.reg[regB];
	    }
	    //nor
	    else if (opcode == 1)
	    {
		    state.reg[dest] = ~(state.reg[regA] | state.reg[regB]);
	    }
	    //lw
	    else if (opcode ==2)
	    {
       		state.reg[regB] = state.mem[state.reg[regA] + offset];
	    }
	    //sw
	    else if (opcode ==3)
	    {
	    	state.mem[state.reg[regA] + offset] = state.reg[regB];
	    }
	    //beq
	    else if (opcode ==4)
	    {
    		if (state.reg[regA] == state.reg[regB]) state.pc += offset;
	    }
	    //jalr
	    else if (opcode ==5)
	    {
	    	state.reg[regB] = state.pc + 1;
	    	state.pc = state.reg[regA] -1;
	    }
	    //halt
	    else if (opcode ==6)
	    {
	        state.pc++;
    		count++;
	    	printf("machine halted\ntotal of %d instructions executed\n", count);
	    	printf("final state of machine: \n");
            printState(&state);
	    	break;
	    }
	    //noop
	    else if (opcode ==7)
	    {

	    }
        else
        {
            printf("error: unrecognized opcode\n");
            exit(1);
        }
        state.pc++;
        count++;
	}
	return 0;
}


void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    
    for (i=0;i<statePtr->numMemory;i++)
    {
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    
    printf("\tregisters:\n");
    
    for (i=0;i<NUMREGS;i++)
    {
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }

    printf("end state\n");
}

int convertNum(int num)
{
    //convert 16-bit number into 32-bit linux integer
    if (num & (1 << 15))
    {
        num -= (1 << 16);
    }
    return num;
}
