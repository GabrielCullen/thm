# Hashing - Crypto 101

## Key Terms

Jargon:

* Plaintext - Data before encryption or hashing
* Encoding - Not a form of encryption, just another way of representing the data
* Hash - A hash is the output of a hash function
* Brute force - Attacking cryptography by trying every different password
* Cryptanalysis - Attacking cryptography by finding a weakness in the underlying maths

**Questions**

	1. Is base64 encryption or encoding?

encoding

## What is a hash function?

Hash functions are different from encryption. There is no key, and they are designed to be very difficult to go from the output back to the input. A hash function essentially takes in data of any size and creates an output of fixed size. Good hashing algorithms will be fast to compute and slow to reverse. Any small change in the input data should cause a large change in the output.

Hashing is used all the time in cyber security, especially in the context of passwords.

A hash collision is when 2 different inputs give the same output. Hash fuctions are designed to try to avoid this, however collisions are not avoidable. This is because there are more possible inputs that there are outputs, this means that some outputs will have more than one input that corresponds to it.

**Questions**

	1. What is the output size in bytes of the MD5 hash function?

16

	2. Can you avoid hash collisions? (Yea/Nay)

Nay

	3. If you have an 8 bit hash output, how many possible hashes are there?

256

## Uses for hashing

Hashing is used for two main purposes in cyber security. To verify integrity of data, or for verifying passwords.

Most webapps need to verify a user's password at somepoint. Instead of storing the hash of the users password, the client can hash their password and then store the password hash on the server. That way the password itself does not need to be stored. The final issue to overcome is that if two users have the same password, then the hashes that will be stored for them are going to be the same. In order to protect against this a salt is added to the passwords. The salt should be randomly generated, be unique to each user and be stored in the database. The salt should be added to either the start or the end of the password before it is hashed, this means that every user will have a different password hash, even if they have the same password.

**Questions**

	1. Crack the hash "d0199f51d2728db6011945145a1b607a" using the rainbow table manually.

I don't have a fkn rainbow table. I'll use hashcat :D
```hashcat -a0 d0199f51d2728db6011945145a1b607a /opt/wordlist/rockyou.txt```
basketball

	2. Crack the hash "5b31f93c09ad1d065c0491b764d04933" using online tools

http://online.crackmyhash.com/
tryhackme

	3. Should you encrypt passwords? Yea/Nay

Nay

## Recognising Password Hashes

Automated hash recognition tools can be handy, but can often get formats incorrect if the hash does not have a prefix. It is important to take into account context when trying to establish the hash type

Unix style hashes are easy to recognise as they hav ea prefix. The standard format is $format$rounds$salt$hash

Windows passwords are hashed using NTLM, which is a variant of md4. They are visually identical to md4 and md5 so context is necessary here

Linux password hashes are stored in /etc/shadow. Normally this file is only readable by root

Windows password hashes are stored in the SAM. Windows attempts to stop regular users from dumping them however tools like mimikatz exist. These hashes are split into NT hashes and LM hashes.

https://hashcat.net/wiki/doku.php?id=example_hashes is a fantastic resource for understanding hash formats.

For lesser known hash types, it may require analysis by length, encoding or research into the application in order to find out the algorithm used to hash these values.

**Questions**

	1. How many rounds does sha512crypt ($6$) use by default?

5000

	2. What's the hashcat example hash (from the website) for Citrix Netscaler hashes?

1765058016a22f1b4e076dccd1c3df4e8e5c0839ccded98ea

	3. How long is a Windows NTLM hash, in characters?

32

## Password Cracking 

Tools like Hashcat and John the Ripper are used in order to crack hashes. Usually this is done by hashing a large quantity of possible passwords from a wordlist and seeing if they match.

Graphics cards excel at the maths involved in cracking hash functions so they can be very good for this purpose, however some hashing algorithms like bcrypt are designed to equalise the time it takes to hash on a GPU with CPU.

**Questions**

	1. Crack this hash: $2a$06$7yoU3Ng8dHTXphAg913cyO6Bjs3K5lBnwq5FJyA6d01pMSrddr1ZG

```sudo /opt/john/run/john hash1.txt --wordlist=/opt/wordlist/rockyou.txt```
85208520

	2. Crack this hash: 9eb7ee7f551d2f0ac684981bd1f1e2fa4a37590199636753efe614d4db30e8e1

```hashcat -a0 -m 1400 hash2.txt /opt/wordlist/rockyou.txt```
haloween

	3. Crack this hash: $6$GQXVvW4EuM$ehD6jWiMsfNorxy5SINsgdlxmAEl3.yif0/c3NqzGLa0P.S7KRDYjycw5bnYkF5ZtB8wQy8KnskuWQS3Yr1wQ0

```sudo /opt/john/run/john hash.txt --wordlist=/opt/wordlist/rockyou.txt```
spaceman

	4. Bored of this yet? Crack this hash: b6b0d451bbf6fed658659a9e7e5598fe

```hashcat -a0 -m 0 hash4.txt /opt/wordlist/rockyou.txt -r /home/gabriel/Submission/rules/OneRuleToRuleThemAll.rule```
funforyou

## Hashing For Integrity Checking

Hashing can be used to check files haven't been changed. If you put the same data in you will get the same data out. It can be used to check the files haven't been modified and ensure that they have downloaded correctly.

HMAC is a method of using cryptograpghic hashing function in order to verify the authenticity and identity of data. HMAC-SHA512 is common for this, they use a secret key and a hashing algorithm in order to produce a hash.

**Questions**

	1. What's the SHA1 sum for the amd64 Kali 2019.4 ISO? http://old.kali.org/kali-images/kali-2019.4/

186c5227e24ceb60deb711f1bdc34ad9f4718ff9

	2. What's the hashcat mode number for HMAC-SHA512 (key = $pass)?

1750