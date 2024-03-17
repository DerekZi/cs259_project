#include <stdio.h>
#include <stdlib.h>

#include "madd-krnl.h"

int main(int argc, char* argv[])
{   
    float * a = (float *)malloc(sizeof(float)*R*C); 
    float * b = (float *)malloc(sizeof(float)*R*C); 
    float * c = (float *)malloc(sizeof(float)*R*C); 
    float * c_acc = (float *)malloc(sizeof(float)*R*C);

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
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
    for(int i = 0; i < R; i++) {
        for(int j=0; j< C; j++){
            b[i*R+j] = float(i*i) / 2;
        }
    }  

    printf("Starting MADD Example \n");

    // execute original reference code
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            c_acc[i*R+j] += a[i*R+j] + b[i*R+j];
        }
    }  


    // execute kernel code 
    madd(a, b, c);

    // test results
    bool err = false;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
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