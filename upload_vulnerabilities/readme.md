# Upload Vulnerabilities

##  Getting Started

Modify etc/hosts with ``` echo "10.10.229.111    overwrite.uploadvulns.thm shell.uploadvulns.thm java.uploadvulns.thm annex.uploadvulns.thm magic.uploadvulns.thm jewel.uploadvulns.thm" | sudo tee -a /etc/hosts
```

When complete run ```sudo sed -i '$d' /etc/hosts```

## Introduction

The ability to upload files to a server has become an integral part of how we interact with web applications. When handled poorly, file uploads can also open up vulnerabilities in the server. These can be minor problems but can lead all the way up to full remote code execution. With unrestricted upload access to a server, an attacker can have effective control over the server. This room will cover various issues/vulnerabilities resulting from improper handling of file uploads including:

* Overwriting existing files on a server
* Uploading and Executing Shells on a server
* Bypassing Client-Side filtering
* Bypassing various kinds of Server-Side filtering
* Fooling content type validation checks

## General Methodology

If we have a file upload point on a site, how do we exploit it?

Firstly enumeration is key. The source code of the page is a good place to start, we can spot client side filtering here. A directory brute forcer like gobuster can also be helpful in web attacks, and may reveal where files are being uploaded to. Intercepting upload requests with Burp can also be helpful and Wappalyser is a helpful extensision.

With an understanding of how the website might be handling our input, we can poke around and see what we can and cannot upload. If the website iss employing client side filtering we can look at the source code in order to find out how to bypass it. If the website has server side filtering, we may have to fuzz the upload to workout what can and cannot be uploaded. Burpsuite and Zap can be very helpful at this stage.

## Overwriting Existing Files

When files are uploaded to the server, a range of checks should be carried out in order to ensure that the file will not overwrite anything that already exists on the server. Common practice is to assign the file a new name when it is uploaded or check if the filename already exists on the server. Web pages should not be writable to the web user thus preventing them from being overwritten.

If no precautions are taken then we might be able to overwrite existing files on the server. Realistically the chances are that file permissions on the server will prevent this however it is worth noting that this can be possible on rare occassions.

Practical

**Questions**

	1. What is the name of the image file which can be overwritten?

mountains.jpg

	2. Overwrite the image. What is the flag you receive?

THM{OTBiODQ3YmNjYWZhM2UyMmYzZDNiZjI5}

## Remote Code Execution

Remote Code Execution will allow us to execute code on the web server. While this is likely to be a low privlaged account, it's still a serious vulnerability. This often occurs when uploading a program in the same language as the back-end of the website (or another language that the server understands). On older services this would usually be PHP, however recently Python Django and Javascript (Node.js) are becoming more common.

The are two basic ways to achieve RCE on a webserver: webshells and reverse shells. Realistically an attacker would prefer a full featured reverse shell however a webshell may be the only option available. In general we want to upload the shell, and then find a way to get the webserver to execute it for us.

#### Web Shells

If we find a webapge with an upload form, we can test uploading standard files. If these can be found on the webserver (through a directory scan with gobuster). If we know the webserver is running with a PHP back-end, we can upload a simple webshell program

```php
<?php
    echo system($_GET["cmd"]);
?>
```

From here we can use execute commands on the webserver machine.

#### Reverse Shells

The process for uploading a reverse shell is pretty much the same. Remember to start a netcat listener on the relevant port first to receive the connection. Form here we can stabilise the shell and escalate privlages.

Practical

**Questions**

	1.Run a Gobuster scan on the website using the syntax from the screenshot above. What directory looks like it might be used for uploads?

/resources

	2. Get either a web shell or a reverse shell on the machine. What's the flag in the /var/www/ directory of the server?

Upload PHP revshell
THM{YWFhY2U3ZGI4N2QxNmQzZjk0YjgzZDZk}

## Filtering

Websitrvers generally have some form of defence against file upload vulnerabilities. Client-side filtering is when the filtering runs in the users browser as opposed to on the server itself. Javascript is usually used as the client side scripting language however alternatives do exist. If the filtering is done client side then (as it is happening on our own computer) it is trivially easy to bypass.

