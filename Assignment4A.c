#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MaxItems 15

int BufferSize;        // size of buffer
sem_t empty;           // Number of empty slots in buffer
sem_t full;            // Number of slots filled
int in = 0;            //index at which producer will put the next data
int out = 0;           // index from which the consumer will consume next data
int *buffer;           // Buffer array
pthread_mutex_t mutex; // Used to provide mutual exclusion for critical sectio
int count = 0, i = 0;
int nproducer = 0, nconsumer = 0;


void *producer(void *pno)
{
    int item;
    if (count == BufferSize)
    {
        printf("\nBUFFER COUNT = %d\nBUFFER IS FULL \nCONSUME AN ITEM NOW\n", count);
    }
    item = rand() % 1000;       // Produce an random item
    sem_wait(&empty);           //Same as wait() operation
    pthread_mutex_lock(&mutex); //Same as wait() operation
    buffer[in] = item;
    printf("\nProducer %d: Inserted Item %d at %d\nBUFFER COUNT = %d\n", *((int *)pno), buffer[in], in, ++count);
    in = (in + 1) % BufferSize;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void *consumer(void *cno)
{
    if (count == 0)
    {
        printf("\nBUFFER COUNT = %d\nBUFFER IS Empty \nPRODUCE AN ITEM !!!\n", count);
    }
    sem_wait(&full);            //Same as wait() operation
    pthread_mutex_lock(&mutex); // Same as wait() operation
    int item = buffer[out];     // fecting item from buffer
    printf("\nConsumer %d: Remove Item %d from %d\nBUFFER COUNT = %d\n", *((int *)cno), item, out, --count);
    out = (out + 1) % BufferSize; // incrementing out
    pthread_mutex_unlock(&mutex); //Same as Signal() operation
    sem_post(&empty);             //Same as Signal() operation
}
int main()
{
    printf("ENTER BUFFER SIZE :: ");
    scanf("%d", &BufferSize);

    pthread_t proID[10], conID[10]; // for collecting id's of producer and consumer
    buffer = (int *)malloc(BufferSize * sizeof(int));

    pthread_mutex_init(&mutex, NULL); // Initialise the mutex
    sem_init(&empty, 0, BufferSize);  //Initialise the semaphore to some initial value
    sem_init(&full, 0, 0);            //Initialise the semaphore to some initial value

    int choice;
    while (1)
    {

        printf("\n---MENU---");
        printf("\n1.produce a item");
        printf("\n2.consume a item");
        printf("\n3.Exit");
        printf("\nENTER YOUR CHOICE ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            nproducer++;
            pthread_create(&proID[i], NULL, (void *)producer, (void *)&nproducer);
            sleep(1);
            break;
        }
        case 2:
        {
            nconsumer++;
            pthread_create(&conID[i], NULL, (void *)consumer, (void *)&nconsumer);
            sleep(1);
            break;
        }
        case 3:
        {
            exit(0);
        }
        default:
            printf("\nINVALID CHOICE\n");
            break;
        }
        i++;
    }
    for (i = 0; i < 10; i++)
    {
        pthread_join(proID[i], NULL);
        pthread_join(conID[i], NULL);
    }
    pthread_mutex_destroy(&mutex); // Destroy the mutex to avoid memory leak
    sem_destroy(&empty);           // Destroy the semaphore to avoid memory leak
    sem_destroy(&full);            // Destroy the semaphore to avoid memory leak

    return 0;
}