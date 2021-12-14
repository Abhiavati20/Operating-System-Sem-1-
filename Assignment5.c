#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int *alloc;
    int *req;
    int *need;
} Process;
int main()
{
    int noOfProcess, noOfResrc;
    printf("ENTER NO OF PROCESSES AND RESOURCES ");
    scanf("%d%d", &noOfProcess, &noOfResrc);

    int avail[noOfProcess], completed[noOfProcess], count = noOfProcess;

    Process p[noOfProcess];

    int i, j;
    for (i = 0; i < noOfProcess; i++)
    {
        p[i].alloc = (int *)malloc((noOfResrc) * sizeof(int));
        p[i].req = (int *)malloc((noOfResrc) * sizeof(int));
        p[i].need = (int *)malloc((noOfResrc) * sizeof(int));
    }

    printf("\nENTER ALLOCATION OF EACH PROCESS\n");
    for (i = 0; i < noOfProcess; i++)
    {
        printf("FOR PROCESS P%d\n", i);
        for (j = 0; j < noOfResrc; j++)
        {
            printf("%c ", (j + 65));
            scanf("%d", &p[i].alloc[j]);
        }
        completed[i] = 0;
    }

    printf("\nENTER MAX RESOURCE OF EACH PROCESS\n");
    for (i = 0; i < noOfProcess; i++)
    {
        printf("FOR PROCESS P%d\n", i);
        for (j = 0; j < noOfResrc; j++)
        {
            printf("%c ", (j + 65));
            scanf("%d", &p[i].req[j]);
        }
    }

    printf("\nENTER AVAILABLE RESOURCE\n");
    for (i = 0; i < noOfResrc; i++)
    {
        scanf("%d", &avail[i]);
    }

    for (i = 0; i < noOfProcess; i++)
    {
        for (j = 0; j < noOfResrc; j++)
        {
            p[i].need[j] = p[i].req[j] - p[i].alloc[j];
        }
    }
    printf("Safe Sequence : ");
    int flag;
    while (count)
    {
        flag = 0;
        for (int i = 0; i < noOfProcess; i++)
        {
            if (completed[i] == 0)
            {
                for (j = 0; j < noOfResrc; j++)
                {
                    if (p[i].need[j] > avail[j])
                    {
                        break;
                    }
                }

                if (j == noOfResrc)
                {
                    printf("P%d -> ", i);
                    completed[i] = 1;
                    count--;
                    flag = 1;
                    for (j = 0; j < noOfResrc; j++)
                    {
                        avail[j] += p[i].alloc[j];
                    }
                }
            }
        }
        if (flag == 0)
        {
            printf("\n DEADLOCK\n");
            break;
        }
    }
    printf("\n\n");
    return 0;
}