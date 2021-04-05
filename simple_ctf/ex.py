#!/usr/bin/env python3

import hashlib
import sys

f = open(sys.argv[1],'r',encoding='utf-8')
contents = f.readlines()
salt='1dac0d92e9fa6bb2'
password='0c01f4468bd75d7a84c7eb73846e8d96'

#count=0
#contents=salt+contents
for line in contents:
	line2 = salt+line
	line2 = line2.strip()
	#if hashlib.md5(str(salt) + line).hexdigest() == password:
	possible_pass = hashlib.md5(line2.encode())
	if possible_pass.hexdigest() == password:
		print("Password Cracked: " + line)
		break