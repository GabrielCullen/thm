# Introductory Networking


## The OSI Model

The OSI (Open Systems Interconnection) model is used to demonstrate the theory behind computer networking

The OSI model consists of seven layers

7. Application
6. Presentation
5. Session
4. Transport
3. Network
2. Data Link
1. Physical

7. The application layer provides networking options to programs running on a computer. It works primarily with applications. When data is given to the application layer it is passed down to the presentation layer

6. The presentation layer receives data from the application layer. The presentation layer translates the data it has been passed into a standardised format that can be read by the receiving computer. It also can be used to encrypt or compress the data. When this is complete it is passed down to the session layer.

5. The session layer attempts to begin a connection with another machine on the network. If this succeeds, the session layer is tasked with maintaining the session and syncronising communications with the session layer on the receiving computer. The session created is unique - you can make requests to different endpoints at the same time without the data being mixed up. When the session is connected, the data is passed down to the transport layer.

4. The transport layer chooses the protocol that the data is transmitted over. TCP and UDP are the most common protocols that are used.

	1. TCP - Transmission Control Protocol - Tcp is connection-based which means that a connection is established and maintained for the duration of the request. This ensures data is sent at an acceptable speed, and that any lost data is resent.

	2. UDP - User Datagram Protocol - Packets of data are sent to another computer, if the receiving computer can't keep up then that is the receiving computers problem.

TCP is generally used for when accuracy is more important than speed (file transfers, loading a webpage).

UDP is generally used for when speed is more important (video streaming)

