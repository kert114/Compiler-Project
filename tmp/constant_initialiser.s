.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
addiu $sp, $sp, -8
li $2, 12345
sw $2, 0($sp)
sw $v0, 8($fp)
addiu $sp, $sp,  8
lw $2,0($fp)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
