// header file
#include <stdio.h>

// compilation and execution of program starts from main function
int main()
{
    int arrivalTime[10];                                // arrival time array
    int burstTime[10];                                  // burst time array
    int temp[10];                                       // temporary array

    int i, smallest, count = 0, time;                               // some index variables and count variables

    double wait_time[10] = {0}, turnaround_time[10] = {0};          // wait time and turn around time as well as completion(end) time
    double end[10] = {0};                                           // completion time
    float avg_waiting_time = 0, avg_turnaround_time = 0;            // average of wait and turn around time

    int noOfProcess;                                                // variable to store total no of process;

    printf("\nENTER NO OF PROCESS : ");                             // message to user
    scanf("%d",&noOfProcess);                                       // scanning total no of process

    printf("\nENTER DETAILS OF PROCESSES\n");                       // user message
    for(i = 0; i < noOfProcess; i++)
    {
        printf("\nENTER ARRIVAL TIME : ");                          // user message
        scanf("%d",&arrivalTime[i]);                                // scanning ith process arrival time
    
        printf("ENTER BURST TIME : ");                              // user message
        scanf("%d",&burstTime[i]);                                  // scanning ith process burst time

        temp[i] = burstTime[i];                                     // assigning ith burst time to temp ith index   
    }
    burstTime[9] = 9999;                                            // making 9th index of burst time as max value

    for (time = 0; count != noOfProcess; time++)                    // looping till the count comes equal to noOfProcess
    {
        smallest = 9;                                               // assigning smallest to largest index
        for (i = 0; i < noOfProcess; i++)                           // nested loop
        {
            if (arrivalTime[i] <= time && burstTime[i] < burstTime[smallest] && burstTime[i] > 0)
            {
                // in above condition we are comparing arrival time with current process in order to look for preemption of process
                // we are also comparing the ith burst time with smallest index , we also checked if ith burst time > 
                smallest = i;
            }
        }
        burstTime[smallest]--;                                      // decrementing the smallest index burst time since it will be executed
        if (burstTime[smallest] == 0)                               // now if burst time of smallest index is 0
        {
            count++;                                                // we will increment the count as a process has completed its execution
            end[smallest] = time + 1;                                         // calculate completion time
            wait_time[smallest] = wait_time[smallest] + end[smallest] - arrivalTime[smallest] - temp[smallest];   // calculating wait time of process
            turnaround_time[smallest] = turnaround_time[smallest] + end[smallest] - arrivalTime[smallest];        // calculating turnAround time
        }
    }
    for(i = 0; i < noOfProcess; i++)                                // looping till no of process
    {
        avg_waiting_time += wait_time[i];                           // calculating total wait time
        avg_turnaround_time += turnaround_time[i];                  // calculating total tat
    }
    avg_waiting_time /= noOfProcess;                                // calculating average wait time 
    avg_turnaround_time /= noOfProcess;                             // calculatin average tat
    
    // printing process table
    printf("\n\nID \t AT \t BT \t CT \t TAT \t WT \n");        // table header
    for(i = 0; i < noOfProcess; i++)
    {
        printf("%d \t%d \t%d \t%.1lf \t%.1lf \t%.1lf \n",i,arrivalTime[i],temp[i],end[i],turnaround_time[i],wait_time[i]);
    }
    
    printf("\nAverage Waiting Time:%.2f\n", avg_waiting_time);
    printf("Average Turnaround Time:%lf\n", avg_turnaround_time);
    return 0;
}