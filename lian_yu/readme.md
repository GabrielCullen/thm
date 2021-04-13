# Lian_YU

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
Open 10.10.27.116:22
Open 10.10.27.116:21
Open 10.10.27.116:80
Open 10.10.27.116:111
Open 10.10.27.116:46146
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-13 15:24 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 0.00s elapsed
Initiating Ping Scan at 15:24
Scanning 10.10.27.116 [2 ports]
Completed Ping Scan at 15:24, 0.04s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 15:24
Completed Parallel DNS resolution of 1 host. at 15:24, 0.04s elapsed
DNS resolution of 1 IPs took 0.04s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 15:24
Scanning 10.10.27.116 [5 ports]
Discovered open port 80/tcp on 10.10.27.116
Discovered open port 111/tcp on 10.10.27.116
Discovered open port 22/tcp on 10.10.27.116
Discovered open port 21/tcp on 10.10.27.116
Discovered open port 46146/tcp on 10.10.27.116
Completed Connect Scan at 15:24, 0.04s elapsed (5 total ports)
Initiating Service scan at 15:24
Scanning 5 services on 10.10.27.116
Completed Service scan at 15:24, 11.36s elapsed (5 services on 1 host)
NSE: Script scanning 10.10.27.116.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 1.96s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 0.08s elapsed
Nmap scan report for 10.10.27.116
Host is up, received syn-ack (0.040s latency).
Scanned at 2021-04-13 15:24:03 BST for 14s

PORT      STATE SERVICE REASON  VERSION
21/tcp    open  ftp     syn-ack vsftpd 3.0.2
22/tcp    open  ssh     syn-ack OpenSSH 6.7p1 Debian 5+deb8u8 (protocol 2.0)
| ssh-hostkey: 
|   1024 56:50:bd:11:ef:d4:ac:56:32:c3:ee:73:3e:de:87:f4 (DSA)
| ssh-dss AAAAB3NzaC1kc3MAAACBAOZ67Cx0AtDwHfVa7iZw6O6htGa3GHwfRFSIUYW64PLpGRAdQ734COrod9T+pyjAdKscqLbUAM7xhSFpHFFGM7NuOwV+d35X8CTUM882eJX+t3vhEg9d7ckCzNuPnQSpeUpLuistGpaP0HqWTYjEncvDC0XMYByf7gbqWWU2pe9HAAAAFQDWZIJ944u1Lf3PqYCVsW48Gm9qCQAAAIBfWJeKF4FWRqZzPzquCMl6Zs/y8od6NhVfJyWfi8APYVzR0FR05YCdS2OY4C54/tI5s6i4Tfpah2k+fnkLzX74fONcAEqseZDOffn5bxS+nJtCWpahpMdkDzz692P6ffDjlSDLNAPn0mrJuUxBFw52Rv+hNBPR7SKclKOiZ86HnQAAAIAfWtiPHue0Q0J7pZbLeO8wZ9XNoxgSEPSNeTNixRorlfZBdclDDJcNfYkLXyvQEKq08S1rZ6eTqeWOD4zGLq9i1A+HxIfuxwoYp0zPodj3Hz0WwsIB2UzpyO4O0HiU6rvQbWnKmUaH2HbGtqJhYuPr76XxZtwK4qAeFKwyo87kzg==
|   2048 39:6f:3a:9c:b6:2d:ad:0c:d8:6d:be:77:13:07:25:d6 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDRbgwcqyXJ24ulmT32kAKmPww+oXR6ZxoLeKrtdmyoRfhPTpCXdocoj0SqjsETI8H0pR0OVDQDMP6lnrL8zj2u1yFdp5/bDtgOnzfd+70Rul+G7Ch0uzextmZh7756/VrqKn+rdEVWTqqRkoUmI0T4eWxrOdN2vzERcvobqKP7BDUm/YiietIEK4VmRM84k9ebCyP67d7PSRCGVHS218Z56Z+EfuCAfvMe0hxtrbHlb+VYr1ACjUmGIPHyNeDf2430rgu5KdoeVrykrbn8J64c5wRZST7IHWoygv5j9ini+VzDhXal1H7l/HkQJKw9NSUJXOtLjWKlU4l+/xEkXPxZ
|   256 a6:69:96:d7:6d:61:27:96:7e:bb:9f:83:60:1b:52:12 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBPfrP3xY5XGfIk2+e/xpHMTfLRyEjlDPMbA5FLuasDzVbI91sFHWxwY6fRD53n1eRITPYS1J6cBf+QRtxvjnqRg=
|   256 3f:43:76:75:a8:5a:a6:cd:33:b0:66:42:04:91:fe:a0 (EdDSA)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIDexCVa97Otgeg9fCD4RSvrNyB8JhRKfzBrzUMe3E/Fn
80/tcp    open  http    syn-ack Apache httpd
| http-methods: 
|_  Supported Methods: POST OPTIONS GET HEAD
|_http-server-header: Apache
|_http-title: Purgatory
111/tcp   open  rpcbind syn-ack 2-4 (RPC #100000)
| rpcinfo: 
|   program version   port/proto  service
|   100000  2,3,4        111/tcp  rpcbind
|   100000  2,3,4        111/udp  rpcbind
|   100024  1          46146/tcp  status
|_  100024  1          48961/udp  status
46146/tcp open  status  syn-ack 1 (RPC #100024)
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 15:24
Completed NSE at 15:24, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 14.20 seconds
```

```
vigilante

RTy8yhBQdscX
```

    1. Deploy the VM and Start the Enumeration.

No answer needed

    2. What is the web directory you found?

2100

Found using gobuster - found `/island` then `/island/2100`

    3. What is the file name you found?

green_arrow.ticket

Found using gobuster `/island/2100/green_arrow.ticket`

    4. What is the FTP Password

!#th3h00d

`echo RTy8yhBQdscX | base58 -d`

    5. What is the file name with SSH password?

shado

magic number fix on `Leave_me_alone.png` provides the password `password` to use with steghide on `aa.jpg`

    6. user.txt

THM{P30P7E_K33P_53CRET5__C0MPUT3R5_D0N'T}

ssh in as the shade user

    7. root.txt

THM{MY_W0RD_I5_MY_B0ND_IF_I_ACC3PT_YOUR_CONTRACT_THEN_IT_WILL_BE_COMPL3TED_OR_I'LL_BE_D34D}

`sudo pkexec /bin/bash` - for privesc