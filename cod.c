#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

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
    printf("Informações do Sistema\n");
    printf("Número de processadores configurados: %d\n", get_nprocs_conf());
    printf("Número de processadores disponíveis: %d\n", get_nprocs());
    printf("Memória Total: %ld\n", getTotalMemory());
    printf("Memória Disponível: %ld\n", getFreeMemory());
    printf("Total de Páginas: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("Tamanho da Página: %ld\n", sysconf(_SC_PAGE_SIZE));
}

int main(int argc, char *argv[], char *const envp[ ]){
    //valida se há duas entradas no terminal   
    if(2 != argc)
    {
        printf("Entrada incorreta\n");
        return 0;
    }
    //resumo do sistema
    info_system();
    
    //aqui para baixo está incorreto ainda


    //cria novo processo com a segunda
    //printf("File: %s\n", argv[1]);    
    struct timeval start, end;
    pid_t child_pid = fork(); 
    char* argXv[] = { argv[1], NULL };
    //execve(argv[1], argXv, envp);
    execv(argv[1],argv);

    if (getppid()+1){
        printf("child PID =  %d, parent pid = %d\n", getpid(), getppid());
    }

    //tem que testar ainda
    struct rusage child;
    start = child.ru_stime;
    getrusage(RUSAGE_CHILDREN, &child);
    //depois que acaba o processo
    end = child.ru_stime;
    /***********
    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    *****/
    printf("Número de trocas de contexto voluntárias: %ld\n", child.ru_nvcsw);
    printf("Número de trocas de contexto involuntárias: %ld\n", child.ru_nivcsw);
    printf("Falta de páginas %ld\n", child.ru_majflt);
    printf("Páginas recuperadas: %ld\n", child.ru_minflt);
    //int pid = getpid();
    //printf("Chamadas de sistema", syscount -c  -p pid);
    //printf("Duração da execução: %ld", child.ru_stime);
    printf("Memória utilizada: %ld\n", child.ru_ixrss);

    return 0;
}