Conversly a server side script will be run on the server. This tends to be more difficult to bypass as you don't have access to the code. As the code is executed on the server, in most cases it will be impossible to bypass the filter completely, instead we have to form a payload which matches the filters in place, but still allows us to execute our code.

*Extension Validation*

File extensions are used to identify the contents of a file. In practice they are easy to change so don't mean much. Windows still uses these to identify file types. Filters that check for extensionss either blacklist extensions (say what extensions are not allowed) or whitelist extensions (say what extensions are allowed).

*File Type Filtering*

File type filtering looks to verify that the contents of the file are acceptable to upload. We'll be looking at two types of file type validation:

* MIME validation - Multipurpose Internet Mail Extension types are used as an identifier for files originally when transferred as attachments over email. The MIME type for a file upload is attached in the header fof the request. They follow the format <\type>/<\subtype>. As an example a jpeg image uploaded will show image/jpeg. As MIME is based on the extension of the file, this is also very easy to bypass.

* Magic Number Validation - Magic numbers are a more accurate way of determining the contents of a file. The magic number is a string of bytes at the beginning of the file which identifies the content. A PNG file will have these bytes ay the top of the file "89 50 4E 47 0D 0A 1A 0A". Unix systems use magic numbers to identify files, and when a file is uploaded the magic numbers can be checked to make sure it is safe to accept. Magic numbers can still be faked however it is still a more effective solution than just checking the extension of a file.

*File Length Filtering*

File length filters are used to prevent huge files from being uploaded. In most cases this should not cause any issues when uploading shells however if our shell is bigger than the maximum file size accepted by the server, we may need to either optimise our shell or find something else to upload.

*File Name Filtering*

Files uploaded to a server should be unique. Usually this is done by adding a random aspect to the file name, however another strategy would be to check if a file with the same name already exists on the server, and give the user an error if so. File names should be sanitised to to ensure that they do not contain any malicious characters. On a well administered system, an uploaded file is unlikely to have the same name it had when it was uploaded.

*File Content Filtering*

More complicated filtering systems may scan the full contents of an uploaded file to ensure that it's not spoofing it's extension. This is more complex than the filters that will be covered in this task.

None of these filters are perfect by themselves, often a combination of filters will be used in order to increase the security.

Different framworks and languages come with their own methods of filtering and validating uploaded files. Language specific exploits may appear that should also be researched and monitored if required.

**Questions**

	1. What is the traditional server-side scripting language?

PHP

	2. When validating by file extension, what would you call a list of accepted extensions (whereby the server rejects any extension not in the list)?

Whitelist

	3. [Research] What MIME type would you expect to see when uploading a CSV file?

text/csv

## Bypassing Client-Side Filtering

There are four easy ways to bypass your average client side file upload filter:

* Turn off Javascript in your browser - This will work provided the website does not require Javascript to provide basic functionality
* Intercept and Modify the incoming page - We intercept the page and strip out the Javascript filter before it has a chance to run.
* Intercept and modify the file upload - Similar to the previous however this allows us to modify the content of the file after it has already passed the filtering
* Send the file directly to the upload point - Posting the data directly to the page which contains the code for handling the file upload is another effective method for completely bypassing a client side filter. ```curl -X POST -F "submit:<value>" -F "<file-parameter>:@<path-to-file>" <site>```

*Practical*

I used method three, uploaded a php reverse shell with the extension changed to .png. Then I sent the POST request to repeater in Burp and changed the file name back to .php, and the MIME type to text/x-php. Sending this request uploaded the PHP reverse shell to the server where it could be executed from the /images directory.

**Questions**

	1. What is the flag in /var/www

THM{NDllZDQxNjJjOTE0YWNhZGY3YjljNmE2}

## Bypassing Server-Side Filtering: File Extensions

