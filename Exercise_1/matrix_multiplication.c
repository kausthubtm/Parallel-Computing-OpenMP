/******************************************************************************
* Matrix multiplication
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 62      // no of rows in matrix A
#define NCA 15      // no of columns in matrix A
#define NCB 7       // no of columns in matrix B

int main(int argc, char *argv[])
{
    int tid, nthreads, i, j, k, chunk;
    double a[NRA][NCA], b[NCA][NCB], c[NRA][NCB];
    chunk = 10;

    #pragma omp parallel shared(a,b,c,chunk,nthreads) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if(tid==0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n",nthreads);
            printf("Initializing matrices....");
        }

        #pragma omp for schedule (static, chunk)
            for(i=0; i<NRA; i++)
                for(j=0; j<NCA; j++)
                    a[i][j] = i+j;
        #pragma omp for schedule (static, chunk)
            for(i=0; i<NCA; i++)
                for(j=0; j<NCB; j++)
                   b[i][j] = i*j;
        #pragma omp for schedule (static, chunk)
            for(i=0; i<NRA; i++)
                for(j=0; j<NCB; j++)
                    c[i][j] = 0;

        printf("Thread %d starting matrix mutiplication....\n", tid);
        #pragma omp for schedule (static, chunk)
        for(i=0; i<NRA; i++)
        {
            printf("Thread=%d did row=%d\n",tid,i);
            for(j=0; j<NCB; j++)
                for(k=0; k<NCA; k++)
                    c[i][j] += a[i][k]*b[k][j]; 
        }

    }

    /*** Print results ***/
    printf("******************************************************\n");
    printf("Result Matrix:\n");
    for (i=0; i<NRA; i++)
    {
    for (j=0; j<NCB; j++) 
        printf("%6.2f   ", c[i][j]);
    printf("\n"); 
    }
    printf("******************************************************\n");
    printf ("Done.\n");


}
