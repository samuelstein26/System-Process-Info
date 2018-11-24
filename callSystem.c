/*
   SIS0563 - Fundamentos de Sistemas Operacionais 
   Samuel Stein 

   Instruções para compilacao:
                               gcc callSystem.c -o callSystem
   Instruções para execucao:
                               ./callSystem <./binary> <tamanho>
   Exemplo:
                               ./callSystem ./randFile 10000                             

   Este codigo monitora a execução de outro programa e retorna informações do sistema e processo.
    
*/

#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

long getTotalMemory(){
    long res = (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE)) / 1024;
    return res;
}

long getFreeMemory(){
    struct sysinfo info;
    sysinfo(&info);
    long res = info.freeram*=(info.mem_unit);
    return res / 1024;
}

void info_system(){
    printf("\nInformações do Sistema\n");
    printf("Número de processadores configurados: %d\n", get_nprocs_conf());
    printf("Número de processadores disponíveis: %d\n", get_nprocs());
    printf("Memória Total: %ld\n", getTotalMemory());
    printf("Memória Disponível: %ld\n", getFreeMemory());
    printf("Total de Páginas: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("Tamanho da Página: %ld\n\n", sysconf(_SC_PAGE_SIZE));
}

int main(int argc, char *argv[], char *const envp[ ]){

    //Ajuda
    if (strcmp(argv[1],"-help") == 0){
        printf("Usage:\n");
        printf("./callSystem ./binary1 argument\n");
        printf("Example:\n");
        printf("./callSystem ./randFile 50\n");
        return 0;
    }

    //Verificar entrada
    if (argc != 3){
        printf("Error: Parametro de entrada incorreto.\n");
        return 0;
    }

    short num;
    char line[1024];
    strcpy(line, argv[1]);
    line[strlen(line)]= '\0';
    char *args[] = {"ignore",argv[2],NULL};

    //Abaixo cria e executa novo processo
    pid_t childPid;
    struct rusage ru;

    switch (childPid = fork()) {
    case -1:{
        printf("Error: Ao executar o comando fork.\n");
        exit(1);
    }

    case 0:
        execvp(line, args);

    default:
        if (wait(NULL) == -1){
            printf("Error: Ao executar o comando wait.\n");
            exit(1);
        }
        if (getrusage(RUSAGE_CHILDREN, &ru) == -1){
            printf("Error: Ao executar o comando getrusage.\n");
            exit(1);
        }
    }

    //Informações do sistema.
    info_system();

    //Informações do processo
    printf("Processo: %s\n", line);
    printf("PID: %ld\n", (long) childPid);
    printf("Número de trocas de contexto voluntárias: %ld\n", ru.ru_nvcsw);
    printf("Número de trocas de contexto involuntárias: %ld\n", ru.ru_nivcsw);
    printf("Falta de páginas: %ld\n", ru.ru_majflt);
    printf("Páginas recuperadas: %ld\n", ru.ru_minflt);
    printf("Memória utilizada: %ld kB\n", ru.ru_maxrss);
    printf("Duração execução (usuário): %ld.%ld segundos\n", ru.ru_utime.tv_sec, ru.ru_utime.tv_usec); 
    printf("Duração execução (CPU): %lf segundos\n", ru.ru_stime.tv_sec + ru.ru_stime.tv_usec / 1000000.0); 

    printf("\nOBS.: Caso o processo utilize threads, a duração de execução \ndo usuário será multiplicada pelos processadores.\n\n");

    return 0;
}