Client side filters are easy to bypass, you can see the code for them. For a server side filter, you cannot see or manipulate the code. Using Burp to Fuzz the upload can be useful to determine what extensions are allowed. Basic enumeration and trying different things always provides the attacker with more knowledge about how the code is working in the background.

Often code for server side filters is written uniquely for the task at hand meaning that there is no strategy for all websites. Good enumeration is key to understanding how the filter works and therefore finding out how to bypass it

*Practical*

**Questions**

	1. What is the flag in /var/www/?

Fuzz entensions on the php reverse shell to try and find one that can be uploaded. .php5 could be uploaded and executed to gain a shell.
THM{MGEyYzJiYmI3ODIyM2FlNTNkNjZjYjFl}

## Bypassing Server-Side Filtering: Magic Numbers

Magic Numbers are a string of hex digits and are always the very first thing in a file. Knowing this it's possible to use magic numbers to validate file uploads. 

List of file signatures: https://en.wikipedia.org/wiki/List_of_file_signatures

hexedit can be used in order to manipulate Magic numbers in the file.

*Practical*

**Questions**

THM{MWY5ZGU4NzE0ZDlhNjE1NGM4ZThjZDJh}

## Example Methodology

Begin by looking at the website as a whole. Wsappalyser can be used to gain an understanding of how the website was built. Burpsuite can be used to enumerate this manually and looking for headers such as 'server' or 'x-powered-by' gain also give information about the server. Looking for attack vectors is also worthwhile (upload page)

Examining the source code for an upload page can be used to determine if there are any client side filters as these can be easily bypassed.

Uploading an innocent file can be done in order to establish how our uploaded file is processed. Is it in an uploads folder? How is it named? Tools such as Gobuster can come in handy if the location is not obvious.

If we know how and where our uploads go we can upload a malicious file. We would expect this to be stopped by a server side filter but we can use this to learn more about the website.

* If you can upload a file with an invalid file extension then it is likely the server is using a blacklist. If the upload fails then it is likely using a whitelist.
* Uploading an innocent file, but changing the magic number to be something you would expect to be filtered can tell you if there is a magic number based filter.
* Try uploading an innocent file then modifying the request MIME type with Burpsuite. If the upload fails then the server is filtering by MIME types.
* Enumerating file length filters is a case of uploading a very small file then uploading progressively bigger files until you hit the filter. The error message may tell you the maximum file size. 

## Challenge

Blackbox test - obtain a shell on a machine.

After examining the website, it was noted that there is a client side filter in upload.js
Intercepting this with burpsuite allowed the client side filter to be stripped out.

Gobuster returned some noteworthy directories /admin /modules /content
It turns out uploaded files go directly into content.

Wappalyser shows that this is a NodeJS based website a reverse shell is retrieved. In order to upload this and bypass the server side filter, it must be renamed to rev_shell.jpg.

From here it is in the /content directory, and it can be found by running a gobuster scan with the wordlist provided in the task. The -x flag is used to specify that we are looking for .jpg extensions. 

```
=====================================================
Gobuster v2.0.1              OJ Reeves (@TheColonial)
=====================================================
[+] Mode         : dir
[+] Url/Domain   : http://jewel.uploadvulns.thm/content/
[+] Threads      : 10
[+] Wordlist     : ../UploadVulnsWordlist.txt
[+] Status codes : 200,204,301,302,307,403
[+] Extensions   : jpg
[+] Timeout      : 10s
=====================================================
2021/03/18 12:50:30 Starting gobuster
=====================================================
/ABH.jpg (Status: 200)
/HKX.jpg (Status: 200)
/LKQ.jpg (Status: 200)
/SAD.jpg (Status: 200)
/UAD.jpg (Status: 200)
=====================================================
2021/03/18 12:56:38 Finished
=====================================================
```

Examining all these files in the URL shows that one of them is our reverse shell.
Using the admin page and executing with ../content/'NAME.jpg' caused the shell to be sent back
Navigating to /var/www/ and the flag is found.

**Questions**

	1. Hack the machine and grab the flag from /var/www/

THM{NzRlYTUwNTIzODMwMWZhMzBiY2JlZWU2}