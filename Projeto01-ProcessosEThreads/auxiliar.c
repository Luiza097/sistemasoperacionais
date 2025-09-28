#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar uma matriz de n linhas por m colunas com valores aleatórios
// e salvá-la em um arquivo.
void gerar_e_salvar_matriz(int n, int m, const char *nome_arquivo) {
    // Aloca memória para a matriz (array de ponteiros para as linhas)
    int **matriz = (int **)malloc(n * sizeof(int *));
    if (matriz == NULL) {
        perror("Erro ao alocar memória para a matriz");
        exit(1);
    }
    
    // Aloca memória para cada linha da matriz
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(m * sizeof(int));
        if (matriz[i] == NULL) {
            perror("Erro ao alocar memória para a linha da matriz");
            exit(1);
        }
    }

    // Preenche a matriz com números aleatórios
    // Os valores serão entre 0 e 99
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matriz[i][j] = rand() % 100;
        }
    }

    // Salva a matriz em um arquivo
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    // Formato do arquivo: primeiro a dimensão, depois os valores
    fprintf(arquivo, "%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Matriz %d x %d gerada e salva em %s\n", n, m, nome_arquivo);

    // Libera a memória alocada
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]) {
    // Verifica se a quantidade de argumentos está correta
    if (argc != 5) {
        printf("Uso: %s n1 m1 n2 m2\n", argv[0]);
        return 1;
    }

    // Converte os argumentos da linha de comando para inteiros
    int n1 = atoi(argv[1]);
    int m1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    int m2 = atoi(argv[4]);

    // Verifica se as dimensões são válidas
    if (m1 != n2) {
        printf("Erro: O número de colunas da Matriz 1 deve ser igual ao número de linhas da Matriz 2 para a multiplicação.\n");
        return 1;
    }

    // Semeia o gerador de números aleatórios com a hora atual
    srand(time(NULL));

    // Gera e salva a primeira matriz no arquivo M1.txt
    gerar_e_salvar_matriz(n1, m1, "M1.txt");

    // Gera e salva a segunda matriz no arquivo M2.txt
    gerar_e_salvar_matriz(n2, m2, "M2.txt");

    return 0;
}