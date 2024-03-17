#ifndef SYRK_KRNL_H
#define SYRK_KRNL_H

#define N 80
#define M 60

void kernel_syrk(float alpha,float beta,float C[N*N],float A[N*M]);

#endif