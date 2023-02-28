#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cliente {

    int chave;
    char nome[20];
    char profissao[50];
    int idade;

} clientes;

int trocas = 0;
int comparacoes = 0;

void troca(struct cliente *a, struct cliente *b) {
    
    trocas++;
    struct cliente temp = *a;
    *a = *b;
    *b = temp;
}

int particiona(struct cliente *clientes, int low, int high) {
    
    int pivot = clientes[high].chave;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (clientes[j].chave < pivot) {
            i++;
            troca(&clientes[i], &clientes[j]);
            //comparacoes++;
        }
        comparacoes++;
    }
    troca(&clientes[i + 1], &clientes[high]);
    return (i + 1);
}

void quicksort(struct cliente *clientes, int low, int high) {
    
    if (low < high) {
        int pi = particiona(clientes, low, high);

        quicksort(clientes, low, pi - 1);
        quicksort(clientes, pi + 1, high);
    }
}

int main() {

    int num_linhas = 0;
    
    FILE *arquivoEntrada, *arquivoSaida;
    char nomearquivo [20];
    char arquivosaida[20];

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXaleatorio.csv'\n");
    scanf("%s", &nomearquivo);
    arquivoEntrada = fopen(nomearquivo, "r");

    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    printf("De um nome para o arquivo de saida: \nEx: 'dadosXaleatorio.csv'");
    scanf("%s", &arquivosaida);
    arquivoSaida = fopen(arquivosaida, "w");

    if (arquivoSaida == NULL) {
        printf("Não foi possível criar o arquivo de saída.\n");
        return 1;
    }

    // Conta o número de linhas no arquivo

    while (!feof(arquivoEntrada)) {
        
        if (fgetc(arquivoEntrada) == '\n') {
            num_linhas++;
        }
    }

    rewind(arquivoEntrada); // Volta para o início do arquivo
    
    clientes clientes[num_linhas];

    char *buffer = (char *) malloc(1024 * sizeof(char)); 
    
    if (buffer == NULL) {
        
        printf("Não foi possível alocar memória para o buffer.\n");
        return 1;
    }  
    
    int novo_num_linhas = 0;

    fgets(buffer, 1024, arquivoEntrada); // Descarta a primeira linha

    // Lê o arquivo CSV e armazena as informações na estrutura

    while(fgets(buffer, 1024, arquivoEntrada)) {
        
        sscanf(buffer, "%d;%[^;];%[^;];%d", &clientes[novo_num_linhas].chave, clientes[novo_num_linhas].nome, clientes[novo_num_linhas].profissao, &clientes[novo_num_linhas].idade);
        novo_num_linhas++;
    }
    
    fclose(arquivoEntrada);

    // Ordena a lista de clientes com o método QuickSort

    clock_t start = clock();
    quicksort(clientes, 0, novo_num_linhas - 1);
    clock_t end = clock();

    // Escreve a lista ordenada no arquivo de saída

    for (int i = 0; i < novo_num_linhas; i++) {
        
        fprintf(arquivoSaida, "%d,%s,%s,%d\n", clientes[i].chave, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
        
    }

    fclose(arquivoSaida);

    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execucao: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Comparacoes realizadas: %d\n", comparacoes);

    free(buffer);

    return 0;
}