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
bne $t0, $0, $lab2
beq $t1, $0, $lab3
$lab2:
li $v0, 1
b $lab4
$lab3:
move $v0, $0
$lab4:
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
