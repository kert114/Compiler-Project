.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
sw $a0, 12($fp)
sw $a1, 16($fp)
lw $2,12($fp)
move $t0, $v0
lw $2,16($fp)
move $t1, $v0
add $v0, $t0, $t1
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
