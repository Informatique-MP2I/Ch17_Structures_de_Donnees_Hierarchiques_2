/**
 * @file simple_bst.c
 * @brief Implementation of a binary search tree in C.
 *
 * This file contains the naive implementation of a binary serach tree, including functions to add and find nodes,
 * compute the height and number of nodes, and print the tree. The implementation supports basic
 * operations to demonstrate a simple binary tree data structure and is meant for educational purposes.
 *
 * @author Grimaud
 * @date 04/15/2024
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "bst.h"

/** 
 * @struct binary_tree_s
 * @brief A structure to represent a node in a binary tree.
 * 
 * This structure holds the value of the node and pointers to the left and right child nodes.
 */
typedef struct binary_tree {
  int value;                         /**< The value of the node */
  struct binary_tree *left;          /**< Pointer to the left child */
  struct binary_tree *right;         /**< Pointer to the right child */
} binary_tree_s;

/**
 * @brief Calculates the height of the binary tree.
 * 
 * This function determines the height of the binary tree recursively. The height of a tree is the number of edges
 * along the longest path from the root down to the farthest leaf node.
 * 
 * @param tree The root of the binary tree.
 * @return The height of the tree. Returns -1 if the tree is empty.
 */
int binary_tree_height(binary_tree_s *tree) {
  if(tree==NULL)
    return -1;
  else {
    int left  = binary_tree_height(tree->left);
    int right = binary_tree_height(tree->right);
    int max = (left > right) ? left : right;
    return max + 1;
  } 
}

/**
 * @brief Counts the total number of nodes in the binary tree.
 * 
 * This function recursively calculates the total number of nodes in the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @return The total number of nodes in the tree. Returns 0 if the tree is empty.
 */
int binary_tree_nodes(binary_tree_s *tree) {
  if(tree==NULL)
    return 0;
  else 
    return binary_tree_nodes(tree->left) + binary_tree_nodes(tree->right) + 1;
}

/**
 * @brief Internal helper function to print the binary tree.
 * 
 * This recursive function assists in printing the binary tree in a structured ASCII art format.
 * The function utilizes depth to determine the prefixes and branching structure for each node.
 * 
 * @param node The current node being printed.
 * @param depth The current depth in the tree.
 * @param height The height of the tree.
 * @param is_left Flag indicating if the current node is a left child.
 * @param prefix The current prefix for aligning the printed output.
 */
