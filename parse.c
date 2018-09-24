#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parse.h"


//Initallizes a structure with type: Param_t, allocating memory and assigning some intial values
Param_t *initParam(){
  
  Param_t *param = malloc(sizeof(Param_t));
  param->inputRedirect = NULL;
  param->outputRedirect = NULL;
  param->background = 0;
  param->argumentCount = 0;
  return param;
}

//Parses the input from the user into tokens and organizes them into the struct param
void parseParams(Param_t *param, char *input){
  
  char *delim = " \n\t"; //The deliminator that strtok uses to parse tokens
  char *token, *input_end; //Pointer to the next token and pointer to the last token in the input buffer
  
  
  token = strtok(input, delim); //Tokenize input to get first token
    if (token != NULL)
      input_end = token;//If token is not NULL then the end of the input buffer is token at this point
      while (token != NULL){
        if (*token == '<'){
          token += 1;//If the '<' is the first character in token then increment token to omit the '<'
          param->inputRedirect = token; //set inputRedirect pointer = token
        }
        else if(*token == '>'){
          token += 1;//If the '>' is the first character in token then increment token to omit the '>'
          param->outputRedirect = token;//set outputRedirect pointer = token
        }
        else{
          param->argumentVector[param->argumentCount] = token;//Input is not a redirect therfore add the token to the argumentVector
          param->argumentCount++;//Increment argumentCount to keep track of how many arguments are recorded
        }
        token = strtok(NULL, delim);//Point to the next token in input
        if (token != NULL)
          input_end = token;//If there is a new token then that becomes the last token in the input buffer
      }
  //The code that will read inputRedirect into the argument vector
  if (param->inputRedirect != NULL){
    FILE *fp = fopen(param->inputRedirect, "r");//open the file that contains input
    input_end += strlen(param->argumentVector[param->argumentCount-1]+2)+2;//Use strlen to locate the end of the input buffer to prevent overwriting other parameters
    fgets(input_end, 256, fp);//read and write the input into the location found by input_end
    param->argumentVector[param->argumentCount] = input_end;//add the new input to the argumentVector
    param->argumentCount++;//count another argument 
    fclose(fp);//close the file
  }
}

//Program to print the contents of the struct with type Param_t
void printParams(Param_t * param){
  
  int i, status; //i used as counter in for loop and status is used by wait to indicate status 
  FILE *fp; //Pointer to the file that is used in output redirect
  pid_t pid, wpid; //the pid numbers used to create a child for output redirect
  
  pid = fork(); // create child so that output redirect does not effect stdout of parent
  
  //if the process is the child
  if (pid == 0){
    if (param->outputRedirect != NULL){
      fp = freopen(param->outputRedirect, "w", stdout);//if outputRedirect is specified then redirect the output to that file
    }
    //Print all varibles within the struct param
    printf("InputRedirect: [%s]\n", (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
    printf("OutputRedirect: [%s]\n", (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
    printf("Background: [%d]\n", param->background);
    printf("ArgumentCount: [%d]\n", param->argumentCount);
    for (i=0; i<param->argumentCount; i++){
      printf("ArgumentVector[%2d]: [%s]\n",i,  param->argumentVector[i]);
    }
    if (param->outputRedirect != NULL){
      fclose(fp); //if the output was redirected, close the file that was opened for streaming
    }
    exit(1);//exit child
  }
  //wait for the child to finish executing before returning to ensure the child terminated
  while ((wpid = wait(&status)) > 0){
  }
  return;
}
void executeShell(Param_t * param){
  
  //i is used in the for loop, numProc is used to allocate the necessary memory for the array of pid numbers and argumentVectors
  //status is used by wait() to record its status
  int i, numProc, status = 0;
  
  numProc = atoi(param->argumentVector[1]); //convert the string representing the number of processes to create to a integer
  pid_t pidArray[numProc];//create an array of pid numbers to record them as they are created
  char *argv[numProc][32]; //an array of argument Vectors, In memory it is a matrix of pointers to strings
  
  pid_t pid, pid_parent, wpid; //pid numbers for the child, parent, and wait 
  pid_parent = getpid(); //record the pid number of the parent
  
  //create all the child processes and record their pid into the pid array
  for(i=0; i<numProc; i++){
    if((pid = fork())==0){
      pidArray[i] = getpid();//at iteration i save the pid of the child
      break;
    }
  }
  
  int j; //varible is only local to each individual child and parent
  if (getpid() != pid_parent) //if current process is not the parent
    for(j=0; j<numProc; j++){ //loop until the current pid matches one in the pid array
      if(getpid() == pidArray[j]){ //if a matching pid is found then proceed
      char c_i = '0'+j; //the iteration of the loop is used to number the children
      char b[32] = "./"; //append the ./ to the begining of the program name that is to be ran
      char *command = strcat(b, param->argumentVector[0]); //strcat is used to concatinate the ./ to the program name
      argv[j][0]= param->argumentVector[0];
      argv[j][1]= param->argumentVector[1];
      argv[j][2]= &c_i;
      argv[j][3]= param->argumentVector[2];
      argv[j][4]= NULL;
      execv(command, argv[j]);
      //execv("./test", argv);
      exit(1);
      }
    }
  
  while ((wpid = wait(&status)) >0){
    printf("child process completed\n");
  }
}

