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

void printParams(Param_t *param);

void parseParams(Param_t *param, char *input);

Param_t *initParam();

#endif