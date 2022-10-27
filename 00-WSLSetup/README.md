## Introduction

The purpose of this assignment is to set up the Windows Subsystem for Linux (WSL).  WSL acts as a virtual machine that will allow you to develop code on a Linux based operating system while working in your Windows environment.  By completing this exercise, you will have the ability to install Linux within WSL, create a program, and start learning about operating systems based on Linux.

For more information on WSL see the documentation on Microsoft's web page: [https://docs.microsoft.com/en-us/windows/wsl/](https://docs.microsoft.com/en-us/windows/wsl/)

## Objectives

By the end of this assignment you will be able to:

- Create a fresh installation of Linux
- Understand the concepts of the Windows Subsystem for Linux (WSL)
- Demonstrate an ability to use a Linux shell.
- Use the 'man' command to obtain documentation about Linux commands
- Explain how to list the contents of a directory in multiple forms.
- Navigate the Linux file system by changing directories.
- Manage the creation and deletion of new files and directories from within the command shell.
- Capture the output of a Linux program executing to a file.

## Install Windows Subsystem for Linux (WSL)

The following procedure is documented in Microsoft's WSL install weg page: [https://docs.microsoft.com/en-us/windows/wsl/install](https://docs.microsoft.com/en-us/windows/wsl/install)

While often you hear of Linux described as an operating system, Linux itself is not an operating system, but a kernel.  Many operating systems have been built using the linux kernel.  These operating systems are often called 'distributions'.  To install a Linux distribution in WSL, you need to perform 2 things:

1. Install the WSL version of the Linux kernel
2. Install the distribution for the Linux operating system

Microsoft makes this easy by doing both in a single step.  By default, the WSL installer installs the Ubuntu Linux distribution, which is sufficient for the work we'll be doing.  If you want to look into installing other distributions, you can find information on the Microsoft WSL install web site: [https://docs.microsoft.com/en-us/windows/wsl/install#ways-to-run-multiple-linux-distributions-with-wsl](https://docs.microsoft.com/en-us/windows/wsl/install#ways-to-run-multiple-linux-distributions-with-wsl)

To install WSL and Ubuntu:

1. Open a command window as Administrator
   1. Open the start menu and type ```cmd.exe```
   2. In the menu on the right, click: Run as Administrator
2. When the command prompt opens run ```wsl --install```

This might take a while as WSL installs the kernel and the Linux distribution.  You'll see status messages printed to the command prompt as it goes.

Once it has completed installation, you will be asked to create a username and password for your Linux distribution.  This does not need to be the same as your Windows login, but it might be easier to remember if you do set it to the same.  The choice is yours.

## File System Setup

Once the installation completes, and you create a username and password you will see a slightly different command prompt.  You are now running in the Ubuntu Linux environment.  Any command you type will default to a Linux command.

### Accessing Windows Files from Linux

On Windows, the file system is typically NTFS and is organized by drive (e.g. C:\ or D:\ etc.).  The file system works slightly different on Linux.  Directories (i.e Folders) are 'mounted' inside each other.  You can think of it like a book on a bookshelf.  Each disk drive on your system is like a book and the file system as a whole is like the shelf.  In Windows, each book is given a drive letter, while in Linux each book is given a directory name.

For example, to access your Windows file system from Linux you have to go where it is mounted (e.g. what shelf it is on).  In WSL, the mount point for each drive is in ```/mnt```.

NOTE: that Linux uses forward slash '/' to delimit a directory while Windows uses the backslash '\'.

The ```cd``` command allows you to change directories while the ```ls``` command allows you to list the contents of a directory from the command line.

```text
user@machine:~$ ls /mnt
c  wsl
user@machine:~$
```

This lists the contents of the ```/mnt``` directory.  In this example, there are two things ```c``` which represents the C: 'drive' on Windows and another directory ```wsl``` which WSL uses for device mapping.

You can access any file in your Windows C: drive from Linux though ```/mnt/c/```.

For example, to list the contents of your Windows desktop you'd type:

```
user@machine:~$ ls /mnt/c/Users/WINDOWSUSERID/Desktop/
```

Replacing ```WINDOWSUSERID``` with your actual Windows username.

### Accessing Linux Files from Windows

On Windows, files are typically accessed through the File Explorer.  WSL makes it easy to get to the Linux file system through the File Explorer.  You can actually open the Windows File Explorer directly from your Linux command line.

```text
user@machine:~$ explorer.exe .
```

NOTE: it is important to use the add the dot (.) after the command.  The dot tells the Windows File Explorer to open the current directory (e.g. your Linux directory) instead of the default directory on Windows.

When the File Explorer opens you'll notice that your Linux file system is actually mapped to a network device in Windows, most likely: ```\\wsl$\Ubuntu```.  If you installed a different Linux distribution, the name might be different.

On Windows, the folder for all of your user files (desktop, document, etc.) is located in ```C:\Users\WINDOWSUSERID```.  On most Linux distributions, your Linux user files are located in ```/home/LINUXUSERID```.  Using the File Explorer that is equivalent to ```\\wsl$\Ubuntu\home\LINUXUSERID```.

