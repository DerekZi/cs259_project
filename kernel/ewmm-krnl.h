#ifndef EWMM_KRNL_H
#define EWMM_KRNL_H

#define R 1024
#define C 1024

void ewmm(const float a[R*C], const float b[R*C], float c[R*C]);

#endif