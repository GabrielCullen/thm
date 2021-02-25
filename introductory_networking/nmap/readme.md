# Nmap

## Introduction

Proper enumeration should be carried out before any exploit attempts are made. If we have an IP, it is first worth gaining knowledge about the systems we will be attacking. This is done by creating a 'map' using nmap.

Firstly this will perform a port scan. Ports are used to establish network connections to remote webservers - each webserver will be connected to using a different, randomly selected port on your machine. Every computer has 65535 available ports, but many of these are registered as standard ports.

```
20 - FTP
22 - SSH
23 - Telnet
80 - HTTP
139 - Netbios
443 - HTTPS
445 - SMB
```
It is possible to alter these standard ports, so it is important that adequate enumeration is done prior to launching any attack.

Nmap connects to each of the ports in turn, depending on how the port responds, it can be registered as Open, Closed or Filtered (firewall). Once the open ports have been established, the services running on each port should be enumerated.

Nmap is the industry standard, with an advanced scripting engine, vulnerability scanning and more functionality than any of it's competitors.

**Questions**

	1. What networking constructs are used to direct traffic to the right application on a server?

Ports

	2. How many of these are available on any network-enabled computer?

65535

	3. [Research] How many of these are considered "well-known"? (These are the "standard" numbers mentioned in the task)

1024

## Nmap Switches

Switches are used to get the most out of nmap, they allow you to specify more advanced options

**Questions**

	1. What is the first switch listed in the help menu for a 'Syn Scan' (more on this later!)?

-sS

	2. Which switch would you use for a "UDP scan"?

-sU

	3. If you wanted to detect which operating system the target is running on, which switch would you use?

-O

	4. Nmap provides a switch to detect the version of the services running on the target. What is this switch?

-sV

	5. The default output provided by nmap often does not provide enough information for a pentester. How would you increase the verbosity?

