.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
addiu $sp, $sp, -8
sw $v0, 8($fp)
addiu $sp, $sp,  8
addiu $sp, $sp, -8
li $2, 1
<<<<<<< HEAD
sw $2, 0($30)
=======
sw $2, 0($sp)
>>>>>>> a1b13c7e0b2f579df6ae1c47040424a3d65644a6
sw $v0, 8($fp)
addiu $sp, $sp,  8
addiu $sp, $sp, -8
lw $2,8($fp)
move $t0, $v0
lw $2,8($fp)
move $t1, $v0
add $v0, $t0, $t1
sw $v0, 8($fp)
addiu $sp, $sp,  8
lw $2,8($fp)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
