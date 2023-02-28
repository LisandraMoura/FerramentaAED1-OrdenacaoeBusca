#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 6000 // máximo de linhas no arquivo .csv
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

int buscar_cliente(int id, struct cliente clientes[], int n, int *contador, int *contador2) {
    for (int i = 0; i < n; i++) {
        if (clientes[i].id == id) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", clientes[i].id);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Profissao: %s\n", clientes[i].profissao);
            printf("Idade: %d\n", clientes[i].idade);
            return i;
        }
        (*contador)++;
    }
    (*contador2)++;
    printf("Cliente não encontrado.\n");
    return -1;
}

int main() {
    char nomeArquivo [20];
    int id_busca = 0;
    int contador =0;
    int contador2 =0;
    struct cliente clientes[MAX_ROWS];

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXcrescente.csv'\n");
    scanf("%s", &nomeArquivo);
    int n = ler_csv(nomeArquivo, clientes);

    printf("Digite o numero que deseja buscar: \n");
    scanf("%d", &id_busca);

    buscar_cliente(id_busca, clientes, n, &contador, &contador2);
    printf("%d\n", contador);
    printf("%d", contador);
    return 0;
}
