#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINELENGTH 1000

struct LABEL
{
    char label[MAXLINELENGTH];
    int offset;
    char *labelNum;
    struct LABEL *next;
};
struct LABEL *head;

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
void addLabel(char *, int);
int findLabel(char *);
int strToNum(char *);
int bitFit(int num, int max);

int main(int argc, char *argv[])
{
    head = (struct LABEL *)malloc(sizeof(struct LABEL));
    head->next = NULL;
    head->labelNum = (char *)malloc(sizeof(char) * 100);
    head->labelNum = NULL;

	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH],
    arg0[MAXLINELENGTH], arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    int pc = -1;
    int labelLen = 0;
	
	if (argc!=3)
	{
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
	}

    inFileString = argv[1];
    outFileString = argv[2];
    
    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr ==NULL)
    {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }

    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr ==NULL)
    {
        printf("error in opening %s\n", outFileString);
    }
    
    while(1)
    {
        if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) break;
        pc++;
        labelLen = strlen(label);
        if (labelLen == 0) continue;
        if (labelLen > 6)
        {
            printf("error: label(%s) exceeds 6 characters\n", label);
            exit(1);
        }
        if (label[0] > 47 && label[0] < 58)
        {
            printf("error: label(%s) starts with a letter\n", label);
            exit(1);
        }
        if (!strcmp(opcode, ".fill"))
        {
            if (atol(arg0)>2147483647 | atol(arg0)<-2147483648)
            {
                printf("error: .fill's numeric value exceeded the upper limit\n");
                exit(1);
            }
        }
        addLabel(label, pc);
        findLabel(label);
    }
    rewind(inFilePtr);
    pc = -1;

    while (1)
    {
        int op_binary;
        int regA, regB, offset, destReg;
        int result = 0;
       
        if (!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) break;
        pc++;
        
        if (!strcmp(opcode, "add"))
        {
            op_binary = 0;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            destReg = strToNum(arg2);
            if (bitFit(regA, 3) && bitFit(regB, 3) && bitFit(destReg, 3))
            {
                result = ((regA << 19) | (regB << 16) | destReg);
            }
            else
            {
                printf("error: bits do not fit in 'add'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "nor"))
        {
            op_binary = 1;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            destReg = strToNum(arg2);
            if (bitFit(regA, 3) && bitFit(regB, 3) && bitFit(destReg, 3))
            {
                result = ((op_binary << 22) | (regA << 19) | (regB << 16) | destReg);
            }
            else
            {
                printf("error: bits do not fit in 'nor'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "lw"))
        {
            op_binary = 2;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            offset = strToNum(arg2);
            if (bitFit(regA, 3) && bitFit(regB, 3) && bitFit(offset, 16))
            {
                result = ((op_binary << 22) | (regA << 19) | (regB << 16) | offset);
            }
            else
            {
                printf("error: bits do not fit in 'lw'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "sw"))
        {
            op_binary = 3;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            offset = strToNum(arg2);
            if (bitFit(regA, 3) && bitFit(regB, 3) && bitFit(offset, 16))
            {
                result = ((op_binary << 22) | (regA << 19) | (regB << 16) | offset);
            }
            else
            {
                printf("error: bits do not fit in 'sw'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "beq"))
        {
            op_binary = 4;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            offset = strToNum(arg2);
            if (bitFit(regA, 3) && bitFit(regB, 3) && bitFit(offset, 16))
            {
                if (!isNumber(arg2)) offset = 0X0000FFFF & (offset - (pc + 1));
                result = ((op_binary << 22) | (regA << 19) | (regB << 16) | offset);
            }
            else
            {
                printf("error: bits do not fit in 'beq'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "jalr"))
        {
            op_binary = 5;
            regA = strToNum(arg0);
            regB = strToNum(arg1);
            if (bitFit(regA, 3) && bitFit(regB, 3))
            {
                result = ((op_binary << 22) | (regA << 19) | (regB << 16));
            }
            else
            {
                printf("error: bits do not fit in 'jalr'\n");
                exit(1);
            }
        }
        else if (!strcmp(opcode, "halt"))
        {
            op_binary = 6;
            result = (op_binary << 22);
        }
        else if (!strcmp(opcode, "noop"))
        {
            op_binary = 7;
            result = (op_binary << 22);
        }
        else if (!strcmp(opcode, ".fill"))
        {
            result = strToNum(arg0);
        }
        else
        {
            printf("error: (%s) is unrecognized opcode\n", opcode);
            exit(1);
        }
        fprintf(outFilePtr, "%i\n", result);
    }
    exit(0);
}

int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0, char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    //delete prior values
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    //read the line from the assembly-language file
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL)
    {
        //reached end of file
        return(0);
    }

    //check for line too long (by looking for a \n)
    if (strchr(line, '\n') == NULL)
    {
        //line too long
        printf("errror: line too long\n");
        exit(1);
    }

    //is there a label?
    ptr = line;
    if (sscanf(ptr, "%[^\t\n\r ]", label))
    {
        //successfully read label: advance pointer over the label
        ptr += strlen(label);
    }

    //parse the rest of the line. Would be nice to have real regular expressions, but scanf will suffice.

    sscanf(ptr, "%*[\t\n\r  ]%[^\t\n\r  ]%*[\t\n\r  ]%[^\t\n\r  ]%*[\t\n\r  ]%[^\t\n\r  ]%*[\t\n\r  ]%[^\t\n\r  ]", opcode, arg0, arg1, arg2);
    return(1);
}

int isNumber(char *string)
{
    //return 1 if string is a number
    int i;
    return ((sscanf(string, "%d", &i)) == 1);
}

void addLabel(char *label, int offset)
{
    struct LABEL *cur;
    struct LABEL *new = (struct LABEL*)malloc(sizeof(struct LABEL));
    new->labelNum = (char *)malloc(sizeof(char)*100);
    strcpy(new->label, label);
    new->offset = offset;
    new->next = NULL;
    cur = head;
    if (cur->next == NULL) cur->next = new;
    else
    {
        while (cur->next!=NULL)
        {
            cur = cur->next;
        }
        cur->next = new;
    }
} 

int findLabel(char *label)
{
    struct LABEL *cur;
    cur = head;
    if (cur->next == NULL) printf("error: there is no label\n");
    else
    {
        cur = cur->next;
        while (1)
        {
            if (!strcmp(cur->label, label))
            {
               return cur->offset;
            }
            cur = cur->next;
            if (cur == NULL) break;
        }
    }
    printf("error: there is no [%s] label\n", label);
    exit(1);
}

int strToNum(char *str)
{
    if (isNumber(str)) return atoi(str);
    else return findLabel(str);
}

int bitFit(int num, int max)
{
    int bit = 1;
    for (int i=0;i<max;i++)
    {
        bit *= 2;
    }
    if (num < bit) return 1;
    else return 0;
}
