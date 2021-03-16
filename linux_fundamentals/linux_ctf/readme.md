# Linux Challenges

## Introduction

**Questions**

	1. How many visible files can you see in garrys home directory?

3

## The Basics

	1. What is flag 1?

f40dc0cff080ad38a6ba9a1c2c038b2c

	2. What is flag 2?

8e255dfa51c9cce67420d2386cede596

	3. Flag 3 is located where bob's bash history gets stored.

cat .bash_history
9daf3281745c2d75fc6e992ccfdedfcd

	4. Flag 4 is located where cron jobs are created.

crontab -e
dcd5d1dcfac0578c99b7e7a6437827f3

	5. Find and retrieve flag 5.

find / | grep flag 5
cat /lib/terminfo/E/flag5.txt
bd8f33216075e5ba07c9ed41261d1703

	6. "Grep" through flag 6 and find the flag. The first 2 characters of the flag is c9.

cat flag6.txt | grep c9
c9e142a1e25b24a837b98db589b08be5

	7. Look at the systems processes. What is flag 7.

ps -aef
274adb75b337307bd57807c005ee6358

	8. De-compress and get flag 8.

tar -xf flag8.tar.gz
75f5edb76fe98dd5fc9f577a3f5de9bc

	9. By look in your hosts file, locate and retrieve flag 9.

cat /etc/hosts
dcf50ad844f9fe06339041ccc0d6e280.com

	10. Find all other users on the system. What is flag 10.

cat etc/passwd
5e23deecfe3a7292970ee48ff1b6d00c

## Linux Functionality

	1. Run the command flag11. Locate where your command alias are stored and get flag 11.

cat .bash_rc
\#b4ba05d85801f62c4c0d05d3a76432e0

	2. Flag12 is located were MOTD's are usually found on an Ubuntu OS. What is flag12?

/etc/update-motd.d
01687f0c5e63382f1c9cc783ad44ff7f

	3. Find the difference between two script files to find flag 13.

diff script1 script2
3383f3771ba86b1ed9ab7fbf8abab531

	4. Where on the file system are logs typically stored? Find flag 14.

cd /var/log
71c3a8ad9752666275dadf62a93ef393

Can you find information about the system, such as the kernel version etc.

	5. Find flag 15.

cat etc/\*release
a914945a4b2b5e934ae06ad6f9c6be45

	6. Flag 16 lies within another system mount.

not sure about this one, in the media directory seems to be a directory for removable media.
/media/f/l/a/g/1/6/is/
cab4b7cae33c87794d82efa1e7f834e6

	7. Login to alice's account and get flag 17. Her password is TryHackMe123

89d7bce9d0bab49e11e194b54a601362

	8. Find the hidden flag 18.

find / | grep flag18
c6522bb26600d30254549b6574d2cef2

	9. Read the 2345th line of the file that contains flag 19.

sed -n 2345 flag19
490e69bd1bf3fc736cce9ff300653a3b

# Data Representation, Strings and Permissions

	1. Find and retrieve flag 20

base64 -d flag20
02b9aab8a29970db08ec77ae425f6e68alice

	2. Inspect the flag21.php file. Find the flag.

nano flag21.php
strings flag21.php
g00djob

	3. Locate and read flag 22. Its represented as hex.

xxd -r -p flag22
9d1ae8d569c83e03d8a8f61568a0fa7d

	4. Locate, read and reverse flag 23.

rev flag23
ea52970566f4c090a7348b033852bff5

	5. Analyse the flag 24 compiled C program. Find a command that might reveal human readable strings when looking in the machine code code.

strings flag24
hidd3nStr1ng

	6. Flag 25 does not exist.

	7. Find flag 26 by searching the all files for a string that begins with 4bceb and is 32 characters long. 

personally I could not find this file. Research online finds the command
```
find / -xdev -type f -print0 2>/dev/null | xargs -0 grep -E '^[a-z0-9]{32}$' 2>/dev/null
```
4bceb76f490b24ed577d704c24d6955d

	8. Locate and retrieve flag 27, which is owned by the root user.

find flag27 | grep flag27
sudo -l
sudo cat /home/flag27
6fc0c805702baebb0ecc01ae9e5a0db5

	9. Whats the linux kernel version?

uname -r
4.4.0-1075-aws

	10. Find the file called flag 29 and do the following operations on it:

	Remove all spaces in file.
	Remove all new line spaces.
	Split by comma and get the last element in the split.

sed 's/ //g' input.txt > no-spaces.txt
fastidiisuscipitmeaei

## SQL, FTP, Groups and RDP

	1. Use curl to find flag 30.

curl localhost
fe74bb12fe03c5d8dfc245bdd1eae13f

	2. Flag 31 is a MySQL database name.
	MySQL username: root
	MySQL password: hello

SHOW DATABASES;
2fb1cab13bf5f4d61de3555430c917f4

	3. Bonus flag question, get data out of the table from the database you found above!

use database_2fb1cab13bf5f4d61de3555430c917f4
SHOW TABLES;
SELECT * FROM flags;
ee5954ee1d4d94d61c2f823d7b9d733c

	4. Using SCP, FileZilla or another FTP client download flag32.mp3 to reveal flag 32.

Couldn't get SCP to work. Used netcat instead
Tryhackme1337

	5. Flag 33 is located where your personal $PATH's are stored.

cat .profile
547b6ceee3c5b997b625de99b044f5cf

	6. Switch your account back to bob. Using system variables, what is flag34?

env
7a88306309fe05070a7c5bb26a6b2def

	7. Look at all groups created on the system. What is flag 35?

cat /etc/group |grep 35
769afb6

	8. Find the user which is apart of the "hacker" group and read flag 36.

getent group hacker
bob
83d233f2ffa388e5f0b053848caed1eb