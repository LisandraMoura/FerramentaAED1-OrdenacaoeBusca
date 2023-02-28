#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            printf("Linha com numero de colunas incorreto: %s", linha);
            continue;
        }
        i++;
    }

    fclose(fp);
    return i;
}

int busca_binaria(struct cliente clientes[], int n, int id, int *contador, int *contador2, int *contadorteste) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (clientes[meio].id == id) {
            return meio;

        } else if (clientes[meio].id < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
        (*contador)++;
    }
    (*contador2)++;
    return -1; // não encontrou
}

int main() {
    int contador = 0;
     int contador2 = 0;
     int contadorteste = 0;
    struct cliente clientes[MAX_ROWS];
    char nomeArquivo [20];
    int id_busca = 0;

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXcrescente.csv'\n");
    scanf("%s", &nomeArquivo);
    int n = ler_csv(nomeArquivo, clientes);

    printf("Digite o numero que deseja buscar: \n");
    scanf("%d", &id_busca);

    int posicao_encontrada = busca_binaria(clientes, n, id_busca, &contador, &contador2, &contadorteste);
    if (posicao_encontrada == -1) {
        printf("Nao encontrado.\n");
    } else {
        printf("Encontrado: %d %s %s %d\n", clientes[posicao_encontrada].id, clientes[posicao_encontrada].nome, clientes[posicao_encontrada].profissao, clientes[posicao_encontrada].idade);
    }
    printf("Numero de comparacoes: %d\n", contador);
    //printf("Teste: %d\n", contador2);
    //printf("Teste 2: %d\n", contadorteste);


    return 0;
}
