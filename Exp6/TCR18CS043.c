#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

/*
This program provides a possible solution for producer-consumer problem using mutex and semaphore.
I have used 5 producers and 5 consumers to demonstrate the solution. You can always play with these values.
*/

#define MaxItems 500 // Maximum items a producer can produce or a consumer can consume
int BufferSize = 20; // Size of the buffer
FILE* fpo ;
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int store =0;
int prate[20];
int crate[20];
int n;
int pcount = 0 ;
int ccount = 0 ;
pthread_mutex_t mutex;

void read_ints (const char* file_name)
{
    FILE* file = fopen (file_name, "r");
    int i = 0,j = 0;
    int count = 0 ;
    if ( file == NULL ) 
    { 
        printf( "input.txt file failed to open." ) ; 
    } 
    else{
        fscanf (file, "%d %d ", &i, &j);    
        while (!feof (file))
        {   
            prate[count] = i;
            crate[count] = j;

            // printf ("%d %d %d\n", i,j,k);
            fscanf (file, "%d %d", &i, &j); 
            count++;
        }
        prate[count] = i;
        crate[count] = j;
    }
    fclose (file);  

    n = count;      
}

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        //critical section
        if (store+prate[pcount]<BufferSize && pcount<n)
        {         
            printf("Buffer space: %d\n", store);
            fprintf(fpo,"Buffer space: %d\n", store);
            printf("Producer produced %d items\n\n",prate[pcount] );
            fprintf(fpo,"Producer produced %d items\n\n",prate[pcount] );
            store+=prate[pcount];
            pcount = (pcount + 1);
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        //critical secttion
        if (store-crate[ccount]>0 && ccount<n)
        {
        
            printf("Buffer space: %d\n", store);
            fprintf(fpo,"Buffer space: %d\n", store);
            printf("Consumer consumed %d items\n\n",crate[ccount] );
            fprintf(fpo,"Consumer consumed %d items\n\n",crate[ccount] );

            store -= crate[ccount];
            ccount = (ccount+1);    
        
        }
         
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{  
    fpo = fopen("output.txt", "w");
    read_ints("input.txt");
    printf("Enter the Buffer size: ");
    scanf("%d",&BufferSize);

    printf("\n\n------Output------\n\n");
    fprintf(fpo,"------Output------\n\n");
    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer
    // pthread_create(&pro[0], NULL, (void *)producer, (void *)&a[0]);
    // pthread_create(&con[0], NULL, (void *)consumer, (void *)&a[0]);
    
    for(int i = 0; i < 1; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 1; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }
    // pthread_join(pro[0], NULL);
    // pthread_join(con[0], NULL);

    for(int i = 0; i < 1; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 1; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("Buffer space: %d\n",store);
    fprintf(fpo,"Buffer space: %d\n",store);
    fclose(fpo);
    return 0;
    
}