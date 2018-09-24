#ifndef PARSE_H
#define PARSE_H

#define MAXARGS 32

struct PARAM
    {
      char *inputRedirect;           /* file name or NULL */
      char *outputRedirect;          /* file name or NULL */
      int  background;               /* either 0 (false) or 1 (true)*/
      int  argumentCount;            /* number of tokens in argument vector */
      char *argumentVector[MAXARGS]; /* array of strings */
    };

 typedef struct PARAM Param_t;

//Prints all the elements of the param struct
void printParams(Param_t *param);

//Tokenizes the user input of the shell and writes the information into the struct param
void parseParams(Param_t *param, char *input);

//Initializes the stucture param, allocating memory, and assigning some inital values. 
Param_t *initParam();

//Process to carry out commands from the user input using the 
void executeShell(Param_t *param);

#endif