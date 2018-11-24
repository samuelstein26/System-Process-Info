/*
   SIS0563 - Fundamentos de Sistemas Operacionais 
   Prof. Vinicius Garcia Pinto 

   Instruções para compilacao:
                               gcc selectionSort.c -o selectionSort
   Instruções para execucao:
                               ./selectionSort <size>
   Exemplo de ordenacao de 200000 de elementos
                               ./selectionSort 200000

   Este codigo implementa uma ordenacao com o algoritmo Selecao. O
   resultado da ordenacao sera comparado com o resultado do algoritmo
   qsort da biblioteca padrao do C. Este codigo deve ser utilizado
   como aplicacao de teste para o Trabalho Pratico da Disciplina
   (Trabalho Prático - Monitoramento de Aplicação e Sistema).  O
   codigo foi adaptado de
   <<https://github.com/msserpa/ufrgs-intel-modern-code/blob/master/selectionSort/selectionSort.c>>.
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void selection_sort(int *v, int n){
  int i, j, min, tmp;

  for(i = 0; i < n - 1; i++){
    min = i;

    for(j = i + 1; j < n; j++)
      if(v[j] < v[min])
	min = j;

    tmp = v[i];
    v[i] = v[min];
    v[min] = tmp;
  }
}

int compare (const void * a, const void * b){
  return (* (int*) a - * (int*) b); /* Do not change it! */
}

int main(int argc, char **argv){
  char *awnser[] = { "bad", "ok" };
  int *vector, *test;
  int i, n, is_ok;
  time_t tstart, tend;
  
  if(argc != 2){
    fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);

  printf("number of elements: %d\n", n);

  vector = (int *) malloc(n * sizeof(int));
  assert(vector != NULL);

  test = (int *) malloc(n * sizeof(int));
  assert(test != NULL);

  srand(time(NULL));

  for(i = 0; i < n; i++)
    vector[i] = rand();

  memcpy(test, vector, n * sizeof(int));

  qsort (test, n, sizeof(int), compare);

  tstart = time(NULL);
  selection_sort(vector, n);
  tend = time(NULL);

  is_ok = (memcmp(vector, test, n * sizeof(int)) == 0);

  printf("sorted values are %s\ntime: %.3f seconds\n", awnser[is_ok], difftime(tend, tstart));
  
  free(vector);
  free(test);

  return 0;
}


