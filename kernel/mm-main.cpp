#include <stdio.h>
#include <stdlib.h>

#include "mm-krnl.h"

int main(int argc, char* argv[])
{   
    float * a = (float *)malloc(sizeof(float)*R*C); 
    float * b = (float *)malloc(sizeof(float)*C*D); 
    float * c = (float *)malloc(sizeof(float)*R*D); 
    float * c_acc = (float *)malloc(sizeof(float)*R*D);

    for(int i=0; i<R; i++){
        for(int j=0; j<D; j++){
            c[i*R+j]=0;
            c_acc[i*R+j]=0;
        }
    }

    // init
    for(int i = 0; i < R; i++) {
        for(int j=0; j< C; j++){
            a[i*R+j] = float(i) / 2;
        }
    }    
    for(int i = 0; i < C; i++) {
        for(int j=0; j< D; j++){
            b[i*C+j] = float(i*i) / 2;
        }
    }  

    printf("Starting MM Example \n");

    // execute original reference code
    for (int i = 0; i < R; ++i) {
        for (int k = 0; k < C; ++k) {
            for (int j = 0; j < D; ++j) {
                c_acc[i*R+j] += a[i*R+k] * b[k*C+j];
            }
        }
    }  


    // execute kernel code 
    mm(a, b, c);

    // test results
    bool err = false;
    for(int i=0; i<R; i++){
        for(int j=0; j<D; j++){
            if ((c[i*R+j] - c_acc[i*R+j]) / c[i*R+j] > 1e-4 || (c[i*R+j] - c_acc[i*R+j]) / c[i*R+j] < -1e-4) {
                err = true;
            }
        }
    }

    free(a);
    free(b);
    free(c);
    free(c_acc);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}