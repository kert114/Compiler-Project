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
move $v0, $t0
slt $v0, $v0, $t1
xori $v0, $v0, 0x1
andi $v0, $v0, 0x00ff
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
