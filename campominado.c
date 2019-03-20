#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//teste

struct itensDaMatriz{

    int temBomba;
    int foiSelecionado;
    int numBombasProximas; //Max 8 - Se for 0 deve liberar os espaços de 0 proximos
    int zeroBombasProximas;
    int marcadoBandeira;
    char status[1];
    int asterisco;

};

void limpaTela(){
    system("cls");

}

void tempoEspera(int tempo){
    //sleep(tempo);
}


void desenhaMatriz(struct itensDaMatriz **matrizGeral,int dimMatrizX, int dimMatrizY){

    for(int i=0;i<dimMatrizX;i++){
        for(int j=0;j<dimMatrizY;j++){
            if(j!=dimMatrizY-1)
                printf(" %d -",matrizGeral[i][j].numBombasProximas);
            else
                printf(" %d\n",matrizGeral[i][j].numBombasProximas);

        }
    }



}




void faltaDeMemoria(int *ponteiro){

    if(*ponteiro == NULL){
        printf("Falta de Memoria para Alocacao.");
        exit(1);
    }
}

void inicializaValoresMatriz(struct itensDaMatriz **matrizGeral, int dimMatrizX, int dimMatrizY){

        for(int i=0; i<dimMatrizX;i++){
            for(int j=0;j<dimMatrizY;j++){
                matrizGeral[i][j].temBomba=0;
                matrizGeral[i][j].foiSelecionado=0;
                matrizGeral[i][j].numBombasProximas=0;
                matrizGeral[i][j].zeroBombasProximas=0;
                matrizGeral[i][j].marcadoBandeira=0;
                matrizGeral[i][j].asterisco=0;
                //strcpy(matrizGeral[i][j].status,"O");

        }
    }

    matrizGeral[0][0].asterisco=1;
}


void inicio(int *numBombas, int *dimMatrizX, int *dimMatrizY){

    printf("Defina o numero de colunas da matriz: ");
    scanf("%d", dimMatrizY);
    printf("Defina o numero de linhas da matriz: ");
    scanf("%d", dimMatrizX);


    printf("Defina o numero de bombas do jogo: ");
    scanf("%d", numBombas);

}

void colocarBombas (struct itensDaMatriz **matrizGeral, int numBombas, int dimMatrizX, int dimMatrizY){

    int posicoesBombas[numBombas][2];
    int aux=0, aux2=0;

    srand(time(NULL));

    for(int i=0; i<numBombas;i++){
        aux=0;
        while(aux==0){

            posicoesBombas[i][0] = rand()%dimMatrizX;
            posicoesBombas[i][1] = rand()%dimMatrizY;
            aux=1;
            for (int j=0; j<i; j++){
                if(posicoesBombas[i][0] == posicoesBombas[j][0] && posicoesBombas[i][1] == posicoesBombas[j][1]){
                    aux=0;
                    break;
                }
            }
        }//while

        aux = posicoesBombas[i][0];
        aux2 = posicoesBombas[i][1];
        matrizGeral[aux][aux2].temBomba = 1;
        //matrizGeral[posicoesBombas[i][0]][posicoesBombas[i][1]].temBomba = 1;


    }//for

}


void colocarNumerosPosicoes(struct itensDaMatriz **matrizGeral, int c,int ce,int e,int be,int b,int bd,int d,int cd,int i,int j){
    if(c==1)
        if(matrizGeral[i][j-1].temBomba==1)//cima
            matrizGeral[i][j].numBombasProximas++;
    if(ce==1)
        if(matrizGeral[i-1][j-1].temBomba==1)//cima esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(e==1)
        if(matrizGeral[i-1][j].temBomba==1)//esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(be==1)
        if(matrizGeral[i-1][j+1].temBomba==1)//baixo esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(b==1)
        if(matrizGeral[i][j+1].temBomba==1)//baixo
            matrizGeral[i][j].numBombasProximas++;
    if(bd==1)
        if(matrizGeral[i+1][j+1].temBomba==1)//baixo direita
            matrizGeral[i][j].numBombasProximas++;
    if(d==1)
        if(matrizGeral[i+1][j].temBomba==1)//direita
            matrizGeral[i][j].numBombasProximas++;
    if(cd==1)
        if(matrizGeral[i+1][j-1].temBomba==1)//cima direita
            matrizGeral[i][j].numBombasProximas++;


}

