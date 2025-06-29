/**
 * @file avl_bst.c
 * @brief Implementation of a binary search tree in C.
 *
 * This file contains the implementation of a binary search tree, including functions to add and find nodes,
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
  int height;                        /**< The height of the tree */
  struct binary_tree *left;          /**< Pointer to the left child */
  struct binary_tree *right;         /**< Pointer to the right child */
} binary_tree_s;

/**
 * @brief Returns the maximum of two integers.
 *
 * This function compares two integers and returns the greater of the two.
 *
 * @param a The first integer to compare.
 * @param b The second integer to compare.
 * @return The greater of the two integers, a or b.
 */
int max(int a, int b) {
  return (a>b)?a:b;
}

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
  else 
    return tree->height;
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
  if (node == NULL) return;
  // print right
  if (node->right != NULL) {
    char *s1 = (is_left) ? "│" : " ";
    char *s2 = (is_left) ? " " : "│";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s          ", prefix, s1);
    binary_tree_print_aux(node->right, depth + 1, height, 0, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s          ", prefix, s2);
  }
  // print node
  printf("%s", prefix);
  char *s1 = (depth) ? ((is_left) ? "└" : "┌") : " ";
  char *s2 = (depth >= height) ? " " : ((node->left) ? ((node->right) ? "┤" : "┐") : ((node->right) ? "┘" : " "));
  printf("%s(%04d)[%02d]%s\n", s1, node->value, node->height, s2);
  // print left
  if (node->left != NULL) {
    char *s1 = (depth) ? ((is_left) ? " " : "│") : " ";
    char *s2 = (depth) ? ((is_left) ? "│" : " ") : " ";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s          ", prefix, s1);
    binary_tree_print_aux(node->left, depth + 1, height, 1, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s          ", prefix, s2);
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
 * @return Node with the minimum value in the given subtree.
 */
int min_value_node(binary_tree_s *node) {
    assert(node!=NULL);
    if(node->left!=NULL)
      return min_value_node(node->left);
    return node->value;
}

/**
 * @brief Performs a left rotation on the binary tree at the root.
 * 
 * This rotation is performed by making the right child of the root the new root of the subtree,
 * and making the original root the left child of the new root. The original right child's left
 * subtree becomes the right subtree of the new left child (original root).
 * 
 * @param tree The root of the binary tree to rotate.
 * @return The new root of the subtree after rotation.
 */
binary_tree_s *bst_rotate_left(binary_tree_s *tree) {
  if (tree == NULL || tree->right == NULL) {
    return tree;  // No rotation needed if tree is NULL or has no right child
  }
  int l = binary_tree_height(tree->left);
  int rl = binary_tree_height(tree->right->left);
  int rr = binary_tree_height(tree->right->right);
  binary_tree_s *new_root = tree->right;
  tree->right = tree->right->left;
  new_root->left = tree;
  tree->height = 1 + max(l,rl);
  new_root->height = 1 + max(tree->height,rr);
  return new_root ;
}

/**
 * @brief Performs a right rotation on the binary tree at the root.
 * 
 * This rotation is performed by making the left child of the root the new root of the subtree,
 * and making the original root the right child of the new root. The original left child's right
 * subtree becomes the left subtree of the new right child (original root).
 * 
 * @param tree The root of the binary tree to rotate.
 * @return The new root of the subtree after rotation.
 */
binary_tree_s *bst_rotate_right(binary_tree_s *tree) {
  if (tree == NULL || tree->left == NULL) {
    return tree;  // No rotation needed if tree is NULL or has no left child
  }
  int r = binary_tree_height(tree->right);
  int ll = binary_tree_height(tree->left->left);
  int lr = binary_tree_height(tree->left->right);
  binary_tree_s *new_root = tree->left;
  tree->left = tree->left->right;
  new_root->right = tree;
  tree->height = 1+max(lr,r);
  new_root->height = 1+max(ll,tree->height);
  return new_root;
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
 * @brief Adds a node to the binary tree and balances the tree using simple rotations.
 * 
 * This function inserts a new node with the specified value into the binary tree following 
 * the binary search tree rules. After insertion, it checks the balance of the tree and 
 * performs a left or right rotation if the tree becomes unbalanced. This is a naive balancing
 * approach and is not as efficient as those used in AVL or Red-Black trees.
 *
 * @param value The value to be added to the tree.
 * @param tree The root of the binary tree (can be NULL if the tree is empty).
 * @return The new or modified root of the tree after insertion and possible rotation.
 */
binary_tree_s *add_node(int value, binary_tree_s *tree) {
  // Regular BST insertion
  if (tree == NULL) {
    tree = malloc(sizeof(binary_tree_s));
    if (tree == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
    }
    tree->value = value;
    tree->height = 0;
    tree->left = tree->right = NULL;
  } else if (value < tree->value) {
    tree->left = add_node(value, tree->left);
  } else if (value > tree->value) {
    tree->right = add_node(value, tree->right);
  }
  // Check balance factors and rotate if necessary (height is stored in each
  // node to avoid O(n) depth computing)
  int left_height = binary_tree_height(tree->left);
  int right_height = binary_tree_height(tree->right);
  tree->height = 1 + ((left_height<right_height)?right_height:left_height) ;
  if (left_height - right_height > 1) {
    // Right rotation
    if (tree->left != NULL && value > tree->left->value) {
      // Left-Right Case: First rotate left on left child
      tree->left = bst_rotate_left(tree->left);
    }
    // Right rotation on the current node
    tree = bst_rotate_right(tree);
  } else if (right_height - left_height > 1) {
    // Left rotation
    if (tree->right != NULL && value < tree->right->value) {
      // Right-Left Case: First rotate right on right child
      tree->right = bst_rotate_right(tree->right);
    }
    // Left rotation on the current node
    tree = bst_rotate_left(tree);
  }
  return tree;
}

/**
 * @brief Removes a node with a specified value from the binary tree and rebalances the tree.
 *
 * This function searches for and removes the node containing the specified value, if it exists.
 * After removal, it assesses the balance of the tree and performs rotations to maintain
 * balance. The method handles the three standard BST deletion cases: deleting a leaf,
 * deleting a node with one child, and deleting a node with two children.
 * Balancing is performed using simple left or right rotations similar to those in AVL trees.
 *
 * @param value The value of the node to be removed.
 * @param tree The root of the binary tree.
 * @return The new or modified root of the tree after the removal and possible rebalancing.
 */
binary_tree_s *remove_node(int value, binary_tree_s *tree) {
  if (tree == NULL) {
    return NULL; // Value not found
  }
  // Step 1: Perform standard BST delete
  if (value < tree->value) {
    tree->left = remove_node(value, tree->left);
  } else if (value > tree->value) {
    tree->right = remove_node(value, tree->right);
  } else {
    // Node with only one child or no child
    if (tree->left == NULL) {
      binary_tree_s *temp = tree->right;
      free(tree);
      tree = temp;
    } else if (tree->right == NULL) {
      binary_tree_s *temp = tree->left;
      free(tree);
      tree = temp;
    } else {
      // Node with two children: Get the inorder successor
      int temp_value = min_value_node(tree->right);
      // Place the inorder successor in position of the node to be deleted
      tree->value = temp_value;
      // Delete the inorder successor
      tree->right = remove_node(temp_value, tree->right);
    }
  }
  // Step 2: Rebalance the tree if the tree was modified
  if (tree == NULL) {
    return tree; // If the tree had only one node and it was deleted
  }
  // Check balance factors and rotate if necessary
  int left_height = binary_tree_height(tree->left);
  int right_height = binary_tree_height(tree->right);
  tree->height = 1 + max(left_height,right_height);
  // If the tree is unbalanced, then try one of the following 4 cases
  if (left_height - right_height > 1) {
    // Left Left Case or Left Right Case
    if (tree->left != NULL && binary_tree_height(tree->left->left) >= binary_tree_height(tree->left->right)) {
      return bst_rotate_right(tree);
    } else {
      tree->left = bst_rotate_left(tree->left);
      return bst_rotate_right(tree);
    }
  } else if (right_height - left_height > 1) {
    // Right Right Case or Right Left Case
    if (tree->right != NULL && binary_tree_height(tree->right->right) >= binary_tree_height(tree->right->left)) {
      return bst_rotate_left(tree);
    } else {
      tree->right = bst_rotate_right(tree->right);
      return bst_rotate_left(tree);
    }
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

