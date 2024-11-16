bits 32

section .text
	align 4
	dd 0x1badb002
	dd 0x00
	dd - (0x1badb002+0x00)

extern kernelMain
extern csInit
extern ramSetup
extern ramInit
global _start
_start:
	cli
	mov esp, 0x4000
	push ebx
	call csInit
	call ramSetup
	pop ebx
	mov esp, eax
	push ebx
	call ramInit
	pop ebx
	call kernelMain
	hlt

global inport
inport:
	push edx
	mov dx, word[esp+8]
	in al, dx
	pop edx
	ret
	
global outport
outport:
	push eax
	push edx
	mov dx, word [esp+12]
	mov al, byte [esp+16]
	out dx, al
	pop edx
	pop eax
	ret
	
global reboot
reboot:
	int 0x18
	ret
