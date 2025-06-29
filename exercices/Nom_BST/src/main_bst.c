/**
 * @file main_bst.c
 * @brief Test program for binary search tree operations defined in bst.h.
 * 
 * This program allows testing of binary tree operations by taking command line arguments to
 * add numbers to a tree, find numbers in the tree, print the tree, remove numbers from the tree,
 * and balance the tree.
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

int verbose=0;

/**
 * @brief Checks if a string represents a valid number.
 * 
 * @param s Pointer to the string to be checked.
 * @return Non-zero if the string is a number, zero otherwise.
 */
int is_number(char *s) {
  if(s[0]=='-')
    s++;
  while(*s != '\0' && *s >= '0' && *s <= '9') 
    s++;
  return *s == '\0';
}

/**
 * @brief Displays usage information for the program.
 */
void help(char *first_arg) {
  printf("Usage: %s [options] commands...\n",first_arg);
  printf("Options:\n");
  printf("  -h, --help         Show this help message and exit.\n");
  printf("  -v, --verbose      Be verbose while processing commands.\n");
  printf("Commands:\n");
  printf("  p, print           Print the current state of the tree.\n");
  printf("  d_asc, dump_asc    Print all values in the binary search tree in the ascending order.\n");
  printf("  d_desc, dump_desc  Print all values in the binary search tree in the descending order.\n");
  printf("  f, find [number]   Find and display if a number is in the tree.\n");
  printf("  r, remove [number] Remove a number from the tree.\n");
  printf("  Numbers:           Add number(s) to the tree.\n");
}

/**
 * @brief Main function which processes command line arguments to manipulate a binary tree.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 0 on success, 1 on error or if help is requested with wrong usage.
 */
int main(int argc, char **argv) {
  char *argv0=argv[0];
  argc--;argv++;
  while(argc>0) { // Process options until first Command.
    if(strcmp(argv[0], "--help") == 0 || strcmp(argv[0], "-h") == 0) {
      help(argv0);
      return 0;
    } else if (strcmp(argv[0], "--verbose") ==0 || strcmp(argv[0], "-v")==0) {
      verbose=1;
      printf("Verbose output requested.\n");
    } else if(argv[0][0]=='-') {
      fprintf(stderr,"unknown option '%s'.\n",argv[1]);
      help(argv0);
      return 1;
    } else 
      break;
    argc--;argv++;
  }
  if(argc<=0) {
    fprintf(stderr,"/!\\ At less one command must be give.\n");
    help(argv0);
    return 1;
  }
  // create the tree used by the commands
  binary_tree_s *tree = NULL ;
  int step=0; 
  while(argc>0) { // process the commands. 
    step++;
    if (strcmp(argv[0], "p") == 0 || strcmp(argv[0], "print") == 0) {
      if(verbose) printf("%02d) process print\n",step);
      binary_tree_print(tree);
      argc--;argv++;
    } else
      if (strcmp(argv[0], "d_asc") == 0 || strcmp(argv[0], "dump_asc") == 0) {
	if(verbose) printf("%02d) process dump ascending\n",step);
	dump_tree(tree,true);
	printf("\n");
	argc--;argv++;
      } else if (strcmp(argv[0], "d_desc") == 0 || strcmp(argv[0], "dump_desc") == 0) {
	if(verbose) printf("%02d) process dump descending\n",step);
	dump_tree(tree,false);
	printf("\n");
	argc--;argv++;
      } else if (strcmp(argv[0], "f") == 0 || strcmp(argv[0], "find") == 0) {
	if (argc > 1 && is_number(argv[1])) {
	  argc--;argv++;
	  int v = atoi(argv[0]);
	  argc--;argv++;
	  if(verbose) printf("%02d) process find %d ",step, v);
	  int b = find_node(v, tree);
	  printf("%s\n", b ? "true" : "false");
	} else {
	  fprintf(stderr,"/!\\ 'find' expects a number argument.\n");
	  help(argv0);
	  return 1;
	}
      } else if (strcmp(argv[0], "r") == 0 || strcmp(argv[0], "remove") == 0) {
	if (argc>1 && is_number(argv[1])) {
	  argc--;argv++;
	  int v = atoi(argv[0]);
	  argc--;argv++;
	  if(verbose) printf("%02d) process remove %d\n", step, v);
	  tree=remove_node(v,tree);
	} else {
	  fprintf(stderr,"/!\\ 'remove' expects one integer argument.\n");
	  help(argv0);
	  return 1;
	}
      } else if (is_number(argv[0])) {
	int v = atoi(argv[0]);
	argc--;argv++;
	if(verbose) printf("%02d) process add %d\n", step, v);
	tree = add_node(v, tree);
      } else {
	fprintf(stderr,"/!\\ Invalid argument '%s'.\n", argv[0]);
	help(argv0);
	return 1;
      }
  }
  binary_tree_free(tree);
  return 0;
}

