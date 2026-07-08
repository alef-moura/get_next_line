*This project has been created as part of the 42 curriculum by alesferr.*

# Get Next Line

`get_next_line()` is a function that reads and returns **one line at a time** from a file descriptor. The project introduces one of the most important concepts in C programming: **static variables**, while reinforcing manual memory management, dynamic allocation, efficient string manipulation, and file descriptor handling.

---

# Table of Contents

- [Description](#description)
- [Objectives](#objectives)
- [Project Structure](#project-structure)
- [Instructions](#instructions)
- [How it Works](#how-it-works)
- [Visual Flow](#visual-flow)
- [Algorithm](#algorithm)
- [Why use a static variable?](#why-use-a-static-variable)
- [BUFFER_SIZE](#buffer_size)
- [Complexity](#complexity)
- [Example](#example)
- [Resources](#resources)
- [AI Usage](#ai-usage)
- [Bonus](#bonus)

---

# Description

The goal of this project is to implement a function capable of reading a file descriptor **one line at a time**.

Unlike traditional file reading functions, `get_next_line()` remembers what has already been read by using a **static variable**, allowing consecutive calls to continue exactly where the previous one stopped.

The function works with both regular files and the standard input while minimizing unnecessary calls to `read()`.

---

# Objectives

This project focuses on learning how to:

- Read from file descriptors using `read()`;
- Manage dynamic memory safely;
- Understand and use static variables;
- Manipulate strings manually;
- Minimize unnecessary reads;
- Return one complete line per function call;
- Handle different `BUFFER_SIZE` values correctly.

---

# Project Structure

```text
.
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
│
├── get_next_line_bonus.c
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```

---

# Instructions

## Compilation

Compile the mandatory project using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c \
get_next_line_utils.c
```

The project must also compile correctly with different buffer sizes, for example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1
```

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999
```

The implementation should behave correctly regardless of the chosen `BUFFER_SIZE`.

---

# How it Works

```text
                 get_next_line(fd)
                        │
                        ▼
          Is there remaining data (stash)?
                 │                 │
                Yes               No
                 │                 │
                 └────────┬────────┘
                          ▼
                 Read from file (read)
                          │
                          ▼
                 Append to stash
                          │
                          ▼
                Newline found?
                 │                 │
                Yes               No
                 │                 │
                 ▼                 │
          Extract one line         │
                 │                 │
                 ▼                 │
      Save remaining characters    │
                 │                 │
                 ▼                 │
          Return the line ◄────────┘
```

---

# Visual Flow

Example:

```text
File

+--------------------------------------+
|Hello\nHow are you?\n42\nBye          |
+--------------------------------------+

BUFFER_SIZE = 5
```

### First call

```text
read()

Hello

Returned:

Hello\n

Remaining (stash):

How
```

---

### Second call

```text
New read:

 are you?\n42

stash before:

How

stash after:

How are you?\n42

Returned:

How are you?\n

Remaining:

42
```

---

### Third call

```text
New read:

\nBye

Returned:

42\n

Remaining:

Bye
```

---

### Fourth call

```text
EOF reached

Returned:

Bye

Remaining:

(empty)
```

---

# Algorithm

## Step 1 — Validate the input

The function first verifies whether:

- the file descriptor is valid;
- `BUFFER_SIZE` is greater than zero.

If one of these conditions is not met, the function immediately returns `NULL`.

```c
if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
```

---

## Step 2 — Keep unread data

A static variable stores characters that have already been read but not yet returned.

```c
static char *stash;
```

Because it is **static**, its value persists between function calls.

---

## Step 3 — Read from the file

The function reads up to `BUFFER_SIZE` bytes.

```c
read(fd, buffer, BUFFER_SIZE);
```

Each newly read buffer is appended to the existing stash.

```text
stash

↓

Hello Wo

+

rld\nHow

↓

Hello World\nHow
```

---

## Step 4 — Search for a newline

Once a newline (`\n`) is found, everything before it becomes the next line to return.

```text
stash

Hello World\nHow are

↓

Returned line

Hello World\n
```

---

## Step 5 — Allocate memory

The extracted line is allocated dynamically using `malloc()`.

The caller is responsible for freeing the returned memory.

---

## Step 6 — Save the remaining characters

After extracting one line, the unused characters remain inside the static variable.

```text
Before

Hello\nHow are you

↓

Returned

Hello\n

↓

Saved

How are you
```

---

## Step 7 — Continue reading

The next call to `get_next_line()` starts from the saved characters instead of rereading the file.

This process repeats until the end of the file is reached.

---

# Why use a static variable?

Without a static variable, every call to `get_next_line()` would lose all previously read data.

The static variable allows the function to remember unread characters between calls, making it possible to continue reading exactly where the previous call stopped.

This is the key concept introduced by this project.

---

# BUFFER_SIZE

`BUFFER_SIZE` determines how many bytes are read during each call to `read()`.

Small values result in:

- more calls to `read()`;
- less memory used per read.

Large values result in:

- fewer calls to `read()`;
- more memory read at once.

The implementation must work correctly regardless of the chosen value.

---

# Complexity

| Operation | Complexity |
|-----------|------------|
| Time | **O(n)** |
| Space | **O(n)** |

Where **n** is the number of characters returned in the current line.

---

# Example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }

    close(fd);

    return (0);
}
```

---

# Resources

### Documentation

- The C Programming Language — Brian W. Kernighan & Dennis M. Ritchie
- Linux `read(2)` manual
- Linux `malloc(3)` manual
- Linux `free(3)` manual
- Linux `open(2)` manual
- 42 Project Subject

---

# AI Usage

ChatGPT was used exclusively as a learning assistant to:

- better understand static variables;
- review algorithm ideas;
- improve the project documentation;
- clarify C programming concepts.

All implementation, debugging, testing, and final code decisions were completed manually.

---

# Bonus

The bonus version extends the project by supporting **multiple file descriptors simultaneously**.

Instead of remembering the reading position for only one file descriptor, the implementation keeps track of each descriptor independently while still using static storage.

Example:

```text
get_next_line(fd3)
↓

get_next_line(fd4)
↓

get_next_line(fd5)
↓

get_next_line(fd3)

↓

Reading continues correctly from fd3 without losing its previous state.
```

This allows the function to alternate between different files without mixing their contents.

---

## Bonus Input Validation

In the bonus version, the function also ensures that the file descriptor does not exceed the maximum allowed limit (`MAX_FD`) to prevent out-of-bounds errors in the static array:

```c
if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
    return (NULL);
```

---