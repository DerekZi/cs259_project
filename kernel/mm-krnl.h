#ifndef MM_KRNL_H
#define MM_KRNL_H

#define R 1024
#define C 1024
#define D 1024

void mm(const float a[R*C], const float b[C*D], float c[R*D]);

#endif