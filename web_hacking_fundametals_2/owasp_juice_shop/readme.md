# OWASP Juice Shop

## Let's go on an adventure!

Perform reconaissance on the website

**Questions**

	1. What is the administrators email address?

admin@juice-sh.op

	2. What parameter is used for searching? 

q

	3. Question #3: What show does Jim reference in his review? 

Star Trek

## Inject the juice

Generally this task will focus on injection vulnerabilities, specifically sql injection.

**Questions**


	1. Login as the administrator account

32a5e0f21372bcc1000a6088b93b458e41f0e02a

	2. Login as the bender account

fb364762a3c102b2db932069c0e6b78e738d4066

## Who broke my lock

In this section we will be exploiting authentication through different flaws.

**Questions**

	1. Bruteforce the administrator accounts password

c2110d06dc6f81c67cd8099ff0ba601241f1ac0e

(admin password = admin123)

	2. Reset Jim's password

094fbc9b48e525150ba97d05b942bbf114987257

## AH! Don't look!

A web application should store data securely. In some cases the developer may not correctly protect their sensitive data making it vulnerable.

**Questions**

	1. Access the Confidential Document!

edf9281222395a1c5fee9b89e32175f1ccf50c5b

	2. Log into MC SafeSearch's account!

66bdcffad9e698fd534003fbb3cc7e2b7b55d7f0

## Who's flying this thing?

Broken access control can be catagorised into two types.

* Horizontal privilege escalation - Wheen you can perform actions as another user with the same level of permissions
* Vertical privilege escalation - When you can perform actions as another user with a higher level of permissions

**Questions**

	1. Access the administrator page

946a799363226a24822008503f5d1324536629a0

	2. View another users shopping basket

41b997a36cc33fbe4f0ba018474e19ae5ce52121 

	3. Remove all 5 star reviews

50c97bcce0b895e446d61c83a21df371ac2266ef


## Where did that come from?

Cross site scripting is a vulnerability that allows an attack to run javascript in web applications.

	1.  Perform a DOM XSS!

9aaf4bbea5c30d00a1f5bbcfce4db6d4b0efe0bf

	2. Perform a persistent XSS!

149aa8ce13d7a4a8a931472308e269c94dc5f156

	3. Perform a reflected XSS!

23cefee1527bde039295b2616eeb29e1edc660a0