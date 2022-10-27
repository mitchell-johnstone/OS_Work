## Introduction

A shell is a program that provides a traditional text-based interface to an operating system.  In Linux, a user types commands into the shell to be executed similar to the command prompt (cmd.exe) on Windows.  The purpose of this lab is to design, code, and test a program that will create a command prompt allowing user to execute commands.  It is intended to familiarize yourself with the system calls needed to create processes on Linux.

## References

There are many shells available for Linux, arguably the most popular is 'bash' which stands for the Bourne-Again SHell.  The shell you will be developing for this lab will work similarly to 'bash' but will have fewer features.  For more information about the 'bash' shell, you can check out the Wikipedia page:  [https://en.wikipedia.org/wiki/Bash_(Unix_shell)](https://en.wikipedia.org/wiki/Bash_(Unix_shell))

For this lab, you will be using the ```fork()``` system call to create child processes, then running ```exec()``` to run the commands specified by the user, finally waiting for the commands to finish executing using the ```wait()``` system call.  Before you start, it might be helpful to read the 'man' pages for these system calls.

- man 2 fork
- man 2 exec
- man 2 wait

## The Exercise

The steps for a typical shell are as follows:

1. Print out a prompt to the user – this may include the user's login name followed by their current working directory.  Shells typically allow the user to configure this through a settings file.  Our shell will use the same prompt every time.
2. Read the command string from the user
3. Invoke the ```fork()``` system call to create a child process to run the command
4. Invoke the ```exec()``` system call in the child process to replace its address space with the command to run
5. Invoke the ```wait()``` system call in the parent process to wait for the child process (running the command) to finish executing
6. Go back to 1

Shells typically run in a loop executing commands and then waiting for more work to do.  For this lab you will be developing a shell called Teeny Tiny Shell (ttsh), that will do the same.

Commands on Linux are pre-compiled programs that exist within the directory structure.  For example, the 'ls' command that you used in previous labs is located at /usr/bin/ls.  The Linux directory structure begins at the root directory.  Each directory name is delimited by the slash (/) character.  The 'ls' command can be executed by the shell using the absolute path (e.g. /usr/bin/ls), however this isn't required because Linux has a set of paths pre-set that it uses to search for commands.  The directory /usr/bin is one of those paths.  When a user just types 'ls' for the command to run, Linux searches the set of paths to find where 'ls' is located.  If it finds it, it runs the command.  If it can't find it, the shell prints out 'command not found'.  Your shell will have to be able to handle this just like 'bash' does.  Thankfully the search paths are built into the ```exec()``` system call for you.

NOTE: if at any time you want to find where a command is located, you can use the 'which' command.

In addition to the commands themselves, the execution of a command also may involve one or more command line arguments.  For example, you can run 'ls' to get the directory listing, but you can run 'ls -l' to have the 'ls' command print out a long, more detailed directory listing.  Command line arguments are separated by spaces in the user input.  Most shells support an unlimited number of command line arguments; however, your shell is only required to support up to 10 command line arguments.

Teeny Tiny Shell supports an additional feature using the semicolon.  Commands separated by a semicolon are run sequentially after each other.  For example:

```text
echo hi ; ls -a ; echo bye
```

will run the 3 commands:

1. 'echo hi' will print 'hi' to the terminal
2. 'ls -a' will print all files in the current directory
3. 'echo bye' will print 'bye' to the terminal

Commands will be executed sequentially: the first command will run to completion (the other two will not run), then the second command will run to completion, finally the third command will run.

While the user might not specify any command line arguments (e.g. if they just execute 'ls' to get the directory listing), any call to exec requires at least one command line argument.  The first argument is ALWAYS the command that is being executed.  For example, if the user types the following command:

```text
$> ls -l
```

This is translated to an execution of the 'ls' command with command line arguments: 'ls' and '-l' 

## Development Requirements

1. While most shells allow the user to customize the prompt, you shell will always use the following prompt string:
   
   ```text
   $>
   ```
   
   A dollar sign ($), followed by a greater than (>), followed by a space ( )
3. Your 'ttsh' must support up to 10 command line arguments for each command (separated by spaces)
4. Your 'ttsh' must support up to 5 commands run sequentially (separated by semicolon)
5. While there many 'flavors' of the exec() system call, for this lab you are required to use execvp().  See the man page for the specifics of how execvp() works.
6. Your shell must support a single internal command called 'quit' which stops the execution loop
7. You must use fork() and execvp() to create child processes and execute commands.  The use of the system() function is not allowed for this lab.
8. Your 'ttsh' must be free of memory leaks and segmentation faults.
9. Your 'ttsh' only needs to support a max user input of 256 characters.

## Getting Started

Parsing the user's input can be kind of complicated.  Using the string tokenizer function (strtok) can be helpful.  For help on how to use strtok see the man page:

- man strtok

Start by downloading the [starter files](ttsh.zip) which includes a source file (ttsh.c) with some code to help you parse the command line.  The starter code also contains a Makefile to help you build your shell.

## Sample Execution

Here is a sample output for an execution of 'ttsh'.  Note the first line and last line shows the prompt presented from 'bash' prior to running 'ttsh'.

```text
user@pc:~/Desktop/cs3840/labs$ ./ttsh
$> ls
ttsh   ttsh.c
$> ls -l
total 500
-rwxrwxr-x 1 user user 17240 Sep 17 12:59 ttsh
-rw-rw-r-- 1 user user  7053 Sep 17 12:47 ttsh.c
$> echo hello world
hello world
$> ps -f -l
F S UID          PID    PPID  C PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S user       43181   43170  0  80   0 -  5173 do_wai 08:59 pts/0    00:00:00 bash
0 R user       46683   43181  0  80   0 -  5029 -      11:59 pts/0    00:00:00 ps -f -l
$> which ls
/usr/bin/ls
$> mkdir testdir
$> ls -l
total 504
-rwxrwxr-x 1 user user 17240 Sep 17 12:59 ttsh
-rw-rw-r-- 1 user user  7053 Sep 17 12:47 ttsh.c
drwxrwxr-x 2 user user 4096 Sep 18 12:02 testdir
$> rmdir testdir
$> ls -l
total 500
-rwxrwxr-x 1 user user 17240 Sep 17 12:59 ttsh
-rw-rw-r-- 1 user user  7053 Sep 17 12:47 ttsh.c
$> asdfasdfasdfasdf
asdfasdfasdfasdf: failed to execute command
$> quit
user@pc:~/Desktop/cs3840/labs$
```

## Development Tips

Consider breaking the lab up into pieces:

1. Create your shell input/execute loop
2. Implement the 'quit' command
3. Read and parse user input for commands 
   1. Break apart commands by semicolon 
   2. Break apart command line arguments by spaces
4. Get fork() and execvp() working to create a child process 
   1. Build the array of command line arguments 
      1. A single command with no command line arguments (remember that even without command line arguments explicitly specified there is always 1 passed to the new process)
      2. A single command with multiple command line arguments (remember that this includes the command name AND the actual command line arguments)
      3. Make sure you end your array of command line arguments with a NULL pointer 
   2. Run multiple commands in sequence with or without command line arguments
5. Handle command not found

Additional tips:

- Your shell has limitations on string length requirements.  Use this to your advantage 
- A max of 256 characters of user input 
- A max of 10 command line arguments (this max includes the first argument for the command name itself, effectively making the number that the user can specify to be 9 arguments)
- A max of 5 commands executed in sequence 
- Don't forget about using gdb to help with debugging (compile with -g to get additional debug symbols)

  NOTE: when using gdb it is helpful to compile your program with additional debug symbols included.  These allow gdb to show you more information when running commands like backtrace (bt).  To compile with additional debug symbols use the -g flag on gcc.  For example:

  ```text
  gcc -Wall -g -o myprog mysourcefile1.c mysourcefile2.c mysourcefile3.c
  ```

- Using valgrind will be helpful in this lab to ensure you do not have any memory leaks.

## Testing and Debugging

Make sure your shell supports all the features listed in the "Development Requirements".  Make sure you test boundary cases and print appropriate error messages to the user as needed. For example, if the user attempts to execute a command with more than 10 command line arguments, print an error message to the user and wait for a new command (without executing the command).

## Deliverables

You will need to include all your source files and any other resources you used to complete lab.  Please don't just google search for a solution, but if you do use Google for any help, include a description and URL of what you used to help you. 

A makefile is useful, but optional for this assignment.  If you created a makefile, include it in your submission. 

All files should be well documented with function comment blocks and inline comments that explain complicated code routines.  While no explicit style guidelines are set for programming in this course, code should be documented and readable.  Include your name, section, and lab name in a comment block at the top of each file.

NOTE: do ***NOT*** submit any IDE configuration files (.idea, project files, etc.).  Only submit your source files and report.

Prepare a lab report and submit it along with your source code.  The report should include the following:

- Your name, section, date, and lab title 
- Introduction – a description the lab in your own words 
- Design – a description of your design decisions in creating your solution
- Resources – a description of any external resources you used to complete the lab 
- Build – instructions on how to build and run your program.  Include the exact commands that are necessary
- Analysis – Discuss the key concepts from the lab and answers to the following questions
  - Commands in TTSH are executed by a call to ```fork()``` followed by a call to ```exec()```.  What would bee the behavior of teeny tiny shell if the calls were reversed?
  - There are many 'flavors' of ```exec()```.  For this lab you used ```execvp```, research the other 'flavors' of ```exec()```.  What is each used for?  Be sure to site your sources:
    - execl
    - execlp
    - execle
    - execv
    - execvp
    - execvpe
  - For this lab you used the ```fork()``` system call to create a child process to execute the command.  There is another version of fork called ```vfork()```.  Research this system call and describe how it works.  Be sure to site your sources.  When would you choose to use ```vfork()``` instead of ```fork()```.
- Conclusion 
  - Summary of what you learned in the lab 
  - What specifically was challenging about this lab? 
  - What did you like about it? 
  - What could we do to improve it for others?

NOTE: You should ensure that this program compiles without warning (-Wall and -Wextra) prior to submitting.

Prepare a zip file with all submitted files and upload the file to Canvas per your instructor's instructions.

## Grading Criteria

- (35 Points) Report
  - (5 Points) Report Introduction - Thorough description of the lab in your own words.
  - (5 Points) Design and Testing Methodology - Detailed description of design and method for testing your implementation.
  - (20 Points) Analysis - Answers to the analysis questions
  - (5 Points) Conclusion - Thorough conclusion with description of what you learned, what you liked, and suggestions for lab improvements.
- (5 Points) Documented Resources - Description of external resources used to complete the lab
- (5 Points) Correct Submission - Followed submission instructions (e.g. IDE project files are not submitted)
- (5 Points) Build - Code compiles without warnings or errors
- (45 Points) Instructor Tests - Implementation passes all instructor test cases
- (5 Points) Memory Management - Program execution is free from memory leaks
