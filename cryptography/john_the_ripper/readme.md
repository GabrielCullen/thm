# John The Ripper

## John who?

John the ripper is a hash cracking tool that combines a fast cracking spped with a large range of compatible hash types.

A hash is a one way function that takes in data of any length and returns it in another form of fixed length. This is done by running the data through the hash algorithm. The output cannot be reversed to get the original input.

Even if the algorithm is not feasibly reversible. You can attempt to hash a large list of words and compare the hashed data, if they match then you have worked out the input. This is known as a dictionary attack. John is also capable of performing brute force attacks on a large array of different hash types.

## Wordlists

In order to perform dictionary attacks, a good wordlist needs to be supplied. Rockyou is a good starting point however https://github.com/danielmiessler/SecLists contains a selection of good wordlists for a variety of attacks.

**Questions**

	1. What website was the rockyou.txt wordlist created from a breach on?

rockyou.com

## Cracking Basic Hashes

John has built in features to detect the hash it is given and select appropriate rules and formats to crack it. --wordlist is used to specify the wordlist

Identifying hashes can be tricky, an online resource can be found at https://hashes.com/en/tools/hash_identifier and https://github.com/blackploit/hash-identifier is a handy tool that I use. --format can be used to specify the format of the hash if you know what it is.

**Questions**

	1. What type of hash is hash1.txt?

md5

	2. What is the cracked value of hash1.txt?

biscuit

	3. What type of hash is hash2.txt?

SHA1

	4. What is the cracked value of hash2.txt

kangeroo
	
	5. What type of hash is hash3.txt?

SHA256

	6. What is the cracked value of hash3.txt

microphone

	7. What type of hash is hash4.txt?

Whirlpool

	8. What is the cracked value of hash4.txt

colossal

## Cracking Windows Hashes

Authenticaton hashes are the hashed versions of passwords that are stored by operating systems, it is sometimes possible to crack them through brute-force.

NThash is the hash format that modern windows operating system machines will store user and service passwords in. It is commonly referred to as NTLM.

These hashes can be found in the SAM database on a windows machine by using a tool like Mimikatz or from the Active Directory database: NTDS.dit.

**Questions**

	1. What do we need to set the "format" flag to, in order to crack this?

NT

	2. What is the cracked value of this password?

```
sudo /opt/john/run/john --format=NT --wordlist=/opt/wordlist/rockyou.txt ntlm.txt
```
mushroom

## Cracking etc/shadow Hashes

The /etc/shadow file is the file on Linux machines where password hashes are stored. It stores other information also, and contains one entry per line for each user or user account of the system. Usually this file is only accessible by the root user so high privlages are required to obtain this.

In order to get these passwords into a format suitable for john, it must be combined with /etc/passwd first. John has a built in tool, unshadow that can do this

```
unshadow [path to passwd] [path to shadow] > unshadowed_pass.txt
```

You can submit the whole file or just the relevant lines from each.

The output from unshadow can then be fed directly into John. If a format is required it will be sha512crypt.

**Questions**

	1. What is the root password?

sudo /opt/john/run/john --format=sha512crypt --wordlist=/opt/wordlist/rockyou.txt etchashes.txt

1234

## Single Crack Mode

In this mode, John uses only the information provided in the username to try and work out the password heuristically by modifying the orders of letters/numbers in the username. John does this by using a set of rules that a user can create.

John also has compatibility with the Gecos fields of the UNIX operating system. These are fields displayed in etc/shado, etc/passwd that are seperated by a colon. These may be full names or home directory names that can also be used in the attack.

```
john --single --format=[format] [path to file]
```

If you're cracking hashes in single crack mode, you need to change the file format that you are inputting in order for John to understand how to create the wordlist. Simply add the username (or word) you wish to try to the front of the hash and add a colon.

**Questions**

	1. What is Joker's password?

sudo /opt/john/run/john --single hash7.txt --format=raw-md5

Jok3r

## Custom Rules

You can create your own set of custom rules to use for word mangling. Many organisations have a password policy to try and combat dictionary attacks, however users are very predictable in the way that they follow these rules. Very often a user will capitalise the first letter, or end with 1,2 or 4 digits.

Custom rules are defined in the john.conf file. There are a massive amount of available rules that can be found here https://www.openwall.com/john/doc/RULES.shtml. In all seriousness just find a good ruleset online for this, there is little point in creating your own ruleset at this stage unless you know the end users password habits.

* Az - Append to the word
* A0 - Prepend to the word
* c - Captitalise the character

* [0-9] - Will include numbers 0-9
* [0] - Will include only the number 0
* [A-z] - Will include both upper and lowercase
* [A-Z] - Will include only uppercase letters
* [a-z] - Will include only lowercase letters
* [a] - Will include only a
* [!£$%@] - Will include the symbols !£$%@

Custom rules can be called by using the --rule flag. 


**Questions**

	1. What do custom rules allow us to exploit?

Password complexity predictability

	2. What rule would we use to add all capital letters to the end of the word?

Az"[A-Z]"

	3. What flag would we use to call a custom rule called "THMRules"

--rule=THMRules

## Cracking Password Protected Zip Files

Zip2john is a tool that will convert a zip file into a hash format that john is able to understand.

```
zip2john [options] [zip_file] > output_file
```

We can then feed the outputted file directly into john and attack it how we wish

**Questions**

	1. What is the password for the secure.zip file?

pass123

	2. What is the contents of the flag inside the zip file?

THM{w3ll_d0n3_h4sh_r0y4l}

## Cracking Password Protected RAR Archives

We can use a process similar to the one in the last task to obtain the password for RAR files.

rar2john is a tool that will convert a rar file into a hash format that john will understand.

```
rar2john [rar file] > output_file
```

**Questions**

	1. What is the password for the secure.rar file?

password

	2. What is the contents of the flag inside the zip file?

THM{r4r_4rch1ve5_th15_t1m3}

## Cracking SSH Keys With John

John can be used to crack the password of id_rsa files. These can be used as authentication keys to login over SSH however often while doing so a password will be required. John can help crack this password

ssh2john is another conversion tool that will convert the file into a hash format that john will understand

```
ssh2john [id_rsa_private] > output_file
```
OR
```
python ssh2john.py [id_rsa_private] > output_file
```
The modified file can then be cracked using John

**Questions**

	1. What is the SSH private key password?

mango

## Further Reading

For more information and help using John the Ripper please familiarise yourself with the wiki found here https://www.openwall.com/john/