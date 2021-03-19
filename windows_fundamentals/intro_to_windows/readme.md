# Intro to Windows

## A Little History

Windows was announced on November 20th, 1985 with a graphical operating system shell. Windows dominates the world in market share and overtook Apple/Mac OS (which was introduced in 1984.)

Windows versions:

* Windows 1
* Windows 2
* Windows 2.x
* Windows 3.x
* Windows 95
* Windows 98
* Windows NT
* Windows XP
* Windows Vista
* Windows 7
* Windows 8.x
* Windows 10

Windows Server versions:

* Windows Server 2003
* Windows Server 2008
* Windows Server 2012 / 2012 R2
* Windows Server 2016
* Windows Server 2019

**Questions**

	1. When was Windows announced?

November 20, 1985

	2. Which is the latest version of Windows?

Windows 10

	3. Which is the latest version of Windows Server?

Windows Server 2019

## Windows File System and Permissions Explained

### What is the file system?

The file system is the method and data structure that the operating system uses to keep track of files on a disk/partition.

Windows file system structure is:
* Logical drives
* Folders
* Files

Folders located on the C drive may have roles, some of these are:
* PerfLogs - Stores the system issues and other reports regarding performance
* Program Files and Program Files (x86) - is the location where programs install unless you change their path
* Users - In the folder the created users are stored. It also stores a users generated data like saving a file on the desktop
* Windows - This folder contains the code to run the operating system and some utility tools.

#### File Permissions

Files permissions can be set by an administrator or higher privileged account. There permissions can be applied to:

* Users
* Groups

Permission that can be set are:

* Full control - allows the user to set the ownership of the folder, set permission for others, modify, read, write, and execute files.
* Modify - allows the user to modify, read, write and execute files
* Read and Execute - allows the user to read and execute files
* List Folder Contents - allows the user to list the contents of a folder
* Read - allows the user to read the files
* Write - allows the user to write data to the specified folder

Permissions can be allowed or denied for users and groups.

To edit permissions for a file or folder, right click on the file and select "Properties". Go to the "Security" tab and click on the "Edit" button.

A user should not have full control permissions on a folder and they could then set permissions and take ownership of the folder without the action of an administrator/privileged user.

A tool you can use to check the files or folder permissions is 'icacls'

This will show permissions in a list for the specified folder

* I - permission inherited from the parent container
* F - full access (full control)
* M - Modify right/access
* OI - object inherit
* IO - inherit only
* CI - container inherit
* RX - read and execute
* AD - append data (add subdirectories)
* WD - write data and add files

Icacls can also be used to check permissions, set ownership of a folder or remove/deny permissions. 

```
icacls C:\Important /setowner Users
```

**Questions**

	1. In which folder are users profiles stored?

Users

## Understanding The Authentication Process

### What is authentication

Authentication is the process of verifying the identity of a person. When you perform authentication the goal is to ensure that the person is who they say they are.

### Local authentication

Local authentication is done using the Local Security Authority (LSA). LSA is a protected subsystem that keeps track of the security policies and the accounts that are on a computer system. It also maintains information about all aspects of local security on a computer.

### Types of Active Directory

There are two types of active directory:
* On-Premise Active Directory (AD)
* Azure Active Directory (AAD)

### Authentication on On-Premise Active Directory

On-Premise active directory has a record of all users, PCs and Servers. It authenticates the users signing in. Once signed in the active directory governs what the user are and are not allowed to do on the system.

In an on-premise active directory environment the authentication can be made by using the following protocols:
* NTLM
* LDAP/LDAPS
* KERBEROS

#### NTLM/NTLM2

NTLM uses a challenge-response sequence of messages between a client and server. While providing authentication, it does not provide data integrity or data confidentiality over the network connection.

#### LDAP/LDAPS

The difference between LDAP and LDAPS is the LDAPS supports encryption. Using LDAP/LDAPS the user's workstation sends the credentials using an API to the Domain Controller in order to validate them and be able to log in.

#### KERBEROS

Another way to authenticate is using Kerberos. Kerberos uses symmetric-key cryptography and requires trusted third-party authorization to verify user identities.

### Authentication on Azure Active Directory

Azure Active Directory is an online authentication store that contains users and groups. Users have a username and password that are used to sign into an application that uses Azure Active Directory for authentication. All of Microsoft Cloud services use this method of authentication.

Azure Active directory supports the following authentication methods.
* SAML (Security Assertion Markup Language)
* OAUTH 2.0
* OpenID Connect

#### SAML (Security Assertion Markup Language)

SAML is a type of Single Sign-On (SSO) standard. It defines a set of rules and protocols that allow users to access web applications with a single login. These applications (Service Providers) all trust the systems that verify users identities (Identify Providers).

* Service Providers - These are the systems and application that users access throughout the day.
* Identity Providers - This would be the system that performs user authentication

#### OAUTH 2.0

OAuth 2.0 is a standard that apps use to provide client application with access. It has four important roles:

