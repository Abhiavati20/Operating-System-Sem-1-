// including some necessary files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>

// a function to swap to data 
// parameter addresses of the data to be swapped
void swap(int *xp, int *yp)
{
    // swapping the data using temp variable
    int temp = *xp;                             
    *xp = *yp;                                  
    *yp = temp;
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

// a function to sort the array of elements in ascending way
// algorithm used bubble sort
void bubbleSort(int *arr, int size)
{   
    int i, j;                                       // index variable
    for (i = 0; i < size - 1; i++)                  // looping through the array
    {
        for (j = 0; j < size - i - 1; j++)          // nested array
        {
            if (arr[j] > arr[j + 1])                // comparing the consecutive elements 
                swap(&arr[j], &arr[j + 1]);         // swapping those elements if they passes the condition
        }
    }
}
// the following method will be useful to print the array
void printArray(int *arr, int size)
{
    int i = 0;                                      // index variable
    printf("\n[ ");                                 // print message
    for(; i < size-1; i++)                          // looping through array
        printf("%d, ",arr[i]);                      // printing array elements
    printf("%d ]\n",arr[i]);                        // printing last element of array
}

// the following function is usefull for providing user choice menu
void userMenu()
{
    printf("\n1. BASIC EXECUTION");                 // option for basic execution
    printf("\n2. ORPHAN STATE EXECUTION");          // option for orphan state demonstration
    printf("\n3. ZOMBIE STATE EXECUTION");          // option for zombie state demonstration
}

// execution and compilation of program will start from main function
int main()
{
    int n;                                          // no of elements variable
    printf("No Of Elements : ");                    // message to user
    scanf("%d",&n);                                 // scanning the value of n from user
    int arrOfEle[n];                                // dynamically defining the size of array
    printf("\nEnter Array Elements\n");             // message to user
    for(int i = 0; i < n; i++)                      // looping till n in order to scan elements one by one
    {
        scanf("%d",&arrOfEle[i]);                   // scanning array elements 1 by 1
    }

    printf("\nINITIALLY THE ARRAY IS \n");          // user message
    printArray(arrOfEle, n);                        // invoking array print function

    // Zombie process and Orphan process wont work during execution of the process
    // for that we need to run two different process in order to demonstrate both zombie and orphan state
    
    int choice;                                     // variable to store user choice

    userMenu();                                     // invoking function in order to display user menu

    printf("\nEnter Your Choice : ");               // message to user
    scanf("%d",&choice);                            // scanning user choice

    // in order to represent the process ids we will use pid_t
    // pid_t stands for process identification
    pid_t process;
    
    // using system call we need to create a child process which will run concurrently with process that makes call
    process = fork();                               // fork returns some value
    // fork returns negative value i.e. child process creation unsuccessful
    // fork return positive value i.e. Returned to parent process and the value is process id of the child
    // fork return zero value i.e. returned newly created child process
    
    
    // if the value returned from fork is 0 then we are executing child process
    // in the child process we will sort array elements with selection sort
    // in the parent process we will sort array elements with bubble sort

    switch (choice)
    {
        case 1:
            // we need to perform the basic execution
            printf("\nINITIATING BASIC EXECUTION\n");
            if(process == 0)                                    // check if we are running child process or not
            {
                printf("\nWE ARE IN CHILD PROCESS\n");          // user message
                // printing values of child process id and its parent process id
                printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID :%d\n", getpid(), getppid()); 
                

                printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
                selectionSort(arrOfEle, n);                     // invoking selection sort
                
                printf("\nSORTING COMPLETED\n");                // user message

                printf("PRINTING SORTED ARRAY");                // message to user

                printArray(arrOfEle, n);                        // invoking array print function
            }
            else                                                // if false the we are executing parent process
            {
                printf("\nWE ARE IN PARENT PROCESS\n");         // user message
                wait(NULL);                                     // will block parent process until any of its children has finished
                printf("\nPARENT PROCESS WITH PID : %d ", getpid()); // user message
                printf(" AND ITS CHILD ID WAS: %d\n", process); //user message
                
                printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
                bubbleSort(arrOfEle, n);                        // invoking bubble sort

                printf("\nSORTING COMPLETED\n");                // user message

                printf("PRINTING SORTED ARRAY");                // message to user

                printArray(arrOfEle, n);                        // invoking array print function            
            }
            break;
        case 2 :
            printf("\nWORKING ON ORPHAN STATE\n");
            
            if(process == 0)                                    // check if we are running child process or not
            {
                printf("\nWE ARE IN CHILD PROCESS\n");          // user message
                // printing values of child process id and its parent process id
                printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID :%d\n", getpid(), getppid()); 
                
                

                printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
                selectionSort(arrOfEle, n);                     // invoking selection sort
                
                printf("\nSORTING COMPLETED\n");                // user message

                printf("PRINTING SORTED ARRAY");                // message to user

                printArray(arrOfEle, n);                        // invoking array print function
            }
            else                                                // if false the we are executing parent process
            {
                // in the orphan state parent process will not wait for child to complete its execution
                printf("\nWE ARE IN PARENT PROCESS\n");          // user message
                printf("\nPARENT PROCESS WITH PID : %d ", getpid()); // user message
                printf(" AND ITS CHILD ID WAS: %d\n", process); //user message
                
                printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
                bubbleSort(arrOfEle, n);                        // invoking bubble sort

                printf("\nSORTING COMPLETED\n");                // user message

                printf("PRINTING SORTED ARRAY");                // message to user

                printArray(arrOfEle, n);                        // invoking array print function            
            }
            break;
        
        case 3 :
            printf("\nINITIATING ZOMBIE EXECUTION...!!\n\n");

            if (process == 0)
            {
                printf("\nWE ARE IN CHILD PROCESS\n");          // user message
                // printing values of child process id and its parent process id
                printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID :%d\n", getpid(), getppid()); 
                
                

                printf("\nSORTING ARRAY ELEMENTS\n");           // user message
                
                selectionSort(arrOfEle, n);                     // invoking selection sort
                
                printf("\nSORTING COMPLETED\n");                // user message

                printf("PRINTING SORTED ARRAY");                // message to user

                printArray(arrOfEle, n);                        // invoking array print function
            }

            else
            {
                sleep(5);
                // in the Zombie state parent process will wait for 5 sec so that child goes in zombie state
                printf("\nWE ARE IN PARENT PROCESS\n");         // user message
                printf("\nPARENT PROCESS WITH PID : %d ", getpid()); // user message
                printf("AND ITS CHILD ID WAS: %d\n", process); //user message
                
                printf("\nSORTING ARRAY ELEMENTS\n");          // user message
                
                bubbleSort(arrOfEle, n);                       // invoking bubble sort

                printf("\nSORTING COMPLETED\n");               // user message

                printf("PRINTING SORTED ARRAY");               // message to user

                printArray(arrOfEle, n);                       // invoking array print function 
            }
            break;
        default:
            printf("\nINVALID INPUT!!\n");
            break;
    }
    return 0;
}