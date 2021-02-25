# Linux Fundamentals - Part 1

## Echo
Echo outputs whatever is put into it

**Questions**

    1. How would you output hello without a newline?


echo -n hello

## ls

ls lists information out files/directories in the current directory

**Questions**

    1. What flag outputs all entries


ls -a


    2. What flag outputs things in a "long list" format    

ls -l

## cat

cat outputs the contents of files to the console

**Questions**

    1. What flag numbers all output lines?    

-n

## Touch
Touch is used to create files - touch gabe.txt would create a text file with name gabe

## Binaries

Binaries are executable files that can be created and downloaded

    1. How would you run a binary called hello using the directory shortcut . ?

./hello

    2. How would you run a binary called hello in your home directory using the shortcut ~ ?

\~/hello

	3. How would you run a binary called hello in the previous directory using the shortcut .. ?

../hello


    Create a file "noot.txt" and execute the binary to find the password to shiba2

    4. What's the password for shiba2        

pinguftw

## su

su allows you to switch user without logging out and back in again.

**Questions**

    1. How do you specify which shell is used when you login?    

su -s

