# CTF Collection Vol 1

## Task 1

## What does the base said?

Can you decode the following?

VEhNe2p1NTdfZDNjMGQzXzdoM19iNDUzfQ==

    1. Feed me the flag!

THM{ju57_d3c0d3_7h3_b453}

`echo VEhNe2p1NTdfZDNjMGQzXzdoM19iNDUzfQ== | base64 -d`

##  Meta meta

Meta! meta! meta! meta...................................

    1. I'm hungry, I need the flag.

THM{3x1f_0r_3x17}

`exiftool Findme.jpg`

## Mon, are we going to be okay?

Something is hiding. That's all you need to know.

    1. It is sad. Feed me the flag.

THM{500n3r_0r_l473r_17_15_0ur_7urn}

`steghide extract -sf Extinction.jpg`

## Erm......Magick

Huh, where is the flag?

    1. Did you find the flag?

THM{wh173_fl46}

`Huh, where is the flag? THM{wh173_fl46}` hidden as whitetext next to the question

## QRrrrr

Such technology is quite reliable.

    1. More flag please!

THM{qr_m4k3_l1f33_345y}

Found by scanning the QR code

## Reverse It Or Read It?

Both works, it's all up to you.

    1. Found the flag?

THM{345y_f1nd_345y_60}

So not sure what was expected here, running strings on the file showed the flag for me.

## Another Decoding Stuff

Can you decode it?

3agrSy1CewF9v8ukcSkPSYm3oKUoByUpKG4L

    1. Oh, Oh, Did you get it?

THM{17_h45_l3553r_l3773r5}

`echo 3agrSy1CewF9v8ukcSkPSYm3oKUoByUpKG4L | base58 -d`

## Left Or Right

Left, right, left, right... Rot 13 is too mainstream. Solve this

MAF{atbe_max_vtxltk}

    1. What did you get?

THM{hail_the_caesar}

`echo MAF{atbe_max_vtxltk} | caesar 7`

## Make A Comment

No downloadable file, no ciphered or encoded text. Huh .......

    1. I'm hungry now... I need the flag

THM{4lw4y5_ch3ck_7h3_c0m3mn7}

In the HTML of the TryHackMe page.

## Can You Fix It

I accidentally messed up with this PNG file. Can you help me fix it? Thanks, ^^

    1. What is the content?

THM{y35_w3_c4n}

`hexedit spoil.png` - change the magic number to be that of a png.

## Read It

Some hidden flag inside Tryhackme social account

    1. Did you find the hidden flag

THM{50c14l_4cc0un7_15_p4r7_0f_051n7}

`https://www.reddit.com/r/tryhackme/comments/eizxaq/new_room_coming_soon/`

## Spin My Head

What is this?

`++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++++++++++++++.------------.+++++.>+++++++++++++++++++++++.<<++++++++++++++++++.>>-------------------.---------.++++++++++++++.++++++++++++.<++++++++++++++++++.+++++++++.<+++.+.>----.>++++.`

    1. Can you decode it?

THM{0h_my_h34d}

Seems to be some kind of overly confusing encoding algorithm called brainfuck.

## An Exclusive!

Exclusive strings for everyone!

S1: 44585d6b2368737c65252166234f20626d
S2: 1010101010101010101010101010101010

    1. Did you crack it? Feed me now!

THM{3xclu51v3_0r}

S1 XOR S2 = flag

## Binary Walk

Please exfiltrate my file :)

    1. Flag! Flag! Flag!

THM{y0u_w4lk_m3_0u7}

`binwalk -e hell.jpg`

## Darkness

There is something lurking in the dark.

    1. What does the flag said?

THM{7h3r3_15_h0p3_1n_7h3_d4rkn355}

Open the image and look at it. If you have sight issues this would be impossible

## A sounding QR

How good is your listening skill?

P/S: The flag formatted as THM{Listened Flag}, the flag should be in All CAPS

    1. What does the bot said?

THM{SOUNDINGQR}

Listen to the link provided by the QR code. If you are hard of hearing, who cares!

## Dig Up The Past

Sometimes we need a 'machine' to dig the past

Targeted website: https://www.embeddedhacker.com/
Targeted time: 2 January 2020

    1. Did you found my past?

THM{ch3ck_th3_h4ckb4ck}

Found using wayback machine.

## Uncrackable!

Can you solve the following? By the way, I lost the key. Sorry >.<

MYKAHODTQ{RVG_YVGGK_FAL_WXF}

Flag format: TRYHACKME{FLAG IN ALL CAP}

    1. The Deciphered text

TRYHACKME{YOU_FOUND_THE_KEY}

Looks like a Vigenere Cipher, mentioning of a key also suggests that. This could likely be cracked manually as we know the first part of the decoded text will be "TRYHACKME". Uploading this first of the ciphertext into [dcode.fr](https://www.dcode.fr/vigenere-cipher "Dcode.fr") showed that the key was "THM". Using this key, the rest of the ciphertext can be decoded.

## Small Bases

Decode the following text.

581695969015253365094191591547859387620042736036246486373595515576333693

    1. What is the flag?

THM{17_ju57_4n_0rd1n4ry_b4535}

Convert to hex then convert to ascii.

## Read The Packet

I just hacked my neighbor's WiFi and try to capture some packet. He must be up to no good. Help me find it.

    1. Did you captured my neighbor's flag?

THM{d0_n07_574lk_m3}

Wireshark to analyse. Looking at GET requests shows a request for flag.txt. Following HTTP stream gives the flag