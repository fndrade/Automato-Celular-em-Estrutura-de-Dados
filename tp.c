#include <stdio.h>
#include <stdlib.h>
#include "automato.h"


int main() {
    int dimensao;
    int geracoes;

    // Solicitar a dimensão do autômato celular
    scanf("%d", &dimensao);
    scanf("%d", &geracoes);

    
    // Alocar espaço para o autômato celular
    AutomatoCelular *autcel = alocarreticulado(dimensao);

    // Verificar se a alocação foi bem sucedida
    if (autcel == NULL) {
        printf("Erro ao alocar memoria para o automato celular.\n");
        return 1; // Encerrar o programa com código de erro
    }

    // // Ler os valores para as células do autômato celular
    leiturareticulado(autcel);

    evoluirreticulado(autcel, geracoes);

    // Imprimir o autômato celular
    printf("\n");
    imprimereticulado(autcel);

    desalocarreticulado(autcel);

    return 0;
}
