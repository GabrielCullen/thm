# Linux Fundamentals - Part 3

## Advanced File Operations

### cp

cp does the same thing as mv, except instad of moving the file, the file is copied (cp file destination)

### cd and mkdir

cd is used to change directory

mkdir is used to create a new directory

**Questions**

    1. Using relative paths, how would you cd to your home directory.

cd ~

    2. Using absolute paths how would you make a directory called test in /tmp

mkdir /tmp/test

### ln

ln can be used to hard link files. This creates another file that is a duplicate of the original, however any changes made to this file will also have an impact on the original file.

ln -s can be used to create a symbolic link - basically just a reference or pointer to the original file

**Questions**

    1. How would I link /home/test/testfile to /tmp/test

ln /home/test/testfile /tmp/test

### find

find can be used to find files on the system, works recursively so will search deeper down from the start point

find -user (user) will list every file owned by the current user

find -group (group) will list every file owned by the group

**Questions**

    1. How do you find files that have specific permissions?

find -perm

    2. How would you find all the files in /home

find /home

    3. How would you find all the files owned by paradox on the whole system

find / -user paradox

### grep

Grep is used to find data. Generally used with piping but can be supplied a file argument also.

**Questions**

    1. What flag lists line numbers for every string found?

grep -n
 
    2. How would I search for the string boop in the file aaaa in the directory /tmp

grep boop /tmp/aaaa

## Finding shiba4's password

This turned out to be annoying. Finding the binary was not easy, however running this command
```
find / shiba4 | grep shiba4 > log.txt
```
and then using cat to view the log made it possible to clearly see all the possiblilities for the binary, in the end the binary was found in /opt/secret

Running this binary gave shiba4's password

shiba4 password = test1234

## Miscellaneous

### sudo

sudo is basically adminstrator privlages. If a command requires sudo, you will need the administrator password to execute it.

**Questions**

    1. How do you specify which user you want to run a command as.

sudo -u

    2. How would I run whoami as user jen?

sudo -u jen whoami

    3. How do you list your current sudo privileges(what commands you can run, who you can run them as etc.)    

sudo -l

### Adding Users and Groups

In order to do this you must be root, or have adminstrator permissions

In order to add a user - adduser username
In order to add a group - addgroup groupname

To add a user to a group use - usermod -a -G groups\_seperated\_by\_commas user

**Questions**

    1. How would I add the user test to the group test

sudo usermod -a -G test test

### nano (worse vim)

nano is a terminal based text editor. Probably more reasonable to focus on learning vim as this seems to be the industry standard. And if accessing a random server somewhere it is more likely to have vim than nano. Although admittedly it's likely to have both.

### Basic Shell Scripting

Run commands one after the other withhout using operators by using storing the commands in a file with the .sh extension.

Begin the shell script with #!/bin/bash in order to be able to remove the .sh extension and mark the file as executable (chmod 777 file)

### Important Files and Directories

    /etc/passwd - Stores user information - used to see all the users on a system

    /etc/shadow - Has all the passwords of these users

    /tmp - Every file inside it gets deleted upon shutdown - used for temporary files

    /etc/sudoers - Used to control the sudo permissions of every user on the system

    /home - The directory where all your downloads, documents etc are.

    /root - The root user's home directory

    /usr - Where software gets installed 

    /bin and /sbin - Used for system critical files - DO NOT DELETE

    /var - The Linux miscellaneous directory, a myriad of processes store data in /var

    $PATH - Stores all the binaries you're able to run - do not need to provide full file path to execute these commands (ls, whoami,find)

### Installing packages using apt

apt install package_name

Just google what you want and how to install it...

### Processes

View a list of processes using the ps command

ps -ef to view all system processes

processes can be killed with the command kill process_id

top can be used to show processes that are taking up system resources