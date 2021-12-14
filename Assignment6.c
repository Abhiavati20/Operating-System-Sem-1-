// NAME : ABHISHEK AJAY AVATI
// ROLL : 33106
// BATCH: M-9

// HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL VARIABLES
int *isHit;
int noOfPageFrames, noOfReferences;

// FIFO CODE
void fifo(int pageFrame[noOfPageFrames][noOfReferences], int *pageRefString)
{
    int pageFrameIndex = noOfPageFrames - 1;
    int i = 1;
    pageFrame[pageFrameIndex][0] = pageRefString[0];
    pageFrameIndex--;
    while (i < noOfReferences)
    {
        for (int j = 0; j < noOfPageFrames; j++)
        {
            pageFrame[j][i] = pageFrame[j][i - 1];
        }

        for (int j = 0; j < noOfPageFrames; j++)
        {
            if (pageFrame[j][i] == pageRefString[i])
            {
                isHit[i] = 1;
                break;
            }
        }

        if (isHit[i] == 0)
        {
            pageFrame[pageFrameIndex][i] = pageRefString[i];
            if (pageFrameIndex == 0)
            {
                pageFrameIndex = noOfPageFrames - 1;
            }
            else
            {
                pageFrameIndex--;
            }
        }
        i++;
    }
}

// LRU CODE
void lru(int pageFrame[noOfPageFrames][noOfReferences], int *pageRefString)
{
    int i = 1;
    pageFrame[noOfPageFrames - 1][0] = pageRefString[0];
    for (int j = noOfPageFrames - 2; j >= 0; j--)
    {
        for (int k = 0; k < noOfPageFrames; k++)
        {
            pageFrame[k][i] = pageFrame[k][i - 1];
        }
        pageFrame[j][i] = pageRefString[i];
        i++;
    }
    while (i < noOfReferences)
    {
        for (int j = 0; j < noOfPageFrames; j++)
        {
            pageFrame[j][i] = pageFrame[j][i - 1];
        }
        for (int j = 0; j < noOfPageFrames; j++)
        {
            if (pageFrame[j][i] == pageRefString[i])
            {
                isHit[i] = 1;
                break;
            }
        }

        if (isHit[i] == 0)
        {
            int isPresent[noOfPageFrames];
            memset(isPresent, 0, sizeof(isPresent));
            int count = 0, k = i - 1;
            for (; k >= 0 && count != noOfPageFrames - 1; k--)
            {
                for (int j = 0; j < noOfPageFrames && count != noOfPageFrames - 1; j++)
                {
                    if (pageFrame[j][i] == pageRefString[k] && isPresent[j] == 0)
                    {
                        isPresent[j] = 1;
                        count++;
                    }
                }
            }
            int j;
            for (j = 0; j < noOfPageFrames && isPresent[j] == 1; j++)
                ;
            pageFrame[j][i] = pageRefString[i];
        }
        i++;
    }
}
// OPR FUNCTION
void opr(int pageFrame[noOfPageFrames][noOfReferences], int *pageRefString)
{
    int i = 1;
    pageFrame[noOfPageFrames - 1][0] = pageRefString[0];
    for (int j = noOfPageFrames - 2; j >= 0; j--)
    {
        for (int k = 0; k < noOfPageFrames; k++)
        {
            pageFrame[k][i] = pageFrame[k][i - 1];
        }
        pageFrame[j][i] = pageRefString[i];
        i++;
    }
    while (i < noOfReferences)
    {
        for (int j = 0; j < noOfPageFrames; j++)
        {
            pageFrame[j][i] = pageFrame[j][i - 1];
        }
        for (int j = 0; j < noOfPageFrames; j++)
        {
            if (pageFrame[j][i] == pageRefString[i])
            {
                isHit[i] = 1;
                break;
            }
        }

        if (isHit[i] == 0)
        {
            int isPresent[noOfPageFrames];
            memset(isPresent, 0, sizeof(isPresent));
            int count = 0, k = i + 1;
            for (; k < noOfReferences && count != noOfPageFrames - 1; k++)
            {
                for (int j = 0; j < noOfPageFrames && count != noOfPageFrames - 1; j++)
                {
                    if (pageFrame[j][i] == pageRefString[k] && isPresent[j] == 0)
                    {
                        isPresent[j] = 1;
                        count++;
                    }
                }
            }
            int j;
            for (j = 0; j < noOfPageFrames && isPresent[j] == 1; j++)
                ;
            pageFrame[j][i] = pageRefString[i];
        }
        i++;
    }
}

