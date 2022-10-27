/*************************************
 * 
 * Class: CS3840 - YOUR SECTION HERE
 * 
 * Name(s): Mitchell Johnstone
 * 
 * Lab: Teeny Tiny Shell
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define INPUT_MAX 256
#define CMD_MAX 5
#define ARG_MAX 10

/* read_cmd_string()
 *     Reads a line of text from the user
 *         Parameters:  dest - target location for the input
 *         Returns: int - 0 on success or 
 *                        -1 on error
 */
int read_cmd_string(char dest[INPUT_MAX])
{
	// Read user input
	if(fgets(dest, INPUT_MAX, stdin) == NULL) {
		fprintf(stderr, "Unable to read user input\n");
		return -1;
	}

	// Remove trailing return character
	int len = strlen(dest);
	if(dest[len-1] == '\n') {
		dest[len - 1] = '\0';
	}

	return 0;
}

/* parse_commands()
 *     Reads a line of text from the user
 *         Parameters:  input - string containing user input
 *                      cmd_strs - the target array for command strings
 *         Returns: int - The number of commands found or
 *                        -1 on error
 */
int parse_commands(char input[INPUT_MAX], char cmd_strs[CMD_MAX][INPUT_MAX])
{
	// Chop the input into command strings
	int cmd_count = 0;
	char* cmd_ptr = strtok(input, ";");
	while(cmd_ptr) {
		if(cmd_count >= CMD_MAX) {
			fprintf(stderr, "Too many commands\n");
			return -1;
		}
		strncpy(cmd_strs[cmd_count], cmd_ptr, INPUT_MAX);
		cmd_count++;
		cmd_ptr = strtok(NULL, ";");
	}

	return cmd_count;
}

/* parse_args()
 *     Reads the args from a command
 *         Parameters:  input - string containing user input
 *                      arg_strs - the target array for argument strings
 *         Returns: int - The number of arguments found or
 *                        -1 on error
 */
int parse_args(char cmd[INPUT_MAX], char * arg_strs[ARG_MAX])
{
    // chop input into arguments!
	int arg_count = 0;
    int sawQuote = 0;
    int sawSpace = 1;
    for(int i = 0; cmd[i]; i++){
        if(cmd[i] == ' '){
            if(!sawQuote && !sawSpace){
                cmd[i] = '\0';
            }
            sawSpace = 1;
        }
        else 
        {
            if(!sawQuote && sawSpace){
                arg_strs[arg_count++] = cmd + i;
                sawSpace = 0;
            }
            if(cmd[i] == '\"') sawQuote ^= 1;
        }

        if(arg_count > ARG_MAX){
            printf("Too many arguments");
            return -1;
        }
    }
    arg_strs[arg_count] = NULL;
    return arg_count;
}

int main()
{
	char user_input[INPUT_MAX];
	char cmd_strs[CMD_MAX][INPUT_MAX];
    char * arg_strs[ARG_MAX+1];

	// get input from the user in a loop
    while(1){

        // Print the input prompt
        printf("$> ");

        // Read user input
        if(read_cmd_string(user_input) == -1) {
            return 1;
        }

        // handle the 'quit' command
        if(!strcmp(user_input,"quit")){
            return 0;
        }

        // Chop the input into command strings
        int cmd_count = parse_commands(user_input, cmd_strs);
        if(cmd_count == -1) {
            return 1;
        }

        // Chop the commands into arguments and execute one at a time
        for(int i = 0; i < cmd_count; i++) {

            
            //    1) Chop the command into command line arguments
            //        need to handle up to 10 arguments
            //        NOTE: the command name is always the first argument
            int arg_count = parse_args(cmd_strs[i], arg_strs);
            if(arg_count == -1){
                return 1;
            }

            // prints out all arguments
            //for(int j = 0; j < arg_count; j++) printf("%s\n", arg_strs[j]);

            //    2) fork a process
            if(!fork()){
                //    3) execute the command with execvp
                execvp(arg_strs[0], arg_strs);
                return 0;
            }
            //    4) wait for previous cmd
            wait(NULL);
        }
    }
	
	return 0;
}
