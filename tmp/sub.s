.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
sw $a0, 12($fp)
sw $a1, 16($fp)
addiu $sp, $sp, -8
sw $v0, 8($fp)
addiu $sp, $sp,  8
addiu $sp, $sp, -8
lw $2,12($fp)
move $t0, $v0
lw $2,16($fp)
move $t1, $v0
sub $v0, $t0, $t1
sw $v0, 8($fp)
addiu $sp, $sp,  8
lw $2,8($fp)
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
