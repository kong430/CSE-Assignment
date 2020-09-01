    lw  0   1   ONE
    lw  1   2   TWO reg[1] dependant to instr[0]
LOOP    beq 3   2   2   reg[2] dependant to instr[2], branch hazard -> fail 3 times
    add 3   1   3
    beq 0   0   LOOP
    halt
ONE .fill   1
TWO .fill   2
THREE   .fill   3
