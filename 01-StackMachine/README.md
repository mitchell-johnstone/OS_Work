## Introduction

The purpose of this lab is to design, code, and test a machine within the confines of the C programming language.  The machine will consist of a data structure for storing data and operations that can be done against the data structure to perform calculations.  While not strictly and "operating systems" exercise, it is intended to familiarize you with the development process on Linux and provide additional practice with dynamic memory.

## Prerequisites

Your VM should be operational, and you should have a development environment (programmer's editor or IDE) setup and tested (i.e. you have written a hello world program).  This assignment will also make use of the program 'valgrind' which may need to be installed.  You can do this at the command line with the commands:

```text
sudo apt update
sudo apt install valgrind
```

## Background

A stack machine is a type of computer architecture in which values are stored on a stack rather than in general purpose registers.  Values can be pushed from memory onto the stack and/or popped from the stack and stored into memory.  Numerical operations are performed on items currently on the stack.  For example, to execute an 'add' operation, the two operands are first pushed onto the stack.  Then the 'add' instruction is executed which pops the values off the stack, adds them, and the result is pushed back on top of the stack.

While it might seem that using general purpose registers makes for a more flexible processor architecture, there are advantages of the simplicity of a stack machine.  For example, there is no need for hardware to decode and access the register file, all operations are performed against the top of the stack.  In fact, the Java Virtual Machine (JVM) is implemented in part as a stack machine.

## The Exercise

For this exercise you will be creating a program that can perform operations using a stack machine.  The machine has no memory so all values for computation are stored entirely on the stack.  Typically, a stack machine interprets instructions through machine code that has been compiled for the architecture, however, our stack machine will use function calls to perform operations.

The stack is a first-in-last-out data structure.  Items are pushed (inserted) onto the top of the stack and popped (removed) from the top of the stack.  The first thing pushed into the stack is therefore the last thing that can be removed.  Think of it like stacking blocks on top of each other.  You can't move the bottom block without first removing all the blocks on top of it.

Beyond push and pop, our stack machine can perform mathematical operations add, subtract, and multiply as well as a special operation called rotate which rotates elements on the stack.
The size (number of elements it can hold) of the stack is unbounded, so you must be able to dynamically allocate and free elements as needed.

## Development

Start by downloading the [starter files](stackm.zip) which include the header file with the stack machine definition along with all required stack functions.  The starter code also contains a sample smTester.c file with some test cases and a Makefile.

A header file is supplied that represents the "public" interface that you must implement.  Each function is documented within the head file.  You are ***NOT*** allowed to change this header file in any way.  You should supply ***ONE*** source file with the implementation for all functions (stackm.c).

Upon reviewing the header file, you may have some impressions.  First, the stack is rather crude.  The functions in this "public" interface only manage the stack's memory and organization.  The user has full access to the internals.  Of course, some of this is an artifact of the C language that does not include the protections provided by languages such as Java and C++.  Also note that the user must pass a pointer to every stack management function.  Again, a necessity due to the lack of object-oriented language features.

In addition to the stack machine implementation, supply a "driver" that will completely test your stack machine implementation.  Here is an example test driver, however it is not all-inclusive.

```c
#include <stdio.h>
#include "stackm.h"

int main(void)
{
    stackm mystack;
    smInit(&mystack);
    
    smPush(&mystack, 2);
    smPush(&mystack, 3);
    smPush(&mystack, 4);
    smPrint(&mystack);
    
    smPop(&mystack);	
    smPrint(&mystack);
    smAdd(&mystack);
    smPrint(&mystack);
    
    int value = 0;
    smTop(&mystack, &value);
    printf("%d\n", value);
    
    smPush(&mystack, 10);
    smPush(&mystack, 11);
    smPrint(&mystack);
    smMult(&mystack);
    smPrint(&mystack);

    smPush(&mystack, 10);
    smPush(&mystack, 11);
    smPrint(&mystack);
    smRotate(&mystack, 5);
    smPrint(&mystack);

    smClear(&mystack);
    smPrint(&mystack);
    return 0;
}
```

You should have already picked an editor or IDE to use.  Compiling at the command line is sometimes easier than using an IDE as IDEs sometimes hide error messages.  Edit, compile, and run your program entirely from the Linux VM.  Using Windows to edit the file and then transferring to Linux can cause formatting problems with the code and might introduce unexpected errors.

You can invoke the compiler at the command line directly:

```text
gcc hello.c
```

This command will build hello.c and product an executable name a.out in the same directory.  Errors and warning will be reported to the console.  You can run a.out by issuing the command:

```text
./a.out
```

Here, the '.' refers to the current directory.

We can get fancier.  Instead of the default output name, we can specify the name of the executable:

```text
gcc -o hello hello.c
```

If we have more than one source file, just list them all:

```text
gcc -o hello hello.c goodbye.c
```

By default, gcc doesn't report all possible warnings.  If you want more warnings (hint, you do), do this:

```text
gcc -Wall -o hello hello.c goodbye.c
```

Another option for compiling your program is to use a Makefile.  Doing so is completely optional for this lab but can be very helpful for building your programs.  Dr. Schilling has an excellent tutorial on Makefiles that you can watch here: [https://www.youtube.com/watch?v=gT2roSrSYfo&feature=youtu.be](https://www.youtube.com/watch?v=gT2roSrSYfo&feature=youtu.be)

Here is a skeleton Makefile that you can use to get you started.

```text
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=source1.c source2.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=exename

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
```

## Testing and Debugging

As stated above, you must write a driver that completely tests your stack machine.  So what is complete testing?  How do you go about this?  You will have to put some thought into this and use your experience to guide you.  It would make sense that you will have to call every method at least once, probably many times under different conditions.  Look for boundary cases.  For example, be sure to test ```smPop()``` with an empty stack as well as a non-empty stack.

Given that we are using C and not Java, there are few protections we can build in to prevent misuse of the stack.  For example, there is no perfect way to make sure ```smInit()``` is called before adding items to the stack.

So, you are calling all the methods, and your program crashes.  What now?  Well, you must track down where it is crashing.  An IDE with debugging will be helpful, but you can also do this with gdb from the command.

NOTE:  The gdb program requires additional debug symbols to be included in your program in order to correctly display information about variable names and function names in call stacks.  To compile your program with additional debugging information, use the -g flag.  For example:

```text
gcc -g -Wall -o hello hello.c goodbye.c
```

The following shows a sample session using gdb to debug a segmentation fault:

```text
~/dev/labs/stack$ ./a.out 
Segmentation fault
~/dev/labs/stack$ gdb ./a.out 
GNU gdb (Debian 7.12-6) 7.12.0.20161007-git

== chopped out copyright stuff ==

Reading symbols from ./a.out...done.
(gdb) run
Starting program: ~/dev/labs/stack/a.out 

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554b3b in smPush (myStack=0x7fffffffe120, toStore=4) at stackm.c:123
123				myStack->top->next = newNode;
(gdb) bt
#0  0x0000555555554b3b in smPush (myStack=0x7fffffffe120, toStore=4) at stackm.c:123
#1  0x00005555555548a4 in main () at smTester.c:30
(gdb)
```

- Running the program directly with ```./a.out``` from the command line produces a Segmentation fault output.  This is not particularly helpful.
- Running ```gdb``` with the program as a command line argument runs the GNU debugger.  Notice the ```(gdb)``` prompt.
- Using the ```run``` command will execute the program in the debugger
- When the program hits the Segmentation fault, using the backtrace (```bt```) command prints a trace similar to the stack trace received from a ```NullPointerException``` in Java outlining exactly where the problem happened.

Another, highly recommended, tool for you to use is valgrind.  Valgrind will monitor the heap and report memory leaks.  The program must run to completion for this to be useful.  Sample output is below:

```text
==10565== Memcheck, a memory error detector
==10565== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10565== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==10565== Command: ./a.out
==10565== 
==10565== 
==10565== HEAP SUMMARY:
==10565==     in use at exit: 100 bytes in 10 blocks
==10565==   total heap usage: 10 allocs, 0 frees, 100 bytes allocated
==10565== 
==10565== LEAK SUMMARY:
==10565==    definitely lost: 100 bytes in 10 blocks
==10565==    indirectly lost: 0 bytes in 0 blocks
==10565==      possibly lost: 0 bytes in 0 blocks
==10565==    still reachable: 0 bytes in 0 blocks
==10565==         suppressed: 0 bytes in 0 blocks
==10565== Rerun with --leak-check=full to see details of leaked memory
==10565== 
==10565== For lists of detected and suppressed errors, rerun with: -s
==10565== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Deliverables

You should have at least three source files in your project:

1. smTester.c – The test driver for your stack machine and should contain the 'main' function.  Make sure your implemented test driver tests more than just the sample
2. stackm.c – the implementation file for your stack machine operations
3. stackm.h – the header file that defines the stack machine operations

A makefile is useful, but optional for this assignment.  If you created a makefile, include it in your submission.

All files should be well documented with function comment blocks and inline comments that explain complicated code routines.  While no explicit style guidelines are set for programming in this course, code should be documented and readable.  Include your name, section, and lab name in a comment block at the top of each file, including the given header file.

NOTE: do ***NOT*** submit any IDE configuration files (.idea, project files, etc.).  Only submit your source files and report.

Prepare a lab report and submit it along with your source code.  The report should include the following:

- Your name, date, and lab title 
- Introduction – a description of the lab in your own words
- Design and Testing Methodology – a description of your design decisions and the process you took to create your test driver
- Resources – a description of any external resources you used to complete the lab
- Build – instructions on how to build and run your program.  Include the exact commands that are necessary 
- Analysis – Discuss the key concepts from the lab and answers to the following questions 
  - All the stack machine functions need a "reference" to the stack structure, and according to this design, that stack reference is passed as a pointer. Why is this necessary? Do all the stack functions need this to be passed as a pointer? Any exceptions? Be specific in your answer. 
  - Unlike a Java or C++ implementation, this implementation cannot "hide" any of the internal structure of the stack. That is, users of the stack could mess up the next pointers if they are careless. Can you think of any way we could hide the structure of the stack to lessen the chances a user will mess up the stack? Describe in brief detail. 
  - What if all smClear() did was assign NULL to top in the stack structure and nothing else. Would the program crash? Would there be any side effects? Try it and report results. 
  - Give an example of why it might be helpful to provide an iterator or random access to elements stored in the stack (rather than always accessing the top) and outline how you could implement such a feature. 
- Conclusion 
  - Summary of what you learned in the lab 
  - What specifically was challenging about this lab? 
  - What did you like about it? 
  - What could we do to improve it for others?

NOTE: You should ensure that this program compiles without warning (-Wall and -Wextra) prior to submitting.

Create a zip file containing your source files and your report and submit the zip file per your instructor's instructions.

## Grading Criteria (100 Points)

- (35 Points) Report
  - (5 Points) Report Introduction - Thorough description of the lab in your own words. 
  - (5 Points) Design and Testing Methodology - Detailed description of design and method for testing your implementation. 
  - (20 Points) Analysis - Answers to the analysis questions
  - (5 Points) Conclusion - Thorough conclusion with description of what you learned, what you liked, and suggestions for lab improvements.
- (5 Points) Documented Resources - Description of external resources used to complete the lab
- (5 Points) Correct Submission - Followed submission instructions (e.g. IDE project files are not submitted)
- (5 Points) Build - Code compiles without warnings or errors
- (10 Points) Test Cases - Thoroughness of submitted test driver 
- (35 Points) Instructor Tests - Implementation passes all instructor test cases 
- (5 Points) Memory Management - Program execution is free from memory leaks