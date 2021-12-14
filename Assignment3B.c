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

    for (total = 0, i = 0; x != 0;)
    {
        if (temp[i] <= timeQuantum && temp[i] > 0)
        {
            total = total + temp[i];
            temp[i] = 0;
            x--;
            wait_time[i] = wait_time[i] + total - arrivalTime[i] - burstTime[i];
            turnaround_time[i] = turnaround_time[i] + total - arrivalTime[i];
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - timeQuantum;
            total = total + timeQuantum;
        }

        if (i == noOfProcess - 1)
        {
            i = 0;
        }
        else if (arrivalTime[i + 1] <= total)
        {
            i++;
        }
        else
        {
            i = 0;
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
        printf("%d \t%d \t%d \t%.1lf \t%.1lf \t%.1lf \n",i,arrivalTime[i],burstTime[i],(turnaround_time[i]+arrivalTime[i]),turnaround_time[i],wait_time[i]);
    }
    
    printf("\nAverage Waiting Time:%.2f\n", avg_waiting_time);
    printf("Average Turnaround Time:%lf\n", avg_turnaround_time);
    return 0;
}