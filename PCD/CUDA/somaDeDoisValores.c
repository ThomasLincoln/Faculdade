%%gpu
#include <stdio.h>

//Função do Kernel CUDA
__global__ void addWithCuda(int *a, int *b, int *c){
    *c= *a + *b;
    return;
}

void helloFromCPU(){
    printf("Hello World from CPU!\n");
    return;
}


int main() {
    // Variaveis para a cpu
    int c_num1, c_num2, c_num3;
    // Variaveis para a gpu
    int *g_num1, *g_num2, *g_num3;

    int size = sizeof(int);
    cudaMalloc((void **) &g_num1, size);
    cudaMalloc((void **) &g_num2, size);
    cudaMalloc((void **) &g_num3, size);

    c_num1 = 8; c_num2 = 2; c_num3 = 0;

    cudaMemcpy(g_num1, &c_num1, size, cudaMemcpyHostToDevice);
    cudaMemcpy(g_num2, &c_num2, size, cudaMemcpyHostToDevice);

    addWithCuda<<<1,1>>>(g_num1, g_num2, g_num3);

    cudaMemcpy(&c_num3, g_num3, size, cudaMemcpyDeviceToHost);

    printf("result is %d\n", c_num3);

    cudaFree(g_num1);
    cudaFree(g_num2);
    cudaFree(g_num3);
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
    A gente precisa fazer a alocação de forma diferente, a cpu e gpu, tem memórias diferentes,
    precisam de variáveis diferentes.
    Então, quando eu quero fazer operações com variáveis,

    Eu crio ponteiros para variáveis e aloco elas usando 

    * cudaMalloc((void**), variavel, tamanho)

    Também temos o nosso copy, que assim, é possível pegar um valor do cpu e por na gpu e vice versa. 


    * cudaMemcpy(var receptora, doadora, size, hostToDevice ou DeviceToHost);

    Para passar parametros para o kernel, se faz assim:

    * addWithCuda<<<1,1>>>(g_num1, g_num2, g_num3);
*/