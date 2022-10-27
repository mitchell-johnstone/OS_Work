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