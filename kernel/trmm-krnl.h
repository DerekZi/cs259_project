#ifndef TRMM_KRNL_H
#define TRMM_KRNL_H

#define R 60
#define C 80

void trmm(const float alpha, const float A[R*R], float B[R*C]);

#endif