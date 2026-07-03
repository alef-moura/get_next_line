*This project has been created as part of the 42 curriculum by alesferr.*

# Get Next Line

## Description

The goal of this project is to implement a function capable of reading a file descriptor one line at a time.

Unlike traditional file reading functions, `get_next_line()` remembers what has already been read through the use of a static variable, allowing consecutive calls to continue exactly where the previous one stopped.

The project introduces one of the most important concepts in C programming: **static variables**, while also reinforcing manual memory management, dynamic allocation, file descriptors, buffer handling and efficient string manipulation.

## Objectives

This project focuses on learning how to:

- read from file descriptors using `read()`;
- manage dynamic memory safely;
- understand and use static variables;
- manipulate strings manually;
- avoid unnecessary reads;
- correctly return one line at a time.

## Project Structure

get_next_line.c
get_next_line_utils.c
get_next_line.h

Bonus:

get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h

## How it works

                get_next_line(fd)
                       │
                       ▼
             Is there leftover data?
                  │           │
                 Yes         No
                  │           │
                  ▼           ▼
          Append new reads from fd
                  │
                  ▼
         Newline found?
          │             │
         Yes            No
          │             │
          ▼             ▼
Return one line     Continue reading
          │
          ▼
Save remaining data
          │
          ▼
 Wait for next function call
 
## Visual flow

File

+--------------------------------------+
|Hello\nHow are you?\n42\nBye          |
+--------------------------------------+

BUFFER_SIZE = 5


Read #1

Hello

Return:

Hello\n


Remaining:

How


Read #2

How are you?\n

Return:

How are you?\n


Remaining:

42\nBye


Read #3

42\n


Remaining:

Bye


Read #4

Bye


EOF

Return:

Bye


## Algorithm

### Step 1

The function starts by checking if the file descriptor is valid.

If it is invalid, or if BUFFER_SIZE <= 0, the function immediately returns NULL.

↓

### Step 2

A static string stores everything that has already been read but has not yet been returned.

static char *stash;

The static variable allows the function to remember previous reads between calls.

↓

### Step 3

The function reads from the file using

read(fd, buffer, BUFFER_SIZE)

Each new buffer is concatenated to the existing stash.

stash

↓

Hello Wo

+

rld\nHow

↓

Hello World\nHow

↓

### Step 4

Whenever a newline (\n) is found, the function extracts everything until that newline.

stash

Hello World\nHow are

↓

line

Hello World\n

↓

### Step 5

The returned line is allocated with malloc().

↓

### Step 6

The remaining characters stay inside the static variable.

Before

Hello\nHow are you

↓

Returned

Hello\n

↓

Saved

How are you

↓

### Step 7

The next function call continues from the remaining data instead of rereading the file.

## Why use a static variable?

Without a static variable, every call to `get_next_line()` would lose all previously read information.

The static variable preserves unread characters between function calls, allowing the function to continue exactly where it stopped.

## Complexity

Time Complexity:

O(n)

Space Complexity:

O(n)

where n is the length of the returned line.

## Resources

Documentation

- The C Programming Language — Kernighan & Ritchie
- Linux `read(2)` man page
- Linux `open(2)` man page
- Linux `malloc(3)` man page
- 42 Subject

AI Usage

ChatGPT was used only as a learning assistant for:
- understanding static variables;
- reviewing algorithm ideas;
- improving documentation;
- clarifying C concepts.

All implementation, debugging and final code decisions were completed manually.

## Bonus

The bonus version extends the project by allowing multiple file descriptors to be handled simultaneously while still using a static variable.