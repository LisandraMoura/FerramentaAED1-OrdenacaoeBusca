#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam 501
typedef struct Cliente {
    int chave;
    char nome[20];
    char profissao[50];
    int idade;
} clientes; // struct dos clientes

void selectionSort(clientes meusClientes[], int n, int *passagens, int *compara) {
    int i, j, minIndex;
    clientes aux;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++){
            (*compara)++;
            if (meusClientes[j].chave < meusClientes[minIndex].chave) {
                minIndex = j;
                (*passagens)++;
            }}
        aux = meusClientes[minIndex];
        meusClientes[minIndex] = meusClientes[i];
        meusClientes[i] = aux;
    }

} //algoritmo em si do selectionSort

int main() {
    int tamanho = 0, i;
    clock_t inicio, fim;
    inicio = clock();
    int passagens  = 0;
    int compara = 0;
    FILE *arquivoSaida, *arquivoEntrada;
    char nomeArquivo [20];
    char arquivosaida[20];
    //encoding

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'dadosXaleatorio.csv'\n");
    scanf("%s", &nomeArquivo);
    arquivoEntrada = fopen(nomeArquivo, "r");
    if (arquivoEntrada == NULL) {
        printf("Nao foi possivel abrir o arquivo de entrada.\n");
        return 1;
    }

    printf("De um nome para o arquivo de saida: \nEx: 'dadosXaleatorio.csv'");
    scanf("%s", &arquivosaida);
    arquivoSaida = fopen(arquivosaida, "w");
    if (arquivoSaida == NULL) {
        printf("Nao foi possivel criar o arquivo de saida.\n");
        return 1;
    }

    // Descobrir o tamanho do arquivo
    while (!feof(arquivoEntrada)) {
        if (fgetc(arquivoEntrada) == '\n') {
            tamanho++;
        }
    }

    rewind(arquivoEntrada);
    clientes clientes[tamanho];
    // Lê o arquivo e armazena os dados na struct

    char buffer[tam];
    //buffer = (char *)malloc(sizeof(char) * 200);
    //pessoas = (clientes *)malloc(sizeof(Pessoa) * 5000); // aloca dinamicamente memória para o vetor de pessoas
    int n = 0;
    fgets(buffer, tam, arquivoEntrada); //descarta a primeira linha
    //lê o arquivo CSV e armazena as informações na estrutura
    while(fgets(buffer, tam, arquivoEntrada)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &clientes[n].chave, clientes[n].nome, clientes[n].profissao, &clientes[n].idade);
        n++;

    }

    fclose(arquivoEntrada);
    // Ordena a lista de clientes com o método insertion sort
    selectionSort(clientes, tamanho, &passagens, &compara);
    // Escreve a lista ordenada no arquivo de saída
    for (i = 0; i < tamanho; i++) {
        fprintf(arquivoSaida, "%d;%s;%s;%d\n", clientes[i].chave, clientes[i].nome, clientes[i].profissao, clientes[i].idade);

    }

    fclose(arquivoSaida);
    fim = clock();
    printf("Numero de passagens: %d\n", passagens);
    printf("Tempo de execucao: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Numero de comparacoes: %d\n", compara);

    return 0;
}