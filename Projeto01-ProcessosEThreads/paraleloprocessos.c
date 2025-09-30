#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

// Estrutura para representar uma matriz
typedef struct {
    int linhas;
    int colunas;
    int dados[];
} Matriz;

// Função para ler uma matriz a partir de um arquivo (mesma do sequencial/threads)
Matriz* ler_matriz_local(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo da matriz");
        return NULL;
    }

    int linhas, colunas;
    if (fscanf(arquivo, "%d %d", &linhas, &colunas) != 2) {
        printf("Erro de formato no arquivo: %s\n", nome_arquivo);
        fclose(arquivo);
        return NULL;
    }

    Matriz *matriz = (Matriz*)malloc(sizeof(Matriz) + (linhas * colunas * sizeof(int)));
    if (matriz == NULL) {
        fclose(arquivo);
        perror("Erro ao alocar memoria para a matriz");
        return NULL;
    }
    matriz->linhas = linhas;
    matriz->colunas = colunas;

    for (int i = 0; i < linhas * colunas; i++) {
        if (fscanf(arquivo, "%d", &matriz->dados[i]) != 1) {
            printf("Erro de leitura de dados no arquivo: %s\n", nome_arquivo);
            fclose(arquivo);
            free(matriz);
            return NULL;
        }
    }

    fclose(arquivo);
    return matriz;
}

// Funcao para multiplicar um segmento da matriz resultado
void multiplicar_segmento(int id, int p_elements, Matriz *m1, Matriz *m2, Matriz *resultado, const char *output_dir) {
    
    #ifdef _WIN32
    clock_t inicio_calc, fim_calc;
    inicio_calc = clock();
    #else
    struct timeval inicio_calc, fim_calc;
    gettimeofday(&inicio_calc, NULL);
    #endif

    int total_elementos = resultado->linhas * resultado->colunas;
    int inicio_segmento = id * p_elements;
    int fim_segmento = inicio_segmento + p_elements;

    if (fim_segmento > total_elementos) {
        fim_segmento = total_elementos;
    }

    for (int k = inicio_segmento; k < fim_segmento; k++) {
        int i = k / resultado->colunas;
        int j = k % resultado->colunas;

        int soma = 0;
        for (int l = 0; l < m1->colunas; l++) {
            soma += m1->dados[i * m1->colunas + l] * m2->dados[l * m2->colunas + j];
        }
        resultado->dados[i * resultado->colunas + j] = soma;
    }

    #ifdef _WIN32
    fim_calc = clock();
    double tempo_ms = ((double)(fim_calc - inicio_calc) * 1000.0) / CLOCKS_PER_SEC;
    #else
    gettimeofday(&fim_calc, NULL);
    double tempo_ms = (fim_calc.tv_sec - inicio_calc.tv_sec) * 1000.0;
    tempo_ms += (fim_calc.tv_usec - inicio_calc.tv_usec) / 1000.0;
    #endif

    // Buffer para construir o caminho completo do arquivo
    char caminho_completo_saida[256];
    
    // Constrói o caminho completo: "diretorio/nome_arquivo"
    // Verifica se o caminho do diretório termina com uma barra
    if (output_dir[strlen(output_dir) - 1] == '/') {
        sprintf(caminho_completo_saida, "%sresultado_processos_%d.txt", output_dir, id);
    } else {
        sprintf(caminho_completo_saida, "%s/resultado_processos_%d.txt", output_dir, id);
    }
    
    FILE *arquivo = fopen(caminho_completo_saida, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo de resultado do segmento");
        exit(1);
    }

    fprintf(arquivo, "%d %d\n", resultado->linhas, resultado->colunas);
    fprintf(arquivo, "%f\n", tempo_ms);
    
    fclose(arquivo);
}

// Funcao para liberar a memoria compartilhada
void liberar_shm(int shmid) {
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Erro ao remover segmento de memoria compartilhada");
    }
}

