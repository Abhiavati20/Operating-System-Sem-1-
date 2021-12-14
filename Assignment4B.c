#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define MAX 10;
sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1, numreader = 0;
int i = 0;
void *writer(void *writerNumber)
{

    sem_wait(&wrt);
    cnt *= 2;
    printf("\nWriter #%d  - Modified count to %d\n", *((int *)writerNumber), cnt);
    sem_post(&wrt); // signal
    sleep(rand() % 10);
}
void *reader(void *readerNumber)
{

    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1) // block writer if first reader
    {
        printf("\nWRITER IS BLOCKED NOW\n");
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("\nReader #%d  - Read count as %d\n", *((int *)readerNumber), cnt);
    sleep(rand() % 10);
    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0) // if last reader, wake up writer
    {
        printf("\nWRITER IS UN-BLOCKED NOW\n");
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    pthread_t r[10], w[10];
    int rid[10], wid[10];
    int choice;
    while (1)
    {

        printf("\n---MENU---");
        printf("\n1.READER");
        printf("\n2.WRITER");
        printf("\n3.Exit");
        printf("\nENTER YOUR CHOICE ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            rid[i] = i;
            // creating threads which execute reader function
            pthread_create(&r[i], NULL, &reader, &rid[i]);
            sleep(1);
            break;
        }
        case 2:
        {
            wid[i] = i;
            // creating threads which execute writer function
            pthread_create(&w[i], NULL, &writer, &wid[i]);
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
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
}