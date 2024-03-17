#include "mm-krnl.h"

#pragma ACCEL kernel
void mm(const float a[R*C], const float b[C*D], float c[R*D]) {
    #pragma ACCEL pipeline
    for (int i = 0; i < R; ++i) {
        for (int k = 0; k < C; ++k) {
            for (int j = 0; j < D; ++j) {
                c[i*R+j] += a[i*R+k] * b[k*C+j];
            }
        }
    }
}