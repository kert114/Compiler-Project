.globl f
f:
addiu $sp, $sp, -128
sw $fp, 4($sp)
move $fp, $sp
li $2, 0
sw $2, 0($sp)
li $t3, 0x1
bne $v0, $t3, $lab1
li $2, 11
sw $2, -8($sp)
b $lab2
$lab1:
li $2, 10
sw $2, -8($sp)
$lab2:
move $sp, $fp
lw $fp, 4($sp)
addiu $sp, $sp, 128
jr $31
