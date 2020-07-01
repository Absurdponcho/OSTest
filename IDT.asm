
%macro PUSHALL 0
	push rax
	push rcx
	push rdx
	push r8
	push r9
	push r10
	push r11
%endmacro

%macro POPALL 0
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rax

%endmacro

	[extern irq0_handler]
irq0:
	PUSHALL
	call irq0_handler
	POPALL
	iretq
	GLOBAL irq0

	[extern _idt_]
idtDescriptor:
	dw 4095
	dq 0
	GLOBAL idtDescriptor

InitIDT:

	lidt[idtDescriptor]
	sti
	
	ret
	GLOBAL InitIDT