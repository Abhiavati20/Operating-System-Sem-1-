// including header files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// the following method will be useful to print the array
void swap(int *xp, int *yp)
{
    // swapping the data using temp variable
    int temp = *xp;                             
    *xp = *yp;                                  
    *yp = temp;
}
void printArray(int *arr, int size)
{
    int i = 0;                                      // index variable
    printf("\n[ ");                                 // print message
    for(; i < size-1; i++)                            // looping through array
        printf("%d, ",arr[i]);
    printf("%d ]\n",arr[i]);
}

// a function to sort the array of elements
// algorithm used selection sort
void selectionSort(int *arr, int size)
{
    int i, j, minIndex;                             // index variables
    for(i = 0; i < size; i++)                       // looping through the array
    {
        minIndex = i;
        for(j = i+1; j < size; j++)                 // nested loop 
            if(arr[j] < arr[minIndex])              // check if jth element is smallest then i th element
                minIndex = j;                       // if true then change the minIndex
        swap(&arr[i], &arr[minIndex]);              // swapping the minIndex with i th   
    }
}

// execution and compilation of program will start from main function
int main()
{
    int n;                                          // no of elements variable
    printf("No Of Elements : ");                    // message to user
    scanf("%d",&n);                                 // scanning the value of n from user
    
    char *arg[n], str1[n];                          // character array useful for passing command line arguements

    int arrOfEle[n];                                // dynamically defining the size of array
    printf("\nEnter Array Elements\n");             // message to user
    for(int i = 0; i < n; i++)                      // looping till n in order to scan elements one by one
    {
        scanf("%d",&arrOfEle[i]);                   // scanning array elements 1 by 1
    }

    printf("\nINITIALLY THE ARRAY IS \n");          // user message
    printArray(arrOfEle, n);                        // invoking array print function

    printf("PARENT PROCESS ID : %d", getpid());     // user message 

    // in order to represent the process ids we will use pid_t
    // pid_t stands for process identification
    pid_t process;
    
    // using system call we need to create a child process which will run concurrently with process that makes call
    process = fork();                           // fork returns some value
    // fork returns negative value i.e. child process creation unsuccessful
    // fork return positive value i.e. Returned to parent process and the value is process id of the child
    // fork return zero value i.e. returned newly created child process
    
    
    // if the value returned from fork is 0 then we are executing child process
    // in the child process we will sort array elements with selection sort
    // in the parent process we will sort array elements with bubble sort
    if (process == 0)
    {
        
        printf("\n\nWE ARE IN CHILD PROCESS, WE WILL INVOKE execv()\n");                                     // user message
        printf("\nCHILD PROCESS ID : %d & ITS PARENT PROCESS ID : %d\n",getpid(),getppid());       // user message
        
        for (int i = 0; i < n; i++)                                                                // looping through
        {
            // sprintf stands for “String print”. Instead of printing on console, it store output on char buffer which are specified in sprintf.
            sprintf(str1, "%d", arrOfEle[i]);
            arg[i] = (char *)malloc(sizeof(char));                                                  // storing the argument on heap
            strcpy(arg[i], str1);                                                                   // copying the buffer string into arg[i]
        }
        arg[n] = NULL;
        
        printf("\nStarted Executing EXECVE \n");
        execv("./child.exe", arg);
        printf("EXECV EXECUTION COMPLETED");
    }
    else if (process > 0)
    {
        printf("\nWE ARE IN PARENT PROCESS\n");         // user message
        wait(NULL);                                     // will block parent process until any of its children has finished
        printf("\nPARENT PROCESS WITH PID : %d ", getpid()); // user message
        printf(" AND ITS CHILD ID WAS: %d\n", process);  //user message
                
        printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
        selectionSort(arrOfEle, n);                        // invoking bubble sort

        printf("\nSORTING COMPLETED\n");                // user message

        printf("PRINTING SORTED ARRAY");                // message to user

        printArray(arrOfEle, n);                        // invoking array print function
    }
    return 0;
}