int main(int argc, char *argv[]) {
    // A quantidade de argumentos esperada agora é 5
    if (argc != 5) {
        printf("Uso: %s arquivo_matriz1.txt arquivo_matriz2.txt P diretorio_saida\n", argv[0]);
        return 1;
    }

    Matriz *m1_local = ler_matriz_local(argv[1]);
    Matriz *m2_local = ler_matriz_local(argv[2]);
    int p = atoi(argv[3]);
    const char *output_dir = argv[4]; // Obtem o novo argumento

    if (m1_local == NULL || m2_local == NULL || m1_local->colunas != m2_local->linhas) {
        printf("Erro na leitura das matrizes ou incompatibilidade para a multiplicacao.\n");
        if (m1_local != NULL) free(m1_local);
        if (m2_local != NULL) free(m2_local);
        return 1;
    }
    
    int shmid_m1, shmid_m2, shmid_resultado;
    Matriz *shm_m1, *shm_m2, *shm_resultado;

    int size_m1 = sizeof(Matriz) + (m1_local->linhas * m1_local->colunas * sizeof(int));
    int size_m2 = sizeof(Matriz) + (m2_local->linhas * m2_local->colunas * sizeof(int));
    int size_resultado = sizeof(Matriz) + (m1_local->linhas * m2_local->colunas * sizeof(int));

    key_t key_m1 = ftok("paralelo_proc_m1", 65);
    key_t key_m2 = ftok("paralelo_proc_m2", 66);
    key_t key_resultado = ftok("paralelo_proc_res", 67);

    shmid_m1 = shmget(key_m1, size_m1, IPC_CREAT | 0666);
    shmid_m2 = shmget(key_m2, size_m2, IPC_CREAT | 0666);
    shmid_resultado = shmget(key_resultado, size_resultado, IPC_CREAT | 0666);
    if (shmid_m1 < 0 || shmid_m2 < 0 || shmid_resultado < 0) {
        perror("Erro ao criar segmentos de memoria compartilhada");
        exit(1);
    }

    shm_m1 = (Matriz *)shmat(shmid_m1, NULL, 0);
    shm_m2 = (Matriz *)shmat(shmid_m2, NULL, 0);
    shm_resultado = (Matriz *)shmat(shmid_resultado, NULL, 0);
    if (shm_m1 == (Matriz *)-1 || shm_m2 == (Matriz *)-1 || shm_resultado == (Matriz *)-1) {
        perror("Erro ao anexar segmentos de memoria compartilhada");
        exit(1);
    }
    
    memcpy(shm_m1, m1_local, size_m1);
    memcpy(shm_m2, m2_local, size_m2);
    shm_resultado->linhas = m1_local->linhas;
    shm_resultado->colunas = m2_local->colunas;

    free(m1_local);
    free(m2_local);

    int total_elementos = shm_resultado->linhas * shm_resultado->colunas;
    int num_processos = (int)ceil((double)total_elementos / p);
    
    printf("Iniciando a criacao de %d processos...\n", num_processos);

    for (int i = 0; i < num_processos; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro ao criar processo filho");
            exit(1);
        } else if (pid == 0) { // Processo filho
            // Passa o diretorio de saida para a funcao
            multiplicar_segmento(i, p, shm_m1, shm_m2, shm_resultado, output_dir);
            exit(0);
        }
    }

    int status;
    for (int i = 0; i < num_processos; i++) {
        wait(&status);
    }

    if (shmdt(shm_m1) == -1 || shmdt(shm_m2) == -1 || shmdt(shm_resultado) == -1) {
        perror("Erro ao desanexar memoria compartilhada");
    }
    
    liberar_shm(shmid_m1);
    liberar_shm(shmid_m2);
    liberar_shm(shmid_resultado);

    printf("Todos os processos finalizaram e a memoria compartilhada foi limpa.\n");

    return 0;
}
