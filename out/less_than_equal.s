.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
sw $a0, 12($fp)
sw $a1, 16($fp)
#placeholder for Declaration
addiu $sp, $sp, -8
