#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_process(void * i){
  sleep(1); // to synchronize messages
  printf("Thread %d gives a message.\n", *((int*)i));
}

int main(void) {
  pthread_t thr;
  int n = 3;
  for (int i=0; i<n; i++){
    pthread_create(&thr, NULL, thread_process, (void*)&i);
    printf("Thread %d was created.\n", i);
    pthread_join(thr, NULL);
    printf("Thread %d exits.\n", i);
  }
  return 0;
}