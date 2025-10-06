#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "automato.h"


struct automatocelular{  //TAD RETICULADO
    int d;
    int **celula;
};   

AutomatoCelular *alocarreticulado (int d){ //ALOCAÇÃO DO RETICULADO

    AutomatoCelular *autcel = (AutomatoCelular *) malloc (sizeof(AutomatoCelular));
    if(autcel == NULL){//teste caso de erro na alocação
        return NULL;
    }
    autcel -> d = d; //alocando variavel tamanho matriz

    autcel -> celula = (int **) malloc (d * sizeof(int *));//alocando matriz linhas
    if(autcel -> celula == NULL){
        free(autcel);//free para caso aconteça um erro desaloque a memoria alocada em "d"
        return NULL;
        
    }

    for(int i=0;i<d;i++){//alocando matriz colunas
        autcel->celula[i] = (int*)malloc(sizeof(int)* d);
    }

    return autcel;
}


AutomatoCelular* desalocarreticulado(AutomatoCelular* autcel){//DESALOCA RETICULADO
    for(int i=0;i<autcel->d;i++){
        free(autcel->celula[i]);//liberando memoria coluna
    }
    free(autcel->celula);//liberando memoria linhas
    free(autcel);//liberando memoria geral
    return autcel;
}

void leiturareticulado (AutomatoCelular *autcel){ //LEITURA RETICULADO  
    for(int i = 0; i < autcel -> d; i++){
        for(int j = 0; j < autcel -> d; j++){
            scanf("%d ", &autcel->celula[i][j]);
        }
    }
}

void confereReticulado(AutomatoCelular *autcel, int **matrizaux) { 
    // Verificar
    for (int i = 0; i < autcel->d; i++) {//percorrendo toda matriz
        for (int j = 0; j < autcel->d; j++) {
            int vizinhos = 0; //valor das celulas ao redor (se elas estão mortas ou vivas )

            // Verificando ao redor
            for (int x = -1; x <= 1; x++) { //locomvendo da posição -1 ate a 1 em x e y para que possa conferir as celulas ao redor
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) {// pulando a celula principal 
                        continue;
                    }

                    int auxX = i + x;//obtendo as coordenadas das celulas vizinhas
                    int auxY = j + y;//obtendo as coordenadas das celulas vizinhas
                    if (auxX >= 0 && auxX < autcel->d && auxY >= 0 && auxY < autcel->d) {//verificação se a celula do vizinho esta dentro dos limites
                        vizinhos += autcel->celula[auxX][auxY];//contador que recebe o valor de vizinhos 0 ou 1 para a verificação das regras do jogo
                    }
                }
            }

            // Aplicar as regras do jogo da vida
            if (autcel->celula[i][j] == 1) {
                if (vizinhos < 2 || vizinhos > 3) {
                    matrizaux[i][j] = 0;
                } else {
                    matrizaux[i][j] = 1;
                }
            } else {
                if (vizinhos == 3) {
                    matrizaux[i][j] = 1;
                } else {
                    matrizaux[i][j] = 0;
                }
            }
        }
    }

    // Copiar da matriz auxiliar para a matriz principal
    for (int i = 0; i < autcel->d; i++) {
        for (int j = 0; j < autcel->d; j++) {
            autcel->celula[i][j] = matrizaux[i][j];
        }
    }
}

void imprimereticulado (AutomatoCelular *autcel){ //IMPRESSÃO MATRIZ    
    for(int i = 0; i < autcel -> d; i++){
        for(int j = 0; j < autcel -> d; j++){
            printf("%d ", autcel->celula[i][j]);
        }
        printf("\n");
    }
}

void evoluirreticulado(AutomatoCelular *autcel, int geracoes){ //FUNÇÃO EVOLUIR RETICULADO
    if(geracoes == 0){
        return;//se não há gerações apenas retornamos o valor da matriz
    }

    int **matrizaux = (int **)malloc(autcel->d * sizeof(int *));
    for (int i = 0; i < autcel->d; i++) {
        matrizaux[i] = (int *)malloc(autcel->d * sizeof(int));
    } //alocando matriz aux

    confereReticulado(autcel, matrizaux);//chama função confere que vai substituir a matriz principal com os valores da auxiliar com a geração seguinte

    for(int i = 0; i < autcel -> d; i++){
        for(int j = 0; j < autcel -> d; j++){
            autcel -> celula[i][j] = matrizaux[i][j];
        }
    }
    // Liberar a matriz auxiliar
    for (int i = 0; i < autcel->d; i++) {
        free(matrizaux[i]);
    }
    free(matrizaux);

    evoluirreticulado(autcel, geracoes - 1);//chamada recursiva
}