* The authorisation server, which is the server that issues the access token
* The resource owner, normally your applications end-user, that grants permission to access the resource server with an access token
* The client, which is the application that requests the access token, and then passes it to the resource server.
* The resource server, which accepts the access token and must verify that it is valid. In this case, this is your application.

#### OpenID Connect

OpenID Connect is an authentication standard built on top of OAuth 2.0. It adds an additional token called an ID token. For this it uses simple JSON Web Tokens (JWT). While OAuth 2.0 is about resource access and sharing, OIDC is all about user authentication.

**Questions**


    1. Which Active Directory is cloud based?

Azure Active Directory

    2. Which authentication method does not provide data integrity?

NTLM

    3. Authentication method that assigns a ticket in order for a user to login?

KERBEROS

    4. Which authentication method allow users to access applications with a single login (short name)?

SAML

    5. Authentication method that uses JSON Web Tokens?

OpenID Connect

## Utility Tools

### Built in utility tools

Windows comes with a variety of utility tools. Some of them are:
* Computer Management
* Local Security Policy
* Disk Cleanup
* Command Line Tools
* Registry Editor

#### Computer Management

Computer Management contains more tools such as:
* Task Scheduler - A tool that allows predefined actions to be automatically executed whenever a certain set of conditions is met.
* Event Viewer - Logs events that happen across the device (Logins/Failures/Errors). Can be used to forward the events to a SSecurity Information and Event Manager which helps the IT team of a company determine possible malicious activities.
* Shared Folders - Is a directory or folder that can be shared across the network and can be accessed by multiple users.
* Local users and computers - Using local users and computers we can create users, and them to built in groups and give the different levels of access
* Performance Monitor - Monitors different activities across the device like CPU usage, memory usage, etc.
* Disk Management - Used to shrink, expand, create new partitions or format partitions
* Services and Applications - Used to check running services on the system and gives you the ability to start, stop or restart them.

#### Local Security Policy

Local Security Policy is a group of settings you can configure to strengthen the computers security. You can set minimum password length, password complexity level and disable guest and local administrator accounts.

#### Disk Cleanup

Disk Cleanup is used to delete files that are no longer needed by the system to save disk space. When running as administrator you can also clean system files.

#### Command Line Tools

Windows comes equipped with command line tools:
* CMD
* Powershell
* Windows Terminal

CMD is the command line interpreter for Windows OS. It is used to automate various system tasks using scripts and batch files. Users can interact with the OS directly through text based commands.

Powershell is basically a more powerful version of CMD. It has more administration capabilities and supports more advanced features, with a more modern shell implementation.

Windows terminal can be used instead of Powershell/CMD but must be installed from the Microsoft Store. Features include tab support, themes and customisation for developers.

#### Registry Editor

Registry Editor can be considered a database that contains low level settings for Windows setting and applications. They are structured as follows:
* HKEY_CLASSES_ROOT
* HKEY_CURRENT_USER
* HKEY_LOCAL_MACHINE
* HKEY_USERS
* HKEY_CURRENT_CONFIG

In Powershell you can browse the registries with 
```cd <REG PATH>```
Windows also has a built-in tool 'reg' that can be used from the command line to add, remove, query, import, export registry keys.

There is also a GUI - Regedit.

## Types of Server

### What is a server?

A server is a piece of hardware or software equipment that provides functionality for other softwares or devices.

### Types of Severs

Severs can be used for a variety of things, the most common ones are:

* Domain Controller - In an AD or AAD infrastructure we can control users, groups, restrict actions, improve security and many more of other computers and servers.
* File Server - Provide a way to share files across devices in a network.
* Web Server - It serves static or dynamic content to a web browser by loading a file from disk and serving it across the network to a user's web browser
* FTP Server - Makes it possible to move one or more files securely between computers while providing file security and organisation as well as transfer control.
* Mail Server - Mail servers move and store mail over corporate networks and across the internet.
* Database Server - A computer system that provides other computers with services relating to accessing and retrieving data from one or more databases.
* Proxy Server - Sits between a client program and an external server to filter requests, improve performance and share connections.
* Application Server - Usually used to connect database servers and the users.

**Questions**

    1. Which can be considered the most important server?

Domain Controller

    2. Which server can store emails?

Mail Server

## Users and Groups Management

In Active Directory user management is done using the **Active directory Users and Computers** tool.

New organisational Units can be created by right clicking and selecting New > organisational unit.

New Users and groups can be created by right clicking an organisational unit and selecting New > User OR New > Group

Right Clicking a User will give an option to add that user to a group

## Creating your first GPO

A Group Policy Object is a feature of an active directory that adds additional controls to user accounts and computers.

To create a GPO we use the **Group Policy Management** tool.

New GPOs can be created by right clicking on Group Policy Objects.

In order to modify what a user can do navigate to Policies > Windows Settings > Security Settings > Local Policies > User Rights Assignment and click on what you would like to modify

Select Define these policy settings > Add user or group > Browse

Relevant users/groups can be searched for here.

Exit the editor and right-click on Domain Controllers OU > Link an existing GPO and select the GPO you created.

To apply the GPO open a CMD as an administrator and run gpupdate /force.