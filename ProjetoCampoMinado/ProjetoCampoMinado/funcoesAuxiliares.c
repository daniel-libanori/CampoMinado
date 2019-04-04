#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//#include <conio.h>


struct itensDaMatriz{

    int bomba;
    int selecionado;
    int numBombasProximas;
    int marcadoBandeira;
    int bandeira;
    int asterisco;

};


void limpaTela(){
    //system("cls");
    system("clear");

}

void lerChar(char *caracter){
    scanf("%c",caracter);
    //*caracter=getchar();
    //*caracter=getch();

}





void tempoEspera(int tempo){
    sleep(tempo);

}

void testeDesenhaMatriz(struct itensDaMatriz **matrizGeral,int numLinhas, int numColunas){

    for(int i=0;i<numLinhas;i++){
        for(int j=0;j<numColunas;j++){
            if(j!=numColunas-1)
                printf(" %d -",matrizGeral[i][j].bandeira);
            else
                printf(" %d\n",matrizGeral[i][j].bandeira);

        }
    }



}

void liberaAlocacaoMatriz(int **ponteiro, int tam){

    for (int i=0;i<tam;i++)
        free(ponteiro[i]);

    free (ponteiro);


}

void liberaAlocacaoMatrizStruct(struct itensDaMatriz **ponteiro, int tam){

    for (int i=0;i<tam;i++)
        free(ponteiro[i]);

    free (ponteiro);


}

