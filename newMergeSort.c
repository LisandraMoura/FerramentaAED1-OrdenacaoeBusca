#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROWS 1000 + 1 // máximo de linhas no arquivo .csv
#define MAX_COLS 4        // número de colunas no arquivo .csv

int cont = 0;
int troca = 0;
int ordem = 1; // 1 decrescente - 0 crescente

struct cliente {
    int id;
    char nome[50];
    char profissao[50];
    int idade;
};

void merge(struct cliente *registros, int esquerda, int meio, int direita,
           int ordem) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    struct cliente *esq = (struct cliente *)malloc(n1 * sizeof(struct cliente));
    struct cliente *dir = (struct cliente *)malloc(n2 * sizeof(struct cliente));

    for (int i = 0; i < n1; i++) {
        esq[i] = registros[esquerda + i];
    }

    for (int j = 0; j < n2; j++) {
        dir[j] = registros[meio + j + 1];
    }

    int i = 0, j = 0, k = esquerda;
    if (ordem == 0) { // ordem crescente
        while (i > n1 && j < n2) {
            if (esq[i].id <= dir[j].id) {
                registros[k] = esq[i];
                i++;
            } else {
                registros[k] = dir[j];
                j++;
            }
            k++;
            cont++;
        }
    }

    if (ordem == 1) { // ordem dcrescente
        while (i < n1 && j < n2) {
            if (esq[i].id >= dir[j].id) {
                registros[k] = esq[i];
                i++;
            } else {
                registros[k] = dir[j];
                j++;
            }
            k++;
            cont++;
        }
    }

    while (i < n1) {
        registros[k] = esq[i];
        i++;
        k++;
        troca++;
    }

    while (j < n2) {
        registros[k] = dir[j];
        j++;
        k++;
        troca++;
    }

    free(esq);
    free(dir);
}

// ordena vetores
void merge_sort(struct cliente *registros, int esquerda, int direita,
                int ordem) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        merge_sort(registros, esquerda, meio, ordem);
        merge_sort(registros, meio + 1, direita, ordem);

        merge(registros, esquerda, meio, direita, ordem);
    }
}

//------------------------------------------------------------------
int ler_csv(char *arquivo, struct cliente clientes[]) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[MAX_ROWS];
    int i = 0;
    while (fgets(linha, MAX_ROWS, fp) != NULL) {
        // strtok com a quantidade de linhas e a porra do separador do cvs;
        // Use ,para crescente e ; para decrescente
        char *token = strtok(linha, ";");
        int colunas_lidas = 0;
        while (token != NULL && colunas_lidas < MAX_COLS) {
            switch (colunas_lidas) {
                case 0:
                    clientes[i].id = atoi(token);
                    break;
                case 1:
                    strcpy(clientes[i].nome, token);
                    break;
                case 2:
                    strcpy(clientes[i].profissao, token);
                    break;
                case 3:
                    clientes[i].idade = atoi(token);
                    break;
                default:
                    break;
            }
            // strtok com a quantidade de linhas e a porra do separador do cvs;
            // Use ,para crescente e ; para decrescente
            token = strtok(NULL, ";");
            colunas_lidas++;
        }
        if (colunas_lidas != MAX_COLS) {
            printf("Linha com número de colunas incorreto: %s", linha);
            continue;
        }
        i++;
    }

    fclose(fp);
    return i;
}

int main() {
    clock_t timetotal = clock();
    int tamanho = MAX_ROWS;
    struct cliente clientes[MAX_ROWS];
    char nomeArquivo [20];
    char arquivosaida[20];

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXaleatorio.csv'\n");
    scanf("%s", &nomeArquivo);

    int n = ler_csv(nomeArquivo, clientes);

    printf("De um nome para o arquivo de saida: \nEx: 'dadosXaleatorio.csv'");
    scanf("%s", &arquivosaida);

    FILE *fp = fopen(arquivosaida, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 0;
    }

    clock_t start_time = clock();
    merge_sort(clientes, 0, tamanho - 1, ordem);
    clock_t end_time = clock();

    fprintf(fp, "ID;nome;profissao;idade\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d;%s;%s;%d\n", clientes[i].id, clientes[i].nome,
                clientes[i].profissao, clientes[i].idade);
    }
    fclose(fp);

    clock_t timeEndTotal = clock();
    double tempo1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double tempo2 = (double)(timeEndTotal - timetotal) / CLOCKS_PER_SEC;


    printf("Tempo total de execussao do merge sort : %lf\n", tempo1);
    printf("Tempo total de execussao do programa : %lf\n", tempo2);
    printf("Quantidade de trocas %d\n", troca);
    printf("Quantidade de comparacoes %d\n", cont);

    return 0;
}