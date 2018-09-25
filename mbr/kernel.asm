use16
org 0x7c00

%include "C:\CGraph\safety\MBR\decompress.asm" ; Include decompressor part

; The decompressor will jump here if it's done
compressorDone:

; Set video mode
mov ax, 13h
int 10h

; Set source address to uncompresed data
mov bx, daddr
mov ds, bx
mov si, uncompressed	

; Get the color table length
mov ah, 0
lodsb

mov bx, 0
mov cx, ax

; Load the color table
setcolor:
	mov dx, 0x3C8
	mov al, bl
	out dx, al
	inc bx
	
	mov dx, 0x3C9
	
	lodsb
	out dx, al
	lodsb
	out dx, al
	lodsb
	out dx, al
	
	loop setcolor

; Set destination address to the video memory
mov bx, 0xA000
mov es, bx
mov di, 0

; Put the pixel data into the video memory
mov cx, 32000
rep movsw

; Let the CPU sleep in an endless loop
halt:
hlt ; No cli, because some emulators may shut down the VM if it's fully halted
jmp halt


; -------------------------------------------
; Constants and extra data for the disk image
; -------------------------------------------

daddr: equ 0x07e0            ; Base address of the data (compressed and uncompressed)
compressed: equ 0x0000       ; Address offset to load the compressed data

times 510 - ($ - $$) db 0    ; Fill the data with zeros until we reach 510 bytes
dw 0xAA55                    ; Add the boot sector signature

comp: incbin "C:\CGraph\safety\MBR\decompressed.bin" ; Include the compressed data (it will go right after the MBR)
compsize: equ $-comp         ; Size of the compressed data

uncompressed: equ compressed+compsize ; Put the uncompressed data right after the compressed data

times 8192 - ($ - $$) db 0   ; Fill the rest of the disk image so it reaches 8192 bytes