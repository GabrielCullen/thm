# Active Directory Basics

## Introduction

Active directory is the directory service for Windows Domain Networks. It is a vital skill to understand when attacking Windows.

#### What is Active Directory

Active Directory is a collection of machines and servers connected inside of domains, that are a part of a bigger forest of domains, that make up the Active Directory network. In this document the following Active Directory components will be covered

* Domain Controllers
* Forests, Trees, Domains
* Users and Groups
* Trusts
* Policies
* Domain Services

#### Why use Active Directory?

The majority of large companies use Active Directory because it allows for the control and monitoring of their users computers through a single domain controller. A single user can sign in to any computer on the network and will have access to their files/folders on the server as well as the local storage on that machine. Instead of setting up multiple users on a single machine, the active directory will sort it all out for you.

## Physical Active Directory

The physical Active Directory is the servers and machines on site. These can be anything from domain controllers and storage servers to domain user machines, basically everything needed for an Active Directory environment minus the software.

#### Domain Controllers

A domain controller is a Windows server that has Active Directory Domain Services (AD DS) installed and has been promoted to a domain controller in the forest. Domains controllers are the centre of the Active Directory as they control the rest of the Domain. Thee domain controller carries out the following tasks:

* Holding the AD DS data store
* Handles authentication and authorisation services
* Replicated updates from other domain controllers in the forest
* Allows admin access to manage domain resources

#### AD DS Data Store

The Active Directory Data Store holds the databases and processes needed to store and manage directory information such as users, groups, and services. The contents and characteristics of an AS DS data store include:

* Contains a NTDS.dit - A database that contains all of the information of an Active Directory domain controller as well as password hashes for domain users
* Stored by default in %SystemRoot%\NTDS
* Accessible only by the domain controller

**Questions**

    1. What database does the AD DS contain?

NTDS.dit

    2. Where is the NTDS.dit stored?

SystemRoot%\NTDS

    3. What type of machine can be a domain controller?

Windows Server

## The Forest

The forest is what defines everything, it's the container that holds all of the other bits and pieces of the network together. A forest is a way of describing the connection created between these trees and domains by the network.

#### Forest Overview

A forest is a collection of one or more domain trees inside of an Active Directory network. It is what categorises the parts of the network as a whole. The forest consists of these parts:

* Trees - A hierarchy of domains in Active Directory Domain Services
* Domains - Used to group and manage objects
* Organisational Units (OUs) - Containers for groups, computers, users, printers and other OUs
* Trusts - Allows users to access resources in other domains
* Objects - Users, Printers, Computers, Shares
* Domain Services - DNS Server, LLMNR, IPv6
* Domain Schema - Rules for object creation

**Questions**

    1. What is the term for a hierarchy of domains in a network?

tree

    2. What is the term for the rules for object creation?

Domain Schema

    3. What is the term for containers for groups, computers, users, printers, and other OUs?

Organisational Units

## Users and Groups

The users and groups that are inside an Active Directory are up to you, a domain controller comes with default groups and two default users, Administrator and Guest. It is up to you to create new users and create new groups to add users to.

#### Users Overview

Users are the core to the Active Directory. There can be more depending on how a company manages it's permissions, however there are four main types of users:

* Domain Admins - This is the boss, they control the domains and are the only ones with access to the domain controller.
* Service Accounts (Can be Domain Admins) - Generally not used except for service maintenance, they are required by Windows for services such as SQL to pair a service with a service account.
* Local Administrators - These users can make changes to local machines as an administrator and may even be able to control other users. They cannot access the domain controller.
* Domain Users - These are generic users. They can log in on the machines they have the authorisation to access and may have local administrator rights to machines depending on the organisation.

#### Groups Overview

Groups make it easier to give permissions to users and object by organising them into groups with specified permissions. There are two types of Active Directory groups:

* Security Groups - These groups specify permissions for a large number of users
* Distribution Groups - These groups are used to specify email distribution lists. 

#### Default Security Groups

There are a lot of default security groups. This is a brief outline of them:

* Domain Controllers - All domain controllers in the domain
* Domain Guests - All domain guests
* Domain Users - All domain users
* Domain Computers - All workstations and servers joined to the domain
* Domain Admins - Designated administrators of the domain
* Enterprise Admins - Designated administrators of the enterprise
* Schema Admins - Designated administrators of the schema
* DNS Admins - DNS Administrators Group
* DNS Update Proxy - DNS clients who are permitted to perform dynamic updates on behalf of some other clients (such as DHCP servers).
* Allowed RODC Password Replication Group - Members in this group can have their passwords replicated to all read-only domain controllers in the domain
* Group Policy Creator Owners - Members in this group can modify group policy for the domain
* Denied RODC Password Replication Group - Members in this group cannot have their passwords replicated to any read-only domain controllers in the domain
* Protected Users - Members of this group are afforded additional protections against authentication security threats. See http://go.microsoft.com/fwlink/?LinkId=298939 for more information.
* Cert Publishers - Members of this group are permitted to publish certificates to the directory
* Read-Only Domain Controllers - Members of this group are Read-Only Domain Controllers in the domain
* Enterprise Read-Only Domain Controllers - Members of this group are Read-Only Domain Controllers in the enterprise
* Key Admins - Members of this group can perform administrative actions on key objects within the domain.
* Enterprise Key Admins - Members of this group can perform administrative actions on key objects within the forest.
* Cloneable Domain Controllers - Members of this group that are domain controllers may be cloned.
* RAS and IAS Servers - Servers in this group can access remote access properties of users

