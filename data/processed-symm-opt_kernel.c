

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//SIDE = 'L'
//UPLO = 'L'
// =>  Form  C := alpha*A*B + beta*C
// A is MxM
// B is MxN
// C is MxN
//note that due to Fortran array layout, the code below more closely resembles upper triangular case in BLAS
  
  
  
  for (i = 0; i < 60; i++) {
    
    
    
    for (j = 0; j < 80; j++) {
      
      double tmp = B[i][j];
      for (k = 0; k < 60; k++) {
        if (k < i) {
          C[k][j] += alpha * tmp * A[i][k];
        }
      }

      double temp2 = ((double )0);
      for (k = 0; k < 60; k++) {
        if (k < i) {
          temp2 += B[k][j] * A[i][k];
        }
      }
      C[i][j] = beta * C[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
    }
  }
}
