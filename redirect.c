//  Created by Ryan Rushton U5192657 on 1/04/2014.
//  Comp2300 Assignment 1
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define STD_IN 0
#define STD_OUT 1

/*
redirect is a recursive function that redirects file when the appropriate
symbols are found. It is pretty straight forward so I will leave comments to a
minimum
*/

void redirect(char ***args, int i){

	if(args[i] != NULL){

	    //Case when a < is found. If the next args is not null it changes
	    //STD_IN to the file

		if(strcmp(args[i][0], "<")==0){
			if(args[i+1][0] == NULL){
				printf("Error: You need an input file.\n");
				exit(EXIT_FAILURE);
			}
			else{
				int infile = open(args[i+1][0], O_RDONLY);
				dup2(infile, STD_IN);
				redirect(args, i+1);
			}
		}

		//Case when a > is found.If the next args is not null it changes
	    //STD_OUT to the file

		if(strcmp(args[i][0], ">")==0){
			if(args[i+1][0] == NULL){
				printf("Error: You need a file to write to.\n");
				exit(EXIT_FAILURE);
			}
			else{
				int outfile = open(args[i+1][0], O_WRONLY | O_CREAT, S_IRUSR |
				    S_IWUSR);
				        dup2(outfile, 1);
				        redirect(args, i+1);
			}
		}

		//Case when >> is foundIf the next args is not null it changes
	    //STD_OUT to the file and appends to the end of it

		if(strcmp(args[i][0], ">>")==0){
			if(args[i+1][0] == NULL){
				printf("Error: You need a file to write to.\n");
				exit(EXIT_FAILURE);
			}
			else{
				int outfile = open(args[i+1][0], O_APPEND | O_WRONLY | O_CREAT,
				    S_IRUSR | S_IWUSR);
				        dup2(outfile, STD_OUT);
				        redirect(args, i+1);
			}
		}

		//Skips over the program/arguements

		else{
			redirect(args, i+1);
		}
	}

	//Executes the initial program. Note throughout the printf is placed after
	//execvp as if wont be called unless execvp fails.

	if(args[i] == NULL){
		if(strcmp(args[0][0], "cd") == 0){
			exit(EXIT_SUCCESS);
		}
		else{
			if(strcmp(args[0][0], "q") == 0){
				exit(EXIT_SUCCESS);
			}
            execvp(args[0][0], args[0]);
			printf("Error: %s is not a valid entry\n", args[i-1][0]);
			exit(EXIT_FAILURE);
		}
	}
}
