//  Created by Ryan Rushton U5192657 on 1/04/2014.
//  Comp2300 Assignment 1
//

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

/*
tokens takes a pointer to a string then creates a 2d array of pointers to
strings which is used as our array of arguements.
*/

char*** tokens(char *in){

    //As "out" is regarded as a matrix of strings we use n for row number and
    //m for column number as per usual notation with matrices.

	int n = 0, m = 0;
	int size_mtrx = 20;
	int size_row = 10;
	char ***out = malloc(size_mtrx*sizeof(char ***));

    if (out != NULL) {

        //We give the row of pointers some memory
        out[n] = malloc(size_row*sizeof(char **));

        if(out[n] != NULL){
            char *tok = strtok(in, " ");

            while(tok != NULL){

                /*
                The first two if statements handle the memory allocation.
                This printf was used to figure out the realloc for the array
                size. I thought it was interesting so I left it in.
                */

                //printf("%d, n = %d, %p\n", size, n, out);
                if (n>=size_mtrx-2) {
                    size_mtrx = size_mtrx*2;
                    char ***temp1 = realloc(out, 2*size_mtrx*sizeof(char ***));
                    if (temp1 != NULL) {
                        out = temp1;
                    }
                    else{
                        printf("Error: realloc failure");
                        exit(EXIT_FAILURE);
                    }
                }
                if (m>=size_row-2) {
                    size_row = size_row*2;
                    char **temp2 = realloc(out[n], 2*size_row*sizeof(char **));
                    if (temp2 != NULL) {
                        out[n] = temp2;
                    }
                    else{
                        printf("Error: realloc failure");
                        exit(EXIT_FAILURE);
                    }
                }

                //This handles tokens that aren't redirection operators.
                //It places successive ones in the columns of a row
                if(strcmp(tok, ">")!=0 && strcmp(tok, "<")!=0 &&
                    strcmp(tok, "|")!=0 && strcmp(tok, ">>")!=0){
                        out[n][m] = tok;
                        tok = strtok(NULL, " ");
                        m++;
                        if(tok == NULL){
                            out[n][m] = NULL;
                        }
                }

                /*
                This handles the operators. It places each new one in a new
                row. Note that if two are in succession there is a row with
                a NULL first element. This is handy to check for improper
                input
                */

                else{
                    if(n==0 && m==0){
                        out[n][m] = tok;
                        tok = strtok(NULL, " ");
                        if (tok != NULL) {
                            n++;
                            out[n] = (char**)malloc(size_row*sizeof(char **));
                        }
                    }
                    else{
                        out[n][m] = NULL;
                        n++;
                        m = 0;
                        out[n] = (char**)malloc(size_row*sizeof(char **));
                        out[n][m] = tok;
                        tok = strtok(NULL, " ");
                        n++;
                        out[n] = (char**)malloc(size_row*sizeof(char **));

                    }
                }
            }
        }
        else{
            printf("Error: tokens out[i] malloc failed.");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("Error: tokens out malloc failed.");
        exit(EXIT_FAILURE);
    }
	out[n+1] = NULL;
    return out;
}
