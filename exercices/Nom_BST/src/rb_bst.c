/**
 * @file rb_bst.c
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
 * @enum node_color_e
 * @brief Enumerates the color states of nodes in a red-black tree.
 *
 * This enumeration is used to set the color attribute of a node within a red-black tree,
 * which helps in maintaining balanced tree properties by coloring the nodes either red or black.
 */
enum node_color_e {
  RED,   /**< Node color red, used in a red-black tree. */
  BLACK  /**< Node color black, used in a red-black tree. */
};

/**
 * @struct binary_tree_s
 * @brief A structure to represent a node in a red-black tree.
 * 
 * Each node of the tree contains a value, color, and pointers to its left and right child nodes.
 * The structure is used in red-black trees, which are a type of self-balancing binary search tree.
 *
 * @details The color property of each node, which is critical for maintaining the balanced properties
 * of the red-black tree, is determined by the node_color_e enumeration. A red-black tree ensures that
 * the tree remains balanced with additional properties that must be maintained after insertions and deletions,
 * which are ensured by rotations and color changes of the nodes.
 *
 * @see node_color_e
 */
typedef struct binary_tree {
  int value;                  /**< The value of the node */
  struct binary_tree *left;   /**< Pointer to the left child */
  struct binary_tree *right;  /**< Pointer to the right child */
  enum node_color_e color;    /**< The color of this node, used in balancing the red-black tree. */
} binary_tree_s;

/**
 * @brief Calculates the height of the binary tree.
 * 
 * This function determines the height of the binary tree recursively. The height of a tree is the number of edges
 * along the longest path from the root down to the farthest leaf node.
 * 
 * @param tree The root of the binary tree.
 * @return The height of the tree. Returns 0 if the tree is empty.
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
  if (node == NULL) return;
  // print right
  if (node->right != NULL) {
    char *s1 = (is_left) ? "│" : " ";
    char *s2 = (is_left) ? " " : "│";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s       ", prefix, s1);
    binary_tree_print_aux(node->right, depth + 1, height, 0, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s       ", prefix, s2);
  }
  // print node
  printf("%s", prefix);
  char *s1 = (depth) ? ((is_left) ? "└" : "┌") : " ";
  char *s2 = (depth >= height) ? " " : ((node->left) ? ((node->right) ? "┤" : "┐") : ((node->right) ? "┘" : " "));
  char *color = (node->color==RED)?"\x1b[31;100m⏺\x1b[0m":"\x1b[30;100m⏺\x1b[0m";
  printf("%s(%04d)%s%s\n", s1, node->value, color, s2);
  // print left
  if (node->left != NULL) {
    char *s1 = (depth) ? ((is_left) ? " " : "│") : " ";
    char *s2 = (depth) ? ((is_left) ? "│" : " ") : " ";
    snprintf(new_prefix, sizeof(new_prefix), "%s%s       ", prefix, s1);
    binary_tree_print_aux(node->left, depth + 1, height, 1, new_prefix);
    snprintf(new_prefix, sizeof(new_prefix), "%s%s       ", prefix, s2);
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
    assert(node!=NULL) ;
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
  /* TODO */
  return NULL;
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
  /* TODO */
  return NULL;
}

/**
 * @brief Adjusts the properties of a red-black tree during insertion to maintain balance and color properties.
 *
 * This function corrects the red-black tree properties after an insertion has potentially disrupted them.
 * It applies color changes and rotations based on the color and position of the nodes relative to their parent and grandparent.
 *
 * @param root The root node of the sub-tree to be fixed. This pointer may change if a rotation occurs.
 *
 * @details
 * The function works through a series of condition checks:
 * - If the left child and its left child are both red, perform a right rotation on the root and recolor the left-left child to black.
 * - If the left child and its right child are both red, perform a left rotation on the left child, then a right rotation on the root, and recolor the left child to black.
 * - If the right child and its right child are both red, perform a left rotation on the root and recolor the right-right child to black.
 * - If the right child and its left child are both red, perform a right rotation on the right child, then a left rotation on the root, and recolor the right child to black.
 *
 * These adjustments maintain the properties that ensure the red-black tree remains balanced and conforms to red-black tree rules,
 * which include ensuring no two consecutive red nodes and balancing the number of black nodes from root to leaves.
 *
 * @return The new root node of the sub-tree after potential rotations and color adjustments.
 */
