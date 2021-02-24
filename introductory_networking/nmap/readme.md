# Nmap

## Introduction

Proper enumeration should be carried out before any exploit attempts are made. If we have an IP, it is first worth gaining knowledge about the systems we will be attacking. This is done by creating a 'map' using nmap.

Firstly this will perform a port scan. Ports are used to establish network connections to remote webservers - each webserver will be connected to using a different, randomly selected port on your machine. Every computer has 65535 available ports, but many of these are registered as standard ports.

20 - FTP
22 - SSH
23 - Telnet
80 - HTTP
139 - Netbios
443 - HTTPS
445 - SMB

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

- TCP Connect scans (-sT)
- SYN Half-open scans (-sS)
- UDP scans (-sU)

There are several less common scan types

- TCP Null scans (-sN)
- TCP FIN scans (-sF)
- TCP Xmas scans (-sX)

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