#include <omp.h>
#include <stdio.h>

/*
* Reduction
*/
int main()
{
    double t1 = omp_get_wtime();

    double pi;
    static long num_steps = 1000000000;
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;

    long i;

#pragma omp parallel
    {
        long chunk = num_steps / (long)omp_get_num_threads();

#pragma omp for schedule(auto) reduction(+ \
                                         : sum)
        for (i = 0; i < num_steps; i++)
        {
            double x;
            if (i == 0)
            {
                printf("Threads num: %d\n", omp_get_num_threads());
            }

            // + 0.5 just picks the
            // middle of the next rectangle
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }

    pi += step * sum;
    printf("Pi: %1.30f\n", pi);

    double t2 = omp_get_wtime();
    printf("Spent: %f\n", t2 - t1);
}