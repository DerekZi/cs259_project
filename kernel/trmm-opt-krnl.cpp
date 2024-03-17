#include "trmm-opt-krnl.h"

#pragma ACCEL kernel
void trmm_opt(const float alpha, const float A[60*60], float B[60*80]) {
    #pragma ACCEL pipeline
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            float sum = B[i*R+j];
            for (int k = 0; k < 60; k++) {
                if (k > i) {
                    sum += A[k*R+i] * B[k*R+j];
                }
            }
            B[i*R+j] = alpha * sum;
        }
    }
}