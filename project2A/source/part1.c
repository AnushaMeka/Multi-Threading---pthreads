#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Function for Each Thread to Run */
void* PhilosopherThread(void* threadid) {
	int* myid = threadid;
	FILE *output = fopen("part1-output.txt","a");
	printf("This is philosopher %d\n", *myid);
    	fprintf(output, "This is philosopher %d\n", *myid);
    	fflush(output);
	fclose(output);
	return NULL;
}

void creatPhilosophers(int threadindex) {
	int rc;
	long t;
	long copy[threadindex];
	pthread_t nthreads[threadindex];
	for(t=0; t<threadindex; t++){
		copy[t] = t;
		rc = pthread_create(&(nthreads[t]), NULL, PhilosopherThread, &(copy[t]));
		if (rc){
	    		printf("ERROR; return code from pthread_create() is %d\n", rc);
	    		exit(EXIT_FAILURE);
		}
    	}
    
    	for(t=0;t<threadindex;t++)
		pthread_join(nthreads[t],NULL);

	printf("%d threads have been joined successfully now\n", threadindex);
}


int main(int argc, char *argv[]) {
	int num_threads;
	num_threads = atoi(argv[1]);
	printf("Anusha Meka, input is %d threads\n", num_threads);
	creatPhilosophers(num_threads);
	return 0;
}
