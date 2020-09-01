    lw  0   0   zero
    lw  0   1   init    store result
    lw  0   2   mcand   store 32766 in reg2
    lw  0   3   mplier  store 10383 in reg3
    lw  0   4   index store index
    lw  0   5   tmp 
loop    nor 3   0   3   invert mpiler and store in reg3
    nor 4   0   4   invert index and store in reg4
    nor 3   4   5   nor inverted mpiler and inverted index and store in tmp
    nor 3   0   3   restore(invert one more) mpiler
    nor 4   0   4   restore(invert one more) index
    beq 5   0   shift 
    add 1   2   1   add mcand to result
shift   add 5   6   6   add calculated reg5 to reg6
    add 2   2   2   left shift mcand
    add 4   4   4   left shift index
    beq 3   6   done
    beq 0   0   loop
    noop
done    halt
mcand   .fill   32766
mplier  .fill   10383
zero    .fill   0
init    .fill   0
index .fill   1
tmp .fill   0
