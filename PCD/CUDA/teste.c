%%nvprof
#include <cuda_runtime.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TAM 1

__global__ void sumArraysOnGPU(const float *A, const float *B, float *C, const int N) {
    //o indice da thread é o numero do bloco vzs o tamanho do bloco mais o identificador da thread dentro do bloco
    long long int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx<N) C[idx] = A[idx] + B[idx];
}

int main() {
    //Tamanho do vetor
    long int nElem = TAM*1024*1024*2+1;

    //Aloca memória pros vetores na CPU
    size_t nBytes = nElem * sizeof(float);
    float *h_A, *h_B, *h_C;
    h_A = (float *)malloc(nBytes);
    h_B = (float *)malloc(nBytes);
    h_C = (float *)malloc(nBytes);

    //Cria dados iniciais
    for (long int i=0; i<nElem; i++) {
        h_A[i] = i;
        h_B[i] = i*i;
		    h_C[i] = 0;
    }

    //Aloca memória para os vetores na GPU
    float *d_A, *d_B, *d_C;
    cudaMalloc((float**)&d_A, nBytes);
    cudaMalloc((float**)&d_B, nBytes);
    cudaMalloc((float**)&d_C, nBytes);

    //Copia os dados para a GPU
    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, h_C, nBytes, cudaMemcpyHostToDevice);

    //Número de blocos e threads a serem passados para o kernel
    //Número de threads no bloco (tamBloco)
    dim3 nThreads = 1024;
    //Número de blocos no grid (tamGrid)
    dim3 nBlocks = (nElem+nThreads.x-1)/nThreads.x;

    //Executa o kernel
    sumArraysOnGPU<<<nBlocks, nThreads>>>(d_A, d_B, d_C, nElem);

    //Copia os dados de volta para a CPU
    cudaMemcpy(h_C, d_C, nBytes, cudaMemcpyDeviceToHost);

    //Avalia os resultados
    for(long int i=0; i<nElem; i++) {
		    assert(h_A[i] + h_B[i] == h_C[i]);
        if(i==nElem-1) printf("Soma realizada com sucesso!");
    }

    //Libera memoria
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);
    return(0);
}