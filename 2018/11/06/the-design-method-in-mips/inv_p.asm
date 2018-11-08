.data
	vis: .space 100
	a: .space 100
	space: .asciiz " "
	endl: .asciiz "\n"

.macro push(%val)
	sw %val,0($sp)
	sub $sp,$sp,4
.end_macro

.macro pop(%val)
	add $sp,$sp,4
	lw %val,0($sp)
.end_macro

.macro print_str(%str)
	la $a0,%str
	li $v0,4
	syscall
.end_macro

.macro print_int(%val)
	li $v0,1
	add $a0,$0,%val
	syscall
.end_macro

.macro read_int(%reg)
	li $v0,5
	syscall
	move %reg,$v0
.end_macro

.macro read_add(%reg)
	li $v0,5
	syscall
	sw $v0,0(%reg)
.end_macro

.macro load_arr(%arr,%x,%reg)
	la $a3,%arr
	
	mul %reg,%x,4
	add %reg,%reg,$a3

	lw %reg,0(%reg)
.end_macro

.macro save_arr(%arr,%x,%reg)
	la $a3,%arr
	
	mul $a2,%x,4
	add $a2,$a2,$a3

	sw %reg,0($a2)
.end_macro

.macro return0()
	li $v0,10
	syscall
.end_macro


.text
	read_int($s0)
	li $s7,1

	li $a0,1
	jal dfs

	return0()

dfs:
	push($ra)
	push($a0)

	bgt $a0,$s0,dfs_ret

dfs_wrk:
	move $t0,$s0
	wrk_st:
	ble $t0,$0,wrk_ed

		load_arr(vis,$t0,$t1)
		bnez $t1,if_ed

		save_arr(vis,$t0,$s7)

		pop($a0)
		push($a0)

		save_arr(a,$a0,$t0)

		add $a0,$a0,1
		push($t0)
		jal dfs
		pop($t0)

		save_arr(vis,$t0,$0)

		if_ed:

	sub $t0,$t0,1
	j wrk_st
	wrk_ed:
	j dfs_end

dfs_ret:

	li $t0,1
	print_st:
	bgt $t0,$s0,print_ed

	load_arr(a,$t0,$t1)
	print_int($t1)
	print_str(space)

	add $t0,$t0,1
	j print_st
	print_ed:
	print_str(endl)

	j dfs_end


dfs_end:
	pop($a0)
	pop($ra)
	jr $ra
