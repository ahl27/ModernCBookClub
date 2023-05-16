#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Workhorse function, called by my_mergesort and does the recursion calling
void mergesort_helper(void *arr, int start, int midpoint, int end, size_t typesize, int (*comparator)(const void*, const void*)){
  if(start+1 != midpoint)
    mergesort_helper(arr, start, (start+midpoint)/2, midpoint, typesize, comparator);
  if(midpoint+1 != end)
    mergesort_helper(arr, midpoint, (midpoint+end)/2, end, typesize, comparator);
  
  void* temparr = malloc(typesize*(end-start+1));

  int ctr1=start, ctr2=midpoint, i=0, offset;
  while(ctr2 < end || ctr1 < midpoint){
    if(ctr2 == end){
      memcpy(temparr+i*typesize, arr + ctr1++*typesize, typesize);
    } else if (ctr1 == midpoint){
      memcpy(temparr+i*typesize, arr + ctr2++*typesize, typesize);
    } else {
      offset = comparator((arr + ctr1*typesize), (arr + ctr2*typesize)) <= 0 ? ctr1++ : ctr2++;
      memcpy(temparr+i*typesize, arr+offset*typesize, typesize);
    }
    i++;
  }

  for(i=start; i<end; i++)
    memcpy(arr+i*typesize, temparr+(i-start)*typesize, typesize);

  free(temparr);
  return;
}


// Main callable mergesort function (different name to avoid conflict with stdlib.h)
void my_mergesort(void *arr, int num, size_t size, int (*comparator)(const void*, const void*)){
  mergesort_helper(arr, 0, num/2, num, size, comparator);
}

/*
 *  Basic functions to compare two values by casting them to the correct type
 *  Each returns -1 if the first value is less, 0 if same, and 1 if second is greater
 */
int int_comparator(const void* x, const void* y){
  if(*(int *)x == *(int *)y)
    return 0;
  return *(int *) x < *(int *) y ? -1 : 1;
}

int char_comparator(const void* x, const void* y){
  if(*(char *)x == *(char *)y)
    return 0;
  return *(char *) x < *(char *) y ? -1 : 1;
}

int double_comparator(const void* x, const void* y){
  if(*(double *)x == *(double *)y)
    return 0;
  return *(double *) x < *(double *) y ? -1 : 1;
}

int main(){
  // Main function to run tests; most of this is just printing
  srand(time(NULL));
  int num_vals = 100;


  // First Test: Sorting integers
  printf("**************\n");  
  int int_test[num_vals];
  for(int i=0; i<num_vals; i++) 
    int_test[i] = rand() % 64;

  printf("Integers Test:\n");
  for(int i=0; i<num_vals; i++){
    if(i%10==0 && i>0)
      printf("\n");
    printf("%02d ", int_test[i]);
  }
  printf("\n");

  my_mergesort(int_test, num_vals, sizeof(int), &int_comparator);
  printf("Result:\n");
  for(int i=0; i<num_vals; i++){
    if(i%10==0 && i>0)
      printf("\n");
    printf("%02d ", int_test[i]);
  }
  printf("\n\n");


  // Second Test: Sorting characters
  printf("**************\n");
  char char_test[num_vals+1];
  for(int i=0; i<num_vals; i++) 
    char_test[i] = (rand() % (122-97)) + 97;
  char_test[num_vals] = '\0';
  printf("String Test:\n%s\n", char_test);

  my_mergesort(char_test, num_vals, sizeof(char), &char_comparator);
  printf("\nResult:\n%s\n\n", char_test);


  // Third Test: Sorting doubles
  printf("**************\n");
  double double_test[num_vals];
  for(int i=0; i<num_vals; i++) 
    double_test[i] = ((float)rand()/(float)(RAND_MAX)) * 5;

  printf("Doubles Test:\n");
  for(int i=0; i<num_vals; i++){
    if(i%10 == 0 && i>0)
      printf("\n");
    printf("%3.2f ", double_test[i]);
  }
  printf("\n");

  my_mergesort(double_test, num_vals, sizeof(double), &double_comparator);
  printf("\nResult:\n");
  for(int i=0; i<num_vals; i++){
    if(i%10 == 0 && i>0)
      printf("\n");
    printf("%3.2f ", double_test[i]);
  }
  printf("\n\n");


  return(EXIT_SUCCESS);
}