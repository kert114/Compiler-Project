.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
#placeholder for Declaration
addiu $sp, $sp, -8
addiu $sp, $sp,  8
#placeholder for Declaration
addiu $sp, $sp, -8
addiu $sp, $sp,  8
#placeholder for Declaration
addiu $sp, $sp, -8
addiu $sp, $sp,  8
#placeholder for Declaration
addiu $sp, $sp, -8
addiu $sp, $sp,  8
lw $2,0($fp)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
