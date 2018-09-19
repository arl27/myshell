#include <stdio.h>
#include <stdlib.h>

/**
 * Tests for primality of a given value.
 *
 * @param value the value to be tested
 *
 * @return 1, if value is prime; otherwise 0
 */
int isPrime(int value) {
    if (value == 1) {
        return 0;
    }
    if (value == 2) {
        return 1;
    }
    if (value % 2 == 0) {
        return 0;
    }

    int i;
    for (i=3; i < value/2; i++) {
        if (value % i == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Tests numbers within a given range for primality. Prime numbers will be printed to 
 * the screen line-by-line.
 *
 * @param start the first number of a range of numbers to be tested
 * @param end the last number of a range of numbers to be tested
 */
void testPrimality (int start, int end)
{
    while (start < end) {
        if (isPrime(start)) {
            printf ("%d\n", start);
        }
        start++;
    }
}

int main (int argc, char** argv)
{
    if (argc != 4) {
        printf ("invalid number of parameters; usage: prime <countInstances> <index> <value>\n");
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

    testPrimality (start, end);

    return 0;
}
