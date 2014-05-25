// Ryan Rushton U5192657 Comp2300 Assignment 1
//
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "tokenize.h"
#include "redirect.h"
#include "piping.h"


#define STD_IN 0

/*
This is the main shell program. It handles the main fork
of the program, it sets the commandline information, it
contains the code for changing directory and takes input.
*/

int main(){
	int pid;
	int size = 512;
	char *in = malloc(size*sizeof(char));

	if(in != NULL){
    	char ***args;
    	char *my_env = {":/bin/:/usr/bin"};

    	//Here we set the PATH environ variable. This allows myshell to look
    	//in /bin, /usr/bin and the current directory
	    setenv("PATH", my_env, 1);


	    //'q' lets us quit the while loop and thus the program
    	while(in[0] != 'q'){
        	char cwd[2*size*sizeof(char)];
        	char *directory;
	        char *cwdtok = strtok(cwd, "/");
        	int count = 0;
        	char input;

	    	/*
	    	The getcwd and the while loop sets the command line text
	    	*/

		    getcwd(cwd, sizeof(cwd));

	        while(cwdtok != NULL){
		        directory = cwdtok;
		        cwdtok = strtok(NULL, "/");
	        }

	        printf("rshell:%s:> ", directory);

	        //This while loop gets the input for the shell
	        while((input = getchar()) != '\n' && input != EOF){
	            if(count > size-2){
	                char *temp;
	                size *= 2;
	                temp = realloc(in, size*sizeof(char));
	                if(temp != NULL){
	                    in = temp;
	                }
	                else{
	                    printf("Error: realloc failure of input");
	                    exit(EXIT_FAILURE);
	                }
	            }
	            in[count] = input;
	            count++;
	        }

	        // Here we execute commands if they are not
	        // new lines or 'q'
            if (strlen(in) > 0 && in[0]!='q') {

                // This tokenizes our input, see tokenize.c
                args = tokens(in);

                //Changes directory
                if(strcmp(args[0][0], "cd") == 0){
                    if(args[0][1] != NULL){
                        chdir(args[0][1]);
                    }
                    if(args[0][1] == NULL){
                        char *home = getenv("HOME");
                        chdir(home);
                    }
                }
                else if(strcmp(args[0][0], "<") == 0 ||
                         strcmp(args[0][0], ">") == 0 ||
                         strcmp(args[0][0], ">>") == 0 ||
                         strcmp(args[0][0], "|") == 0){
                             printf("Error: \"%s\" cannot be first character\n",
                                args[0][0]);
                }
                else{

                    // Here we fork and run the programs entered int the child
                    // with the parent waiting

                    pid = fork();

                    if(pid==0){
                        int has_pipe = pipe_find(args, 0);
                            if(has_pipe == 1){
                                //printf("INPIPE\n");
                                piper(args, 0, STD_IN);
                            }
                            else if(has_pipe == 0){
                                /*
                                This printf is for troubleshooting.
                                Currently when a single program or program
                                with >, < or >> is entered this part gets
                                skipped. I cannot seem to figure out why. It
                                gets executed without going through redirect
                                or piper.
                                */
                                //printf("IN REDIR\n");
                                redirect(args, 0);
                            }
                    }
                    else if(pid > 0){
                       int j;
                       if(count >0){
                           for(j=0; j<count;j++){
                               in[j] = 0;
                           }
                           count = 0;
                       }
                       wait(NULL);
                    }
                    else{
                        printf("fork failed");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        if(in[0] == 'q'){
	        free(in);
        }
	}
   	else{
        printf("Error: in malloc failed");
    	exit(EXIT_FAILURE);
    }
    return 0;
}
