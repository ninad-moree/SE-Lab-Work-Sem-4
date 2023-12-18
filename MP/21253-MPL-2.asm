;Name    - Ninad More
;Roll No - 21253
;Subject - MPL
;Title   - To display length of the String

section .data
	msg db 'Enter a string:'
	msglen equ $-msg
	msg2 db 'Length of string is:'
	msg2len equ $-msg2
	
section .bss
	string resb 200
	result resb 200
	
section .text
global _start
	_start:
		;DISPLAY MSG
		mov rax,1
		mov rdi,1
		mov rsi,msg
		mov rdx,msglen
		syscall
		
		;READ THE STRING FROM THE USER
		mov rax,0
		mov rdi,0                                     ;rdi is std i/p or o/p
		mov rsi,string                                ;rsi stores the input given by the user
		mov rdx,200              
		syscall
		
		dec rax
		mov rbx,rax
		mov rdi,result
		mov rcx,16
		
		loop:
			rol rbx,4
			mov al,bl
			and al,0fh
			cmp al,09h
			jg add_37
			add al,30h
			jmp skip
			
		add_37: 
			add al,37h
			
		skip:
			mov[rdi],al
			inc rdi
			dec rcx
			jnz loop
			
		;Display 2nd message
		mov rax,1
		mov rdi,1
		mov rsi,msg2
		mov rdx,msg2len
		syscall
		
		;DISPLAY RESULT
		mov rax,1
		mov rdi,1
		mov rsi,result
		mov rdx,16
		syscall
		
		;exit
		mov rax,60
		mov rdi,0
		syscall
