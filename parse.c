#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"

Param_t *initParam(){
  
  Param_t *param = malloc(sizeof(Param_t));
  param->inputRedirect = NULL;
  param->outputRedirect = NULL;
  param->background = 0;
  param->argumentCount = 0;
  return param;
}

void parseParams(Param_t *param, char *input){
  
  char *delim = " \n\t";
  char *token;
  
  token = strtok(input, delim);
 
      while (token != NULL){
        if (*token == '<'){
          token += 1;
          param->inputRedirect = token;
        }
        else if(*token == '>'){
          token += 1;
          param->outputRedirect = token;
        }
        else{
          param->argumentVector[param->argumentCount] = token;
          param->argumentCount++;
        }
        token = strtok(NULL, delim);
      }
      
}

void printParams(Param_t * param){
  
  int i;
  printf("InputRedirect: [%s]\n", (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
  printf("OutputRedirect: [%s]\n", (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
  printf("Background: [%d]\n", param->background);
  printf("ArgumentCount: [%d]\n", param->argumentCount);
  for (i=0; i<param->argumentCount; i++){
    printf("ArgumentVector[%2d]: [%s]\n",i,  param->argumentVector[i]);
  }
  return;
}