// including header files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>

int main(int argc, char *argv[])
{
    // argc = length of argv array
    int revarr[argc], arrint[argc];                         // array to store reverse of command line arguements 
    

    // converting string array to integer array
    for (int i = 0; i < argc; i++)                          // looping through string array i.e. cmd line arguements
        arrint[i] = atoi(argv[i]);                          // convert string into int and store it into array
    
    printf("\nREVERSING THE ARRAY\n");                      // user message
    for (int i = 0; i < argc; i++)                          // looping through array
        revarr[i] = arrint[argc - i - 1];                   // reversing the array

    printf("\nREVERSED ARRAY\n");                           // user message
    printf("\n[ ");                                         // print message
    int j =0;           
    for(j = 0; j < argc-1; j++)                            // looping through array
        printf("%d, ",revarr[j]);                          // printing array elements
    printf("%d ]\n",revarr[j]);                            // printing last element
    
    return 0;
}