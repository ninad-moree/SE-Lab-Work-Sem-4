;Name    - Ninad More
;Roll No - 21253
;Subject - MPL
;Title   - Display the five 64 bit Hexadecimal numbers from the user


;for constant variables
section .data
	msg1 db 'Enter five 64 bit numbers:'
	msg1len equ $-msg1
	msg2 db 'You have entered these numbers:'
	msg2len equ $-msg2

;for uninitialised variable
section .bss
	array resd 200                               ;reserve a doubleword(space)
	counter resb 1                               ;reserve a byte
	
section .text
global _start
	_start:
		;display the first msg
		mov rax,1
		mov rdi,1
		mov rsi,msg1
		mov rdx,msg1len
		syscall
		
		;add the numbers to the array
		mov byte[counter],05
		mov rbx,00
			loop1:
				mov rax,0
				mov rdi,0
				mov rsi,array
				add rsi,rbx
				mov rdx,17
				syscall
				add rbx,17
				dec byte[counter]
				JNZ loop1
				
		;display the second msg
		mov rax,1
		mov rdi,1
		mov rsi,msg2
		mov rdx,msg2len
		syscall
		
		;display th stored the numbers
		mov byte[counter],05
		mov rbx,00
			loop2:
				mov rax,1
				mov rdi,1
				mov rsi,array
				add rsi,rbx
				mov rdx,17
				syscall
				add rbx,17
				dec byte[counter]
				JNZ loop2
				
			;exit
			mov rax,60
			mov rdi,0
			syscall			
