    lw  0   1   3   load reg1 with 3 (numeric address)
    lw  0   2   seven   load reg2 with seven(symbolic address)
    lw  0   3   1   load reg3 with 1 (numeric address)
    lw  0   4   ten    load reg4 with four(symbolic address)
    add  1   2   3  add 3 with seven, store results in reg3
    sw  0   4   10  store reg4 to memory address 10
    beq  3   2   1  branch to the address 9
    sw  0   1   negTwo  store reg1 into memory address negTwo
    noop
done    halt
seven    .fill   7
ten    .fill   10
two    .fill   2
negTwo    .fill   -1
