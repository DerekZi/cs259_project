#include <stdio.h>
#include <stdlib.h>

#include "syrk-krnl.h"

int main(int argc, char* argv[])
{   
    float * A = (float *)malloc(sizeof(float)*N*M); 
    float * C = (float *)malloc(sizeof(float)*N*N); 
    float * C_acc = (float *)malloc(sizeof(float)*N*N);
    float alpha = 2.5;
    float beta = 3.5;

    // init
    for(int i = 0; i < N; i++) {
        for(int j=0; j< M; j++){
            A[i*M+j] = float(i) / 2;
        }
    }    
    for(int i = 0; i < N; i++) {
        for(int j=0; j< N; j++){
            C[i*N+j] = float(i*i) / 2;
            C_acc[i*N+j] = C[i*N+j];
        }
    }  

    printf("Starting SYRK Example \n");

    // execute original reference code
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j <= i) {
                C_acc[i*N+j] *= beta;
            }
        }
        for(int k = 0; k < M; k++){
            for (int j = 0; j < N; ++j) {
                if (j <= i) {
                    C_acc[i*N+j] += alpha * A[i*M+k] * A[j*M+k];
                }
            }
        }
    }
        
     


    // execute kernel code 
    kernel_syrk(alpha, beta, C, A);

    // test results
    bool err = false;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if ((C[i*N+j] - C_acc[i*N+j]) / C[i*N+j] > 1e-4 || (C[i*N+j] - C_acc[i*N+j]) / C[i*N+j] < -1e-4) {
                err = true;
            }
        }
    }

    free(A);
    free(C);
    free(C_acc);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}