binary_tree_s *fix_red_black(binary_tree_s *root) {
  if(root->left != NULL && root->left->color == RED && root->left->left != NULL && root->left->left->color == RED){
    root->left->left->color = BLACK;
    return bst_rotate_right(root);
  }
  if(root->left != NULL && root->left->color == RED && root->left->right != NULL && root->left->right->color == RED){
    root->left->color = BLACK;
    root->left = bst_rotate_left(root->left);
    return bst_rotate_right(root);  
  }
  if(root->right != NULL && root->right->color == RED && root->right->right != NULL && root->right->right->color == RED){
    root->right->right->color = BLACK;
    return bst_rotate_left(root);
  }
  if(root->right != NULL && root->right->color == RED && root->right->left != NULL && root->right->left->color == RED){
    root->right->color = BLACK;
    root->right = bst_rotate_right(root->right);
    return bst_rotate_left(root);
  }
  return root;
}

/**
 * @brief Recursively adds a node with a specified value to a binary tree.
 *
 * This function finds the appropriate location within the tree to insert a new node with the given value.
 * It handles the recursion that navigates the tree, comparing the values to find the correct insertion point.
 * Upon reaching the insertion point (where a tree node is NULL), it creates a new red node and attaches it.
 * After insertion, `fix_red_black` is called to adjust the tree's properties to maintain the red-black rules.
 *
 * @param value The integer value to be inserted into the tree.
 * @param root The current root of the tree or subtree; this may be NULL if the subtree is empty.
 *
 * @details
 * - If `root` is NULL, a new red node is created with the provided value.
 * - If the `value` is less than the current root's value, the function is called recursively for the left subtree.
 * - If the `value` is greater than the current root's value, the function is called recursively for the right subtree.
 * - If the `value` matches the current root's value, the insertion may be handled based on specific tree requirements (e.g., ignoring duplicates).
 * - The function `fix_red_black` is responsible for maintaining the red-black tree properties post-insertion, such as ensuring no two consecutive red nodes and balancing the number of black nodes from root to leaves.
 *
 * @return The root of the subtree after the insertion, potentially adjusted by `fix_red_black`.
 */
binary_tree_s *add_node_rec(int value, binary_tree_s *root) {
  if (root == NULL) {
    binary_tree_s *node = malloc(sizeof(binary_tree_s));
    assert(node != NULL);
    node->value = value;
    node->left = node->right = NULL;
    node->color = RED;
    return node;
  }
  if (value < root->value) {
    root->left = add_node_rec(value, root->left);
    root = fix_red_black(root);
  } else if (value > root->value) {
    root->right = add_node_rec(value, root->right);
    root = fix_red_black(root);
  }
  return root;
}

/**
 * @brief Inserts a new node with a specified value into the red-black tree and ensures the root remains black.
 *
 * This function serves as the public API for inserting new values into a red-black tree. It calls `add_node_rec`
 * to handle the recursive insertion of the new value. After insertion, this function ensures that the property of
 * the red-black tree requiring the root node to always be black is maintained, adjusting the root's color if necessary.
 *
 * @param value The integer value to be inserted into the tree.
 * @param root The root of the red-black tree where the value is to be inserted. This can be NULL if the tree is initially empty.
 *
 * @details
 * - The function first calls `add_node_rec` to recursively find the correct location in the tree and insert the new node.
 * - The newly returned root from `add_node_rec` might be red, especially if the tree was empty or if rotations made the new node the root.
 * - After insertion, the color of the root node is set to black to maintain the red-black tree property that the root must always be black.
 * - The returned root might be a new node if the tree was previously empty or if rotations have changed the root.
 *
 * @return The root of the red-black tree after the insertion. This root is guaranteed to be black.
 */
