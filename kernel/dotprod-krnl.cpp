#include "dotprod-krnl.h"

#pragma ACCEL kernel
void dot_product(const float a[VS], const float b[VS], float c[0]) {
  float prod = 0.f;

  #pragma ACCEL pipeline
  for (int i = 0; i < VS; ++i) {
    prod += a[i] * b[i];
  }
  c[0] = prod;
}

// void dot_product(const float a[VS], const float b[VS], float c[0]) {
//   float prod_buf[VS];
//   for(int i=0; i<VS; i++){
//     prod_buf[i]=0.f;
//   }

//   #pragma ACCEL parallel factor=2
//   for(int i=0; i<64; i++){
//     #pragma ACCEL parallel factor=64
//     for(int j=0; j<64; j++){
//       prod_buf[j] += a[i*64+j]*b[i*64+j];
//     }
//   }
//   float final_prod = 0.f;
//   #pragma ACCEL parallel factor=64
//   for(int i=0; i<VS; i++){
//     final_prod += prod_buf[i];
//   }
//   c[0] = final_prod;
// }