#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>

int nop;
#define N 5
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
FILE* fpo;
int state[50]; 
int phil[50]; 

sem_t mutex; 
sem_t S[50]; 

void test(int phnum) 
{ 
	if (state[phnum] == HUNGRY 
		&& state[(phnum + nop-1) % nop ] != EATING 
		&& state[(phnum + 1) % nop] != EATING) { 
		// state that eating 
		state[phnum] = EATING; 

		sleep(2); 

		printf("Philosopher %d takes fork %d and %d\n",phnum + 1, (phnum + nop-1) % nop  + 1, phnum + 1); 
		fprintf(fpo,"Philosopher %d takes fork %d and %d\n",phnum + 1, (phnum + nop-1) % nop  + 1, phnum + 1); 

		printf("Philosopher %d is Eating\n", phnum + 1); 
		fprintf(fpo,"Philosopher %d is Eating\n", phnum + 1); 

		// sem_post(&S[phnum]) has no effect 
		// during takefork 
		// used to wake up hungry philosophers 
		// during putfork 
		sem_post(&S[phnum]); 
	} 
} 

// take up chopsticks 
void take_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// state that hungry 
	state[phnum] = HUNGRY; 

	printf("Philosopher %d is Hungry\n", phnum + 1); 
	fprintf(fpo,"Philosopher %d is Hungry\n", phnum + 1); 

	// eat if neighbours are not eating 
	test(phnum); 

	sem_post(&mutex); 

	// if unable to eat wait to be signalled 
	sem_wait(&S[phnum]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// state that thinking 
	state[phnum] = THINKING; 

	printf("Philosopher %d putting fork %d and %d down\n",phnum + 1, (phnum + nop-1) % nop  + 1, phnum + 1); 
	fprintf(fpo,"Philosopher %d putting fork %d and %d down\n",phnum + 1, (phnum + nop-1) % nop  + 1, phnum + 1); 
	printf("Philosopher %d is thinking\n", phnum + 1); 
	fprintf(fpo,"Philosopher %d is thinking\n", phnum + 1); 

	test((phnum + nop-1) % nop ); 
	test((phnum + 1) % nop); 

	sem_post(&mutex); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		sleep(1); 

		take_fork(*i); 

		sleep(0); 

		put_fork(*i); 
	} 
} 

int main() 
{ 
	fpo = fopen("output.txt", "w");
	FILE *fp = fopen("input.txt", "w");
	printf("------Dining Philosphers' Problem------\n");
	fprintf(fp,"------Dining Philosphers' Problem------\n");
	printf("Enter the number of philosphers: ");
	fprintf(fp,"Enter the number of philosphers: ");
	scanf("%d",&nop);
	fprintf(fp,"%d\n",nop);
	int i; 
	for ( i = 0; i < nop; i++)
	{
		phil[i] = i;
	}
	
	pthread_t thread_id[nop]; 

	// initialize the semaphores 
	sem_init(&mutex, 0, 1); 

	for (i = 0; i < nop; i++) 

		sem_init(&S[i], 0, 0); 

	for (i = 0; i < nop; i++) { 

		// create philosopher processes 
		pthread_create(&thread_id[i], NULL, philospher, &phil[i]); 

		printf("Philosopher %d is thinking\n", i + 1); 
		fprintf(fpo,"Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < nop; i++) 
		pthread_join(thread_id[i], NULL); 

	fclose(fpo);
	fclose(fp);
} 
