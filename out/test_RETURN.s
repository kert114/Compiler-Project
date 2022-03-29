.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
li $2, 10
sw $2, -8($30)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