Find this folder on your Windows File Explorer and add it to your quick access bar.  It will be very helpful to do this for accessioning your Linux file later.

## Installing Software

We'll need to use several Linux applications in this class.  Installing software in Linux is pretty easy.  Ubuntu provides a command called ```apt``` which stands for Application Package Tool.  It utilizes a central repository for commands that can be installed directly from the command line.

To install the software we'll need for this course run the following.  You'll have to enter your password to grant ```apt``` administrator authority on your Linux installation.

```text
sudo apt-get update
sudo apt-get install gcc make
```

You'll be asked to confirm before ```apt``` starts downloading and installing the software.

- ```gcc```: is the [GNU](https://www.gnu.org/) C compiler - we'll be using that to build programs
- ```make``` is a build tool that can be used to automate builds for projects.

## Editing a Text File

Using the Windows File Explorer, create a text file in your Linux home directory.  Add some text to the file, use your favorite text editor.

From the Linux command window, change to your home directory by typing ```cd``` without any arguments.  You'll know you're in your home directory when you see a tilde (~) symbol at your command prompt.

Now, display the contents of the file with the ```cat``` command on Linux.  For example, from the command prompt try this:

```text
user@machine:~$ ls
text.txt
user@machine:~$ cat text.txt
this is some text
```

The ```cat``` command is short for "concatenate".  It will print out the contents of a file to the command prompt.

## Exploring Linux

Now that you have WSL and Ubuntu Linux set up and installed, you will explore your Linux environment.  This exploration will involve experimenting with some other command.  There are some interesting and powerful things you can accomplish with relative ease.

From your Linux command window and experiment with the commands below.  You can get help on commands with the ```man``` command (which is short for "manual").  For example, try running ```man ls```.

You can search for appropriate commands with the ```apropos``` command. For example, try running ```apropos zip```.

Some commands you should experiment with (these are all typed via the command line, or terminal):

1. view a man page: man < command > e.g. man ls
2. list a directory: ls
3. list a directory, long: ls -l
4. list a directory, long, all: ls -al
5. search for a file in the file system: find -name .profile
6. Search through a file or a through a program output: grep
7. change directory: cd < dir >
8. change directory up one level: cd ..
9. change to last directory: cd –
10. make directory: mkdir < dir >
11. remove file: rm < file >
12. remove directory: rmdir < dir >
13. copy files: cp < source > < dest >
14. display contents of a file: cat output.txt
15. zip some files into a .zip file: zip lab1 hello.cpp output.txt
16. Create a tarball: tar -cf new tar file.tar *
17. Extract a tarball: tar -xvf new tar file.tar
18. Create an empty file touch empty.txt

Some of these commands may not be installed yet, if you need to install them use ```apt``` as we did before.  For example, to install ```zip``` you'd use: ```sudo apt-get install zip```.

As you are experimenting write a description (in your own words) of what each command (ls, find, cd, mkdir, rmdir, cp, cat, zip, tar, touch) is used for.  Include the command description in your report (see "Deliverables" below).

## Creating a Development Environment

### Create a Development Directory

Next you will want to create a development directory to hold the projects you will complete. To do this, create a directory (folder) in your Linux home directory for this class.  Feel free to do this from the Linux command line or the Window File Explorer.

### Setting up your Development Editor

**WINDOWS**:

For this class, it will be easiest to edit files from Windows and then build and execute them from your Linux command line.  With that, feel free to use any Windows editor that you like.  Here are a couple recommendations

- Notepad++ [https://notepad-plus-plus.org/](https://notepad-plus-plus.org/) is a simple text editor with text highlighting and has project file management as well
- Eclipse is a Java based editor that has a C/C++ plugin.  It can be installed by going to [https://www.eclipse.org/cdt/](https://www.eclipse.org/cdt/).
- CLion - This is a C/C++ editor created by JetBrains and is similar in look and feel to IntelliJ.
  - You can download CLion from JetBrains web site: [https://www.jetbrains.com/clion/](https://www.jetbrains.com/clion/)
  - There is no community version, but you can get a free license if you register with JetBrains as a student: [https://www.jetbrains.com/community/education/#students](https://www.jetbrains.com/community/education/#students)
- VSCode [https://code.visualstudio.com/](https://code.visualstudio.com/) is an IDE created by Microsoft with lots of configuration and plugin options.

Choose the editor that you like best.  Feel free to experiment with multiple if you'd like.

**LINUX**:

While for this class, it will be easiest to edit files from Windows and then build and execute them from your Linux command line, if you want to experiment with editors on Linux there are many out there:

- Notepad++ doesn't exist for Linux there is a similar one called notepadqq which has similar features.  It can be installed by running: ```sudo apt install notepadqq```
- gedit is simple text editor with tabbed editing and code highlighting but isn't an integrated development environment.  It can be installed by running: ```sudo apt install gedit```
- Codelite has a similar interface to notepadqq and does have compiler integration.  It can be installed by running: ```sudo apt install codelite```
- vim is a non-graphical text editor that you might have used if you use Git Bash on Windows.  It is installed by default on your WSL Ubuntu installation.  More information on vim can be found here: [https://www.vim.org/](https://www.vim.org/)
- Emacs is another non-graphical text editor.  It can be installed by running: ```sudo apt install emacs```.  More information on emacs can be found here: [https://www.gnu.org/software/emacs/](https://www.gnu.org/software/emacs/)

NOTE: If you wish to enter the long-running debate of 'emacs' vs 'vim' ([https://en.wikipedia.org/wiki/Editor_war](https://en.wikipedia.org/wiki/Editor_war) feel free to try out one (or both) of those editors.

## Building and Running a Program

Try compiling the following program (copy/paste to a file named hello.c or [download it](hello.c)):

```c
/**********************************
 * hello.c
 * Written by: H. Welch - 11/26/2006
 * Modified W. Schilling - 8/15/2009
 *
 * Demonstrate basic C-program along with
 * system call requiring struct and pointer
 * manipulation.
 ***********************************/
 #include <stdio.h>
 #include <sys/utsname.h>
 #include <stdlib.h>
 int main (int argc, char* argv[]) {
     /* Get system information using the uts system interface.*/
     /* Declare a buffer to store information about the system. */
     struct utsname buf;     
     /* Declare a pointer to the user information. */
     char *usr;
     /* Populate the buffer with data from the system. */
     uname(&buf);
     /* Get information about the user from the system. */
     usr=getenv("USER");
     /* Print out system information to the console. */
     printf("Hello %s:%s:%s:%s:z%s\n", buf.sysname, buf.nodename,
          buf.release,buf.version,buf.machine);
     printf("The size of the UTS structure is %lu.\n", sizeof(buf));
     /* Print out the user information if the pointer is not NULL. */
     if (usr != NULL) {
          printf("%s\n",usr); 
     } else { 
          printf("User information not returned by the operating system.");
     }
     /* Return to O/S */
     return 0;
}
```

Now try compiling the program.  Answer the questions as you go.

At the command shell, issue the command: 

```text
gcc -E hello.c | less 
```

This command will preprocess the source code and pipe the results to the console.

Questions:

1.	What is the length of the ```sysname``` element of the ```utsname``` structure? 
2.	How did you determine the sizes?

Now issue the commands:

```text
gcc -S hello.cpp 
```

This will compile the given code, resulting in the creation of a ".s" file containing the assembly code for the program.  You can view the contents of the file through ```less``` which is a command to display a text file in the terminal (command window) allowing you to move up and down using the arrow keys

```text
less hello.s
```

Create a "screenshot" image of the output from less (you don't have to include all the output, just one "page" is enough) and include this in your report.

Questions:

3. Notice the align command in the assembly output.  This aligns the start of the definition on an 8-byte boundary.  Why does the compiler add this?
4. Do a Google search to find out more information on compiler memory alignment.  Document your resources in your answer.
5. Of the assembly code, which seems to be the most common instructions? Why do you think this is the case?
6. Do a Google search for the most common instructions that you see in the .s file.  What do they do?  Make sure you document your resources in your answer.

Now issue the commands:
```text
gcc -c hello.c
ls -al 
```
The first command creates an object file for the hello.c source code. This is code which contains assembled instructions that can later be linked by the linker.

Questions:

7. What extension is given to this file?
8. Research object files and give a short description in your own words.  Make sure you document your resources in your answer.

Lastly, issue the command:
```text
gcc -o hello hello.c
ls -al
```
This will perform all stages of compilation, writing the given file to the program hello.  .

Questions:

9. Viewing the output from ls what is the difference in size between the object file (.o) and the complete executable?
10. Do some research on Linux executables to see if you can figure out why there is a difference in size.  Write a short description in your report.  Make sure you document your resources in your answer.

Now issue the command:
```text
./hello
``` 
This will run the program.  Follow the instructions in the program and create a screenshot of your output to include in your report.

## Deliverables

Once you've completed all the activities and have answers to all the questions, create a report (text, doc, or pdf file) including the following:

- Your name, date, and title
- Introduction – a description the assignment in your own words
- Resources – a description of any external resources you used to complete the assignment
- Analysis – a description of your experience working with Linux
    - A reflection on your experience working with command line tools in Linux and the descriptions of the commands you used in your own words.
    - Include all required screenshots.
    - Answers to the questions from the "Building and Running a Program" section.
- Conclusion
    - Summary of what you learned
    - What specifically was challenging?
    - What did you like about it?
    - What could we do to improve it for others?

Submit your report to per your instructor's instructions.

## Grading Criteria (100 Points)

- (20 Points) Report introduction- Thorough description of the assignment in your own words.
- (60 Points) Analysis - Answers to the analysis questions
- (20 Points) Report Conclusion - Thorough conclusion with description of what you learned, what you liked, and suggestions for improvements.