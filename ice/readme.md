# Ice

## Recon

First I began by running rustscan against the machine. When comparing with an all port nmap scan I noticed nmap had found two additional ports that rustscan missed.

**Questions**

    1. One of the more interesting ports that is open is Microsoft Remote Desktop (MSRDP). What port is this open on?

3389

    2. What service did nmap identify as running on port 8000? (First word of this service)

Icecast

    3. What does Nmap identify as the hostname of the machine? (All caps for the answer)

DARK-PC

## Gain Access

**Questions**

    1. What type of vulnerability is it?

Execute Code Overflow

    2. What is the CVE number for this vulnerability?

CVE-2004-1561

    3. What is the full path for the exploitation module?

`exploit/windows/http/icecast_header`

    4. What is the only required setting which currently is blank?

RHOSTS

Run the metasploit exploit.

## Escalate

    1. What's the name of the shell we have now?

meterpreter

    2. What user was running that Icecast process?

Dark

    3. What build of Windows is the system?

760

    4. First, what is the architecture of the process we're running?

x64

    5. Running the local exploit suggester will return quite a few results for potential escalation exploits. What is the full path (starting with exploit/) for the first returned exploit?

`exploit/windows/local/bypassuac_eventvwr`

Background the current shell and run this exploit, the session option must be provided, in my case this was done through `set session 2`.

    6. We'll have to set one more as our listener IP isn't correct. What is the name of this option?

LHOST

    7. We can now verify that we have expanded permissions using the command `getprivs`. What permission listed allows us to take ownership of files?

SeTakeOwnershipPrivilege

## Looting

We need to move to a process with administrator privileges in order to interact with the lsass service, the service responsible for authentication. The printer spool service is recommended by this task.

**Questions**

    1. What's the name of the printer service?

`spoolsv.exe`

I am going to migrate to `winlogon.exe` instead.

    2. Let's check what user we are now with the command `getuid`. What user is listed?

NT AUTHORITY/SYSTEM

Use `load kiwi` to load a version of mimikatz

    3. Which command allows up to retrieve all credentials?

creds_all

    4. Run this command now. What is Dark's password?

Password01!

## Post Exploitation

    1. What command allows us to dump all of the password hashes stored on the system?

hashdump

    2. While more useful when interacting with a machine being used, what command allows us to watch the remote user's desktop in real time?

screenshare

    3. How about if we wanted to record from a microphone attached to the system?

    record_mic

    4. To complicate forensics efforts we can modify timestamps of files on the system. What command allows us to do this?

timestomp

    5. Mimikatz allows us to create what's called a `golden ticket`, allowing us to authenticate anywhere with ease. What command allows us to do this?

golden_ticket_create

## Extra Credit

In order to gain access without metasploit, an exploit was suggested. I could not get this to work. After a little research I found this [Github repo](https://github.com/ivanitlearning/CVE-2004-1561 "Github") that contained a modified C exploit and a python exploit. With a little bit of tinkering I was able to get both of these exploits to run and gain code execution on the machine.