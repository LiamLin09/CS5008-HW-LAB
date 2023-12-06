# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans: we are setting up the frame for the main function.
	pushq %rbp			# pushq %rbp: saves the pointer value onto the stack.
	movq  %rsp, %rbp		# movq  %rsp, %rbp: move eight bytes values from %rsp register into the %rbp register.

					# (2) What is going on here
					# Ans:
	movq $1, %rax			# movq $1, %rax: moves the constant value 1 into the %rax register.
					# setting the syscall number for sys-write.
	movq $1, %rdi			# movq $1, %rdi: %rdi is used to specify the file descriptor.
					# 1 is the file descriptor for standard output.
	leaq .hello.str,%rsi		# leaq .hello.str,%rsi: load effective address from .hello.str into %rsi register.


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: enable users to request a service from the operating system.
					# to execute a system call, the execution of the process is halted,
					# and the execution of the system call starts in kernel mode.
	syscall				# Which syscall is being run?
					# Ans: sys-write is being run.
					# it writes to a file descriptor, it is specified by the constant value 1 in %rax.

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: I think we can use printf to achieve this.

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans: the command is sys_exit to terminates the program.
					# movq $60, %rax: the syscall number for sys_exit which is 60 is set to %rax.
					# movq	$0, %rdi: %rdi holds the exit status. 
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: 13 means the size in bytes of the string "hello world".
					# 12 characters + 1 for the new line = 13 in total.
