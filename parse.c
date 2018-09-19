#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
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
  char *token, *input_end;
  
  
  token = strtok(input, delim);
    if (token != NULL)
      input_end = token;
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
        if (token != NULL)
          input_end = token;
      }
  if (param->inputRedirect != NULL){
    FILE *fp = fopen(param->inputRedirect, "r");
    input_end += strlen(param->argumentVector[param->argumentCount-1]);
    fgets(input_end, 256, fp);
    param->argumentVector[param->argumentCount] = input_end;
    param->argumentCount++;
    fclose(fp);
  }
}

void printParams(Param_t * param){
  
  int i, status;
  FILE *fp;
  pid_t pid, wpid;
  
  pid = fork();
  if (pid == 0){
    if (param->outputRedirect != NULL){
      
      fp = freopen(param->outputRedirect, "w", stdout);
    }
    printf("InputRedirect: [%s]\n", (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
    printf("OutputRedirect: [%s]\n", (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
    printf("Background: [%d]\n", param->background);
    printf("ArgumentCount: [%d]\n", param->argumentCount);
    for (i=0; i<param->argumentCount; i++){
      printf("ArgumentVector[%2d]: [%s]\n",i,  param->argumentVector[i]);
    }
    if (param->outputRedirect != NULL){
      
      fclose(fp);
    }
    exit(1);
  }
  while ((wpid = wait(&status)) > 0){
  }
  return;
}
void executeShell(Param_t * param){
  
  int i, numProc, status = 0;
  char childNum;
  char *argv[] = {"test", NULL};
  numProc = atoi(param->argumentVector[1]);
  
  pid_t pid, pid_parent, wpid;
  pid_parent = getpid();
  for(i=0; i<numProc; i++){
    if((pid = fork())==0)
      break;
  }
  
  if (getpid() != pid_parent){
    childNum = i;
    //argv[0]= param->argumentVector[0];
    //argv[1]= childNum;
    //argv[2]= param->argumentVector[2];
    printf("in child process: %d\n", getpid());
    execv("./test", argv);
    printf("execv failed in child: %d\n", getpid());
    exit(1);
  }
  
  while ((wpid = wait(&status)) >0){
    printf("child process completed\n");
  }
}

