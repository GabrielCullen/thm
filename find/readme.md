# The Find Command

## Task 1: Start Finding

The syntax of the find command can be broken down into `find <where> <what>`.

Wildcards are supported, for both directories and names. `find / *.txt`

## Task 2: Be More Specific

Most of the time you won't be looking for something in your working directory so the first argument should be the directory you would like to search. To search the whole filesystem, use `find /`.

Two useful flags are `-type` and `-name`. With `-type` you can use `d` to find only directories and `f` to only find files. The `-name` flag is use to specify a name or pattern to look for. You can type the whole name, or use wildcards to specify only part(s) of the name. If wildcards are used then you should enclose the pattern in quotes. Lastly, the `-iname` flag performs the same as name, however it is case insensitive.

**Questions**

    1. Find all filees whose name ends with ".xml"

`find / -type f -name "*.xml"`
    
    2. Find all files in the /home directory (recursive) whose name is "user.txt" (case insensitive)

`find /home -type f -iname user.txt`
    
    3. Find all directories whose name contains the word "exploits"

`find / -type d -name "\*exploits\*"`

## Task 3: Know Exactly What You're Looking For

In some situations, specifying the name of a file will not be enough. You can also specify the owner, the size, the permissions, and the time the file was last accessed/modified as well.

The username of the owner of a file is specified with the `-user` flag.

The size of a file is specified with the `-size` flag. For numerical values you can use `-n`,`n`,`+n`. `-n` is a number less than n, `n` is exactly n and `+n` is a number greater than n. To specify a size a suffix is needed: `c` for bytes, `k` for kilobytes `M` for megabytes. To specify a file less than 30 bytes the argument `-30c` should be used.

The `-perm` flag is used to specify permissions. Generally octal form is used here but symbolic from `u=r` is also allowed. The `-` prefix finds files with at least the specified permissions. The `/` prefix will match any of the permissions that have been set.

Time related searches are more complex. They consist of a word and a prefix. The words are `min` and `time` for minutes and days respectively. The prefixes are `a`,`m` and `c` for accessed, modified or status changed. For numerical values the same rules as seen in the `-size` flag apply here.

**Questions**

    1. Find all files owned by the user "kittycat"

`find / -type f -user kittycat`

    2. Find all files that are exactly 150 bytes in size

`find / -type f -size 150c`

    3. Find all files in the /home directory (recursive) with size less than 2 KiB’s and extension ".txt"

`find /home -type f -size -2k -name "*.txt"`

    4. Find all files that are exactly readable and writeable by the owner, and readable by everyone else (use octal format)

`find / -type f -perm 644`

    5. Find all files that are only readable by anyone (use octal format)

`find / -type f -perm /444`

    6. Find all files with write permission for the group "others", regardless of any other permissions, with extension ".sh" (use symbolic format)

`find / -type f -perm -o=w -name "*.sh"`

    7. Find all files in the /usr/bin directory (recursive) that are owned by root and have at least the SUID permission (use symbolic format)

`find /usr/bin -type f -user root -perm -u=s`

    8. Find all files that were not accessed in the last 10 days with extension ".png"

`find / -type -f -atime +10 -name "*.png"`

    9. Find all files in the /usr/bin directory (recursive) that have been modified within the last 2 hours

`find /usr/bin -type f -mmin -120`

## Task 4: Have You Found It

The redirection operator can be used to redirect the output of the find command to a file. It can also be used to suppress errors to make the output more readable. This is done by appending `2> /dev/null` to the command. Another thing to note is the `-exec` flag which can be used to execute a new command. It is possible that this may be used as a vector for privilege escalation.