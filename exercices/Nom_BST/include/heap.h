#ifndef HEAP_H
#define HEAP_H

/** 
 * @file heap.h
 * @brief Structure and functions for managing a heap data structure.
 */

/** 
 * @struct heap_s
 * @brief Structure of the heap_s.
 */
typedef struct heap heap_s;

/** 
 * @brief Creates a new heap and initializes it.
 * @return A pointer to the newly created empty heap.
 */
heap_s *heap_create();

/** 
 * @brief Adds a given value to the heap.
 * @param value A new value to add.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is already created and has enough space.
 */
heap_s *heap_add(int value, heap_s *heap);

/** 
 * @brief Tests if the heap is empty.
 * @param heap The address of the current heap.
 * @return true if the heap is empty, false otherwise.
 * @note Asserts that the heap is created.
 */
bool heap_empty(heap_s *heap);

/** 
 * @brief Reads the head element without removing it.
 * @param heap The address of the current heap.
 * @return The value of the head element.
 * @note Asserts that the heap is not empty.
 */
int heap_peek(heap_s *heap);

/** 
 * @brief Removes the head element.
 * @param heap The address of the current heap.
 * @return The address of the updated heap.
 * @note Asserts that the heap is not empty.
 */
heap_s *heap_remove(heap_s *heap);

/** 
 * @brief Prints the heap elements from the head to the last element.
 * @param heap The address of the current heap.
 * @note Asserts that the heap is already created.
 */
void heap_print(heap_s *heap);

/** 
 * @brief Erases the heap.
 * @param heap The address of the current heap.
 * @note Asserts that the heap is already created.
 */
void heap_delete(heap_s *heap);

#endif // HEAP_H
