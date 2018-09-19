#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    if (argc != 4) {
        printf ("invalid number of parameters; usage: testme <countInstances> <index> <value>\n");
        return -1;
    }

    int numInst = atoi( argv[1] );
    if (numInst <= 0) {
        printf ("invalid number of instances; value cannot be 0 or negative\n");
        return -1; 
    }


    int index = atoi( argv[2] );
    if (index < 0 || index >= numInst) {
        printf ("invalid index; value must be greater or equal to zero and less the total number of instances\n");
        return -1;
    }

    int val = atoi ( argv[3] );
    if (val <= 0) {
        printf ("invalid parameter value; value must be greater than zero\n");
    }

    int start = index*val/numInst;
    int end = (index+1)*val/numInst;

    printf ("run %d of %d: processing values %d through %d\n", index, numInst, start, end); 

    return 0;
}
