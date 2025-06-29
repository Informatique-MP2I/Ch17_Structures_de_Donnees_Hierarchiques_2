/**
 * @file priority_queue.c
 * @brief Implementation of a priority queue in C using binary search trees.
 *
 * This file contains the naive implementation a priority queue using binary search trees. 
 *
 * @author Grimaud
 * @date 04/15/2024
 * @version 1.0
 */

#include <stdbool.h> 
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "bst.h"

/**
 * @struct queue_s
 * @brief Structure of the queue_s.
 */
typedef struct queue {
  binary_tree_s *inner_bst;
} queue_s;

/**
 * @brief Creates a new empty priority queue.
 *
 * Creates a new empty priority queue.
 * @return Pointer to the newly created queue.
 */
queue_s *queue_create() {
  queue_s *res = (queue_s *)malloc(sizeof(queue_s));
  assert(res!=NULL);
  res->inner_bst = NULL;
  return res;
}

/**
 * @brief Adds a given value to the priority queue.
 *
 * Adds a given value to the priority queue.
 * @param value New value to add.
 * @param queue Address of the current queue.
 * @return Address of the updated queue.
 * @note Asserts if the queue already created and if the queue has enough space.
 */
queue_s *queue_enqueue(int value, queue_s *queue) {
  assert(queue != NULL);
  queue->inner_bst = add_node(value,queue->inner_bst);
  return queue;
}

/**
 * @brief Tests if the priority queue is empty or not.
 *
 * Tests if the priority queue is empty or not.
 * @param queue Address of the current queue.
 * @return true if the queue is empty, false otherwise.
 * @note Asserts if the queue is created.
 */
bool queue_empty(queue_s *queue) {
  assert(queue != NULL);
  return binary_tree_nodes(queue->inner_bst) == 0;
}

/**
 * @brief Reads the head element without removing it.
 *
 * Reads the head element without removing it.
 * @param queue Address of the current queue.
 * @return Value of the head element.
 * @note Asserts if the queue is not empty.
 */
int queue_peek(queue_s *queue) {
  assert(!queue_empty(queue));
  return min_value_node(queue->inner_bst);
}

/**
 * @brief Removes the head element.
 *
 * Removes the head element.
 * @param queue Address of the current queue.
 * @return Address of the updated queue.
 * @note Asserts the queue is not empty.
 */
queue_s *queue_dequeue(queue_s *queue) {
  assert(!queue_empty(queue));
  queue->inner_bst = remove_node(queue_peek(queue),queue->inner_bst);
  return queue;
}

/**
 * @brief Prints the priority queue elements from the head to the last element.
 *
 * Prints the priority queue elements from the head to the last element.
 * @param queue Address of the current queue.
 * @note Asserts if the queue is already created.
 */
void queue_print(queue_s *queue) {
  assert(queue != NULL);
  dump_tree(queue->inner_bst,true);
  return;
}

/**
 * @brief Erases the priority queue.
 *
 * Erases the priority queue.
 * @param queue Address of the current queue.
 * @note Asserts if the queue is already created.
 */
void queue_delete(queue_s *queue) {
  assert(queue != NULL);
  binary_tree_free(queue->inner_bst);
  free(queue);
  return;
}

