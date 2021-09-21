#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

void producer(); //function for producer threads
void consumer(); //function for consumer threads

int count = 0; // number next element
char buffer[BUFFER_SIZE];

int mutex = 0; //mutex for threads
int size = 0; //number of filled cells in the buffer
int empty = BUFFER_SIZE; //number of empty cells in buffer

void producer_wait(){
  while(empty==0){ 
    //while consumer doesn't take element from buffer -> do nothing
  }
}

void consumer_wait(){
  while(size==0){
    //while producer doesn't put element to buffer -> do nothing
  }
}

int main()
{    
  pthread_t ptid,ctid;           

  pthread_create(&ptid,NULL,producer,NULL);
  pthread_create(&ctid,NULL,consumer,NULL);

  pthread_join(ptid,NULL);
  pthread_join(ctid,NULL);

  return 0;
}

void producer()
{    
  while(1){

    if (mutex == 0){ //check if available
      mutex = 1;

      if(count == BUFFER_SIZE){ //if buffer is full -> wait
        
        mutex = 0;                        
        producer_wait();
        continue; //new loop iteration, otherwise race condition
      } 

      buffer[count+1] = '!'; // random buffer filling
      printf("Produce : %d \n", count+1);
      size++;
      empty--;
      count++;
      mutex = 0;      
    }    
  }
}

void consumer()
{
  while(1){ 

    if (mutex == 0){ //check if available
        mutex = 1;

      if(count == 0){ //if buffer is empty -> wait
        
        mutex = 0;         
        consumer_wait();
        continue; //new loop iteration, otherwise race condition
      }  
          
      printf("Consume : %d \n", count);        
      size--;
      empty++;
      count--;
      mutex = 0;                
    }    
  }
}