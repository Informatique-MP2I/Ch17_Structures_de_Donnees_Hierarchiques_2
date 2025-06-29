#ifndef QUEUE_H
#define QUEUE_H

/**
 * @file queue.h
 * @brief Header file for queue operations.
 */

/** 
 * Structure of the queue.
 */
typedef struct queue queue_s;

/**
 * @brief Creates a new empty queue.
 *
 * Creates a new empty queue.
 * @return Pointer to the newly created queue.
 */
queue_s *queue_create();

/**
 * @brief Adds a given value to the queue.
 *
 * Adds a given value to the queue.
 * @param value New value to add.
 * @param queue Address of the current queue.
 * @return Address of the updated queue.
 * @note Asserts if the queue already created and if the queue has enough space.
 */
queue_s *queue_enqueue(int value, queue_s *queue);

/**
 * @brief Tests if the queue is empty or not.
 *
 * Tests if the queue is empty or not.
 * @param queue Address of the current queue.
 * @return true if the queue is empty, false otherwise.
 * @note Asserts if the queue is created.
 */
bool queue_empty(queue_s *queue);

/**
 * @brief Reads the head element without removing it.
 *
 * Reads the head element without removing it.
 * @param queue Address of the current queue.
 * @return Value of the head element.
 * @note Asserts if the queue is not empty.
 */
int queue_peek(queue_s *queue);

/**
 * @brief Removes the head element.
 *
 * Removes the head element.
 * @param queue Address of the current queue.
 * @return Address of the updated queue.
 * @note Asserts the queue is not empty.
 */
queue_s *queue_dequeue(queue_s *queue);

/**
 * @brief Prints the queue elements from the head to the last element.
 *
 * Prints the queue elements from the head to the last element.
 * @param queue Address of the current queue.
 * @note Asserts if the queue is already created.
 */
void queue_print(queue_s *queue);

/**
 * @brief Erases the queue.
 *
 * Erases the queue.
 * @param queue Address of the current queue.
 * @note Asserts if the queue is already created.
 */
void queue_delete(queue_s *queue);

#endif // QUEUE_H
