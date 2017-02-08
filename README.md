# Harvard_IntroCompSciCourse
This is my repository to store my projects and homework assignments for my second intro course. I decided to take a second intro to really solidify a base, and the projects/technology seemed pretty interesting! 

## pset1 

The first pset was really to introduce me to the world of C/Linux

Objectives:
  1. Get comfortable with Linux
  2. Start thinking more carefully
  3. Solve some problems in C

#### Hello.c 

  a hello world! And a hello to C!
  
#### water.c

  a program that prompts the user for the length of shower (as a positive int), and then prints
  the equivalent number of bottles of water they are using! Take shorter showers!
  
#### mario.c

  a program that 'recreates' the half-pyramid using hashes(#) for blocks. The user is prompted for the half-pyramid's
  height, a non negative integer no greater than 23. If user fails to provide what's needed, they are re-prompted
  then the half-pyramid is generated making sure to align the bottom-left corner of thehalf-pyramid with the left-hand 
  edge of the terminal window
  
  A couple of testing files are incorporated into the folder, I am debating on taking them out, but I liked 
  to see how I thought when I was working through the problem. For now, I would like to keep them there. 
  
  
  
## pset2
  
The second problem set had me really get better acquainted to functions and using libraries 
  
Objectives:
  1. Become better acquainted with functions and libraries
  2. Dabble in cryptography
  
#### initials.c

  A program that prompts hte user for their name, and then outputs their initials in uppercase
  no spaces or periods, and then followed by a new line. 

#### caesar.c

  A program that encrpyts a message using Caesar's cipher! A secret!

#### vigenere.c

  A program that encrypts a message using Vigenere's Cipher, which improves upon Caesar's by encrypting messages
  using a sequence of keys. If p is some plaintext and k is a keyword.
  
  
## pset3
  
  The Game of Fifteen! Creates our first working game! Sorting algorithns, O(n), all included and learned this week. 
  
Objectives:
  1. Accustom you to reading someone else's code
  2. Introduce you to larger programs and programs with multiple source files
  3. Empower you with Makefiles
  4. Implement a party favor
  
#### Find

Prompts user for as many as MAX values until EOF is reached, 
then proceeds to search that "haystack" of values for given needle.
helpers files and make included. 

#### Fifteen

Implements Game of Fifteen (generalized to d x d).
Usage: fifteen d
whereby the board's dimensions are to be d x d,
where d must be in [DIM_MIN,DIM_MAX]
  
## pset4
  
  The problem set focuses on working with images, recovering images, uncovering hidden
  images. 
  
Objectives:
  1. Acquaint you with file I/O
  2. Get you more comfortable with data structures, hexadecimal, and pointers.
  3. Introduce you to computer scientists
  4. Help Mr. Boddy
  
#### BMP

Copies a BMP piece by piece, uncover the hidden image!

#### Resize

a program called resize that resizes 24-bit uncompressed BMPs by a factor of n. The program accepts exactly three command-line arguments, per the below usage, whereby the first (n) must be a positive integer less than or equal to 100, the second the name of the file to be resized, and the third the name of the resized version to be written.

#### Recover

Professor Malan snapped a bunch of people's photos on campus, but lost all the data! He thought it was "deleted",
but it was more so "forgotten". The CF card says it was "blank", but we built a program that recovers all of the 
"deleted" images. 
  
## pset5

Created a spellchecker in C! 

Objectives:
  1. Allow you to design and implement your own data structure.
  2. Optimize your code's (real-world) running time. 
  
#### Dictionary

Implements a dictionary's functionality.

#### Speller

Implemented a spell checker using dictionary's functionality
  
## pset6

A problem set that started to transition away from C into web programming. Worked and built a we  server
that would handle and respond to requests. 
Note: Much of this code was provided, and I implemented many of the functions with it. 

Objectives:
  1. Become familiar with HTTP
  2. Apply familiar techniques in unfamiliar contexts
  3. Transition from C to web programming

#### Server

the web server that handles requests, parses through it, provides a response. 
  
## pset7

C$50 Finance! Implemented a website via which users can "buy" and "sell" stocks. 

Objectives:
  1. Create a functional website
  2. Utilize and implement a backend database (SQL)
  3. Allow users to buy and sell stock, check their history, update within the database

This problem set was all done via Python, Flask, Bootstrap, HTML/CSS, SQLlite

#### application

Within this file is the bulk of how the sever operated, using functions from the hlper, all of the templates that generated the 
content on the web page etc within the subsequent folders/files. Really awesome project, and my friends all practiced!
I found a pretty big bug that allowed a user to input a negative value in the "buy" section, and my friend
gave himself 1mil extra cash! Quickly squashed that bug
  
