# Encryption - Crypto 101

## Key terms

* Ciphertext - The result of encrypting a plaintext.
* Cipher - A method of encrypting or decrypting data.
* Plaintext - Data before encryption.
* Encryption - Transforming data into a ciphertext using a cipher.
* Encoding - Not a form od encryption, just another form of data representation (Binary, base64).
* Key - Some information that is needed in order to correctly decrypt the ciphertext.
* Passphrase - Seperate to the key, a passphrase is similar to a password and is used to protect a key.
* Asymmetric Encryption - Uses different keys to encrypt and decrypt.
* Symmetric Encryption - Uses the same key to encrypt and decrypt.
* Brute Force - Attacking cryptography by trying every possible key.
* Cryptanalysis - Attacking cryptography by finding a weakness in the underlying maths.

**Questions**

	1. Are SSH keys protected with a passphrase or a password?

Passphrase

## Why is encryption important?

Cryptography is used to protect confidentiality, ensure integrity and ensure authenticity.

In SSH, the client and server establish an encrypted tunnel that cannot be snooped on

Online websites often have certificates of authenticity

Downloaded files can be used to generate a checksum

Whenever data is stored it should be encrypted. It should also be encrypted while it is being transmitted. (PCI-DSS)

**Questions**

	1. What does SSH stand for?

Secure Shell

	2. How do webservers prove their identity?

Certificate

	3. What is the main set of standards you need to comply with if you store or process payment card details?



## Crucial Crypto Maths.

The modulo operator is used fairly often in cryptography. x % y us the remained when X is divided by y.

**Questions**

	1. What's 30 % 5?

0

	2. What's 25 % 7?

4

	3. What's 118613842 % 9091?

3565

## Types of Encryption

Symmetric encryption uses the same key to encrypt and decrypt the data. DES and AES are examples. They tend to use smaller keys and are faster than asymmetric cryptography.

Asymmetric encryption uses a pair of keys, one to encrypt and another to decrypt. RSA and Elliptic Curve Cryptography are both Asymmetric. Normally these keys are referred to as a public and private key. Things encrypted with your public key can only be decrypted by your private key. Asymmetric encryption tends to be slower and uses larger keys than symmetric encryption.

**Questions**

	1. Should you trust DES? Yea/Nay

Nay

	2. What was the result of the attempt to make DES more secure so that it could be used for longer?

Triple DES

	3. Is it ok to share your public key? Yea/Nay

Yea

## RSA - Rivest Shamir Adleman

RSA is based on the mathematically difficult problem of working out the factors of a large number.

Tools for defeating RSA challenges include:

* https://github.com/Ganapati/RsaCtfTool
* https://github.com/ius/rsatool

The key variables that you need to know about for RSA in CTFs are p, q, m, n, e, d, and c.

p and q are large prime numbers.
n is the product of p and q
e and n is the public key
d and n is the private key
m is the message in plaintext
c is the encrypted m

More information can be found at https://muirlandoracle.co.uk/2020/01/29/rsa-encryption/

**Questions**

	1. p = 4391, q = 6659. What is n?

29239669

## Establishing Keys Using Asymmetric Cryptography

A common use of asymmetric cryptography is exchanging keys for symmetric encryption. Asymmetric encryption is slower so for things like HTTPS symmetric encryption is faster, however asymmetric encryption is required in order to establish the symmetric key securely.


In reality, you need a little more cryptography to verify the person you’re talking to is who they say they are, which is done using digital signatures and certificates. A more detailed example of how HTTPS works can be found at https://robertheaton.com/2014/03/27/how-does-https-actually-work/

## Digital Signatures and Certificates

Digital Signatures are a way to prove the authenticity of files. Using asymmetric cryptography, you produce a signature with your private key that can be verified using your public key. As only you should have access to your private key, this proves that you signed the file. 

A simple form of digital signature would be encrypting the document with your private key, and then if someone wanted to verify this signature they would decrypt it with you public key and check if the files match.

Certificates are used for HTTPS to ensure that the web browser knows that it is talking to the correct website. The web server will have a certificate that confirms it is the correct website. Certificates have a chain of trust starting from the root CA (certificate authority). Root CA's are automatically trusted by your Device/OS/Browser and certficates below that are trusted if they are trusted by the root CA. Certificates below that are trusted because they have been issues by someone the root CA trusts. There are long chains of trust.

**Questions**

	1. What company is TryHackMe's certificate issued to?

Cloudflare

## SSH Authentication

By default SSH is authenticated using usernames and passwords in the same way that you would login to the physical machine. SSH can also be configured with key authentication instead which uses public and private keys to prove that the client is a valid and authorised user on the server. By default this will use RSA keys, and a passphrase can be created during generation to encrypt the key. (ssh-keygen)

Private SSH keys are like passwords, they shouldn't be shared. Tools can be used to attack the passphrase in a similar style to password attacks so similar policies must be followed in order to keep the passphrase secure.

The \~/.ssh folder is the default storage place for ssh keys and you can copy your public key into the authorized_keys file in order to add your key for future logins through SSH. Leaving an SSH key in the authorized_keys file can be a useful way to create a backdoor, presuming the current user has login enabled. This technique can also be used to stabilise the shell if required.

**Questions**

	1. What algorithm does the key use?

RSA

	2. Crack the password with John The Ripper and rockyou, what's the passphrase for the key?

sudo /opt/john/run/ssh2john.py idrsa.id_rsa > id.hash3
sudo /opt/john/run/./john id.hash3 --wordlist /opt/wordlist/rockyou.txt --format=ssh

delicious


## Explaining Diffie Hellman Key Exchange

Alice has a private key a
Bob has a private key b
public variables g and n are established
Alice calculates (g^a mod n) and sends this to Bob
Bob calculates (g^b mod n) and sends this to Alice
Alice and Bob both combine their own private keys and end up with (g^a\*b mod n)

Alice and Bob have now generated two identical keys for commuinication, and all data shared publically does not assist an eavesdropper. They need to solve the discreet log problem in order to establish the key.

## PGP, GPG and AES

PGP stands for Pretty Good Privacy. It's software that implements encryption for files, performs digital signing and more.

GPG is an open source implementation of PGP.

AES, sometimes known as Rijndael, stands for Advanced Encryption Standard. It was a replacement for DES.

**Questions**

	1. You have the private key, and a file encrypted with the public key. Decrypt the file. What's the secret word?

gpg --import tryhackme.key
gpg -d message.gpg

Pineapple


## The Future - Quantum Computers and Encryption

While it's unlikely we will have sufficiently powerful quantum computers until around 2030, once these exist both RSA and Elliptic Curve cryptography will be very fast to break. Quantum computers will able to efficiently solve the mathematical problems that these algorithms rely on for their strength.

AES 128 bit is going to be threatened by quantum computers, however AES 256 bit will retain a portion of it's security. Triple DES will also be broken.

The NSA recommends using RSA-3072 or better for asymmetric encryption and AES-256 or better for symmetric encryption.