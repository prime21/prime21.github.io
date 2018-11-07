.data
	a_arr: .space 400
	space: .asciiz " "
	endl: .asciiz "\n"

.macro print_str(%str)
	la $a0,%str
	li $v0,4
	syscall
.end_macro

.macro print_int(%val)
	move $a0,%val
	li $v0,1
	syscall
.end_macro

.macro read_add(%add)
	li $v0,5
	syscall
	sw $v0,0(%add)
.end_macro

.macro read_reg(%val)
	li $v0,5
	syscall
	move %val,$v0
.end_macro

.macro load_arr(%arr,%x,%reg)
	la $a0,%arr
	add %reg,%x,0
	mul %reg,%reg,4
	add %reg,%reg,$a0

	lw %reg,0(%reg)
.end_macro

.macro save_arr(%arr,%x,%reg)
	la $a0,%arr

	add $a1,%x,0
	mul $a1,$a1,4
	add $a1,$a1,$a0

	sw %reg,0($a1)
.end_macro

.macro return0()
	li $v0,10
	syscall
.end_macro

.text
	read_reg($s1)

	li $t0,0
	la $t1,a_arr
	input_st:
	bge $t0,$s1,input_ed

		read_add($t1)

	add $t0,$t0,1
	add $t1,$t1,4
	j input_st
	input_ed:

	li $t0,0
	for_1_st:
	bge $t0,$s1,for_1_ed

		add $t1,$t0,1
		for_2_st:
		bge $t1,$s1,for_2_ed

			load_arr(a_arr,$t0,$t2)
			load_arr(a_arr,$t1,$t3)

			ble $t2,$t3,if_end

				save_arr(a_arr,$t0,$t3)
				save_arr(a_arr,$t1,$t2)

			if_end:

		add $t1,$t1,1
		j for_2_st
		for_2_ed:

	add $t0,$t0,1
	j for_1_st
	for_1_ed:

	li $t0,0
	prt_st:
	bge $t0,$s1,prt_ed

		load_arr(a_arr,$t0,$t1)
		print_int($t1)
		print_str(space)

	add $t0,$t0,1
	j prt_st
	prt_ed:

	return0()
