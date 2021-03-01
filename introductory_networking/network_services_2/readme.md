# Network Services 2

## NFS

### Understanding NFS

Network File System allows a system to share directories and files with others over a network. Users can access files on remote systems as if they were local files. By mounting a portion of the file system on a server, clients can then access this with the relevant permissions.

The client will request to mount a directory from the remote host in the same way you would mount a physical device. The service will connect to the relevant mount daemon using RPC. The server will check if the user has permission to mount the relevant directory and will return a file handle that uniquely identifies everything on the server.

If a client wants to access a file using NFS, an RPC is placed to the daemon on the server. This call takes parameters such as:

* The file handle
* The name of the file to be accessed
* The users userID
* The users groupID

These are used to determine access rights to the specified file.

Using the NFS protocol, you can transfer files between Windows and other operating systems.

**Questions**

	1. What does NFS stand for?

Network File System

	2. What process allows an NFS client to interact with a remote directory as though it was a physical device?

Mounting

	3. What does NFS use to represent files and directories on the server?

file handle

	4. What protocol does NFS use to communicate between the server and client?

RPC

	5. What two pieces of user data does the NFS server take as parameters for controlling user permissions? Format: parameter 1 / parameter 2

user ID / group ID

	6. Can a Windows NFS server share files with a Linux client? (Y/N)

Y

	7. Can a Linux NFS server share files with a MacOS client? (Y/N)

Y

	8. What is the latest version of NFS? [released in 2016, but is still up to date as of 2020] This will require external research.

4.2

### Enumerating NFS

Use nmap -A -p- $IP

Use this command to mount a new NFS share

```
sudo mount -t nfs IP:share /tmp/mount/ -nolock
```

**Questions**

	1. Conduct a thorough port scan scan of your choosing, how many ports are open?

7

	2. Which port contains the service we're looking to enumerate?

2049

	3. Now, use /usr/sbin/showmount -e [IP] to list the NFS shares, what is the name of the visible share?

/home

Time to mount the share to our local machine!

First, use "mkdir /tmp/mount" to create a directory on your machine to mount the share to. This is in the /tmp directory- so be aware that it will be removed on restart.

Then, use the mount command we broke down earlier to mount the NFS share to your local machine. 

	4. Change directory to where you mounted the share- what is the name of the folder inside?

cappucino

Have a look inside this directory, look at the files. Looks like  we're inside a user's home directory...

Interesting! Let's do a bit of research now, have a look through the folders. 

	5. Which of these folders could contain keys that would give us remote access to the server?

```
ls -la
```

.ssh

	6. Which of these keys is most useful to us?

id_rsa

Copy this file to a different location your local machine, and change the permissions to "600" using "chmod 600 [file]".

Assuming we were right about what type of directory this is, we can pretty easily work out the name of the user this key corresponds to.

	7. Can we log into the machine using ssh -i <key-file> <username>@<ip> ? (Y/N)

Y

### Exploiting NFS

Currently I have a low privlage shell on the machine.

By default on NFS shares, root squashing is enabled, preventing anyone who connects to the NFS share from having root access to the NFS volume. If this is turned off, it can allow the creation of SUID bit files, allowing a remote user access to the connected system.

When files have the SUID bit set, the file can be ran with the permissions of the owner/group. If this is a super-user, this can be leveraged to get a shell with root privleges.

The plan is to create a bash shell executable with the SUID bit set execute this and gain a root shell on the server.

This is the full attack

* NFS access
* Low privilege shell
* Upload bash executable to NFS share
* Set SUID permissions through NFS due to misconfigured root squash
* Login through ssh
* Execute SUID bash executable
* Gain root access

**Questions**

First, change directory to the mount point on your machine, where the NFS share should still be mounted, and then into the user's home directory.

Download the bash executable to your Downloads directory. Then use "cp \~/Downloads/bash ." to copy the bash executable to the NFS share. The copied bash shell must be owned by a root user, you can set this using "sudo chown root bash"

Now, we're going to add the SUID bit permission to the bash executable we just copied to the share using "sudo chmod +[permission] bash". 

	1. What letter do we use to set the SUID bit set using chmod?

