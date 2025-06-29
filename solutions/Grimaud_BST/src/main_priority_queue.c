/**
 * @file main_priority_queue.c
 * @brief Test program for priority queue operations defined in queue.h.
 * 
 * This program allows testing of priority queue operations by taking command line arguments to
 * add numbers to a priority queue, print the output of queue and remove it. 
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
#include "queue.h"

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
    queue_s *my_queue;
    if(argc==1 || strcmp(argv[1],"-help")==0) {
      printf("%s: usage\n",argv[0]);
      printf("\t%s <cmd1> <cmd2> <cmd3> ...\n",argv[0]);
      printf("\twhere <cmdx> in :\n");
      printf("\t\tp      : means print the output of queue\n");
      printf("\t\tnumber : (e.g -3) means enqueue an input number in the queue\n");
      printf("\t\tr      : means dequeue (remove) the output from the queue\n");
      printf("\ttry\n");
      printf("\t\t%s 4 5 p 7 8 6 p r p r p 1 2 p r r r r p r \n",argv[0]); 
      printf("\n");
      return 0;
    }	
    my_queue=queue_create();
    printf("queue_create    -> ");
    queue_print(my_queue);
    printf("\n");
    for (int i=1;i<argc;i++) {
      if(strcmp(argv[i],"p")==0) {
	printf("queue_peek      -> %d\n",queue_peek(my_queue));
      } else if(strcmp(argv[i],"r")==0) {
	printf("queue_dequeue  ");
	my_queue=queue_dequeue(my_queue);
	printf(" -> ");
	queue_print(my_queue);
	printf("\n");
      } else if(is_number(argv[i])) {
	int v=atoi(argv[i]);
	printf("queue_enqueue %d",v);
	my_queue=queue_enqueue(v,my_queue);
	printf(" -> ");
	queue_print(my_queue);
	printf("\n");
      } else {
	printf("Operation '%s' is undefined. Try -help.\n",argv[i]);
	return 1;
      }
    }
    queue_delete(my_queue);
    printf("queue_delete\n");
    return 0;
}