// PRINT FUNCTION
void print(int pageFrame[noOfPageFrames][noOfReferences], int *pageRefString)
{
    int totalFault = 0, totalHit = 0, noOfLines = 0;
    printf("\n");
    printf("    ");
    for (int i = 0; i < noOfReferences; i++)
    {
        noOfLines += printf("%5d |", pageRefString[i]);
    }
    printf("\n");
    noOfLines += 4;
    for (int i = 0; i < noOfLines; i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < noOfPageFrames; i++)
    {
        printf("F%d |", noOfPageFrames - i);
        for (int j = 0; j < noOfReferences; j++)
        {
            if (pageFrame[i][j] == -1)
            {
                printf("      |");
            }
            else
            {
                printf("%5d |", pageFrame[i][j]);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < noOfLines; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("    ");
    for (int i = 0; i < noOfReferences; i++)
    {
        if (isHit[i] == 0)
        {
            totalFault++;
            printf(" Fault|");
        }
        else
        {
            totalHit++;
            printf("   Hit|");
        }
    }
    printf("\n\n");

    printf("Total Fault = %d\nTotal Hit = %d\n", totalFault, totalHit);
    printf("Miss Ratio = %d/%d = %f\n", totalFault, noOfReferences, (float)totalFault / noOfReferences);
    printf("Hit Ratio = %d/%d = %f\n", totalHit, noOfReferences, (float)totalHit / noOfReferences);
}

// MAIN FUNCTION
int main()
{
    printf("\nEnter the no of Page Frames and the no of Page references\n");
    scanf("%d%d", &noOfPageFrames, &noOfReferences);

    int pageRefString[noOfReferences];
    printf("\nEnter the page no of each page reference\n");
    for (int i = 0; i < noOfReferences; i++)
    {
        scanf("%d", &pageRefString[i]);
    }

    int choice;
    do
    {
        printf("\nEnter 1 for FIFO Page Replacement\n");
        printf("Enter 2 for Optimal Page Replacement\n");
        printf("Enter 3 for Least Recently Used Page Replacement\n");
        printf("Enter 4 to exit\n");

        printf("\nEnter your choice\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int pageFrame[noOfPageFrames][noOfReferences];
            memset(pageFrame, -1, sizeof(pageFrame));

            isHit = (int *)malloc(noOfReferences * sizeof(int));
            memset(isHit, 0, sizeof(isHit));

            fifo(pageFrame, pageRefString);
            print(pageFrame, pageRefString);
            break;
        }
        case 2:
        {
            int pageFrame[noOfPageFrames][noOfReferences];
            memset(pageFrame, -1, sizeof(pageFrame));

            isHit = (int *)malloc(noOfReferences * sizeof(int));
            memset(isHit, 0, sizeof(isHit));

            opr(pageFrame, pageRefString);
            print(pageFrame, pageRefString);
            break;
        }
        case 3:
        {
            int pageFrame[noOfPageFrames][noOfReferences];
            memset(pageFrame, -1, sizeof(pageFrame));

            isHit = (int *)malloc(noOfReferences * sizeof(int));
            memset(isHit, 0, sizeof(isHit));

            lru(pageFrame, pageRefString);
            print(pageFrame, pageRefString);
            break;
        }
        case 4:
            break;
        default:
            printf("\nInvalid Choice\n");
        }
    } while (choice != 4);
}

/*
OUTPUT 

---------------------------------------------------------------------------------------------------

TEST CASE 1

Enter the no of Page Frames and the no of Page references
3   
12

Enter the page no of each page reference
1 
2 3 4 1 2 5 1 2 3 4 5

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
1

        1 |    2 |    3 |    4 |    1 |    2 |    5 |    1 |    2 |    3 |    4 |    5 |
----------------------------------------------------------------------------------------
F3 |      |      |    3 |    3 |    3 |    2 |    2 |    2 |    2 |    2 |    4 |    4 |
F2 |      |    2 |    2 |    2 |    1 |    1 |    1 |    1 |    1 |    3 |    3 |    3 |
F1 |    1 |    1 |    1 |    4 |    4 |    4 |    5 |    5 |    5 |    5 |    5 |    5 |
----------------------------------------------------------------------------------------
     Fault| Fault| Fault| Fault| Fault| Fault| Fault|   Hit|   Hit| Fault| Fault|   Hit|

Total Fault = 9
Total Hit = 3
Miss Ratio = 9/12 = 0.750000
Hit Ratio = 3/12 = 0.250000

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
3

        1 |    2 |    3 |    4 |    1 |    2 |    5 |    1 |    2 |    3 |    4 |    5 |
----------------------------------------------------------------------------------------
F3 |      |      |    3 |    3 |    3 |    2 |    2 |    2 |    2 |    2 |    2 |    5 |
F2 |      |    2 |    2 |    2 |    1 |    1 |    1 |    1 |    1 |    1 |    4 |    4 |
F1 |    1 |    1 |    1 |    4 |    4 |    4 |    5 |    5 |    5 |    3 |    3 |    3 |
----------------------------------------------------------------------------------------
     Fault| Fault| Fault| Fault| Fault| Fault| Fault|   Hit|   Hit| Fault| Fault| Fault|

Total Fault = 10
Total Hit = 2
Miss Ratio = 10/12 = 0.833333
Hit Ratio = 2/12 = 0.166667

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
4

-------------------------------------------------------------------------------------------------

TEST CASE 2

-------------------------------------------------------------------------------------------------
Enter the no of Page Frames and the no of Page references
4 13

Enter the page no of each page reference
5 7 0 1 7 6 7 2 1 6 7 6 1

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
3

        5 |    7 |    0 |    1 |    7 |    6 |    7 |    2 |    1 |    6 |    7 |    6 |    1 |
-----------------------------------------------------------------------------------------------
F4 |      |      |      |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |
F3 |      |      |    0 |    0 |    0 |    0 |    0 |    2 |    2 |    2 |    2 |    2 |    2 |
F2 |      |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |
F1 |    5 |    5 |    5 |    5 |    5 |    6 |    6 |    6 |    6 |    6 |    6 |    6 |    6 |
-----------------------------------------------------------------------------------------------
     Fault| Fault| Fault| Fault|   Hit| Fault|   Hit| Fault|   Hit|   Hit|   Hit|   Hit|   Hit|

Total Fault = 6
Total Hit = 7
Miss Ratio = 6/13 = 0.461538
Hit Ratio = 7/13 = 0.538462

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
2

        5 |    7 |    0 |    1 |    7 |    6 |    7 |    2 |    1 |    6 |    7 |    6 |    1 |
-----------------------------------------------------------------------------------------------
F4 |      |      |      |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |    1 |
F3 |      |      |    0 |    0 |    0 |    6 |    6 |    6 |    6 |    6 |    6 |    6 |    6 |
F2 |      |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |    7 |
F1 |    5 |    5 |    5 |    5 |    5 |    5 |    5 |    2 |    2 |    2 |    2 |    2 |    2 |
-----------------------------------------------------------------------------------------------
     Fault| Fault| Fault| Fault|   Hit| Fault|   Hit| Fault|   Hit|   Hit|   Hit|   Hit|   Hit|

Total Fault = 6
Total Hit = 7
Miss Ratio = 6/13 = 0.461538
Hit Ratio = 7/13 = 0.538462

Enter 1 for FIFO Page Replacement
Enter 2 for Optimal Page Replacement
Enter 3 for Least Recently Used Page Replacement
Enter 4 to exit

Enter your choice
4
-------------------------------------------------------------------------------------------------
*/