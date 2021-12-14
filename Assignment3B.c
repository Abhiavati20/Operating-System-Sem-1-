// following program is implemented using round robin
// including header files
#include <stdio.h>

int main()
{
    int noOfProcess;                                                // variable to store no of process
    int i, total = 0, x, timeQuantum;                               // index variables, and time quantum variable

    int arrivalTime[10];                                            // arrival time array
    int burstTime[10];                                              // burst time array
    int temp[10];                                                   // temporary array

    double wait_time[10] = {0}, turnaround_time[10] = {0};          // wait time and turn around time as well as completion(end) time
    double end[10] = {0};                                           // completion time
    float avg_waiting_time = 0, avg_turnaround_time = 0;            // average of wait and turn around time
    
    printf("\nENTER NO OF PROCESS : ");                             // message to user
    scanf("%d",&noOfProcess);                                       // scanning total no of process
    x = noOfProcess;                                                // assigning no of process to x variable 

    for (i = 0; i < noOfProcess; i++)                               // looping through no of process
    {
        printf("\nPROCESS ID %d \n", i + 1);                        // message to user
        printf("ARRIVAL TIME : ");                                  // message to user
        scanf("%d", &arrivalTime[i]);                               // scanning arrival time
        
        printf("BURST TIME : ");                                    // message to user
        scanf("%d", &burstTime[i]);                                 // scanning burst time
        
        temp[i] = burstTime[i];                                     // storing burst time in temp array
    }

    printf("\nENTER TIME QUANTUM : ");                              // message to user
    scanf("%d", &timeQuantum);                                      // scanning time quantum

    for (total = 0, i = 0; x != 0;)                                 // looping untill all process are executed
    {
        if (temp[i] <= timeQuantum && temp[i] > 0)                  // check the value of process burst time
        {
            // if burst time is less than quantum time then process will be completely executed
            total = total + temp[i];                                // calculating total time 
            temp[i] = 0;                                            // now making that process burst time = 0
            x--;                                                    // decrementing 
            wait_time[i] = wait_time[i] + total - arrivalTime[i] - burstTime[i];    // calculating wait time of ith process
            turnaround_time[i] = turnaround_time[i] + total - arrivalTime[i];       // calculating turn around time of ith process
        }
        else if (temp[i] > 0)                                       // if burst time > 0 and burst time > quantum time
        {   
            temp[i] = temp[i] - timeQuantum;                        // execute the process for time quantum and subtract time quantum from burst time
            total = total + timeQuantum;                            // add time quantum to total time
        }

        if (i == noOfProcess - 1)                                   // check if we are executing 2nd last process
        {
            i = 0;                                                  // if true reassign index i to 0
        }
        else if (arrivalTime[i + 1] <= total)                       // check if arrival of next process is less than total time
        {
            i++;                                                    // if true then increment index i and proceed to next process
        }
        else
        {
            i = 0;                                                  // else reassign index i to 0
        }
    }
    for(i = 0; i < noOfProcess; i++)                                // looping till no of process
    {
        avg_waiting_time += wait_time[i];                           // calculating total wait time
        avg_turnaround_time += turnaround_time[i];                  // calculating total tat
    }
    avg_waiting_time = avg_waiting_time * 1.0 / noOfProcess;        // calculating average wait time 
    avg_turnaround_time = avg_turnaround_time * 1.0 / noOfProcess;  // calculatin average tat
    
    // printing process table
    printf("\n\nID \t AT \t BT \t CT \t TAT \t WT \n");             // table header
    for(i = 0; i < noOfProcess; i++)
    {
        // printing table row
        printf("%d \t%d \t%d \t%.1lf \t%.1lf \t%.1lf \n",i,arrivalTime[i],burstTime[i],(turnaround_time[i]+arrivalTime[i]),turnaround_time[i],wait_time[i]);
    }
    
    printf("\nAverage Waiting Time:%.2f\n", avg_waiting_time);      // printing average waiting time
    printf("Average Turnaround Time:%lf\n", avg_turnaround_time);   // printing turn around time
    return 0;                                                       // return 0
}