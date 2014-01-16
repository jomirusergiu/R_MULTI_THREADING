//
//  main.c
//  R_MULTI_THREADING
//
//  Created by RocKK on 16/01/14.
//  Copyright (c) 2014 RocKK.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms are permitted
//  provided that the above copyright notice and this paragraph are
//  duplicated in all such forms and that any documentation,
//  advertising materials, and other materials related to such
//  distribution and use acknowledge that the software was developed
//  by the RocKK.  The name of the
//  RocKK may not be used to endorse or promote products derived
//  from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED ''AS IS'' AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#include <pthread.h>
#include <stdio.h>

//This function is run by the second thread 
void *inc_x(void *x_void_ptr)
{
	//Increment x to 100
	int *x_ptr = (int *)x_void_ptr;
	while(++(*x_ptr) < 100);
	printf("x increment finished\n");
	//The function must return something - NULL will do
	return NULL;
}

int main()
{
	//This variable is our reference to the second thread
	pthread_t inc_x_thread;
	int x = 0, y = 0;
	printf("x: %d, y: %d\n", x, y);
	
	//Create a second thread which executes inc_x(&x)
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	else{
		printf("Second thread - inc_x_thread created\n");
	}

	//Increment y to 100 on the first thread
	while(++y < 100);
	printf("y increment finished\n");
	
	//Wait for the second thread to finish
	if(pthread_join(inc_x_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}
	else{
	     	printf("Second thread - inc_x_thread finished, joining\n");
	}

	//Show the results - x is now 100 thanks to the second thread
	printf("x: %d, y: %d\n", x, y);
	
	return 0;
}