**Questions**

    1. Which type of groups specify user permissions?

Security Groups

    2. Which group contains all workstations and servers joined to the domain?

Domain Computers

    3. Which group can publish certificates to the directory?

Cert Publishers

    4. Which user can make changes to a local machine but not to a domain controller?

Local Administrator

    5. Which group has their passwords replicated to read-only domain controllers?

## Trusts and Policies

Trusts and policies go hand in hand to help the domain and trees communicate with each other and maintain security inside of the network. They put the rules in place of how the domains inside of a forest can interact with each other, how an external forest can interact with the forest, and the overall domain rules or policies that a domain must follow.

#### Domain Trusts Overview

Trusts are a mechanism in place for users in the network to gain access to other resources in the domain. Trusts basically outline the way that the domains in the forest communicate with each other. Trusts can also be extended out to external domains and even forests in some cases.

There are two types of trusts that determine how the domains communicate:
* Directional - The direction of the trust flows from a trusting domain to a trusted domain
* Transitive - The trust relationship expands beyond two domains to include other trusted domains

The type of trusts put in place determine how domains and trees in the forest are able to communicate with each other. Sometimes these trusts can be abused to move laterally throughout the network.

#### Domain Policies Overview

Policies dictate how the server operates and what rules the Active Directory will and will not follow. The policies apply do the domain as a whole. Along with a large amount of domain policies, domain admins can choose to add in their own policies not already on the domain controller. The options for domain policies are almost endless and it is important for an attacker to understand these when enumerating an Active Directory network.

**Questions**

    1. What type of trust flows from a trusting domain to a trusted domain?

Directional

    2. What type of trusts expands to include other trusted domains?

Transitive

## Active Directory Domain Services and Authentication

The Active Directory domain services are the core functions of an Active Directory Network. This is how the domain controller decides what it wants to do and what services it wants to provide for the domain.

#### Domain Services Overview

Domain services are services that the domain controller provided to the rest of the domain or tree. There are a wide range of services however only the default domain services will be covered here:
* LDAP - Lightweight Directory Access Protocol; provides communication between applications and directory services
* Certificate Services - allows the domain controller to create, validate, and revoke public key certificates
* DNS, LLMNR, NBT-NS - Domain Name Services for identifying IP hostnames

#### Domain Authentication Overview

The most important part of the active directory are the authentication protocols set in place. There are two main types of authentication, NTLM and Kerberos:
* NTLM - default Windows authentication protocol uses an encrypted challenge/response protocol
* Kerberos - The default authentication service for Active Directory uses ticket-granting tickets and service tickets to authenticate users and give users access to other resources across the domain.

The Active Directory domain services are the main access point for attackers and contain some of the most vulnerable protocols for Active Directory.

**Questions**

    1. What type of authentication uses tickets?

Kerberos

    2. What domain service can create, validate, and revoke public key certificates?

Certificate services

## AD In The Cloud

Recently Active Directory has been pushing companies to cloud networks. The most notable AD cloud provider is Azure AD. It's default settings are much more secure than an on-premise physical Active Directory network, but the cloud may still have vulnerabilities in it.

#### Azure AD Overview

Azure acts as the middle man between your physical Active Directory and your users sign on. This allows for a more secure transaction between domains, making a lot of Active Directory attacks ineffective.

#### Cloud Security Overview

The best way to show you how the cloud takes security precautions past what is already provided with a physical network is to show you a comparison with a cloud Active Directory environment:

| Windows Server AD | Azure AD    |
| ----------------- | ------ |
|               LDAP|Rest APIs|
|               NTLM| OAuth/SAML|
|           Kerberos|OpenID|
|            OU Tree|Flat Stucture|
|Domains and Forests|Tenants|
|             Trusts|Guests|

**Questions**

    1. What is the Azure AD equivalent of LDAP?

Rest APIs

    2. What is the Azure AD equivalent of Domains and Forests?

Tenants

    3. What is the Windows Server AD equivalent of Guests?

Trusts

## Hands on Lab

Use Active Directory and Powershell to enumerate a Forest. [PowerView Cheat Sheet](https://gist.github.com/HarmJ0y/184f9822b195c52dd50c379ed3117993 "Github")

**Questions**


    1. What is the name of the Windows 10 operating system?
`Get-NetComputer -fulldata |select operatingsystem`

Windows 10 Enterprise Evaluation    

    2. What is the second "Admin" name?
`Get-NetUser`

Admin2

    3. Which group has a capital "V" in the group name?

`Get-NetGroup`
Hyper-V Administrators

    4. When was the password last set for the SQLService user?
`Get-NetUser | select name`

`Get-NetUser -Username SQLService`

5/13/2020 8:26:58 PM