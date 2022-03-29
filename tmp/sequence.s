.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
addiu $sp, $sp, -8
