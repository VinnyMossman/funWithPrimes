#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void * threadPartialTest(void * args);
bool globalIsPrime;
int numberOfThreads = 16;
long int globalN;
//pthread_mutex_t updateIsPrimeLock;

/******************************************************************
* Function isPrime returns true if n is prime, else returns false *
******************************************************************/
bool isPrime(long int n) {

  globalN = n;
  globalIsPrime = true;

  long i;
  int errorCode;
  pthread_t * threadHandles = (pthread_t *) malloc(numberOfThreads * sizeof(pthread_t));

  for (i = 0; i <  numberOfThreads; i ++) {
    if (errorCode = pthread_create(&threadHandles[i], NULL, threadPartialTest, (void *) i) != 0) {
     printf("pthread %d failed to be created with error code %d\n", i, errorCode);
    }
  }

  for (i = 0; i < numberOfThreads; i++) {
    if (errorCode = pthread_join(threadHandles[i], (void **) NULL) != 0) {
      printf("pthread %d failed to be joined with error code %d\n", i, errorCode);
    }
  }

  return globalIsPrime;

}

void * threadPartialTest(void * rank) {

  if (globalIsPrime == false) {
    pthread_exit(0);
  }

  long int n = globalN;
  long int i = 2;
 
  if (n > numberOfThreads * 2) {

    int checkRange = (n / numberOfThreads) / 2;

    if ((long int) rank < (long int) numberOfThreads - 1) {
      for (i = 2 + ((long int) rank * checkRange); i <= (((long int) rank + 1) * checkRange) + 1; i++) {
          if (n % i == 0) {
	  globalIsPrime = false;
	  break;
	}
      }
    }
    else {
      for (i = (numberOfThreads - 1) * checkRange; i <= (n / 2); i++) {
	if (n % i == 0) {
	  globalIsPrime = false;
	  break;
	}
      }
    }

  }

  else {

    while (n % i != 0) {
      if (i > (n / 2)) {
	i = n;
	break;
      }
      i++;
    }
    if (i < n) {
      globalIsPrime = false;
    }
 
  }

}
