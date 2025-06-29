/**
 * @file main_heapsort.c
 * @brief Implements and tests heapsort algorithm.
 * 
 * This program implements heapsort using functions in heap.h and tests it by taking command line numbers.
 *
 * @author Grimaud
 * @date 04/15/2024
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

void my_heapsort(int *array, int n){
  // Create a heap
  heap_s *heap = heap_create();
  // Add array element in the heap
  for (int i = 0; i < n; i++) {
    heap_add(array[i], heap);
  }
  // Get the elements in the expected order
  for (int i = n - 1; i >= 0; i--) {
    array[i] = heap_peek(heap); 
    heap_remove(heap); 
  }
  // Delete the heap
  heap_delete(heap);
  return;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s num1 num2 num3 ...\n", argv[0]);
    return 1;
  }

  int n = argc - 1;
  int *array = (int *)malloc(n * sizeof(int));
  assert(array != NULL);
  
  for (int i = 0; i < n; i++) {
    array[i] = atoi(argv[i + 1]);
  }
  
  printf("Before heapsort :\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  my_heapsort(array, n);
  
  printf("After heapsort :\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  
  free(array);
  return 0;
}