void colocarNumeros (struct itensDaMatriz **matrizGeral, int dimMatrizX, int dimMatrizY){

    for (int i=0; i<dimMatrizX;i++){
        for(int j=0; j<dimMatrizY;j++){
            if(matrizGeral[i][j].temBomba==1)
                matrizGeral[i][j].numBombasProximas=-1;

            else{
                if(i!=0 && i!=(dimMatrizX-1) && j!=0 && j!=(dimMatrizY-1))  //fora de qualquer borda
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,1,1,1,i,j);

                else if(i==0 && j==0)                                       //posicao 0,0
                    colocarNumerosPosicoes(matrizGeral,0,0,0,0,1,1,1,0,i,j);
                else if(i==0 && j==(dimMatrizY-1))                          //posicao 0,final
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,0,0,1,1,i,j);
                else if(i==(dimMatrizX-1) && j==(dimMatrizY-1))             //posicao final,final
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,0,0,i,j);
                else if(i==(dimMatrizX-1) && j==0)                          //posicao final,0
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,0,0,0,i,j);

                else if(i==0 && j>0 && j<(dimMatrizY-1))                    //posicao borda da esquerda
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,1,1,1,1,i,j);
                else if(i>0 && i<(dimMatrizX-1) && j==(dimMatrizY-1))       //posicao borda de baixo
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,1,1,i,j);
                else if(i==(dimMatrizX-1) && j>0 && j<(dimMatrizY-1))       //posicao borda da direita
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,0,0,0,i,j);
                else if(i>0 && i<(dimMatrizX-1) && j==0)                    //posicao borda de cima
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,1,1,0,i,j);
            }


        }
    }






}


void perderJogo(int situacao){
// situacao
// 0 - Avisar a funcao que perdeu
// 1 - Mostrar que perdeu na tela (após atualizar a tela

    static int a=0;
    char jogarDeNovo;

    if(situacao==0){
        a=1;
    }
    if(situacao==1 && a==1){
        printf("Voce Perdeu... Deseja jogar novamente? (s/n)");
        fflush(stdin);
        scanf("%c",&jogarDeNovo);
    }




}



void revelarZerosProximos(struct itensDaMatriz** matrizGeral, int dimMatrizX, int dimMatrizY, int posicaoAsterisco[2]){

    int a = posicaoAsterisco[0];
    int b = posicaoAsterisco[1];
    int sair=0, aux=0;

while(sair==0){

    sair=1;

    for (int i=0;i<dimMatrizY;i++){//direita
        for(int j=0;j<dimMatrizX;j++){
            if(j!=dimMatrizX-1)
                if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].foiSelecionado==1 && matrizGeral[i][j+1].numBombasProximas!=0 && matrizGeral[i][j+1].foiSelecionado==0){
                    matrizGeral[i][j+1].foiSelecionado=1;
                    sair=0;
                }

                if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].foiSelecionado==1 && matrizGeral[i][j+1].numBombasProximas==0 && matrizGeral[i][j+1].foiSelecionado==0){
                    matrizGeral[i][j+1].foiSelecionado=1;
                    sair=0;
                }

        }
    }
    for (int i=0;i<dimMatrizY;i++){//esquerda
        for(int j=dimMatrizX-1;j>0;j--){
            if(j!=0)
                if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].foiSelecionado==1 && matrizGeral[i][j-1].numBombasProximas==0 && matrizGeral[i][j-1].foiSelecionado==0){
                    matrizGeral[i][j-1].foiSelecionado=1;
                    sair=0;
                }

        }
    }

    for (int i=0;i<dimMatrizY;i++){//baixo
        for(int j=0;j<dimMatrizX;j++){
            if(i!=dimMatrizY-1)
                if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].foiSelecionado==1 && matrizGeral[i+1][j].numBombasProximas==0 && matrizGeral[i+1][j].foiSelecionado==0){
                    matrizGeral[i+1][j].foiSelecionado=1;
                    sair=0;
                }
        }
    }
    for (int i=dimMatrizY-1;i>0;i--){//cima
        for(int j=0;j<dimMatrizX;j++){
            if(j!=0)
                if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].foiSelecionado==1 && matrizGeral[i-1][j].numBombasProximas==0 && matrizGeral[i-1][j].foiSelecionado==0){
                    matrizGeral[i-1][j].foiSelecionado=1;
                    sair=0;
                }

        }
    }

}


}

void selecionar(struct itensDaMatriz** matrizGeral, int dimMatrizX, int dimMatrizY, int posicaoAsterisco[2]){

    int a=posicaoAsterisco[0];
    int b=posicaoAsterisco[1];

   if(matrizGeral[a][b].foiSelecionado==1){
    //None
   }
   else{
        matrizGeral[a][b].foiSelecionado=1;

        if(matrizGeral[a][b].temBomba==1){
            //Perder o Jogo
        }
        if(matrizGeral[a][b].numBombasProximas==0){
            revelarZerosProximos(matrizGeral,dimMatrizX,dimMatrizY,posicaoAsterisco);
        }
   }










}




