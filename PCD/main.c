#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 2

struct ThreadArgs
{
    double *vetorR1;
    double *vetorR2;
    double *vetorT1;
    double *vetorT2;
    double *vetorD;
    int start;
    int end;
};

void *CalculaThread(void *args)
{
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;

    for (int i = threadArgs->start; i < threadArgs->end; i++)
    {
        double r1 = threadArgs->vetorR1[i];
        double r2 = threadArgs->vetorR2[i];
        double theta1 = threadArgs->vetorT1[i];
        double theta2 = threadArgs->vetorT2[i];

        double theta_diff = theta1 - theta2;
        double cos_theta_diff = cos(theta_diff * 3.14 / 180);

        threadArgs->vetorD[i] = sqrt(r1 * r1 + r2 * r2 - 2 * r1 * r2 * cos_theta_diff);
    }
}

int main(void)
{

    double n = 100000;
    double *vetorR1 = (double *)malloc(n * sizeof(double));
    double *vetorR2 = (double *)malloc(n * sizeof(double));
    double *vetorT1 = (double *)malloc(n * sizeof(double));
    double *vetorT2 = (double *)malloc(n * sizeof(double));
    double *vetorD = (double *)malloc(n * sizeof(double));
    srand(time(NULL));

    if (vetorR1 == NULL || vetorR2 == NULL || vetorT1 == NULL || vetorT2 == NULL)
    {
        printf("Falha na alocação de memória.\n");
        return 1;
    }
    printf("opa\n");
    for (int i = 0; i < n; i++)
    {
        double auxR1 = (double)rand() /(double)RAND_MAX * 100;
        vetorR1[i] = auxR1;
        double auxR2 = rand() % (100 - 0 + 1) + 0;
        vetorR2[i] = auxR2;
        double auxT1 = rand() % (360 - 0 + 1) + 0;
        vetorT1[i] = auxT1;
        double auxT2 = rand() % (360 - 0 + 1) + 0;
        vetorT2[i] = auxT2;
    }

    pthread_t threads[NUM_THREADS];
    struct ThreadArgs threadArgs[NUM_THREADS];

    int step = n / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadArgs[i].vetorR1 = vetorR1;
        threadArgs[i].vetorR2 = vetorR2;
        threadArgs[i].vetorT1 = vetorT1;
        threadArgs[i].vetorT2 = vetorT2;
        threadArgs[i].vetorD = vetorD;
        threadArgs[i].start = i * step;
        threadArgs[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * step;
        pthread_create(&threads[i], NULL, CalculaThread, (void *)&threadArgs[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 100; i++)
    {
        printf("D[%d]: %lf\n", i, vetorD[i]);
    }

    free(vetorR1);
    free(vetorR2);

    free(vetorT1);
    free(vetorT2);

    return 0;
}
