#include "ewmm-krnl.h"

#pragma ACCEL kernel
void ewmm(const float a[R*C], const float b[R*C], float c[R*C]) {
    #pragma ACCEL pipeline
    for (int i = 0; i < R; ++i) {
        for(int j=0; j<C; j++){
            c[i*R+j] = a[i*R+j] * b[i*R+j];
        }
    }
}