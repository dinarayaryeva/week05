#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// just simple implementation of greatest common divisor
int gcd(int n1, int n2) {

    if (n2 != 0)
        return gcd(n2, n1 % n2);
    else
        return n1;
}

//checks if all elements in the array are equal
int all_equal(int arr[], int n){

  for (int i=0; i<n-1; i++){
    if (arr[i]!=arr[i+1]) return 0;
  }
  return 1;
}

/*least common multiplier function
  it takes a pair a, b and assign lcm to both variables
*/
void* lcm (void* n){

  int** arr= (int**)n;
  int* a = arr[0];
  int* b = arr[1];

  if (*a<*b) { //because gcd(a,b) will work only if a>b
    int t =*a;
    *a = *b;
    *b = t;
  }

  int lcm = *a * *b / gcd(*a, *b);
  *arr[0] = lcm;
  *arr[1] = lcm;
  return NULL;
}

int main(int argc, char* argv[]){

  if (argc != 3) {
    printf("Wrong number of arguments!");
    return -1;}
  
  char* file_name = argv[1];

  int n = atoi(argv[2]);

  if (n==0){
    printf("Wrong number of threads!");
    return -1;}

  FILE* file;

  file = fopen(file_name,"r");
  if (file == NULL) {
    printf("Cannot fopen the file!");
    return -1;}

  int numbers[256];

  int count = 0; //number of numbers in the file

  int d = 0;
  while (1){ //formatting loop

    char t = fgetc(file);

    if (t==EOF) break;

    if (t==' ') {

      numbers[count] = d;
      d = 0;
      count++;
      }
    else d = d*10 + t -'0';
  }

  numbers[count] = d;
  count++;
  
  int cnt = 0; // number of loop iterations

  while (!all_equal(numbers, count)){
    
    int i = cnt%2; // odd or even iteration
    //alternation of odd and even loops guarantee termination

    while ((i+i%2) < (count - count%2*(1-i%2))){ 
      //condition formula derived in the experimental way

      pthread_t thr;
      int m;
      int min = ((count-1)<(2*n+i)) ? (count-1) : (2*n+i);
      // min - minimum(from two cases) index that we can reach in the next loop iteration

      for (m = i; m < min; m+=2){
        //for each pair in our range

        int* k[2] = {&numbers[m], &numbers[m+1]};
        pthread_create(&thr, NULL, lcm, (void *)k);
      }

      pthread_join(thr, NULL);
      i = m; //if n < number of pairs => we need more loop iterations
    }
    cnt++;
  }

  printf("The least common multiple is %d\n", numbers[0]);
}