void binary_tree_print_aux(binary_tree_s *node, int depth, int height, int is_left, char *prefix) {
  char new_prefix[200]; // Buffer limited to 200 bytes (<200 characters)
  if (node == NULL || height < 0) return;
  // print right
  if (node->right != NULL) {
    char *s1 = (is_left) ? "│" : " ";
    char *s2 = (is_left) ? " " : "│";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s      ", prefix, s1);
    binary_tree_print_aux(node->right, depth + 1, height, 0, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s      ", prefix, s2);
  }
  // print node
  printf("%s", prefix);
  char *s1 = (depth) ? ((is_left) ? "└" : "┌") : " ";
  char *s2 = (depth >= height ) ? " " : ((node->left) ? ((node->right) ? "┤" : "┐" ) : ((node->right) ? "┘"  : " "));
  printf("%s(%04d)%s\n", s1, node->value, s2);
  // print left
  if (node->left != NULL) {
    char *s1 = (depth) ? ((is_left) ? " " : "│") : " ";
    char *s2 = (depth) ? ((is_left) ? "│" : " ") : " ";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s      ", prefix, s1);
    binary_tree_print_aux(node->left, depth + 1, height, 1, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s      ", prefix, s2);
  }
  return;
}

/**
 * @brief Public function to print the entire binary tree.
 * 
 * This function prints the binary tree starting from the root. It displays the tree's height and number of nodes
 * before printing the tree structure.
 * 
 * @param tree The root of the binary tree to be printed.
 */
void binary_tree_print(binary_tree_s *tree) {
  int height = binary_tree_height(tree);
  int nodes = binary_tree_nodes(tree);
  printf("height : %d  - nodes : %d\n", height, nodes);
  if (binary_tree_height(tree)>=0) 
    binary_tree_print_aux(tree, 0, binary_tree_height(tree), 0, "");
  else
    printf("Empty binary tree.\n");
  return;
}

/**
 * @brief Find the node with the minimum value in a binary search tree.
 * 
 * This helper function is used to find the in-order successor, i.e., the smallest node
 * in the given binary tree rooted at the specified node.
 * 
 * @param node The root node of the subtree.
 * @return the minimum value in the given subtree.
 */
int min_value_node(binary_tree_s *node) {
  assert(node != NULL);
  if(node->left!=NULL)
    return min_value_node(node->left);
  return node->value;
}

/**
 * @brief Adds a node with a specific value to the binary tree.
 * 
 * If the tree is empty (i.e. tree is NULL), it creates a new node and returns it.
 * If the value already exists in the tree, it returns the existing node without adding a duplicate.
 * The function uses recursion to find the correct position for the new node according to binary search tree rules.
 * 
 * @param value The value to be added to the tree.
 * @param tree The root of the binary tree (can be NULL if the tree is empty).
 * @return The root of the modified tree.
 */
binary_tree_s *add_node(int value, binary_tree_s *tree) {
  if(tree==NULL) {
    binary_tree_s *res = malloc(sizeof(binary_tree_s));
    assert(res != NULL);
    res->value = value;
    res->left = res->right = NULL;
    return res;
  }
  if(tree->value == value) {
    return tree;
  }
  if(tree->value > value) {
    tree->left = add_node(value, tree->left);
  } else {
    tree->right = add_node(value, tree->right);
  }
  return tree;
}

/**
 * @brief Searches for a node with a specific value in the binary tree.
 * 
 * This function checks if the tree contains a node with the specified value using a binary search approach.
 * It returns true if the value is found and false otherwise.
 * 
 * @param value The value to search for in the tree.
 * @param tree The root of the binary tree.
 * @return true if the value is found, false otherwise.
 */
bool find_node(int value, binary_tree_s *tree) {
  if(tree==NULL)
    return false;
  if(tree->value==value)
    return true;
  if(tree->value < value) 
    return find_node(value, tree->right);
  return find_node(value, tree->left);
}

/**
 * @brief Prints all values in the binary search tree in a sorted order.
 * 
 * This function outputs all the values from the binary search tree rooted at the specified node
 * to the standard output. The values are displayed in ascending order if `ascending` is true,
 * and in descending order if `ascending` is false. This is useful for debugging or visual verification
 * of tree contents.
 * 
 * @param tree The root node of the binary tree to be dumped.
 * @param ascending Specifies the order of the output: true for ascending, false for descending.
 */
void dump_tree(binary_tree_s *tree, bool ascending) {
  if(tree != NULL){
    if(ascending){
      // Ascending to boolean
      if (tree->left != NULL)
	dump_tree(tree->left,ascending);
      printf("%d ",tree->value);
      if (tree->right != NULL)
	dump_tree(tree->right,ascending);
    } else {
      if (tree->right != NULL)
	dump_tree(tree->right,ascending);
      printf("%d ",tree->value);     
      if (tree->left != NULL)
	dump_tree(tree->left,ascending);
    }
  }
  return;
}   


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
binary_tree_s *remove_node(int value, binary_tree_s *tree) {
  if (tree == NULL) {
    return NULL; // Value not found, return NULL
  }
  // Navigate the tree and recurse down to find the node
  if (value < tree->value) {
    tree->left = remove_node(value, tree->left);
  } else if (value > tree->value) {
    tree->right = remove_node(value, tree->right);
  } else {
    // Node with only one child or no child
    if (tree->left == NULL) {
      binary_tree_s *temp = tree->right;
      free(tree);
      return temp;
    } else if (tree->right == NULL) {
      binary_tree_s *temp = tree->left;
      free(tree);
      return temp;
    }
    // Node with two children: Get the inorder successor (smallest in the right subtree)
    int temp_value = min_value_node(tree->right);
    // Copy the inorder successor's content to this node
    tree->value = temp_value;
    // Delete the inorder successor
    tree->right = remove_node(temp_value, tree->right);
  }
  return tree;
}

/**
 * @brief Frees the memory occupied by a binary tree.
 *
 * This function recursively frees all nodes of a binary tree, starting from the leaves
 * towards the root. It safely handles trees that are NULL by terminating early.
 *
 * @param tree Pointer to the root of the binary tree to be freed.
 */
void binary_tree_free(binary_tree_s *tree) {
  if(tree==NULL)
    return;
  if(tree->left != NULL)
    binary_tree_free(tree->left);
  if(tree->right !=NULL)
    binary_tree_free(tree->right);
  free(tree);
}
