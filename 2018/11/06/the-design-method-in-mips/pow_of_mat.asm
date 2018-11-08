.data
	a_mat: .space 100
	r_mat: .space 100
	c_mat: .space 100
	space: .asciiz " "
	space: .asciiz "\n"
.macro print_int(%val)
	li $v0,1
	add $a0,$0,%val
	syscall
.end_macro

.macro print_str(%str)
	la $a0,%str
	li $v0,4
	syscall
.end_macro

.macro read_add(%add)
	li $v0,5
	syscall
	sw $v0,0(%add)
.end_macro

.macro read_reg(%add)
	li $v0,5
	syscall
	moev %reg,$v0
.end_macro

.macro load_mat(%mat,%line,%x,%y,%reg)
	add $a0,%mat
	add %reg,%x,0
	mul %reg,%reg,%line
	add %reg,%reg,%y
	mul %reg,%reg,4
	add %reg,%reg,$a0

	lw %reg,0(%reg)
.end_macro

.macro save_mat(%mat,%line,%x,%y,%reg)
	add $a0,%mat
	add $a1,%x,0
	mul $a1,$a1,%line
	add $a1,$a1,%y
	mul $a1,$a1,4
	add $a1,$a1,$a0

	sw %reg,0($a1)
.end_macro

.text
	read_reg($s1)
	read_reg($s2)

	li $t0,0
	la $t1,
	input_st:
	bge $t0,$s2,input_ed

		read_add($t1)

	add $t0,$t0,1
	add $t1,$t1,4
	j input_st
	input_ed:


	li $t0,0
	li $t1,1
	la $t2,r_mat
	init_st:
	bge $t0,$s2,init_ed

		save_mat($t2,$s2,$t0,$t0,$t1)

	add $t0,$t0,1
	j init_st
	init_ed:

	li $s3,1
	fpm_st:
	ble $s2,$0,fpm_ed

		and $t0,$s3,$s2
		ble $t0,$0,if_ed

			la $a2,r_mat
			la $a3,a_mat
			jal mul

		if_ed:

			la $a2,a_mat
			la $a3,a_mat
			jal mul

	srl $s2,$s2,1
	j fpm_st
	fpm_ed:


	la $t2,r_mat
	li $t0,0
	prt_1_st:
	bge $t0,$s2,prt_1_ed

		li $t1,0
		prt_2_st:
		bge $t1,$s2,prt_2_ed

			load_mat($t2,$s2,$t0,$t1,$t7)
			print_int($t7)
			print_str(space)

		add $t1,$t1,1
		j prt_2_st
		prt_2_ed:
		print_str(endl)

	add $t0,$t0,1
	j prt_1_st
	prt_1_ed:

	return0()

mul:
	push($ra)

	la $s5,c_mat

	li $t5,0
	mul_1_st:
	bge $t5,$s2,mul_1_ed

		li $t6,0
		mul_2_st:
		bge $t6,$s2,mul_2_ed

			li $s4,0

			li $t7,0
			mul_3_st:
			bge $t7,$s2,mul_3_ed

				load_mat($a2,$s2,$t5,$t7,$s6)
				load_mat($a3,$s2,$t7,$t6,$s7)

				mul $s6,$s6,$s7
				add $s4,$s4,$s6

			add $t7,$t7,1
			j mul_3_st
			mul_3_ed

			save_mat($s5,$s2,$t5,$t6,$s4)

		add $t6,$t6,1
		j mul_2_st
		mul_2_ed:

	add $t5,$t5,1
	j mul_1_st
	mul_1_ed:

	li $t5,0
	cp_1_st:
	bge $t5,$s2,cp_1_ed

		li $t6,0
		cp_2_st:
		bge $t6,$s2,cp_2_ed

			load_mat($s5,$s2,$t5,$t6,$t7)
			save_mat($a2,$s2,$t5,$t6,$t7)

		add $t6,$t6,1
		j cp_2_st
		cp_2_ed:

	add $t5,$t5,1
	j cp_1_st
	cp_1_ed

	pop($ra)
	jr $ra
