#include <omp.h>
#include <stdio.h>


int main()
{
    double t1 = omp_get_wtime();

    double pi;
    long num_steps = 1000000000;
    double step = 1.0 / (double)num_steps;

#pragma omp parallel
    {
        double x, sum = 0.0;
        int n_threads = omp_get_num_threads();
        long chunk = num_steps / n_threads;

        int ID = omp_get_thread_num();
        long thread_start_i = chunk * ID;
        long thread_end_i = thread_start_i + chunk;

        long i;
        for (i = thread_start_i; i < thread_end_i; i++)
        {
            // + 0.5 just picks the
            // middle of the next rectangle
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        pi += step * sum;
    }
    printf("Pi: %1.20f\n", pi);

    double t2 = omp_get_wtime();
    printf("Spent: %f\n", t2 - t1);
}