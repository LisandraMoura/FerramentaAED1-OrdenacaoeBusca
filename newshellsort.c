#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROWS 5000 // máximo de linhas no arquivo .csv
#define MAX_COLS 4 // número de colunas no arquivo .csv

struct cliente {
    int id;
    char nome[50];
    char profissao[50];
    int idade;
};

int ler_csv(char* arquivo, struct cliente clientes[]) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[1024];
    int i = 0;
    while (fgets(linha, 1024, fp) != NULL) {
        char* token = strtok(linha, ";");
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

void shell_sort(struct cliente clientes[], int n, int *passagens, int *comparacoes) {
    int gap = 1;
    while (gap < n) {
        gap = 3 * gap + 1;
    }
    while (gap > 1) {
        gap /= 3;
        for (int i = gap; i < n; i++) {
            struct cliente temp = clientes[i];
            int j = i - gap;
            while (j >= 0 && clientes[j].id > temp.id) {
                (*passagens)++;
                clientes[j + gap] = clientes[j];
                (*comparacoes)++;
                j -= gap;

            }
            clientes[j + gap] = temp;
            (*comparacoes)++;
        }
    }
}

int main() {
    struct cliente clientes[MAX_ROWS];
    char nomeArquivo [20];
    char arquivosaida[20];
    int passagens = 0;
    int comparacoes = 0;

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXaleatorio.csv'\n");
    scanf("%s", &nomeArquivo);

    int n = ler_csv(nomeArquivo, clientes);

    clock_t start_time = clock();
    shell_sort(clientes, n, &passagens, &comparacoes);
    clock_t end_time = clock();

    double tempo = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("De um nome para o arquivo de saida: \nEx: 'dadosXaleatorio.csv'");
    scanf("%s", &arquivosaida);

    FILE* fp = fopen(arquivosaida, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 0;
    }

    fprintf(fp, "ID;nome;profissao;idade\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d;%s;%s;%d\n", clientes[i].id, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
    }

    fclose(fp);

    printf("\n************\n");
    printf("Tempo de execucao: %f segundos\n", tempo);
    printf("Numero de passagens: %d\n", passagens);
    printf("Numero de comparacoes : %d\n", comparacoes);
    printf("\n-----------------------------------\n");

    return 0;
}
