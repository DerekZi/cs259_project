
void kernel_2mm(int ni, int nj, int nk, int nl, double alpha, double beta, double tmp[40][50], double A[40][70], double B[70][50], double C[50][80], double D[40][80])
{
  int i;
  int j;
  int k;
  // #pragma scop
  /* D := alpha*A*B*C + beta*D */

  //<PLACEHOLDER>
  for (i = 0; i < 40; i++)
  {

    //<PLACEHOLDER>
    for (j = 0; j < 50; j++)
    {
      tmp[i][j] = 0.0;
      //<PLACEHOLDER>
      for (k = 0; k < 70; ++k)
      {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }

  //<PLACEHOLDER>
  for (i = 0; i < 40; i++)
  {

    //<PLACEHOLDER>
    for (j = 0; j < 80; j++)
    {
      D[i][j] *= beta;
      //<PLACEHOLDER>
      for (k = 0; k < 50; ++k)
      {
        D[i][j] += tmp[i][k] * C[k][j];
      }
    }
  }
  // #pragma endscop
}
