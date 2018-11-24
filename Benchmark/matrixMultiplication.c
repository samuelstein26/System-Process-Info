/*
   SIS0563 - Fundamentos de Sistemas Operacionais 
   Prof. Vinicius Garcia Pinto 

   Instruções para compilacao:
                               gcc matrixMultiplication.c -o matrixMutiplication
   Instruções para execucao:
                               ./matrixMultiplication <matrixSize>
   Exemplo para matriz de 1024 x 1024
                               ./matrixMutiplication 1024                             

   Este codigo implementa uma multiplicacao de matrizes. O mesmo deve
   ser utilizado como aplicacao de teste para o Trabalho Pratico da
   Disciplina (Trabalho Prático - Monitoramento de Aplicação e Sistema).  O codigo foi adaptado de
   <<https://github.com/msserpa/ufrgs-intel-modern-code/blob/master/matrixMultiplication/matrixMultiplication.c>>. 
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void matrix_mult(double *A, double *B, double *C, int N){
  int i, j, k;

  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      for(k = 0; k < N; k++)
	C[i * N + j] += A[i * N + k] * B[k * N + j];

}

int main(int argc, char **argv){
  char *awnser[] = { "bad", "ok" };
	
  int i, j, n, is_ok;
  time_t tstart, tend;

	
  if(argc != 2){
    fprintf(stderr, "Usage: %s <size>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);
	
  n = n % 8 == 0 ? n : n + (8 - n % 8);
	
  printf("number of rows x cols: %i\n", n);
	
  double *A = malloc(n * n * sizeof(double));
  assert(A != NULL);
	
  double *B = malloc(n * n * sizeof(double));
  assert(B != NULL);
	
  double *C = malloc(n * n * sizeof(double));
  assert(C != NULL);
	
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++){
      A[i * n + j] = 1; /* Do not */
      B[i * n + j] = 1; /* change */
      C[i * n + j] = 0; /* it */
    }

  tstart = time(NULL);
  matrix_mult(A, B, C, n);
  tend = time(NULL);
	
  is_ok = 1;	
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      if(C[i * n + j] != (double) n){
	is_ok = 0;
	i = n;
	j = n;
      }
	
  printf("multiply values are %s\ntime: %.3f seconds\n", awnser[is_ok], difftime(tend, tstart));

  free(A);
  free(B);
  free(C);

  return 0;
}
