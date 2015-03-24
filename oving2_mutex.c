#include <pthread.h>
#include <stdio.h>


int victor;
pthread_mutex_t lock;

void* someThreadFunction(){
	int i;
	for(i=0;i<1000000;i++){
		pthread_mutex_lock(&lock);
		victor--;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}


void* someOtherThreadFunction(){
	int i;
	for(i=0;i<1000001;i++){
		pthread_mutex_lock(&lock);
		victor++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(){
	victor  = 0;
	pthread_t someThread;
	pthread_t someOtherThread;
	
	pthread_create(&someThread, NULL, someThreadFunction, NULL);
	pthread_create(&someOtherThread, NULL, someOtherThreadFunction, NULL);
		
	pthread_join(someThread, NULL);
	pthread_join(someOtherThread,NULL);
	pthread_mutex_destroy(&lock);
	printf("Congratulations!! You have won: %d.\n",victor);
	
	return 0;
}

