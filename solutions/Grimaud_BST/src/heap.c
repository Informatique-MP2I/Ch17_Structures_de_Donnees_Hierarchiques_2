/**
 * @file heap.c
 * @brief Structure and functions for managing a heap data structure. 
 *
 * This file contains the implementation a heap using arrays. 
 *
 * @author Grimaud
 * @date 04/15/2024
 * @version 1.0
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

#define HEAP_MAX_SIZE 1000

void swap(int *a, int *b) {
  int tmp=*a;
  *a=*b;
  *b=tmp;
}

/** 
 * @struct heap
 * @brief Structure of the heap.
 */
typedef struct heap {
  int array[HEAP_MAX_SIZE];
  int nb_elements;
} heap_s;

/** 
 * @brief Creates a new heap and initializes it.
 * @return A pointer to the newly created empty heap.
 */
heap_s *heap_create() {
  heap_s *res=malloc(sizeof(heap_s));
  assert(res!=NULL);
  res->nb_elements=0;
  return res;
}

/** 
 * @brief Adds a given value to the heap.
 * @param value A new value to add.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is already created and has enough space.
 */
heap_s *heap_add(int value, heap_s *heap) {
  assert(heap!=NULL);
  assert(heap->nb_elements<HEAP_MAX_SIZE);
  int i=heap->nb_elements;
  heap->nb_elements++;
  heap->array[i]=value;
  while(i>0 && heap->array[i] > heap->array[(i-1)/2]) {
    swap(&(heap->array[i]),&(heap->array[(i-1)/2])); // restore the heap property
    i=(i-1)/2; // go forward to the parent
  }
  return heap;
}

/** 
 * @brief Tests if the heap is empty.
 * @param heap The address of the current heap.
 * @return true if the heap is empty, false otherwise.
 * @note Asserts that the heap is created.
 */
bool heap_empty(heap_s *heap) {
  assert(heap!=NULL);
  return heap->nb_elements==0;
}

/** 
 * @brief Reads the head element without removing it.
 * @param heap The address of the current heap.
 * @return The value of the head element.
 * @note Asserts that the heap is not empty.
 */
int heap_peek(heap_s *heap) {
  assert(!heap_empty(heap));
  return heap->array[0];
}

/** 
 * @brief Removes the head element.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is not empty.
 */
heap_s *heap_remove(heap_s *heap) {
  assert(heap!=NULL);
  heap->array[0]=heap->array[heap->nb_elements-1];
  heap->nb_elements--;
  int i=0; // index of the actual tree node
  while(i<heap->nb_elements) {
    int left_index = i*2+1;
    int right_index = i*2+2;
    int largest_index = i;
    if(left_index<heap->nb_elements && heap->array[left_index] > heap->array[largest_index]) 
      largest_index = left_index;
    if(right_index<heap->nb_elements && heap->array[right_index] > heap->array[largest_index]) 
      largest_index = right_index;
    if(largest_index == i) 
      break;
    swap(&(heap->array[i]), &(heap->array[largest_index])); // restore the heap property
    i=largest_index; // go forward to the child
  }
  return heap;
}

/** 
 * @brief Prints the heap elements from the head to the last element.
 * @param heap The address of the current heap.
 * @note Asserts that the heap is already created.
 */
void heap_print(heap_s *heap) {
  int i;
  assert(heap!=NULL);
  printf("heap:\n");
  printf("┌─────%s",(heap->nb_elements>0)?"┬":"┐");
  for(i=0;i<heap->nb_elements;i++)
    printf("────%s",(i<heap->nb_elements-1)?"┬":"┐");
  printf("\n"); 
  printf("│index│");
  for(int i=0;i<heap->nb_elements;i++) 
    printf("% 4d│",i);
  printf("\n");
  printf("│value│");
  for(int i=0;i<heap->nb_elements;i++) 
    printf("% 4d│",heap->array[i]);
  printf("\n");
  printf("└─────%s",(heap->nb_elements>0)?"┴":"┘");
  for(i=0;i<heap->nb_elements;i++)
    printf("────%s",(i<heap->nb_elements-1)?"┴":"┘");
}

/** 
 * @brief Erases the heap.
 * @param heap The address of the current heap.
 * @note Asserts that the heap is already created.
 */
void heap_delete(heap_s *heap) {
  assert(heap!=NULL);
  free(heap);
  return;
}

