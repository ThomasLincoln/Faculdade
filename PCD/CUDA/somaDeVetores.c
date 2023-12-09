%%nvprof
#include <cuda_runtime.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TamanhoDoVetor 1

//Função do Kernel CUDA
__global__ void arraySumWithCUDA(const float * A, const float * B, float * C, const int N){
    // ? O indice da thread é (id do bloco * tamanho do bloco) + id da thread
    long long int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx<N) C[idx] = A[idx] + B[idx];
}



int main() {
    long int numeroDeElementos = TamanhoDoVetor * 1024;

    //Alocando a memória para a CPU
    size_t numeroDeBytes = numeroDeElementos * sizeof(float);

    float *vetorCA, *vetorCB, *vetorCC;

    vetorCA = (float *)malloc(numeroDeBytes);
    vetorCB = (float *)malloc(numeroDeBytes);
    vetorCC = (float *)malloc(numeroDeBytes);

    //Criar dados iniciais
    for (long int i =0; i <numeroDeElementos; i++){
        vetorCA[i] = i;
        vetorCB[i] = i*i;
        vetorCC[i] = 0;
    }


    //Alocar memória pro GPU
    float *vetorGA, *vetorGB, *vetorGC;

    cudaMalloc((void **) &vetorGA, numeroDeBytes);
    cudaMalloc((void **) &vetorGB, numeroDeBytes);
    cudaMalloc((void **) &vetorGC, numeroDeBytes);

    //Copiando os valores dos vetores CPU para GPU
    cudaMemcpy(vetorGA, vetorCA, numeroDeBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(vetorGB, vetorCB, numeroDeBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(vetorGC, vetorCC, numeroDeBytes, cudaMemcpyHostToDevice);

    //Definindo tamanho do bloco
    dim3 numeroDeThreads = 1024;
    //número de blocos
    dim3 numeroDeBlocos = (numeroDeElementos+numeroDeThreads.x -1)/numeroDeThreads.x;

    //Executa o kernel
    arraySumWithCUDA<<<numeroDeBlocos, numeroDeThreads>>>(vetorGA, vetorGB, vetorGC, numeroDeElementos);

    cudaMemcpy(vetorCC, vetorGC, numeroDeBytes, cudaMemcpyDeviceToHost);

    //Testando os resultados
    for(long int i =0; i<numeroDeElementos; i++){
        assert(vetorCA[i] + vetorCB[i] == vetorCC[i]);
        if(i == numeroDeElementos-1){
            printf("Soma realizada com sucesso");
        }
    }
    
    cudaFree(vetorGA);
    cudaFree(vetorGB);
    cudaFree(vetorGC);
    free(vetorCA);
    free(vetorCB);
    free(vetorCC);

    cudaDeviceReset();
    cudaDeviceSynchronize();

    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess) {
        fprintf(stderr, "Erro CUDA: %s\n", cudaGetErrorString(error));
        return -1;
    }
    printf("Hello World from CPU!\n");

    return 0;
}

/*
 O importante aqui é entender como nós lidamos com os dados em um vetor. 

    * O número de elementos é basicamente Tamanho * 1024, assim, podemos variar a variavel tamanho e ter mais ou menos elementos

    Também precisamos de calculos para o calculo de numero de blocos e numero de threads
    *   dim3 numeroDeThreads = 1024;
    *   dim3 numeroDeBlocos = (numeroDeElementos+numeroDeThreads.x -1)/numeroDeThreads.x;

    Para manipular o vetor, nós precisamos definir em que localização cada gpu vai alterar o dado:
        * long long int idx = blockIdx.x * blockDim.x + threadIdx.x;
            ? o Indice a ser alterado é o id do bloco * o tamanho do bloco + id do thread
        * if(idx<N) C[idx] = A[idx] + B[idx];
            ? fazemos uma verificação para que não alteremos valores fora do tamanho do vetor
*/