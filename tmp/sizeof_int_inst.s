.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
addiu $sp, $sp, -8
sw $v0, 8($fp)
addiu $sp, $sp,  8
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
