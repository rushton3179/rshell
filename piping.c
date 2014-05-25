//  Created by Ryan Rushton U5192657 on 1/04/2014.
//  Comp2300 Assignment 1
//

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include<sys/wait.h>

#define STD_IN 0
#define STD_OUT 1
#define PIPE_READ 1
#define PIPE_WRITE 0

/*
pipe_find looks for pipes in the arguments and returns 1 for true. It has inputs
of "args"-the arguement array, "in"-the position to start looking in the array
*/

int pipe_find(char *** args, int i){
	if(args[i] !=  NULL){
		if(strcmp(args[i][0], "|") == 0){
			return 1;
		}
		else{
			i++;
			return pipe_find(args, i);
		}
	}
	if(args[i] == NULL){
		return 0;
	}
	return 0;
}

/*
piper handles the recursive piping as well as any file redirection associated
with it. It has inputs of "args"-the arguement array, "in"-the position to start
looking in the array, "pipe_in"-the pipe to use replace STD_IN
*/

void piper(char ***args, int i, int pipe_in){
	
	if(args[i] != NULL){
	    
	    /*
	    This large if statement handles the output redirection and the case when
	    a program file is the last non-NULL arguement. Essentially it handles 
	    last few arguements
	    */
	    
	    //This is the case when a program is the last arguement
		if(i>0 && strcmp(args[i-1][0], "|") == 0){
			if(args[i+1] == NULL){
				dup2(pipe_in, STD_IN);
                execvp(args[i][0], args[i]);
				printf("Error: execve couldnt find %s\n", args[i][0]);
				exit(EXIT_FAILURE);
			}
			
			//This is the case when we have file output redirection, ie find
			// a ">"
			if(strcmp(args[i+1][0], ">") == 0){
				int outfile = open(args[i+2][0], O_WRONLY | O_CREAT, S_IRUSR | 
				    S_IWUSR);
				        dup2(outfile, STD_OUT);
				        dup2(pipe_in, STD_IN);
                        execvp(args[i][0], args[i]);
				        printf("Error: execve couldnt find %s\n", args[i][0]);
				        exit(EXIT_FAILURE);
			}
			
			//This is the case when we have file output redirection that appends
			//to the file, ie find a ">>"
			if(strcmp(args[i+1][0], ">>") == 0){
				int outfile = open(args[i+2][0], O_APPEND | O_WRONLY | 
				    O_CREAT, S_IRUSR | S_IWUSR);
				        dup2(outfile, STD_OUT);
				        dup2(pipe_in, STD_IN);
                        execvp(args[i][0], args[i]);
				        printf("Error: execve couldnt find %s\n", args[i][0]);
				        exit(EXIT_FAILURE);
			}
			if(strcmp(args[i+1][0], "|") != 0){
				printf("Error: %s is not a valid entry\n", args[i+1][0]);
				exit(EXIT_FAILURE);
			}
		}
		
		/*
		This large if statement handles the recursive piping and the case of
		input file redirection. It forks for each new pipe.
		*/
        
		if(strcmp(args[i][0], "|") == 0){
			int pid;
			int mypipe[2];
            
            if (args[i+1][0] == NULL) {
                printf("Error: You need a program to pipe to\n");
                exit(EXIT_FAILURE);
            }
            
			else{
			
                pipe(mypipe);
                pid = fork();
                
                if(pid == 0){
                    
                    //Case for input file redirection including program
                    //execution and pipe construction
                    if(i>2 && strcmp(args[i-2][0], "<") == 0){
                        int infile = open(args[i-1][0], O_RDONLY);
                        dup2(infile, STD_IN);
                        close(mypipe[PIPE_WRITE]);
                        dup2(mypipe[PIPE_READ], STD_OUT);
                        execvp(args[i-3][0], args[i-3]);
                        printf("Error: execve couldnt find %s\n", args[i-3][0]);
                        exit(EXIT_FAILURE);
                    }
                    
                    //Program execution and pipe construction
                    else{
                        close(mypipe[PIPE_WRITE]);
                        dup2(mypipe[PIPE_READ], STD_OUT);
                        dup2(pipe_in, STD_IN);
                        execvp(args[i-1][0], args[i-1]);
                        printf("Error: execve couldnt find %s\n", args[i-1][0]);
                        exit(EXIT_FAILURE);
                    }
                }
                
                //Here the parent recurses
                else if(pid>0){
                    close(mypipe[PIPE_READ]);
                    close(pipe_in);
                    piper(args, i+1, mypipe[PIPE_WRITE]);
					
                }
                else{
                    printf("Error: Fork failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
        
		else{
			piper(args, i+1, pipe_in);
		}
	}
}






