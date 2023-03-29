# About
This project is about creating a lightweight version of bash (Born Again Shell).
## Features
- prompts user for input
- checks user input for valid commands else returns appropriate errors
- executes commands with options (Ex: `ls -l`)
- handles multiple pipes (Ex: `ls | head -2 | wc`)
- custom built-ins (cd, pwd, echo, unset, export, env)
- I/O redirections (<, >, <<, >>)
- handles signals (Ctrl-C, Ctrl-D, Ctrl-\)

## What I learned
- UNIX programming in general
- bash's behaviour in various situations and how it is implemented
- How to create processes and retrieve valuable informations from them. Like exit codes
- How to create a pipeline that handles I/O redirections
- How to analyze files

## Tips & Tricks
- Use the `lsof -c <name_of_your_program>` or `ps aux | grep program_name` commands to see the current processes of a specific program

## Useful Links
### Tutorials
- Tutorial - [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) by Stephen Brennan
- [Let's Build a Command Line Shell in C](http://www.dmulholl.com/lets-build/a-command-line-shell.html)
- [Multipipe_tutor](https://clemedon.github.io/Multipipe_tutor/)
- [Pipe: an Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
### Manuals
- Systems Programming : Chapter 5 : [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [The Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