-v

	6. Verbosity level one is good, but verbosity level two is better! How would you set the verbosity level to two?
    (Note: it's highly advisable to always use at least this option)

-vv


	We should always save the output of our scans -- this means that we only need to run the scan once (reducing network traffic and thus chance of detection), and gives us a reference to use when writing reports for clients.

	7. What switch would you use to save the nmap results in three major formats?

-oA

	8. What switch would you use to save the nmap results in a "normal" format?

-oN

	9. A very useful output format: how would you save results in a "grepable" format?

-oG


    Sometimes the results we're getting just aren't enough. If we don't care about how loud we are, we can enable "aggressive" mode. This is a shorthand switch that activates service detection, operating system detection, a traceroute and common script scanning.

	10. How would you activate this setting?

-A


    Nmap offers five levels of "timing" template. These are essentially used to increase the speed your scan runs at. Be careful though: higher speeds are noisier, and can incur errors!

	11. How would you set the timing template to level 5?

-t5

	12. How would you tell nmap to only scan port 80?

-p 80

	13. How would you tell nmap to scan ports 1000-1500?

-p 1000-1500

	14. How would you tell nmap to scan all ports?

-p-

	15. How would you activate a script from the nmap scripting library (lots more on this later!)?

--script

	16. How would you activate all of the scripts in the "vuln" category?

--script=vuln

# Scan Types

## Overview

When port scanning with nmap, there are three basic scan types
```
- TCP Connect scans (-sT)
- SYN Half-open scans (-sS)
- UDP scans (-sU)
```
There are several less common scan types
```
- TCP Null scans (-sN)
- TCP FIN scans (-sF)
- TCP Xmas scans (-sX)
```
Most of these are used for a similar purpose, however they all work differently.

## TCP Connect Scans

-sT

Perform the TCP/IP three way handshake with each port in turn. Nmap can determine if the port is open or not by the response it receives.

If nmap sends a SYN request to a closed port, the server will respond with a RST (Reset) flag, this tells nmap that the port is closed.

If the request goes to an open port, the server will send a SYN/ACK packet. This allows nmap to confirm the port is open and complete the handshake by sending back an ACK packet.

If nmap receives nothing back, it is likely that a firewall is blocking nmaps connection. Although it is not complicated to set a firewall to respond with a RST packet, meaning it is hard to confirm that an accurate reading has been obtained.

**Questions**

	1. Which RFC defines the appropriate behaviour for the TCP protocol?

RFC 793 - ("... If the connection does not exist (CLOSED) then a reset is sent in response to any incoming segment except another reset.  In particular, SYNs addressed to a non-existent connection are rejected by this means.")

	2. If a port is closed, which flag should the server send back to indicate this?

RST

## SYN scans

-sS

SYN scans function similarly to the TCP connect scan, however instead of completing the handshake, after receiving the SYN/ACK packet from the server an RST packet is sent back.

Older systems look out for three-way handshakes so this can by used to bypass their Intrusion Detection System.

SYN scans may not be logged by applications listening on open ports - standard practice is that established connections are logged.

SYN scans are stealthier and significantly faster than a TCP connect scan.

Sudo permissions are required to perform this as only the root user has the ability to create raw packets.

Unstable services can be brought down by SYN scans.

SYN scans are the default scans used by nmap if ran with sudo permissions, if ran without sudo permissions nmap will use the TCP connect scan.

**Questions**

	1. There are two other names for a SYN scan, what are they?

Half-open, Stealth

	2. Can Nmap use a SYN scan without Sudo permissions?

No

## UDP Scans

-sU

UDP connections are stateless. There is no handshake, and you have to send packets to a target port and hope they are received. 

When a packet is sent to an open UDP port then there should be no response. If this is the case, nmap will refer to the port as (open|filtered) - the port is probably open, but could be firewalled. 

Rarely it can receive a UDP response in which case it will mark the port as open.

If the port is closed the server should send back an ICMP packet that confirms the port is unreachable, nmap will mark these ports as closed.

UDP scans take a very long time, using the --top-ports argument, the user can specify the number of ports they want to check (nmap -sU --top-ports 10 will scan the top 10 most commonly used UDP ports).

To scan UDP ports, nmap usually sends empty requests, for ports that are commonly used for well known services it will send a protocol specific payload that is more likely to elicit a response.

**Questions**

	1. If a UDP port doesn't respond to an Nmap scan, what will it be marked as?

"open\|filtered"

	2. When a UDP port is closed, by convention the target should send back a "port unreachable" message. Which protocol would it use to do so?

ICMP

## NULL, FIN and Xmas

All of these scans are stealthier than a regualar SYN scan.

NULL scans (-sN) involve sending a TCP request with no flags set. The target host should respond with RST if the port is closed.

FIN scans (-sF) work similarly to null scans, except nmap sends a FIN flag (used to close an active connection). If the port is closed nmap will receive a RST flag if the port is closed.

Xmas scans (-sX) send a malformed TCP packet setting the PSH, URG and FIN flags, it expects a RST response from closed ports.

For all these scans, the expected response to an open port is the same. If the port is open then there should be no response to the packet sent, however this is also what we would expect if the port is protected by a firewall. These scans will only identify ports as open\|filtered, closed or filtered.

On Windows it is common for a RST packet to be returned when we send a malformed TCP packet, meaning that all ports will show up as closed.

Many firewalls are configured to drop incoming TCP packets to blocked ports when they contain the SYN flag, by using these scans that do not send SYN flags this type of firewall can be bypassed. When dealing with more modern systems, intrusion defence systems are going to be more capable of recognising these scans and stopping them.

**Questions**

	1. Which of the three shown scan types uses the URG flag?

Xmas

	2. Why are NULL, FIN and Xmas scans generally used?

Firewall evasion

	3. Which common OS may respond to a NULL, FIN or Xmas scan with a RST for every port?

Microsoft Windows

## ICMP Network Scanning

Upon connection to a target network in a black box assignment, it is useful to obtain a map of the network structure - which IP addresses are active and which are not.

A way to do this is by using the ping sweep function within nmap - it will send a ICMP packet to each possible IP address, if it receives a response then it is marked as alive. This is not perfectly accurate, but can provide a good baseline.

To perform a ping sweep use the (-sn) switch. This switch tells nmap not to scan any ports and to rely on ICMP echo packets to identify targets. The switch also sends a SYN to port 443 of the target and an ACK (SYN if not root) packet to port 80 of the target


**Questions**

	1. How would you perform a ping sweep on the 172.16.x.x network (Netmask: 255.255.0.0) using Nmap? (CIDR notation)

nmap -sn 172.16.0.0/16

# NSE Scripts

## Overview

The Nmap Scripting Engine gives nmap considerably more functionality than it has by default. They are written in the *Lua* programming language and do a wide variety of things

Many catagories include:

* safe - Won't affect the target.
* intrusive - Likely to affect the target (crash the machine, demand significant resources)
* vuln - scan for known vulnerabilities.
* exploit - attempt to exploit a vulnerability.
* auth - attempt to bypass authentication for running services (Log on to FTP server anonymously).
* brute - Attempt to brute force credentials for running services.
* discovery - Attempt to query running services for more information about the network.

**Questions**

	1. What language are NSE scripts written in?

Lua

	2. Which category of scripts would be a very bad idea to run in a production environment?

Intrusive

## Working with the NSE

Use scripts by using (--script=vuln)

You can also run single scripts in the same way

You can run multiple scripts seperated by commas

Scripts can have arguments, these are given by using the --script-args command. An example is shown below

```
nmap -p 80 --script http-put --script-args http-put.url='/dav/shell.php',http-put.file='./shell.php'
```

**Questions**

	1. What optional argument can the ftp-anon.nse script take?

maxlist

## Searching for Scripts

In order to find relevant scripts you can check the nmap website (https://nmap.org/nsedoc/) or examing the /usr/share/nmap/scripts folder, which is where nmap checks to find scripts it is going to use

Navigating to /usr/share/nmap/scripts/script.db there is a file that contains formatted text of all the scripts available. Using the grep command, it is possible to find scripts that may be relevant for a particular task. (grep "ftp" /usr/share/nmap/scripts/script.db)

Scripts can be manually installed from Nmap 

```
sudo wget -O /usr/share/nmap/scripts/<script-name>.nse https://svn.nmap.org/nmap/scripts/<script-name>.nse

nmap --script=updatedb
```

**Questions**

Search for "smb" scripts in the /usr/share/nmap/scripts/ directory using either of the demonstrated methods.

	1. What is the filename of the script which determines the underlying OS of the SMB server?

smb-os-discovery.nse

	2. Read through this script. What does it depend on?

smb-brute

# Firewall evasion

It has already been established that stealth scans can be used to attempt to get around a firewall.

A windows host with a default firewall will block all ICMP packets. As nmap uses ping to establish whether the target is alive this presents a problem, by default nmap will think this host is dead and will not attempt to scan it.

-Pn tells nmap to not bother pinging the host before scanning it. Nmap will always treat the host as alive in this instance. If the host acutally is dead, nmap will waste a lot of time actively checking every port.

Other switches that can be useful for firewall evasion include

* -f - Used to fragment the packets making it less likely that the packets will be detected by the firewall or other intrusion detection system.

* -- mtu (number) - works like -f but you can set the maximum size of the packets, this must be done in multiples of 8

* --scan-delay (time) - This adds a delay (in ms) between the packets that are being sent. This is useful if the network is unstable, but also for evading time based firewalls

* --badsum - this is used to generate an invalid checksum for packets. A TCP/IP stack will drop this packet, but a firewall may respond automatically without checking the checksum. This can be used to esablish the presence of a firewall.

**Questions**

	1. Which simple (and frequently relied upon) protocol is often blocked, requiring the use of the -Pn switch?

ICMP

	2. [Research] Which Nmap switch allows you to append an arbitrary length of random data to the end of packets?

--data-length

# Practical

**Questions**

	1. Does the target (10.10.72.42)respond to ICMP (ping) requests (Y/N)?

```
sudo nmap -PE 10.10.72.42
[sudo] password for gabriel: 
Starting Nmap 7.80 ( https://nmap.org ) at 2021-02-25 16:24 GMT
Note: Host seems down. If it is really up, but blocking our ping probes, try -Pn
Nmap done: 1 IP address (0 hosts up) scanned in 2.11 seconds

```

N

	2. Perform an Xmas scan on the first 999 ports of the target -- how many ports are shown to be open or filtered?

```
sudo nmap -sX -p 1-999 -Pn 10.10.72.42 -vv
Starting Nmap 7.80 ( https://nmap.org ) at 2021-02-25 16:32 GMT
Initiating Parallel DNS resolution of 1 host. at 16:32
Completed Parallel DNS resolution of 1 host. at 16:32, 0.04s elapsed
Initiating XMAS Scan at 16:32
Scanning 10.10.72.42 [999 ports]
XMAS Scan Timing: About 15.52% done; ETC: 16:35 (0:02:49 remaining)
XMAS Scan Timing: About 30.08% done; ETC: 16:36 (0:02:22 remaining)
XMAS Scan Timing: About 45.10% done; ETC: 16:36 (0:01:51 remaining)
XMAS Scan Timing: About 60.11% done; ETC: 16:35 (0:01:20 remaining)
XMAS Scan Timing: About 75.13% done; ETC: 16:35 (0:00:50 remaining)
Completed XMAS Scan at 16:35, 201.28s elapsed (999 total ports)
Nmap scan report for 10.10.72.42
Host is up, received user-set.
All 999 scanned ports on 10.10.72.42 are open|filtered because of 999 no-responses

Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 201.40 seconds
           Raw packets sent: 1998 (79.920KB) | Rcvd: 0 (0B)
```

999

	3. There is a reason given for this -- what is it?
	Note: The answer will be in your scan results. Think carefully about which switches to use -- and read the hint before asking for help!

no response

	4. Perform a TCP SYN scan on the first 5000 ports of the target -- how many ports are shown to be open?

```
sudo nmap -sS -p 1-5000 10.10.72.42 -Pn -vv
[sudo] password for gabriel: 
Starting Nmap 7.80 ( https://nmap.org ) at 2021-02-25 16:52 GMT
Initiating Parallel DNS resolution of 1 host. at 16:52
Completed Parallel DNS resolution of 1 host. at 16:52, 0.03s elapsed
Initiating SYN Stealth Scan at 16:52
Scanning 10.10.72.42 [5000 ports]
Discovered open port 80/tcp on 10.10.72.42
Discovered open port 53/tcp on 10.10.72.42
Discovered open port 3389/tcp on 10.10.72.42
Discovered open port 21/tcp on 10.10.72.42
Discovered open port 135/tcp on 10.10.72.42
Completed SYN Stealth Scan at 16:52, 14.46s elapsed (5000 total ports)
Nmap scan report for 10.10.72.42
Host is up, received user-set (0.034s latency).
Scanned at 2021-02-25 16:52:09 GMT for 14s
Not shown: 4995 filtered ports
Reason: 4995 no-responses
PORT     STATE SERVICE       REASON
21/tcp   open  ftp           syn-ack ttl 127
53/tcp   open  domain        syn-ack ttl 127
80/tcp   open  http          syn-ack ttl 127
135/tcp  open  msrpc         syn-ack ttl 127
3389/tcp open  ms-wbt-server syn-ack ttl 127

Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 14.60 seconds
           Raw packets sent: 10005 (440.220KB) | Rcvd: 15 (660B)

```

5

	5. Open Wireshark and perform a TCP Connect scan against port 80 on the target, monitoring the results. Make sure you understand what's going on.

Sure...

	6.Deploy the ftp-anon script against the box. Can Nmap login successfully to the FTP server on port 21? (Y/N)

```
sudo nmap --script=ftp-anon -p 21 10.10.156.6 -Pn -vv
Starting Nmap 7.80 ( https://nmap.org ) at 2021-02-25 17:19 GMT
NSE: Loaded 1 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 1) scan.
Initiating NSE at 17:19
Completed NSE at 17:19, 0.00s elapsed
Initiating Parallel DNS resolution of 1 host. at 17:19
Completed Parallel DNS resolution of 1 host. at 17:19, 0.04s elapsed
Initiating SYN Stealth Scan at 17:19
Scanning 10.10.156.6 [1 port]
Discovered open port 21/tcp on 10.10.156.6
Completed SYN Stealth Scan at 17:19, 0.13s elapsed (1 total ports)
NSE: Script scanning 10.10.156.6.
NSE: Starting runlevel 1 (of 1) scan.
Initiating NSE at 17:19
Completed NSE at 17:19, 30.21s elapsed
Nmap scan report for 10.10.156.6
Host is up, received user-set (0.068s latency).
Scanned at 2021-02-25 17:19:04 GMT for 31s

PORT   STATE SERVICE REASON
21/tcp open  ftp     syn-ack ttl 127
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_Can't get directory listing: TIMEOUT

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 1) scan.
Initiating NSE at 17:19
Completed NSE at 17:19, 0.00s elapsed
Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 30.61 seconds
           Raw packets sent: 1 (44B) | Rcvd: 1 (44B)

```

Yes