    lw  0   1   ONE
    beq 3   4   2   branch hazard. jumps to instr[4]
    lw  1   2   ONE reg[1] is dependant to instr[0]
    lw  2   3   TWO reg[2] is dependant to instr[1]
    add 1   2   4   reg[1] and reg[2] are dependant to instr[1], instr[2]
    add 3   4   5   reg[3] and reg[4] is dependant to instr[2], instr[3]
    lw  0   2   THREE   no dependancy
    sw  2   5   TWO reg[2] and reg[5] is dependant to instr[4], instr[5]
    halt
ONE .fill   1
TWO .fill   2
THREE   .fill   3
FOUR    .fill   4
FIVE    .fill   5
SIX .fill   6