When the protocol is selected the transport layer divides the message into smaller pieces (on TCP they are called segments, on USP they're called datagrams). This makes it easier to transmit the message successfully.

3. The network layer is responsible for locating the destination for the request. The network layer takes the IP address for the page and figures out the best route to take. At this stage the layer is still working with Logical addresses which are used to provide order to networks, catagorising them and allowing us to sort through them. (Often in IPV4 format (192.168.1.1))

2. The data link layer is responsible for the physical addressing of the transmission, it's the physical address that determines exactly where to send the information. The data link layer receives a packet from the network layer which includes the IP address of the remote computer, and adds in the MAC address of the revieving endpoint. Every networked computer has a Network Interface Card which comes with a MAC address. 

The MAC address cannot be changed, but it can be spoofed.

The data link layer ensures data is presented in a format suitable for transmission.

Lastly the data link layer ensures that data hasn't been corrupted during transmission, which can happen when transmitted by layer 1, the physical layer.

1. The physical layer is in the hardware of the computer. This is where the electrical pulses that make up the data transfer over a network are sent and received. The physical layer converts the binary transmission of the signals and transmits them over the network, it is also reponsible for translating received signals and converting them into binary data.

**Questions**

1. Which layer would choose to send data over TCP or UDP?

Transport layer

2. Which layer checks received packets to make sure that they haven't been corrupted?

Data link layer

3. In which layer would data be formatted in preparation for transmission?

Data link layer

4. Which layer transmits and receives data?

Physical layer

5. Which layer encrypts, compresses, or otherwise transforms the initial data to give it a standardised format?

Presentation layer

6. Which layer tracks communications between the host and receiving computers?

Session layer

7. Which layer accepts communication requests from applications?

Application layer

8. Which layer handles logical addressing?

Network layer

9. When sending data over TCP, what would you call the "bite-sized" pieces of data?

segments

10. [Research] Which layer would the FTP protocol communicate with?

Application layer

11. Which transport layer protocol would be best suited to transmit a live video?

UDP

## Encapsulation

As data is passed down the model, information specific to the layer in question is added to the start of the transmission. (Network header will add source, dest IP addresses). The data link layer also adds data to the end of the transmission that is used to check for corrupted or tampered data. This process is referred to as encapsulation

Encapsulated data is given a different name at different stages in the process.

Application layer - Data
Presentation layer - Data
Session layer - Data
Transport layer - Segments/Datagrams
Network layer - Packets
Data link layer - Frames
Physical later - Data Stream/Bits

When the message is received by the receiving machine, the steps are completed in reverse, this is called de-encapsulation. Encapsulation allows the method for sending data to be standardised. This means that any device can communicate with any other device, regardless of their software/operating system.

**Questions**

1. How would you refer to data at layer 2 of the encapsulation process (with the OSI model)?

Frames

2. How would you refer to data at layer 4 of the encapsulation process (with the OSI model), if the UDP protocol has been selected?

Datagrams

3. What process would a computer perform on a received message?

de-encapsulation

4. Which is the only layer of the OSI model to add a trailer during encapsulation?

data link layer

5. Does encapsulation provide an extra layer of security?

yes

## The TCP/IP Model

The TCP/IP model is similar to the OSI model, however it only consists of 4 layers, that cover the same range of functions as seen in the OSI model.

4. Application layer - Application, Presentation, Session

3. Transport layer - Transport

2. Internet - Network

1. Network interface - Data link, Physical

The process of encapsulation is still used. At each layer of the TCP/IP model a header is added during encapsulation and removed during de-encapsulation.

TCP/IP takes it's name from Transmission Control Protocol that controls the flow of data between endpoints and the Internet Protocol which controls how packets are addressed and sent.

TCP is a connection based protocol - in order to send data via TCP, a handshake must first be completed between the two computers.

In order to make a connection, the sending computer sends a SYN request to the receiving computer. The receiving computer sends a SYN/ACK request back to the oringinal computer, when this is received the sending computer will send a final ACK back to comfirm that the connection has been established successfully. Thhis is called a three way handshake.

Any data that is lost on transmission is re-sent, meaning data can reliably be shared between the two computers.

TCP/IP was created in 1982 to provide a standard for manufacturers to follow and is still the standard upon which modern networking is based.

**Questions**

1. Which model was introduced first, OSI or TCP/IP?

TCP/IP

2. Which layer of the TCP/IP model covers the functionality of the Transport layer of the OSI model (Full Name)?

Transport

3. Which layer of the TCP/IP model covers the functionality of the Session layer of the OSI model (Full Name)?

Application

4. The Network Interface layer of the TCP/IP model covers the functionality of two layers in the OSI model. These layers are Data Link, and?.. (Full Name)?

Physical

5. Which layer of the TCP/IP model handles the functionality of the OSI network layer?

Internet

6. What kind of protocol is TCP?

Connection based

7. What is SYN short for?

synchronise

8. What is the second step of the three way handshake?

SYN/ACK

9. What is the short name for the "Acknowledgement" segment in the three-way handshake?

ACK

## Wireshark

'''
Frame 1: 142 bytes on wire (1136 bits), 142 bytes captured (1136 bits)
Ethernet II, Src: IntelCor_76:2c:e4 (0c:8b:fd:76:2c:e4), Dst: Technico_e9:bb:16 (a4:91:b1:e9:bb:16)
Internet Protocol Version 4, Src: 192.168.1.151, Dst: 99.86.255.93
Transmission Control Protocol, Src Port: 54646, Dst Port: 80, Seq: 1, Ack: 1, Len: 76
Hypertext Transfer Protocol
'''

Frame 1 - this is showing details from the physical layer of the OSI model 

Ethernet II - this is showing details from the Data Link layer of the OSI model (transmission medium, source and destination MAC addresses)

Internet Protocol Version 4 - this is showing details from the Network layer of the OSI model (source and destination IP addresses)

Transmission Control Protocol - this is showing details from the Transport layer of the OSI model. (protocol, port, etc)

Hypertext Transfer Protocol - this is showing details from the Application layer of the OSI model.

**Questions**

Click on the second captured packet (in the top window) and answer the following questions:

'''
Frame 2: 81 bytes on wire (648 bits), 81 bytes captured (648 bits)
Ethernet II, Src: IntelCor_76:2c:e4 (0c:8b:fd:76:2c:e4), Dst: HuaweiTe_9e:5d:32 (20:0b:c7:9e:5d:32)
Internet Protocol Version 4, Src: 172.16.16.77, Dst: 193.60.169.52
User Datagram Protocol, Src Port: 37578, Dst Port: 53
Domain Name System (query)
'''


1. What is the protocol specified in the section of the request that's linked to the Application layer of the OSI and TCP/IP Models?

Domain name system

2. Which layer of the OSI model does the section that shows the IP address "172.16.16.77" link to (Name of the layer)?

Network

3. In the section of the request that links to the Transport layer of the OSI and TCP/IP models, which protocol is specified?

User Datagram Protocol

4. Over what medium has this request been made (linked to the Data Link layer of the OSI model)?

Ethernet II

5. Which layer of the OSI model does the section that shows the number of bytes transferred (81) link to?

Physical

6. [Research] Can you figure out what kind of address is shown in the layer linked to the Data Link layer of the OSI model?

MAC

# Networking Tools

## Ping

Ping is used to test whether a connection to a remote service is possible.

Ping uses the ICMP protocol, based on TCP/IP.

ping target

Ping is supported by almost all operating systems, and can be used to retrieve IP addresses of websites/computers

**Questions**

1. What command would you use to ping the bbc.co.uk website?

ping bbc.co.uk

2. Ping muirlandoracle.co.uk - What is the IPv4 address?

217.160.0.152

3. What switch lets you change the interval of sent ping requests?

ping -i

4. What switch would allow you to restrict requests to IPv4?

ping -4

5. What switch would give you a more verbose output?

ping -v

## Traceroute

Traceroute is used to map the path that the request makes on the route to the target machine - it allows you to see all the intermediate steps between your computer and the resourse you are targetting.

**Questions**

1. Use traceroute on tryhackme.com - Can you see the path your request has taken?

Yes

2. What switch would you use to specify an interface when using Traceroute?

traceroute -i

3. What switch would you use if you wanted to use TCP SYN requests when tracing the route?

traceroute -T

4. [Lateral Thinking] Which layer of the TCP/IP model will traceroute run on by default (Windows)?

internet

## WHOIS

Whois allows a user to query a domain name and find out who it is registered to. In Europe personal information is redacted, but when used on websites located elsewhere a lot of useful information can be found.

**Questions**

1. Perform a whois search on facebook.com

yes

2. What is the registrant postal code for facebook.com?

94025

3. When was the facebook.com domain first registered?

29/03/1997

4. Perform a whois search on microsoft.com

yes

5. Which city is the registrant based in?

Redmond

6. [OSINT] What is the name of the golf course that is near the registrant address for microsoft.com?

Bellevue Golf Course

7. What is the registered Tech Email for microsoft.com?

msnhst@microsoft.com

## Dig

A url is translatedinto an IP address through the TCP/IP protocol called DNS (Domain Name System)

When a request is made for a website, your computer will first check the cache to see if it already has an IP stored for that website. If not it will send a request to a recursive DNS server. Your router knows where to find these, this server stores popular domains that are cached, however if it is not found here then the recursive server will pass the request to a root name server.

There are 13 root name DNS servers in the world, they keep track of DNS servers in the next level down and redirect you to the appropriate one. These servers are called Top-Level Domain servers.

Top level domain servers are split by extensions - One server handles .com request, another handles .co.uk domains. TLD servers keep track of servers the next level down, when a TLD server receives your request for information, the server passes it down to an appropriate Authoritative name server.

Authoritative name servers store DNS records for domains directly - every domain in the world will have it's records on an authoritative name server somewhere. When your request reaches here, it will send all the relevant information back to you, allowing you to connect to thhe IP address behind the domain that was requested. 

The dig command allows a user to manually query recursive DNS servers for information about domains. It is a very useful tool for network troubleshooting.

The ANSWER section shows the IP address for the domain name that was queried. It also gives the Time To Live of the record. This is how long it will remain stored in the local cache (in seconds).

**Questions**

1. What is DNS short for?

Domain Name System

2. What is the first type of DNS server your computer would query when you search for a domain?

recursive

3. What type of DNS server contains records specific to domain extensions (i.e. .com, .co.uk*, etc)*? Use the long version of the name.

Top Level Domain

4. Where is the very first place your computer would look to find the IP address of a domain?

local cache

5. [Research] Google runs two public DNS servers. One of them can be queried with the IP 8.8.8.8, what is the IP address of the other one?

8.8.4.4

6. If a DNS query has a TTL of 24 hours, what number would the dig query show?

86400