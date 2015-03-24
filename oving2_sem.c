#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

int victor;
sem_t sem_victor;

void* someThreadFunction(){
	int i;
	for(i=0;i<1000000;i++){
		sem_wait(&sem_victor);
		victor--;
		sem_post(&sem_victor);
	}
	return NULL;
}


void* someOtherThreadFunction(){
	int i;
	for(i=0;i<1000001;i++){
		sem_wait(&sem_victor);
		victor++;
		sem_post(&sem_victor);
	}
	return NULL;
}

int main(){
	sem_init(&sem_victor, 0, 1);

	victor  = 0;
	pthread_t someThread;
	pthread_t someOtherThread;
	
	pthread_create(&someThread, NULL, someThreadFunction, NULL);
	pthread_create(&someOtherThread, NULL, someOtherThreadFunction, NULL);
		
	pthread_join(someThread, NULL);
	pthread_join(someOtherThread,NULL);
	sem_destroy(&sem_victor);
	printf("Congratulations!! You have won: %d.\n",victor);
	
	return 0;
}

