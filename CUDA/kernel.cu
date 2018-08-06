#include "kernel.hpp"
#include <iostream>
#include <random>
#include <ctime>
#define N 10
using namespace std;



__global__ void myKernel(void) {

}

__global__ void add(int *a, int *b, int *c) {
    //threads can use shared memory within a block. using keyword __shared__
    __shared__ int temp;
    
    int x_idx = threadIdx.x +blockIdx.x*blockDim.x;
    int y_idx = threadIdx.y +blockIdx.y*blockDim.y;
    int z_idx = threadIdx.z +blockIdx.z*blockDim.z;
    *c = *a + *b;
    c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

void cudaFunc() {
    srand(time(NULL));
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = N*sizeof(int);

    cudaMalloc((void**) &d_a, size);
    cudaMalloc((void**) &d_b, size);
    cudaMalloc((void**) &d_c, size);

    a = new int[N] {1};
    b = new int[N] {2};
    c = new int[N]{};

    // target, source, size, type
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    add<<<N,1>>>(d_a, d_b, d_c);


    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    for (int i = 0; i<N; i++ ) {
        cout << a[i] << "+" << b[i] << "=" << c[i] << endl;
    }
    
}