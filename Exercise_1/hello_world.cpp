/******************************************************************************
* Printing hello world from each thread along with their thread_id (tid).
* The total no of threads is printed only by the master thread.
******************************************************************************/

#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

 int nthreads, tid;

 /* Fork a team of threads with each thread having a private tid variable */
 #pragma omp parallel private(tid)
   {

   /* Obtain and print thread id */
   tid = omp_get_thread_num();
   printf("Hello World from thread = %d\n", tid);

   /* Only master thread does this */
   if (tid == 0) 
     {
     nthreads = omp_get_num_threads();
     printf("Number of threads = %d\n", nthreads);
     }

   } 

   return 0;

 }