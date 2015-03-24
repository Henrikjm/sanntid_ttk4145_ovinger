#include <pthread.h>
#include <stdio.h>


int victor;

void* someThreadFunction(){
	int i;
	for(i=0;i<1000000;i++){
	victor--;
	}
}


void* someOtherThreadFunction(){
	int i;
	for(i=0;i<1000000;i++){
	victor++;
	}
}

int main(){
	victor  = 0;
	pthread_t someThread;
	pthread_t someOtherThread;
	
	pthread_create(&someThread, NULL, someThreadFunction, NULL);
	pthread_create(&someOtherThread, NULL, someOtherThreadFunction, NULL);
		
	pthread_join(someThread, NULL);
	pthread_join(someOtherThread,NULL);
	printf("Congratulations!! You have won: %d.\n",victor);

	return 0;
}