s

	2. Let's do a sanity check, let's check the permissions of the "bash" executable using "ls -la bash". What does the permission set look like? Make sure that it ends with -sr-x.

```
chmod +s bash
chmod +x bash
```

-rwsr-sr-x

Now, SSH into the machine as the user. List the directory to make sure the bash executable is there. Now, the moment of truth. Lets run it with "./bash -p". The -p persists the permissions, so that it can run as root with SUID- as otherwise bash will sometimes drop the permissions.

```
./bash -p
```

	3. Great! If all's gone well you should have a shell as root! What's the root flag?

THM{nfs_got_pwned}

## SMTP

### Understanding SMTP

Simple Mail Transfer Protocol is utilised to handle the sending of emails. In order to support email services, SMPT protocol is used for outgoing email, and POP/IMAP is used to retrieve incoming emails.

The SMTP server peforms 3 basic functions

* It verifies who is sending emails through the SMTP server
* It send the outgoing mail 
* If the outgoing mail cannot be delivered then it sends a message back to the sender

POP (Post Office Protocol) and IMAP (Internet Message Access Protocol) are both email protocols responsible for transferring emails between a client and a mail server. POP will download the clients inbox from the mail server, IMAP syncronises the current inbox with mail stored on the mail server. Any new emails will be downloaded.

Email delivery functions work as explained here

* The email client or external program connects to the SMTP server of your domain. This initiates the SMTP handshake. This is usually done over the standard SMTP port - 25. Once a connection has been established the SMTP session starts
* The client submits the sender, the recipient, the body of the email and any attachments to the SMTP server.
* The server checks whether the domain name of the recipient and the sender are the same
* The SMTP server of the sender will connect to the recipients SMTP server before relaying the email. If the server cannot be accessed the email is put into a SMTP queue.
* The recipients SMTP server will verify the incoming email, by checking if the domain and user name have been recognised. The server will then forward the email to the relevant POP/IMAP server.
* The email will show up in the recipients inbox.

SMTP is readily available on Windows server platforms, and variants are available to run on Linux

**Questions**

	1. What does SMTP stand for?

Simple Mail Transfer Protocol

	2. What does SMTP handle the sending of?

Emails

	3. What is the first step in the SMTP process?

SMTP handshake

	4. What is the default SMTP port?

25

	5. Where does the SMTP server send the email if the recipient's server is not available?

SMTP queue

	6. On what server does the Email ultimately end up on?

POP/IMAP

	7. Can a Linux machine run an SMTP server? (Y/N)

Y

	8. Can a Windows machine run an SMTP server? (Y/N)

Y


### Enumerating SMTP

Poorly configured or vulnerable mail servers can provide an initial foothold into the network. Metasploit has a module called 'smtp_version' that can be used to determine some information about the SMTP server

The SMTP service has two internal commands that allow the enumeration of users

* VRFY - confirms the names of valid users
* EXPN - reveals the actual address of user's aliases and lists of email.

Using these commands, we can reveal a list of valid users. Metasploit also contains a handy module called smtp_enum that can be handy to use for enumerating SMTP. Also worth considering using smtp-user-enum tool.

**Questions**

	1. First, lets run a port scan against the target machine, same as last time. What port is SMTP running on?

25

	2. Okay, now we know what port we should be targeting, let's start up Metasploit. What command do we use to do this?

msfconsole

	3. Let's search for the module "smtp_version", what's it's full module name?

auxiliary/scanner/smtp/smtp_version

	4. Great, now- select the module and list the options. How do we do this?

options

	5. Have a look through the options, does everything seem correct? What is the option we need to set?

RHOSTS

	6. Set that to the correct value for your target machine. Then run the exploit. What's the system mail name?

polosmtp.home

	7. What Mail Transfer Agent (MTA) is running the SMTP server? This will require some external research.

Postfix

	8. Good! We've now got a good amount of information on the target system to move onto the next stage. Let's search for the module "smtp_enum", what's it's full module name?

auxiliary/scanner/smtp/smtp_enum

	9. What option do we need to set to the wordlist's path?

USER_FILE

	10. Once we've set this option, what is the other essential paramater we need to set?

RHOSTS

	11. Run the exploit. Okay! Now that's finished, what username is returned?

