%%nvprof
#include <stdio.h>
#include <assert.h>

#define N 4

__global__ void additionMatricesKernel(int *d_a, int *d_b, int *d_c){
  //Define os índices das threads
  int i = threadIdx.y+blockIdx.y*blockDim.y;
  int j = threadIdx.x+blockIdx.x*blockDim.x;
  //Realiza a soma de cada elemento
  d_c[i*N+j] = d_a[i*N+j] + d_b[i*N+j];
}

int main(){

  //Define as matrizes quadradas NxN
    int MatriCA[N][N], MatrizCB[N][N], MatrizCC[N][N];

  //Preenche as matrizes
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			MatriCA[i][j] = MatrizCB[i][j] = i+j;
			MatrizCC[i][j] = 0;
		}
	}

	//Declara os ponteiros para a GPU
	int *MatrizGA, *MatrizGB, *MatrizGC;

	const int numeroBytes = N * N * sizeof(int);

  //Aloca memória na GPU
	cudaMalloc((void**)&MatrizGA,numeroBytes);
	cudaMalloc((void**)&MatrizGB,numeroBytes);
	cudaMalloc((void**)&MatrizGC,numeroBytes);

  //Copia dados da CPU para a GPU
	cudaMemcpy(MatrizGA, MatriCA, numeroBytes, cudaMemcpyHostToDevice);
	cudaMemcpy(MatrizGB, MatrizCB, numeroBytes, cudaMemcpyHostToDevice);
	cudaMemcpy(MatrizGC, MatrizCC, numeroBytes, cudaMemcpyHostToDevice);

    //Declaração do tamanho do grid e tamanho dos blocos
    dim3 blockSize(2,2);
	dim3 gridSize(N/2,N/2);

	//Executa o kernel
	additionMatricesKernel<<<gridSize,blockSize>>>(MatrizGA, MatrizGB, MatrizGC);

  //Copia os dados de volta para a CPU
	(cudaMemcpy(MatrizCC, MatrizGC, numeroBytes, cudaMemcpyDeviceToHost));

  //Testa se a soma foi executada corretamente
	for(int i=0; i < N; i++){
		for(int j=0; j < N; j++){
			assert(MatriCA[i][j] + MatrizCB[i][j] == MatrizCC[i][j]);
		}
	}
  printf("\nSOMA EXECUTADA COM SUCESSO!\n\n");

  //Desaloca memória
	cudaFree(MatrizGA);
	cudaFree(MatrizGB);
	cudaFree(MatrizGC);
}