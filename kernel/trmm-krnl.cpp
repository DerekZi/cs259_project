#include "trmm-krnl.h"

#pragma ACCEL kernel
void trmm(const float alpha, const float A[60*60], float B[60*80]) {


// #pragma ACCEL PIPELINE auto{__PIPE__L0}
  
// #pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
// #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
//   for (int i = 0; i < 60; i++) {
    
// #pragma ACCEL PIPELINE auto{__PIPE__L1}
    
// #pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
// #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
//     for (int j = 0; j < 80; j++) {
      
//     #pragma ACCEL PARALLEL reduction=B FACTOR=auto{__PARA__L2}
//       for (int k = 0; k < 60; k++) {
//         if (k > i) {
//           B[i][j] += A[k][i] * B[k][j];
//         }
//       }
//       B[i][j] = alpha * B[i][j];
//     }
//   }


    #pragma ACCEL PIPELINE auto{__PIPE__L0}
  
    #pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
    #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
    for (int i = 0; i < 60; i++) {
        #pragma ACCEL PIPELINE auto{__PIPE__L1}
    
        #pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
        #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
        for (int j = 0; j < 80; j++) {
            #pragma ACCEL PARALLEL reduction=B FACTOR=auto{__PARA__L2}
            for (int k = 0; k < 60; k++) {
                if (k > i) {
                    B[i*R+j] += A[k*R+i] * B[k*R+j];
                }
            }
            B[i*R+j] = alpha * B[i*R+j];
        }
    }
}