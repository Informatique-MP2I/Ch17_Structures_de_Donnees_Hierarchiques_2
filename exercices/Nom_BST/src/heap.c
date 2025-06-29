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
  /* TODO */
  return NULL;
}

/** 
 * @brief Adds a given value to the heap.
 * @param value A new value to add.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is already created and has enough space.
 */
heap_s *heap_add(int value, heap_s *heap) {
  /* TODO */
  return NULL;
}

/** 
 * @brief Tests if the heap is empty.
 * @param heap The address of the current heap.
 * @return true if the heap is empty, false otherwise.
 * @note Asserts that the heap is created.
 */
bool heap_empty(heap_s *heap) {
  /* TODO */
  return false;
}

/** 
 * @brief Reads the head element without removing it.
 * @param heap The address of the current heap.
 * @return The value of the head element.
 * @note Asserts that the heap is not empty.
 */
int heap_peek(heap_s *heap) {
  /* TODO */
  return -1;
}

/** 
 * @brief Removes the head element.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is not empty.
 */
heap_s *heap_remove(heap_s *heap) {
  /* TODO */
  return NULL;
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
  /* TODO */
  return;
}

