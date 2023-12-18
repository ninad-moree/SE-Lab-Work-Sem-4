;Name    - Ninad More
;Roll No - 21253
;Subject - MPL
;Title   - To display greatest number from given array element

section .data
	array: dq 0xAB34567891012456, 4888885646545595h,7984465111111107h, 34h, 50h


	msg2 db "The largest number is :"
	m2 equ $-msg2

section .bss
	result resb 20
 
section .text
	global _start
	_start:


	mov rsi,array        ;pointing rsi towards the data
	xor rax , rax        ;setting al as current max num which is 0
	mov rcx ,05h         ; setting counter for comparison

	arrloop:
		mov rbx , qword[rsi]  ;moving the 16digit number to rbx
		cmp rbx , rax         ;comparing current array element and max num
		jb update             ;if not greater jump to next loop i.e carry execution on next array element
		mov rax , rbx         ;if found greater then storing it in al i.e updating value of rax

	update:                  ;updating the pointer and counter
		add rsi,08h   ;adding 8 to rsi as we need to move 8bytes forward i.e point to next 16digit number
		dec rcx          
		jnz arrloop


	mov rcx ,16h             ;reinitializing the counter to 16 for conversion (0xA == 10h)
	mov rsi ,result          ;pointing rsi to result
	;mov bl ,al              ;copying ans stored in al to bl for further processing


	hexatoscii:
		rol rax ,04      
		mov dl ,al
		and dl ,0x0F
		cmp dl ,09h
		jbe copydigit
		add dl ,07h

	copydigit:
		add dl ,30h
		mov byte[rsi] ,dl
		inc rsi
		dec rcx
		jnz hexatoscii

	mov rax,01                  ;displaying msg to enter numbers
	mov rdi,01
	mov rsi,msg2
	mov rdx,m2
	syscall


	mov rax,1
	mov rdi,1
	mov rsi,result
	mov rdx,16
	syscall

	mov rax,60
	mov rdx,0
	syscall						
