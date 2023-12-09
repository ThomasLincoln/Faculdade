%%gpu
#include <stdio.h>

//Função do Kernel CUDA
__global__ void helloWorldCuda(){
    helloFromCPU();
    printf("Hello World from GPU! Block number: %d Thread number: %d\n", blockIdx.x ,threadIdx.x);
    return;
}

void helloFromCPU(){
    printf("Hello World from CPU!\n");
    return;
}


int main() {
    // Chama a função com um único bloco e um único thread
    helloWorldCuda<<<5,2>>>();

    
    cudaDeviceReset();
    // Esperar que o GPU termine antes de continuar
    cudaDeviceSynchronize();

    // Verificar erros na chamada do kernel
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess) {
        fprintf(stderr, "Erro CUDA: %s\n", cudaGetErrorString(error));
        return -1;
    }
    printf("Hello World from CPU!\n");

    return 0;
}

/*
    ? Então, basicamente, você que criar um kernel, que é a função que cada thread de cada bloco vai executar


    Um bloco é composto por n threads, você modifica isso mudando os valores de:
        helloWorldCuda<<<numero de blocos, numero de threads>>>();


    Depois disso, você executa essas funções para encerrar o processo cuda
    
    cudaDeviceReset();
    cudaDeviceSynchronize();

*/