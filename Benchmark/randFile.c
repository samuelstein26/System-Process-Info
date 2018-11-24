/*
   SIS0563 - Fundamentos de Sistemas Operacionais 
   Prof. Vinicius Garcia Pinto 

   Instruções para compilacao:
                               gcc randFile.c -o randFile
   Instruções para execucao:
                               ./randFile <size>
   Exemplo para geracao e escrita de 100.000.000 de elementos
                               ./randFile 100000000

   Este codigo gera valores aleatórios e após escreve cada valor
   gerado em uma linha de um arquivo texto. Este codigo deve ser
   utilizado como aplicacao de teste para o Trabalho Pratico da
   Disciplina (Trabalho Prático - Monitoramento de Aplicação e
   Sistema).
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void rand_to_file(int *randvalues, int n){
  int i;
  char flname[] = "outfile.txt";
  FILE *flhandle = fopen(flname,"w");

  if(flhandle == NULL){
    printf("Error - cannot open file <%s>", flname);   
    exit(1);             
  }

  for(i = 0; i < n; i++)
    fprintf(flhandle, "%d\n",randvalues[i]);

  fclose(flhandle);
}

int main(int argc, char **argv){
  int *vector;
  int i, n;
  time_t tstart, tend;
  
  if(argc != 2){
    fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);

  printf("number of elements: %d\n", n);

  vector = (int *) malloc(n * sizeof(int));
  assert(vector != NULL);

  srand(time(NULL));

  for(i = 0; i < n; i++)
    vector[i] = rand();

  tstart = time(NULL);
  rand_to_file(vector, n);
  tend = time(NULL);

  printf("%d random values were written to a file in \ntime: %.3f seconds\n", n,  difftime(tend, tstart));
  
  free(vector);

  return 0;
}

