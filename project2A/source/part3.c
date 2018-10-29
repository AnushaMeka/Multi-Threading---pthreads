#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_NUM_THREADS 100

int nthreads;
int philosopherId = 0;	
pthread_mutex_t chopstick;
pthread_cond_t eat_turn;
FILE *output;

void thinking(){	
	usleep(rand()%500);

}

void eating(int threadIndex){	
	printf("Philosopher %d is eating\n", threadIndex+1);
	FILE *output = fopen("part3-output.txt","a");
        fprintf(output, "Philosopher %d is eating\n", threadIndex+1);
	usleep(rand()%500);
	if(philosopherId == (nthreads - 1)){
		philosopherId = 0;
	}else{
		philosopherId += 1;
	}
	if(philosopherId == (threadIndex + 1)){
		pthread_cond_broadcast(&eat_turn);
	}
}

void pickUpChopsticks(int threadIndex){
	pthread_mutex_lock(&chopstick);
	while(philosopherId != threadIndex){
		pthread_cond_wait(&eat_turn, &chopstick);
	}
}

void putDownChopsticks(int threadIndex){
	pthread_mutex_unlock(&chopstick);
}


void *PhilosopherThread(void *threadIndex){
	long myid;
	myid = (long)threadIndex;

	thinking();
	pickUpChopsticks(myid);
	eating(myid);
	putDownChopsticks(myid);

	pthread_exit(NULL);
}

void creatPhilosopher(int num_threads){
	pthread_t nthreads[num_threads];
	int rc;
	long t;
	for(t = 0; t < num_threads; t++){
		rc = pthread_create(&nthreads[t], NULL, PhilosopherThread, (void *)t);
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	for(t = 0; t < num_threads; t++)
		rc = pthread_join(nthreads[t], NULL);

	pthread_exit(NULL);
}

int main(int argc, char ** argv ){
	nthreads = atoi(argv[1]);
	srandom(time(NULL));
	pthread_mutex_init(&chopstick, NULL);
	pthread_cond_init(&eat_turn, NULL);
	creatPhilosopher(nthreads);
	pthread_mutex_destroy(&chopstick);
	pthread_cond_destroy(&eat_turn);
	fclose(output);
}
