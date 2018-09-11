#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
//#include "vector.h"


int main ( int argc, char **argv )
{
    Param_t *param = initParam();   
    char input[256];
  
    while (1){
      printf("Enter command: ");
      scanf(" %[^\n]", input);
      parseParams(param, input);
      
      if (argv[1] != NULL && !strcmp(argv[1], "-debug"))
        printParams(param); 
      if (!strcmp(param->argumentVector[0],"exit")){
        free(param);
        return 0;
      }
      param->argumentCount = 0;
      param->inputRedirect = NULL;
      param->outputRedirect = NULL;
    }
    
    free(param);
    return 0;
}