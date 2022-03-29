.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
addiu $sp, $sp, -8
li $2, 10
sw $2, 0($30)
sw $v0, 8($fp)
addiu $sp, $sp,  8
addiu $sp, $sp, -8
li $2, 20
sw $2, 0($30)
move $t0, $v0
lw $2,0($fp)
move $t1, $v0
add $v0, $t0, $t1
sw $v0, 8($fp)
addiu $sp, $sp,  8
lw $2,0($fp)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