administrator

### Exploiting SMTP

Having gained valuable information from he enumeration stage, including:

* A user account name
* The type of SMTP server and OS runnning
* Only ports 22 (ssh) and 25 (smtp) are open.

Let's try and brutefource the ssh login with Hydra

```
"hydra -t 16 -l administrator -P /opt/wordlist/rockyou.txt -vV 10.10.242.181 ssh"
```

**Questions**

	1. What is the password of the user we found during our enumeration stage?

alejandro

	2. Great! Now, let's SSH into the server as the user, what is contents of smtp.txt

THM{who_knew_email_servers_were_c00l?}

## MySQL

### Understanding MySQL

MySQL is a relational database management system based on structured query language.

The server handles all database instructions such as creating and accessing data. It manages these requests and communicates using the mySQL protocol. This is a client-server communication model.

* MySQL creates a database for storing and manipulating data, defining the relationship of each table.
* Clients make requests by making specific statements in SQL.
* The server will respond to the client with whatever information has been requested

MySQL can run on various platforms, and is commonly used as a backend database. It is an essential component of the LAMP stack (Linux, Apache, MySQL, PHP).

**Questions**

	1. What type of software is MySQL?

Relational Database Management System

	2. What language is MySQL based on?

SQL

	3. What communication model does MySQL use?

client-server

	4. What is a common application of MySQL?

Back end database

	5. What major social network uses MySQL as their back-end database? This will require further research.

Facebook

### Enumerating MySQL

Unlikely to be the first point of attack.

Typically some credentails will be found from enumerating other services, if these don't work on other services (ssh). It may be worth trying them for MySQL.

**Questions**

	1. As always, let's start out with a port scan, so we know what port the service we're trying to attack is running on. What port is MySQL using?

3306

	2. Good, now- we think we have a set of credentials. Let's double check that by manually connecting to the MySQL server. We can do this using the command "mysql -h [IP] -u [username] -p"

mysql -h 10.10.222.79 -u root -p

Okay, we know that our login credentials work. Lets quit out of this session with "exit" and launch up Metasploit.

We're going to be using the "mysql_sql" module.

	3. Search for, select and list the options it needs. What three options do we need to set? (in descending order).

PASSWORD/RHOSTS/USERNAME

	4. Run the exploit. By default it will test with the "select module()" command, what result does this give you?

5.7.29-0ubuntu0.18.04.1

	5. Great! We know that our exploit is landing as planned. Let's try to gain some more ambitious information. Change the "sql" option to "show databases". how many databases are returned?

4

### Exploiting MySQL

We know:

* MySQL server credentials
* The version on MySQL
* The number of databases, and their names

In MySQL, schema is equivalent to database.

We're going to attempt to retrieve hashed passwords from the database

**Questions**

	1. First, let's search for and select the "mysql_schemadump" module. What's the module's full name?

auxiliary/scanner/mysql/mysql_schemadump

	2. Great! Now, you've done this a few times by now so I'll let you take it from here. Set the relevant options, run the exploit. What's the name of the last table that gets dumped?

x$waits_global_by_latency

	3. Awesome, you have now dumped the tables, and column names of the whole database. But we can do one better... search for and select the "mysql_hashdump" module. What's the module's full name?

auxiliary/scanner/mysql/mysql_hashdump

	4. Again, I'll let you take it from here. Set the relevant options, run the exploit. What non-default user stands out to you?

carl

Another user! And we have their password hash. This could be very interesting. 
	
	5. What is the user/hash combination string?

carl:\*EA031893AA21444B170FC2162A56978B8CEECE18

	6. Now, we need to crack the password! What is the password of the user we found?

doggie

Awesome. Password reuse is not only extremely dangerous, but extremely common. What are the chances that this user has reused their password for a different service?

	7. What's the contents of MySQL.txt

THM{congratulations_you_got_the_mySQL_flag}

## Useful links

* https://web.mit.edu/rhel-doc/4/RH-DOCS/rhel-sg-en-4/ch-exploits.html
* https://www.nextgov.com/cybersecurity/2019/10/nsa-warns-vulnerabilities-multiple-vpn-services/160456/