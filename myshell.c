#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"


int main ( int argc, char **argv )
{
    //param is the stucture that organizes the user input
    Param_t *param = initParam();   
    //input is the buffer to hold all user input
    char input[256];
    char *reset
  
    while (1){
      //Prompt for user input and write into the input buffer
      printf("Enter command: ");
      scanf(" %[^\n]", input);
      //Tokenizes the input and organizes the user input into the param structure
      parseParams(param, input);
      
      //Print all the contents of the param stucture if -debug is used when shell is ran
      if (argv[1] != NULL && !strcmp(argv[1], "-debug"))
        printParams(param); 
      //Exit the shell if user input is "exit" and free memory 
      if (!strcmp(param->argumentVector[0],"exit")){
        free(param);
        return 0;
      }
      
      //Program did not exit so shell arguments are carried out 
      executeShell(param);
      
      //set the values of param to allow for it to be reused 
      param->argumentCount = 0;
      param->inputRedirect = NULL;
      param->outputRedirect = NULL;
    }
    //Should never reach here but if it did then memory would be freed
    free(param);
    return 0;
}