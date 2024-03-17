#include <stdio.h>
#include <stdlib.h>

#include "trmm-krnl.h"

int main(int argc, char* argv[])
{   
    float * A = (float *)malloc(sizeof(float)*R*R); 
    float * B = (float *)malloc(sizeof(float)*R*C); 
    float * Bcopy = (float *)malloc(sizeof(float)*R*C); 

    float alpha=2.5;

    // init
    for(int i = 0; i < R; i++) {
        for(int j=0; j< R; j++){
            A[i*R+j] = float(i) / 2;
        }
    }    
    for(int i = 0; i < R; i++) {
        for(int j=0; j< C; j++){
            B[i*R+j] = float(i*i) / 2;
            Bcopy[i*R+j] = B[i*R+j];
        }
    }  

    printf("Starting TRMM Example \n");

    // execute original reference code
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            for (int k = 0; k < 60; k++) {
                if (k > i) {
                    Bcopy[i*R+j] += A[k*R+i] * Bcopy[k*R+j];
                }
            }
            Bcopy[i*R+j] = alpha * Bcopy[i*R+j];
        }
    }


    // execute kernel code 
    trmm(alpha, A, B);

    // test results
    bool err = false;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if ((B[i*R+j] - Bcopy[i*R+j]) / B[i*R+j] > 1e-4 || (B[i*R+j] - Bcopy[i*R+j]) / B[i*R+j] < -1e-4) {
                err = true;
            }
        }
    }

    free(A);
    free(B);
    free(Bcopy);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}