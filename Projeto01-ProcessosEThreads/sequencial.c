#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para medição de tempo com microsegundos

// Estrutura para representar uma matriz com suas dimensões
typedef struct {
    int linhas;
    int colunas;
    int **dados;
} Matriz;

// Função para ler uma matriz a partir de um arquivo
Matriz* ler_matriz(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo da matriz");
        return NULL;
    }

    Matriz *matriz = (Matriz *)malloc(sizeof(Matriz));
    if (matriz == NULL) {
        fclose(arquivo);
        perror("Erro ao alocar memória para a matriz");
        return NULL;
    }

    // Lê as dimensões da matriz do arquivo
    if (fscanf(arquivo, "%d %d", &matriz->linhas, &matriz->colunas) != 2) {
        printf("Erro de formato no arquivo: %s\n", nome_arquivo);
        fclose(arquivo);
        free(matriz);
        return NULL;
    }

    // Aloca memória para a matriz (array de ponteiros para linhas)
    matriz->dados = (int **)malloc(matriz->linhas * sizeof(int *));
    if (matriz->dados == NULL) {
        fclose(arquivo);
        free(matriz);
        perror("Erro ao alocar memória para as linhas da matriz");
        return NULL;
    }

    // Aloca memória para cada linha da matriz
    for (int i = 0; i < matriz->linhas; i++) {
        matriz->dados[i] = (int *)malloc(matriz->colunas * sizeof(int));
        if (matriz->dados[i] == NULL) {
            // Libera a memória já alocada em caso de erro
            for (int k = 0; k < i; k++) {
                free(matriz->dados[k]);
            }
            fclose(arquivo);
            free(matriz->dados);
            free(matriz);
            perror("Erro ao alocar memória para as colunas da matriz");
            return NULL;
        }
    }

    // Lê os valores da matriz do arquivo
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            if (fscanf(arquivo, "%d", &matriz->dados[i][j]) != 1) {
                printf("Erro de leitura de dados no arquivo: %s\n", nome_arquivo);
                fclose(arquivo);
                // Libera toda a memória antes de sair
                for (int k = 0; k < matriz->linhas; k++) {
                    free(matriz->dados[k]);
                }
                free(matriz->dados);
                free(matriz);
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return matriz;
}

// Função para multiplicar duas matrizes sequencialmente
Matriz* multiplicar_matrizes(Matriz *m1, Matriz *m2) {
    if (m1->colunas != m2->linhas) {
        printf("Erro: As matrizes não são compatíveis para a multiplicação.\n");
        return NULL;
    }

    Matriz *resultado = (Matriz *)malloc(sizeof(Matriz));
    if (resultado == NULL) {
        perror("Erro ao alocar memória para a matriz resultado");
        return NULL;
    }
    resultado->linhas = m1->linhas;
    resultado->colunas = m2->colunas;
    
    // Aloca memória para a matriz resultado
    resultado->dados = (int **)malloc(resultado->linhas * sizeof(int *));
    for (int i = 0; i < resultado->linhas; i++) {
        resultado->dados[i] = (int *)malloc(resultado->colunas * sizeof(int));
    }
    
    // Realiza a multiplicação de matrizes
    for (int i = 0; i < resultado->linhas; i++) {
        for (int j = 0; j < resultado->colunas; j++) {
            resultado->dados[i][j] = 0;
            for (int k = 0; k < m1->colunas; k++) {
                resultado->dados[i][j] += m1->dados[i][k] * m2->dados[k][j];
            }
        }
    }

    return resultado;
}

// Função para salvar a matriz resultado e o tempo em um arquivo
void salvar_resultado(Matriz *matriz, double tempo_ms, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo de resultado");
        return;
    }

    // Salva as dimensões e os elementos da matriz resultado
    fprintf(arquivo, "%d %d\n", matriz->linhas, matriz->colunas);
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            fprintf(arquivo, "%d ", matriz->dados[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    // Salva o tempo de cálculo no final
    fprintf(arquivo, "%f\n", tempo_ms);

    fclose(arquivo);
    printf("Resultado salvo em %s com tempo de %.4f ms\n", nome_arquivo, tempo_ms);
}

// Função para liberar a memória alocada para uma matriz
void liberar_matriz(Matriz *matriz) {
    if (matriz == NULL) return;
    for (int i = 0; i < matriz->linhas; i++) {
        free(matriz->dados[i]);
    }
    free(matriz->dados);
    free(matriz);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s arquivo_matriz1.txt arquivo_matriz2.txt\n", argv[0]);
        return 1;
    }

    Matriz *m1 = ler_matriz(argv[1]);
    Matriz *m2 = ler_matriz(argv[2]);

    if (m1 == NULL || m2 == NULL) {
        return 1;
    }

    // Mede o tempo de cálculo usando clock()
    clock_t inicio, fim;
    inicio = clock();

    // Multiplica as matrizes sequencialmente [cite: 36]
    Matriz *resultado = multiplicar_matrizes(m1, m2);
    if (resultado == NULL) {
        liberar_matriz(m1);
        liberar_matriz(m2);
        return 1;
    }

    fim = clock();

    // Calcula a diferença de tempo em milissegundos
    double tempo_ms = ((double)(fim - inicio) * 1000.0) / CLOCKS_PER_SEC;

    // Salva o resultado no arquivo com o tempo [cite: 37, 38]
    salvar_resultado(resultado, tempo_ms, "resultado_sequencial.txt");

    // Libera a memória alocada
    liberar_matriz(m1);
    liberar_matriz(m2);
    liberar_matriz(resultado);

    return 0;
}