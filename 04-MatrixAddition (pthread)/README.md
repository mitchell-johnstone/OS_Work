## Introduction

For this lab you will create a program that add matrices and times the addition just as in lab 3, except in this lab you will do so with threads.

## Details

You should determine the number of cores on your computer and write a program such that each thread (including the main thread) does and qual amount of computation.

In other words if I have 4 cores (8 threads) on my computer and an 7x7 matrices (49 values) then each thread should do 49 / 8 (integer division) additions with the main thread picking up the any remainder. Thus, in this case, the main thread does 7 addtions and every  other thread 6.

Assume all matrices will require each thread to do at least 1 addition.

## Testing and Debugging

There are [several matrix files](matrices.zip) located provided along with this specification.  You can use those to help get your programs working.  You are also required to create some of your own and include those in your submission.  Don't forget to test large matrices.

## Deliverables

You will need to include all your source files and any other resources you used to complete lab. 

A makefile is useful, but optional for this assignment.  If you created a makefile, include it in your submission. 

All files should be well documented with function comment blocks and inline comments that explain complicated code routines.  While no explicit style guidelines are set for programming in this course, code should be documented and readable.  Include your name, section, and lab name in a comment block at the top of each file.

NOTE: do ***NOT*** submit any IDE configuration files (.idea, project files, etc.).  Only submit your source files.

NOTE: You should ensure that this program compiles without warning (-Wall and -Wextra) prior to submitting.

Prepare a zip file with all submitted files and upload the file to Canvas per your instructor's instructions.

## Grading Criteria (100 Points)

Demonstrate that your lab is working by compiling it, running it, and running any test code in person during lab hours.
