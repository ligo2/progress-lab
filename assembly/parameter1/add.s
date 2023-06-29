.global my_function
.type my_function, %function
my_function:
	ldr x8, [sp, #0]
	ldr x9, [sp, #8]
	add x0, x0, x1
	add x0, x0, x2
	add x0, x0, x3
	add x0, x0, x4
	add x0, x0, x5
	add x0, x0, x6
	add x0, x0, x7
	add x0, x0, x8
	add x0, x0, x9
	ret
    