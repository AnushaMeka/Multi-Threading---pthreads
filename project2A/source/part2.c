#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t chopstick[100];
int nthreads;
FILE *output;

void thinking (){
   	usleep(rand()%500);
}

void pickUpChopsticks (int threadIndex){
   	pthread_mutex_lock(&chopstick[threadIndex]);
   	pthread_mutex_lock(&chopstick[(threadIndex+1)%nthreads]);
}

void eating (int threadIndex){
   	printf("Philosopher %d is eating\n", threadIndex+1);
   	FILE *output = fopen("part2-output.txt","a");
	fprintf(output, "Philosopher %d is eating\n", threadIndex+1);
	usleep(rand()%500);
	fflush(output);
}

void putDownChopsticks (int threadIndex){
   	pthread_mutex_unlock(&chopstick[threadIndex]);
   	pthread_mutex_unlock(&chopstick[(threadIndex+1)%nthreads]);
}

void *PhilosopherThread(void *threadIndex)
{
   	long myid;
        myid  = (long)threadIndex;
   
   	thinking();
   	pickUpChopsticks(myid);
   	eating(myid);
   	putDownChopsticks(myid);

   	pthread_exit(NULL);
}

void creatPhilosopher(int threadindex){
        pthread_t nthreads[threadindex];
        int rc;
        long t;
	//FILE *output = fopen("part2-output.txt","a");
        for(t=0;t<threadindex;t++){
                rc = pthread_create(&(nthreads[t]), NULL, PhilosopherThread, (void *)t);
                if (rc) {
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(EXIT_FAILURE);
                }
        }
        for(t=0;t<threadindex;t++)
                rc = pthread_join(nthreads[t], NULL);
}


int main(int argc, char *argv[]){
        int i;
	srandom(time(NULL));
        nthreads = atoi(argv[1]);
        for (i=0; i<nthreads; i++)
                pthread_mutex_init(&chopstick[i], NULL);
	creatPhilosopher(nthreads);
	fclose(output);
}

