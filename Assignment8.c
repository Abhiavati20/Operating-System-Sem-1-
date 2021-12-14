#include <stdio.h>
int arr[100];
int isVisited[100];
int length, n, current;

#define INF 9999999

void sort()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int mod(int n)
{

    return n >= (-1 * n) ? n : (-1 * n);
}

void SSTF()
{

    int total_track_movement = 0;
    int tempCurrent = current;

    printf("\n\nOrder by SSTF:\n%d => ", tempCurrent);

    int min_diff = INF;

    for (int i = 0; i < n; i++)
    {
        isVisited[i] = 0;
    }

    int closest_index;

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (isVisited[i] == 0)
            {

                if (mod(tempCurrent - arr[i]) < min_diff)
                {
                    closest_index = i;
                    min_diff = mod(tempCurrent - arr[i]);
                }
            }
        }

        isVisited[closest_index] = 1;

        total_track_movement += mod(tempCurrent - arr[closest_index]);

        tempCurrent = arr[closest_index];

        min_diff = INF;

        printf("%d => ", tempCurrent);
    }

    printf("\nTotal Track movement = %d\n\n", total_track_movement);
}

void SCAN()
{

    int total_track_movement = 0;

    sort();

    total_track_movement = length - 1 - current;

    if (current > arr[0])
    {
        total_track_movement += length - 1 - arr[0];
    }

    printf("\n Order by SCAN:");

    printf("\n%d => ", current);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > current)
        {
            printf("%d => ", arr[i]);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] < current)
        {
            printf("%d => ", arr[i]);
        }
    }

    printf("\nTotal Track movement = %d\n\n", total_track_movement);
}

void CLOOK()
{

    int total_track_movement = 0;

    sort();

    total_track_movement = arr[n - 1] - current;

    if (arr[0] < current)
    {
        total_track_movement += arr[n - 1] - arr[0];
    }

    printf("\n Order by C-LOOK:");

    printf("\n%d => ", current);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > current)
        {
            printf("%d => ", arr[i]);
        }
    }

    int i;

    for (i = 0; arr[i] < current; i++)
    {

        printf("%d => ", arr[i]);
    }

    if (arr[0] < current)
    {
        total_track_movement += arr[i - 1] - arr[0];
    }

    printf("\nTotal Track movement = %d\n\n", total_track_movement);
}

int main()
{

    printf("Enter number of requests\n");
    scanf("%d", &n);

    printf("\nEnter Requests\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nEnter total length of the track\n");
    scanf("%d", &length);

    printf("\nEnter current position of read-write head\n");

    scanf("%d", &current);

    int choice;
    while (1)
    {
        printf("\nMenu\n");
        printf("1.SSTF\n");
        printf("2.SCAN\n");
        printf("3.CLOOK\n");
        printf("4.Return\n");
        printf("\nENTER YOUR CHOICE :: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            SSTF();
            break;
        case 2:
            SCAN();
            break;
        case 3:
            CLOOK();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid Choice");
            break;
        }
    }
    return 0;
}
/*

Enter number of requests
7

Enter Requests
72 160 33 130 14 6 180

Enter total length of the track
200

Enter current position of read-write head
50

Menu
1.SSTF
2.SCAN
3.CLOOK
4.Return

ENTER YOUR CHOICE :: 1


Order by SSTF:
50 => 33 => 14 => 6 => 72 => 130 => 160 => 180 => 
Total Track movement = 218


Menu
1.SSTF
2.SCAN
3.CLOOK
4.Return

ENTER YOUR CHOICE :: 2

 Order by SCAN:
50 => 72 => 130 => 160 => 180 => 33 => 14 => 6 => 
Total Track movement = 342


Menu
1.SSTF
2.SCAN
3.CLOOK
4.Return

ENTER YOUR CHOICE :: 3

 Order by C-LOOK:
50 => 72 => 130 => 160 => 180 => 6 => 14 => 33 => 
Total Track movement = 331


Menu
1.SSTF
2.SCAN
3.CLOOK
4.Return

ENTER YOUR CHOICE :: 4

*/