binary_tree_s *add_node(int value, binary_tree_s *root) {
  root = add_node_rec(value, root);
  root->color = BLACK; 
  return root;
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
  /* TODO */
  return false;
}


/**
 * @brief TODO
 *
 */
void dump_tree(binary_tree_s *tree, bool ascending) {
  /* TODO */
  return;
}

/**
 * @brief Finds the parent of a node with a specified value in the binary tree.
 *
 * This function searches for the parent of the node with the specified value.
 * If the node with the given value is found, it returns the parent node. If the node
 * is not found or is the root (and thus has no parent), it returns NULL.
 *
 * @param value The integer value of the node whose parent is to be found.
 * @param root The root of the tree or subtree to be searched.
 *
 * @return The parent node of the node with the specified value, or NULL if not found or if the node is the root.
 */
binary_tree_s *find_parent(int value, binary_tree_s *root) {
    if (root == NULL || root->left == NULL && root->right == NULL) {
        // Tree is empty or root has no children, so no parent exists
        return NULL;
    }
    // Check if the current node is the parent of the node with the given value
    if ((root->left != NULL && root->left->value == value) ||
        (root->right != NULL && root->right->value == value)) {
        return root;
    }
    // Recur to the left subtree if the value is less than
    // the current node's value
    if (value < root->value) {
        return find_parent(value, root->left);
    }
    // Recur to the right subtree if the value is greater than
    // the current node's value
    if (value > root->value) {
        return find_parent(value, root->right);
    }
    // If the value matches the current node's value
    // (should not happen in a valid call)
    return NULL;
}

/**
 * @brief Removes a node with a specified value from the red-black tree.
 *
 * This function searches for a node with the specified value and removes it if found.
 * It ensures that the red-black properties are maintained after the node is removed 
 * by performing appropriate rotations and recoloring.
 *
 * @param value The integer value of the node to be removed.
 * @param root The root of the tree or subtree from which the node is to be removed.
 *
 * @details
 * - If the tree is empty, nothing is removed.
 * - Recursively searches for the node to be removed in the left or right subtree.
 * - Once the node is found:
 *   1. **Case 1: Node is red**:
 *      - If the node is a leaf, it is simply removed.
 *      - If the node has one child, the node is replaced with its child.
 *      - If the node has two children, the node's value is replaced with its in-order successor, and the successor is removed.
 *   2. **Case 2.1: Node is black with a single red child (right)**:
 *      - The right child is made black, and the node is replaced with its right child.
 *   3. **Case 2.2: Node is black with a single red child (left)**:
 *      - The left child is made black, and the node is replaced with its left child.
 *   4. **Case 2.3: Node is black with two red children**:
 *      - Both children are made black, the node's value is replaced with its in-order successor, and the successor is removed.
 *   5. **Case 3: Node is black with no children or black children**:
 *      - The sibling is checked for color and children to determine the appropriate rotation and recoloring to maintain balance.
 *      - Various sub-cases handle rotations and recoloring based on the sibling's color and the colors of its children.
 *
 * @return The new root of the subtree after the node has been removed.
 */