void acaoJogo(struct itensDaMatriz** matrizGeral, int dimMatrizX, int dimMatrizY, char acao, int posicaoAsterisco[2]){

    int a=0,b=0;

    a=posicaoAsterisco[0];
    b=posicaoAsterisco[1];
    matrizGeral[a][b].asterisco = 0;

    printf("\n\nPosicao Ast Ants: %d e %d\n", posicaoAsterisco[0],posicaoAsterisco[1]);

    switch(acao){

        case 'W':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;
printf("\n\n");
    desenhaMatriz(matrizGeral,dimMatrizX,dimMatrizY);
        case 'S':
            if(posicaoAsterisco[0]!=dimMatrizY-1)
                posicaoAsterisco[0]++;
            break;
        case 'A':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'D':
            if(posicaoAsterisco[1]!=dimMatrizX-1)
                posicaoAsterisco[1]++;
            break;
        case 'E':
            selecionar(matrizGeral,dimMatrizX,dimMatrizY,posicaoAsterisco);
            break;
        case 'w':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;

        case 's':
            if(posicaoAsterisco[0]!=dimMatrizX-1)
                posicaoAsterisco[0]++;
            break;
        case 'a':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'd':
            if(posicaoAsterisco[1]!=dimMatrizY-1)
                posicaoAsterisco[1]++;
            break;
        case 'e':
            selecionar(matrizGeral,dimMatrizX,dimMatrizY,posicaoAsterisco);
            break;
        default:
            printf("Digite uma opcao valida.");
            break;






    }

    //printf("Posicao Ast Dps: %d e %d", posicaoAsterisco[0],posicaoAsterisco[1]);
    a=posicaoAsterisco[0];
    b=posicaoAsterisco[1];
    matrizGeral[a][b].asterisco = 1;


}


void interface(struct itensDaMatriz** matrizGeral, int dimMatrizX, int dimMatrizY, int posicaoAsteristico[2]){

    char acao;

    limpaTela();

    printf("\n\tTeclas:\n");
    printf("\tW - Cima\n");
    printf("\tS - Baixo\n");
    printf("\tA - Esquerda\n");
    printf("\tD - Direita\n");
    printf("\tE - Seleciona\n\n");

    printf("\t\t\t ");
    for(int i=0;i<dimMatrizX;i++)
        printf("---");

    printf("\n");

    for(int i=0; i<dimMatrizX;i++){
        printf("\t\t\t|");
        for(int j=0;j<dimMatrizY;j++){

            if(matrizGeral[i][j].asterisco==0){
                if(matrizGeral[i][j].foiSelecionado == 0)
                    printf(" - ");
                else{
                    if(matrizGeral[i][j].numBombasProximas==0)
                        printf("   ");
                    else if(matrizGeral[i][j].temBomba==1)
                        printf(" B ");
                    else
                        printf(" %d ", matrizGeral[i][j].numBombasProximas);
                }
            }//asterisco==0


            if(matrizGeral[i][j].asterisco==1){
                if(matrizGeral[i][j].foiSelecionado == 0)
                    printf(" -*");
                else{
                    if(matrizGeral[i][j].numBombasProximas==0)
                        printf("  *");
                    else if(matrizGeral[i][j].temBomba==1)
                        printf(" B*");
                    else
                        printf(" %d*", matrizGeral[i][j].numBombasProximas);
                }
            }//asterisco==1



        }//for J
        printf("|\n");
    }//for i
    printf("\t\t\t ");
    for(int i=0;i<dimMatrizX;i++)
        printf("---");

printf("\n\n");
    desenhaMatriz(matrizGeral,dimMatrizX,dimMatrizY);
    fflush(stdin);

    printf("\n\n\tDigite sua acao: ");
    scanf("%c",&acao);

    acaoJogo(matrizGeral,dimMatrizX,dimMatrizY,acao,posicaoAsteristico);
    tempoEspera(3);
    //Verificar se ganhou o jogo



}


void main(){

    int numBombas, dimMatrizX, dimMatrizY;
    struct itensDaMatriz **matrizGeral;
    int posicaoAsteristico[2] = {0,0};


    inicio(&numBombas, &dimMatrizX, &dimMatrizY);


    matrizGeral = (struct itensDaMatriz**)malloc(dimMatrizX * sizeof(struct itensDaMatriz*));
    for(int i = 0; i < dimMatrizX; i++){
        matrizGeral[i] = (struct itensDaMatriz*)calloc(dimMatrizY, sizeof(struct itensDaMatriz));
    }

    inicializaValoresMatriz(matrizGeral,dimMatrizX,dimMatrizY);

    colocarBombas(matrizGeral,numBombas,dimMatrizX,dimMatrizY);
    colocarNumeros(matrizGeral,dimMatrizX,dimMatrizY);



    while (1)
        interface(matrizGeral,dimMatrizX,dimMatrizY,posicaoAsteristico);
    //desenhaMatriz(matrizGeral,dimMatrizX,dimMatrizY);


}
