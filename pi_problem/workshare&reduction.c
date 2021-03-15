#include <stdio.h>
#include <omp.h>
double step;
static long num_steps = 100000000;

int main() {
    int i;
    double x, pi, sum=0.0;
    step = 1.0/(double) num_steps;
    double start_time, run_time;
    start_time = omp_get_wtime();
    omp_set_num_threads(4);

    #pragma omp parallel for reduction(+:sum)
        for(i=0;i<num_steps;i++) {
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }

    pi = step*sum;
    run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf milli-seconds\n ",num_steps,pi,run_time);
}