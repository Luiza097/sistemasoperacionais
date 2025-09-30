#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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
    int **dados;
} Matriz;

// Estrutura para passar dados para cada thread
typedef struct {
    int id;               
    int p_elements;       
    Matriz *m1;           
    Matriz *m2;           
    Matriz *resultado;    
    const char *output_dir; // Adicionado o campo para o diretório de saída
} DadosThread;

// Funções ler_matriz e liberar_matriz (invariáveis)
Matriz* ler_matriz(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo da matriz");
        return NULL;
    }

    Matriz *matriz = (Matriz *)malloc(sizeof(Matriz));
    if (matriz == NULL) {
        fclose(arquivo);
        perror("Erro ao alocar memoria para a matriz");
        return NULL;
    }

    if (fscanf(arquivo, "%d %d", &matriz->linhas, &matriz->colunas) != 2) {
        printf("Erro de formato no arquivo: %s\n", nome_arquivo);
        fclose(arquivo);
        free(matriz);
        return NULL;
    }

    matriz->dados = (int **)malloc(matriz->linhas * sizeof(int *));
    for (int i = 0; i < matriz->linhas; i++) {
        matriz->dados[i] = (int *)malloc(matriz->colunas * sizeof(int));
    }
    
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            if (fscanf(arquivo, "%d", &matriz->dados[i][j]) != 1) {
                 printf("Erro de leitura de dados no arquivo: %s\n", nome_arquivo);
                for (int k = 0; k < matriz->linhas; k++) {
                    free(matriz->dados[k]);
                }
                free(matriz->dados);
                free(matriz);
                fclose(arquivo);
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return matriz;
}

void liberar_matriz(Matriz *matriz) {
    if (matriz == NULL) return;
    for (int i = 0; i < matriz->linhas; i++) {
        free(matriz->dados[i]);
    }
    free(matriz->dados);
    free(matriz);
}

// Função executada por cada thread (modificada para salvar no diretório)
void *multiplicar_segmento(void *dados_thread) {
    DadosThread *dados = (DadosThread *)dados_thread;
    
    #ifdef _WIN32
    clock_t inicio_calc, fim_calc;
    inicio_calc = clock();
    #else
    struct timeval inicio_calc, fim_calc;
    gettimeofday(&inicio_calc, NULL);
    #endif

    int total_elementos = dados->resultado->linhas * dados->resultado->colunas;
    int inicio_segmento = dados->id * dados->p_elements;
    int fim_segmento = inicio_segmento + dados->p_elements;
    
    if (fim_segmento > total_elementos) {
        fim_segmento = total_elementos;
    }

    for (int k = inicio_segmento; k < fim_segmento; k++) {
        int i = k / dados->resultado->colunas;
        int j = k % dados->resultado->colunas;
        
        dados->resultado->dados[i][j] = 0;
        for (int l = 0; l < dados->m1->colunas; l++) {
            dados->resultado->dados[i][j] += dados->m1->dados[i][l] * dados->m2->dados[l][j];
        }
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
    if (dados->output_dir[strlen(dados->output_dir) - 1] == '/') {
        sprintf(caminho_completo_saida, "%sresultado_threads_%d.txt", dados->output_dir, dados->id);
    } else {
        sprintf(caminho_completo_saida, "%s/resultado_threads_%d.txt", dados->output_dir, dados->id);
    }
    
    FILE *arquivo = fopen(caminho_completo_saida, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo de resultado do segmento");
        pthread_exit(NULL);
    }

    fprintf(arquivo, "%d %d\n", dados->resultado->linhas, dados->resultado->colunas);
    fprintf(arquivo, "%f\n", tempo_ms);
    
    fclose(arquivo);
    
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    // A quantidade de argumentos esperada agora é 5
    if (argc != 5) {
        printf("Uso: %s arquivo_matriz1.txt arquivo_matriz2.txt P diretorio_saida\n", argv[0]);
        return 1;
    }

    Matriz *m1 = ler_matriz(argv[1]);
    Matriz *m2 = ler_matriz(argv[2]);
    int p = atoi(argv[3]);
    const char *output_dir = argv[4]; // Obtem o novo argumento

    if (m1 == NULL || m2 == NULL || m1->colunas != m2->linhas) {
        printf("Erro na leitura das matrizes ou incompatibilidade para a multiplicação.\n");
        if (m1 != NULL) liberar_matriz(m1);
        if (m2 != NULL) liberar_matriz(m2);
        return 1;
    }
    
    Matriz *resultado = (Matriz *)malloc(sizeof(Matriz));
    resultado->linhas = m1->linhas;
    resultado->colunas = m2->colunas;
    resultado->dados = (int **)malloc(resultado->linhas * sizeof(int *));
    for (int i = 0; i < resultado->linhas; i++) {
        resultado->dados[i] = (int *)malloc(resultado->colunas * sizeof(int));
    }

    int total_elementos = resultado->linhas * resultado->colunas;
    int num_threads = (int)ceil((double)total_elementos / p);
    
    pthread_t threads[num_threads];
    DadosThread dados_threads[num_threads];

    printf("Iniciando a criação de %d threads...\n", num_threads);

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].id = i;
        dados_threads[i].p_elements = p;
        dados_threads[i].m1 = m1;
        dados_threads[i].m2 = m2;
        dados_threads[i].resultado = resultado;
        dados_threads[i].output_dir = output_dir; // Passa o novo argumento
        
        if (pthread_create(&threads[i], NULL, multiplicar_segmento, (void *)&dados_threads[i])) {
            perror("Erro ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Todas as threads finalizaram o cálculo.\n");

    liberar_matriz(m1);
    liberar_matriz(m2);
    liberar_matriz(resultado);

    return 0;
}