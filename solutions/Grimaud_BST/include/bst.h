#ifndef _BST_H_
#define _BST_H_

/**
 * @file bst.h
 * @brief Definitions for the operations on a binary search tree.
 */

/**
 * @struct binary_tree_s
 * @brief Internal structure of nodes in a binary tree.
 */
typedef struct binary_tree binary_tree_s;

/**
 * @brief Adds a node with a specified value to a binary tree.
 * 
 * The node is added to the tree and the modified tree structure is returned.
 * Note that the addition may not necessarily modify the original structure passed.
 * 
 * @param value The integer value to add to the tree.
 * @param tree The pointer to the starting binary tree node (can be NULL if the tree is empty).
 * @return The new root of the tree after insertion, which may be different from the input.
 */
binary_tree_s *add_node(int value, binary_tree_s *tree);

/**
 * @brief Checks whether a node with a specified value exists within the tree.
 * 
 * @param value The value to find in the tree.
 * @param tree The pointer to the starting binary tree node.
 * @return Boolean.
 */
bool find_node(int value, binary_tree_s *tree);

/**
 * @brief Removes a node with a specific value from the binary tree if it exists.
 * 
 * This function searches for a node with the specified value and removes it if found. 
 * It handles three cases: removing a leaf node, a node with one child, and a node with two children
 * by finding the node's in-order successor to maintain the binary search tree properties.
 * The function uses recursion to find and remove the node.
 * 
 * @param value The value to be removed from the tree.
 * @param tree The root of the binary tree.
 * @return The root of the modified tree; NULL if the tree is empty after removal.
 */
binary_tree_s *remove_node(int value, binary_tree_s *tree);

/**
 * @brief Calculates the height of the binary tree. 
 * 
 * @param tree The root of the binary tree. 
 * @return The height of the tree. Returns 0 if the tree is empty. 
 */
int binary_tree_height(binary_tree_s *tree);

/**
 * @brief Counts the number of elements in the binary tree.
 * 
 * @param tree The pointer to the starting binary tree node.
 * @return The number of elements as an integer.
 */
int binary_tree_nodes(binary_tree_s *tree);

/**
 * @brief Find the node with the minimum value in a binary search tree.
 * 
 * This helper function is used to find the in-order successor, i.e., the smallest node
 * in the given binary tree rooted at the specified node.
 * 
 * @param node The root node of the subtree.
 * @return the minimal value in the given subtree.
 */
int min_value_node(binary_tree_s *node);

/**
 * @brief TODO
 * 
 */
void dump_tree(binary_tree_s *tree, bool ascending);

/**
 * @brief Generates a text representation (ASCII art) of the binary tree.
 * 
 * @param tree The pointer to the starting binary tree node.
 */
void binary_tree_print(binary_tree_s *tree);

/**
 * @brief Frees the memory occupied by a binary tree.
 *
 * This function recursively frees all nodes of a binary tree, starting from the leaves
 * towards the root. It safely handles trees that are NULL by terminating early.
 *
 * @param tree Pointer to the root of the binary tree to be freed.
 */
void binary_tree_free(binary_tree_s *tree);

#endif /* _BST_H_ */
