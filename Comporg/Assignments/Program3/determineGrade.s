############################## determineGrade #####################
# Purpose:
#   determineGrade determines the grade of a student based on a 
#   1000 pt scale.  
# Parameters:
#   i 8(%ebp)  int iG1       Grade 1
#   i 12(%ebp) int iG2       Grade 2
#   i 16(%ebp) int iG3       Grade 3
#   i 20(%ebp) int iG4       Grade 4
#   i 24(%ebp) int iG5       Grade 5
#   i 28(%ebp) int iG6       Grade 6
#   i 32(%ebp) int iG7       Grade 7
#   i 36(%ebp) int iG8       Grade 8
#   i 40(%ebp) int iG9       Grade 9
#   i 44(%ebp) int iG10      Grade 10
# Locals:
#   -4(%ebp)  int iqTot
#   -8(%ebp)  int iTot
# Notes:
#   Grade is determined by
#       ??
# Return Value:
#   total grade on a 1000 pt scale
# Register Usage
#   %eax - mostly working register until after .L7 then it works as a return 
	.file	"determineGrade.s"
	.text
.globl determineGrade
	.type	determineGrade, @function
determineGrade:
	pushl	%ebp  # push caller's stack frame ptr            
	movl	%esp, %ebp  # set callee's stack frame ptr      
	pushl	%ebx                # Save the caller's %ebx since we are using %ebx
	call  dumpRegs  
	subl	$20, %esp  # reserve bytes for local
	call  dumpRegs
  movl  %ebp, 0(%esp) #put the buffer to %esp register 
  movl  $64, 4(%esp)  #put 64 bytes 
  movl  $12, 8(%esp)  #
  call  hexDump
	movl	$0, -4(%ebp)   #initialize iqTot to 0   
	movl	8(%ebp), %eax   #put value of iG1 -> %eax   
	addl	12(%ebp), %eax  #add iG2 to iG1 and store it to %eax   
	addl	16(%ebp), %eax  #add iG3 to %eax and store it to %eax     
	movl	%eax, -8(%ebp)   #Store %eax to iTot    
	movl	20(%ebp), %eax   #put value of iG4 -> %eax  
	cmpl	24(%ebp), %eax   #compare iG4 to %iG5   
	jle	.L2                  #jump to .L2 if %eax is less then or equal to iG5  	
	movl	20(%ebp), %eax   #put value of iG4 to %eax   
	addl	%eax, -4(%ebp)   #add %eax to iqTot  
	jmp	.L3                  #jump to .L3   
.L2:                            
	movl	24(%ebp), %eax   #put value of iG5 to %eax
	addl	%eax, -4(%ebp)   #add %eax to iqTot   
.L3:
	movl	28(%ebp), %eax   #put value of iG6 to %eax   
	cmpl	32(%ebp), %eax   #compare %eax to value of iG7  
	jle	.L4                  #jump to .L4 if %eax is less then or equal to iG7   
	movl	28(%ebp), %eax   #put value of iG6 to %eax   
	addl	%eax, -4(%ebp)   #add %eax to iqTot    
	jmp	.L5                  #jump to .L5   
.L4:                            
	movl	32(%ebp), %eax   #put value of iG7 to %eax    
	addl	%eax, -4(%ebp)   #add %eax to iqTot   
.L5:
	cmpl	$0, 36(%ebp)     #compare value of iG8 with 0
	jne	.L6                  #jump to .L6 if value of iG8 is not equal to 0  
	movl	44(%ebp), %eax   #put value of iG10 to %eax   
	movl	%eax, 36(%ebp)   #put %eax to iG8   
.L6:
	cmpl	$0, 40(%ebp)     #compare value of iG9 to 0   
	jne	.L7                  #jump to .L7 if value of iG8 is not equal to 0     
	movl	44(%ebp), %eax   #put value of iG10	to %eax   
	movl	%eax, 40(%ebp)   #put %eax to iG9   
.L7:
	movl	-4(%ebp), %edx   #put iqTot to %edx  
	movl	-8(%ebp), %eax   #put iTot to %eax   
	addl	%edx, %eax       #add iqTot to iTot and store it in %eax  
	addl	36(%ebp), %eax   #add value of iG8 to %eax 
	movl    40(%ebp), %ebx   #put value of iG9 to %ebx  
	sall	$1, %ebx         #arthmetic shift %ebx left by 1 bits   
	addl	%ebx, %eax       #add %ebx and %eax and store it to %eax   
	movl	44(%ebp), %ebx   #put value of iG10 to %ebx   
	leal  	(%ebx,%ebx,2),%ebx #multiply %ebx by 3 and store it to %ebx  ->>> basicaly means (ebx * 2 + ebx)
	add   	%ebx, %eax         #add %ebx and %eax and store it to %eax
	movl  	%eax, -8(%ebp)     #put %eax to iTot 
	addl	$20, %esp        #deallocate  
	popl	%ebx                # restore the caller's ebx
	popl	%ebp             #restore the callee stack frame   
	ret                      #returns   
	.size	determineGrade, .-determineGrade
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
