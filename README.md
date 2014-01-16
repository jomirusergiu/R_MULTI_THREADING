R_MULTI_THREADING
=========

R_MULTI_THREADING is a small C project showing some basic examples on multhithreading, for executing several tasks in parallel, based on Pthreads.

INTRODUCTION
-------------

Pthreads are a simple and effective way of creating a multi-threaded application. This introduction to pthreads shows the basic functionality – executing two tasks in parallel and merging back into a single thread when the work has been done.

First we’ll run through the basics of threading applications with pthreads. Multi-threaded applications allow two or more tasks to be executed concurrently (ie: at the same time). 
When a thread is created using pthread_create, both the original thread and the new thread share the same code base and the same memory – it’s just like making two function calls at the same time. 
Multi-threaded applications come with a whole host of concurrency issues, which will be discussed further in a future post.

All C programs using pthreads need to include the pthread.h header file (ie: #include <pthread.h>). There are four steps to creating a basic threaded program:
1: Define thread reference variables
The variable type pthread_t is a means of referencing threads. There needs to be a pthread_t variable in existence for every thread being created. Something like pthread_t thread0; will do the trick.

2: Create an entry point for the thread
When creating a thread using pthreads, you need to point it to a function for it to start execution. The function must return void * and take a single void * argument. For example, if you want the function to take an integer argument, you will need to pass the address of the integer and dereference it later. This may sound complicated but, as is shown below, it’s pretty simple. An example function signature would be void *my_entry_function(void *param);

3: Create the thread
Once the pthread_t variable has been defined and the entry point function created, we can create the thread using pthread_create. This method takes four arguments: a pointer to the pthread_t variable, any extra attributes (don’t worry about this for now – just set it to NULL), a pointer to the function to call (ie: the name of the entry point) and the pointer being passed as the argument to the function. Now there’s a lot of pointers in that call, but don’t stress – it’s not as tricky as it sounds. This call will look something like pthread_create(&thread0, NULL, my_entry_function, &parameter);

4: Join everything back up
When the newly-created thread has finished doing it’s bits, we need to join everything back up. This is done by the pthread_join function which takes two parameters: the pthread_t variable used when pthread_create was called (not a pointer this time) and a pointer to the return value pointer (don’t worry about this for now – just set it to NULL). This call will look something like pthread_join(thread0, NULL);

And that’s all there is to it. The function used as the thread entry point can call other functions, create variables or do anything any other function can do. It can also use the variables set by the other thread.
When compiling the program, you will also need to add -lpthread to the compile command. ie: 
```
gcc main.c -o main -lpthread
```

Project Usage and Output
-------------
```BASH
RocKK$ gcc main.c -o main -lpthread
RocKK$ ./main
x: 0, y: 0
Second thread - inc_x_thread created
y increment finished
x increment finished
Second thread - inc_x_thread finished, joining
x: 100, y: 100
```

