/**
 * @file main_heap.c
 * @brief Test program for heap operations defined in heap.h.
 * 
 * This program allows testing of heap operations by taking command line arguments to
 * add numbers to a heap, print output of the heap and remove it. 
 *
 * @author Grimaud
 * @date 04/15/2024
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

int is_number(char *string) {
    assert(string != NULL);
    if(*string=='-') string++;
    if(*string=='\0') return 0;
    while(*string>='0' && *string<='9')
      string++;
    while(*string==' ' || *string=='\t' || *string=='\n')
      string++;
    return *string=='\0';
}

int main(int argc, char **argv) {
  heap_s *my_heap;
  if(argc==1 || strcmp(argv[1],"-help")==0) {
    printf("%s: usage\n",argv[0]);
    printf("\t%s <cmd1> <cmd2> <cmd3> ...\n",argv[0]);
    printf("\twhere <cmdx> in :\n");
    printf("\t\tp      : means print the output of heap\n");
    printf("\t\tnumber : (e.g -3) means enqueue an input number in the heap\n");
    printf("\t\tr      : means dequeue (remove) the output from the heap\n");
    printf("\ttry\n");
    printf("\t\t%s 4 5 p 6 6 7 p r p r p 1 2 p r r r r p r \n",argv[0]); 
    printf("\n");
    return 0;
  }	
  my_heap=heap_create();
  printf("heap_create -> ");
  heap_print(my_heap);
  printf("\n");
  for (int i=1;i<argc;i++) {
    if(strcmp(argv[i],"p")==0) {
	    printf("heap_peek   -> %d\n",heap_peek(my_heap));
    } else if(strcmp(argv[i],"r")==0) {
	    printf("heap_remove ");
	    my_heap=heap_remove(my_heap);
	    printf("-> ");
	    heap_print(my_heap);
	    printf("\n");
    } else if(is_number(argv[i])) {
	    int v=atoi(argv[i]);
	    printf("heap_add %d",v);
	    my_heap=heap_add(v,my_heap);
	    printf("  -> ");
	    heap_print(my_heap);
	    printf("\n");
    } else {
	    printf("Operation '%s' is undefined. Try -help.\n",argv[i]);
	    return 1;
    }
  }
  heap_delete(my_heap);
  printf("heap_delete\n");
  return 0;
}

