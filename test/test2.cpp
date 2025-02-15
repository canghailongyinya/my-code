#include <stdio.h>
#include <omp.h>
int main()
{
    omp_set_num_threads(8);
    #pragma omp parallel 
    {
        int i = omp_get_thread_num();
        printf( "Hello from thread %d\n",i);
    }
}