binary_tree_s *remove_node(int value, binary_tree_s *root) {
  if (root == NULL) {
    // Tree is empty, nothing to remove
    return root;
  }
  
  if (value < root->value) {
    // Recur to the left subtree
    root->left = remove_node(value, root->left);
  } else if (value > root->value) {
    // Recur to the right subtree
    root->right = remove_node(value, root->right);
  } else {
    // Node to be deleted is found
    printf("to remove %d\n", root->value);
    // Case 1: Node is red
    if (root->color == RED) {
      // If the node is a leaf node, simply remove it
      if (root->left == NULL && root->right == NULL) {
	free(root);
	return NULL;
      }
      
      // If the node has one child, replace the node with its child
      if (root->left == NULL || root->right == NULL) {
	binary_tree_s *child = (root->left != NULL) ? root->left : root->right;
	free(root);
	return child;
      }
      
      // If the node has two children
      if (root->left != NULL && root->right != NULL) {
	// Find the in-order successor (smallest in the right subtree)
	int successor_value = min_value_node(root->right);
	// Replace the value of root with the successor's value
	root->value = successor_value;
	// Delete the in-order successor
	root->right = remove_node(successor_value, root->right);
      }
    } else {
      // Case 2.1: Node is black with a single red child (right)
      if (root->right != NULL && root->right->color == RED&&root->left == NULL){
	// Make the right child black
	root->right->color = BLACK;
	// Replace the root with its right child
	binary_tree_s *child = root->right;
	free(root);
	return child;
      }
      
      // Case 2.2: Node is black with a single red child (left)
      if (root->left != NULL && root->left->color == RED&&root->right == NULL){
	// Make the left child black
	root->left->color = BLACK;
	// Replace the root with its left child
	binary_tree_s *child = root->left;
	free(root);
	return child;
      }

      // Case 2.3: Node is black with two red children
      if (root->left != NULL && root->left->color == RED &&
	  root->right != NULL && root->right->color == RED) {
	// Replace the root with its in-order successor
	int successor_value = min_value_node(root->right);
	root->value = successor_value;
	root->right = remove_node(successor_value, root->right);
	return root; 
      }
      
      // Case 2.3: Node is black with two red children
      if (root->left != NULL && root->left->color == RED &&
	  root->right != NULL && root->right->color == RED) {
	// Make both children black
	root->left->color = BLACK;
	root->right->color = BLACK;
	// Replace the root with its in-order successor
	int successor_value = min_value_node(root->right);
	root->value = successor_value;
	root->right = remove_node(successor_value, root->right);
	return root;
      }
      
      // Case 3: Node is black with no children or black children
      binary_tree_s *parent = find_parent(value, root);
      if (parent != NULL) {
	binary_tree_s *sibling = (parent->left == root) ? parent->right : parent->left;
	if (sibling != NULL) {
	  if (sibling->color == RED) {
	    // Case 3.1
	    // Colorise the sibling in black 
	    sibling->color = BLACK;
	    // Colorise the parent in red
	    parent->color = RED;
	    // Rotation around the parent
	    if (parent->right == sibling) {
	      // Left rotation if the sibling is the right child
	      root = bst_rotate_left(parent);
	    } else {
	      // Right rotation if the sibling is the left child
	      root = bst_rotate_right(parent);
	    }
	  } else
	    if ((sibling->left == NULL || sibling->left->color == BLACK) &&
		(sibling->right == NULL || sibling->right->color == BLACK)) {
	      // Case 3.2
	      // Colore the sibling in red
	      sibling->color = RED;
	      // Moving the double black to the parent
	      if (parent->color == BLACK) {
		// If the parent is black, then it becomes double black
		parent->color = BLACK;
	      } else {
		// If the parent is red, then it becomes black
		parent->color = BLACK;
	      }
	    } else {
	      // Case 3.3
	      if (sibling->left != NULL && sibling->left->color == RED) {
		// If the sibling has a red internal child (left)
		sibling->left->color = BLACK;
		root = bst_rotate_right(sibling);
		sibling = parent->right; // Update sibling after the rotation
	      }
	      if (sibling->right != NULL && sibling->right->color == RED) {
		// If the sibling has a red external child (right)
		sibling->color = parent->color;
		parent->color = BLACK;
		sibling->right->color = BLACK;
		root = bst_rotate_left(parent);
	      }
	      
	    }
	}
      } else {// parent == NULL
	if  (root->right != NULL){
	  // Replace the root with its in-order successor
	  int successor_value = min_value_node(root->right);
	  root->value = successor_value;
	  root->right = remove_node(successor_value, root->right);
	} else {
	  root = NULL;
	}
      }
    }
  }

  return root;
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

