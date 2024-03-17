#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "jacobi_1d-krnl.h"

int main(int argc, char* argv[])
{   
    float * A = (float *)malloc(sizeof(float)*N); 
    float * B = (float *)malloc(sizeof(float)*N); 
    float * Acpy = (float *)malloc(sizeof(float)*N); 
    float * Bcpy = (float *)malloc(sizeof(float)*N); 

    // init
    for(int i = 0; i < N; i++) {
        A[i] = float(i) / 2;
        Acpy[i] = A[i];
    }

    for(int i = 0; i < N; i++) {
        B[i] = float(i*i) / 2;
        Bcpy[i] = B[i];
    }  

    printf("Starting jacobi_1d Example \n");
    // execute original reference code
    //#pragma scop
    for (int t = 0; t < steps; t++) {
        for (int i = 1; i < N - 1; i++) {
            Bcpy[i] = 0.33333 * (Acpy[i - 1] + Acpy[i] + Acpy[i + 1]);
        }
        
        for (int i = 1; i < N - 1; i++) {
            Acpy[i] = 0.33333 * (Bcpy[i - 1] + Bcpy[i] + Bcpy[i + 1]);
        }
    }
    //#pragma endscop

    // execute kernel code 
    kernel_jacobi_1d(A, B);

    // test results
    bool err = false;
    for(int i=0; i<N; i++){
        if ((A[i] - Acpy[i]) / A[i] > 1e-4 || (A[i] - Acpy[i]) / A[i] < -1e-4) {
            err = true;
        }
        if ((B[i] - Bcpy[i]) /B[i] > 1e-4 || (B[i] - Bcpy[i]) / B[i] < -1e-4) {
            err = true;
        }
    }

    free(A);
    free(B);
    free(Acpy);
    free(Bcpy);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}