# Linux Fundamentals - Part 2

SSH is the act of remotely accessing a machine.  It allows you to remotely execute commands.

Putty can be used on Windows as an equivalent.

## Linux Operators

### &&

&& means and. It allows you to execute two commands back to back, but only if the first one completes successfully. 

ls && echo toothpick will run the ls command, and then output toothpick upon completion.

### &

& backgrounds the current command. The command will still execute but you can run other commands while waiting for that particular command to finish.</p>

### $
The dollar sign is used to denote environment variables. Some are already set up by the computer/OS ($USER will return the user) but as a user you can create your own. Can be handy to export victim machines ip to a variable in order to quickly access it when needed. </p>

#### How would you set nootnoot equal to 1111

export nootnoot=1111

#### What is the value of the home environment variable

/home/shiba2

### |

The pipe is used to take the output of a command and use it as part of the input for the second command - "history | grep ls"

### ;

The semi colon works similarly to the && operator, however it does not require the first command to be executed successfully in order for the second to be run.

### >

> is used for output redirection, instead of outputting to the commandline, the result of a command can be placed in a file instead

#### How would you output twenty to a file called test

echo twenty > test

### >>

Does the same as >, except instead of overwriting the file, the >> command appends to the end of the file

## Obtaining shiba3's password

Apparently there is a binary that checks to see if a variable 'test1234' exists, and if it does, does it equate to the $USER variable.

Create the 'test1234' variable and set it to the $USER variable

export test1234=$USER

Shiba3's password - happynootnoises

## Advanced File Operations

### chown

chown is used to change the user and group for a file. You need to have higher permissions than that user so this should usually be done as root

#### How would you change the owner of file to paradox

chown paradox file

#### What about the owner and the group of file to paradox

chown paradox:paradox file

#### What flag allows you to operate on every file in the directory at once?

chown -r

### chmod

used to modify the permissions users, groups and everyone has for a specific file

1 = executed
2 = write
3 = executed, write
4 = read
5 = read, executed
6 = read, write
7 = read, write, execute

3 sets of 3 for (x,r,w)(user,group,everyone)

#### What permissions mean the user can read the file, the group can read and write to the file, and no one else can read, write or execute the file?

460

#### What permissions mean the user can read, write, and execute the file, the group can read, write, and execute the file, and everyone else can read, write, and execute the file.

777

### rm

rm is used to remove a file, directory, or brick your system. Personal preference is to never use this if a GUI is available.

#### What flag deletes every file in a directory

rm -r

#### How do you suppress all warning prompts

rm -f

### mv

mv allows the user to move files around their system. This can also rename files upon moving

#### How would you move file to /tmp

mv file /tmp