#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#include "funcoesAuxiliares.h"


void revelarZerosProximos(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2]){

    int sair=0;

    while(sair==0){

        sair=1;

        for (int i=0;i<numLinhas;i++){//direita
            for(int j=0;j<numColunas;j++){
                if(j!=numColunas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i][j+1].selecionado==0){
                        matrizGeral[i][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }
        for (int i=0;i<numLinhas;i++){//esquerda
            for(int j=numColunas-1;j>0;j--){
                if(j!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i][j-1].selecionado==0){
                        matrizGeral[i][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }

        for (int i=0;i<numLinhas;i++){//baixo
            for(int j=0;j<numColunas;j++){
                if(i!=numLinhas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j].selecionado==0){
                        matrizGeral[i+1][j].selecionado=1;
                        sair=0;
                    }
            }
        }
        for (int i=numLinhas-1;i>0;i--){//cima
            for(int j=0;j<numColunas;j++){
                if(i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j].selecionado==0){
                        matrizGeral[i-1][j].selecionado=1;
                        sair=0;
                    }

            }
        }


        for (int i=0;i<numLinhas;i++){//baixo-direita
            for(int j=0;j<numColunas;j++){
                if(j!=numColunas-1 && i!=numLinhas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j+1].selecionado==0){
                        matrizGeral[i+1][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }

        for (int i=0;i<numLinhas;i++){//baixo-esquerda
            for(int j=numColunas-1;j>0;j--){
                if(j!=0 && i!=numLinhas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j-1].selecionado==0){
                        matrizGeral[i+1][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }



        for (int i=0;i<numLinhas;i++){//cima-esquerda
            for(int j=numColunas-1;j>0;j--){
                if(j!=0 && i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j-1].selecionado==0){
                        matrizGeral[i-1][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }


        for (int i=0;i<numLinhas-1;i++){//cima-direita
            for(int j=0; j<numColunas-1;j++/*numColunas-1;j>0;j--*/){
                if(j!=numColunas-1 && i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j+1].selecionado==0){
                        matrizGeral[i-1][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }



    }//while


}

void selecionar(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2]){

    int a=posicaoAsterisco[0];
    int b=posicaoAsterisco[1];

   if(matrizGeral[a][b].selecionado==1){
    //None
   }
   else{
        matrizGeral[a][b].selecionado=1;
        if(matrizGeral[a][b].numBombasProximas==0){
            revelarZerosProximos(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
        }
   }


}

void acaoJogo(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, char acao, int posicaoAsterisco[2], int numBombas, int *bombasNaoMarcadas){

    int a=0,b=0;

    a=posicaoAsterisco[0];
    b=posicaoAsterisco[1];
    matrizGeral[a][b].asterisco = 0;



    switch(acao){

        case 'W':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;
        case 'S':
            if(posicaoAsterisco[0]!=numLinhas-1)
                posicaoAsterisco[0]++;
            break;
        case 'A':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'D':
            if(posicaoAsterisco[1]!=numColunas-1)
                posicaoAsterisco[1]++;
            break;
        case 'E':
            if(matrizGeral[a][b].bandeira==0)
                selecionar(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
            break;
        case 'Q':
            if(matrizGeral[posicaoAsterisco[0]][posicaoAsterisco[1]].selecionado==0){

                if(matrizGeral[a][b].bandeira==1){
                    if(*bombasNaoMarcadas==numBombas)
                        break;
                    matrizGeral[a][b].bandeira=0;
                    (*bombasNaoMarcadas)++;
                    break;
                }

                else if (matrizGeral[a][b].bandeira==0)
                    if(*bombasNaoMarcadas==0)
                        break;
                    matrizGeral[a][b].bandeira=1;
                    (*bombasNaoMarcadas)--;
            }
            break;
        case 'w':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;

        case 's':
            if(posicaoAsterisco[0]!=numLinhas-1)
                posicaoAsterisco[0]++;
            break;
        case 'a':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'd':
            if(posicaoAsterisco[1]!=numColunas-1)
                posicaoAsterisco[1]++;
            break;
        case 'e':
            if(matrizGeral[a][b].bandeira==0)
                selecionar(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
            break;
        case 'q':
            if(matrizGeral[posicaoAsterisco[0]][posicaoAsterisco[1]].selecionado==0){

                if(matrizGeral[a][b].bandeira==1){
                    if(*bombasNaoMarcadas==numBombas)
                        break;
                    matrizGeral[a][b].bandeira=0;
                    (*bombasNaoMarcadas)++;
                    break;
                }

                else if (matrizGeral[a][b].bandeira==0)
                    if(*bombasNaoMarcadas==0)
                        break;
                    matrizGeral[a][b].bandeira=1;
                    (*bombasNaoMarcadas)--;
            }
            break;
        default:
            printf("Digite uma opcao valida.");
            break;






    }

    a=posicaoAsterisco[0];
    b=posicaoAsterisco[1];
    matrizGeral[a][b].asterisco = 1;


}

void condicaoMatrizPossiveisJogadas(struct itensDaMatriz** matrizGeral,int numLinhas,int numColunas, int** matrizPossiveisJogadas, int i, int j, int i2, int j2){

    if(matrizGeral[i][j].selecionado==1 && matrizGeral[i][j].numBombasProximas!=0 && matrizGeral[i2][j2].selecionado==0)
                    matrizPossiveisJogadas[i2][j2]=1;


}

void analisarProbabilidades(struct itensDaMatriz** matrizGeral, int proximaJogadaBot[2], int numLinhas, int numColunas, int posicaoAsterisco[2], int *marcarBandeira, int **bombasCalculadasBot){

    //int **matrizPossiveisJogadas;
    int **blocosNaoSelecionadosAoRedor, **numBombasJaCalculadasAoRedor;


    int auxSaida=0;

    proximaJogadaBot[0]=-1;//Caso nao consiga calcular com certeza a proxima jogada terei o valor -1
    proximaJogadaBot[1]=-1;

    //matrizPossiveisJogadas = (int**)malloc(numLinhas * sizeof(int*));
    //for(int i = 0; i < numLinhas; i++)
    //    matrizPossiveisJogadas[i] = (int*)calloc(numColunas, sizeof(int));

    blocosNaoSelecionadosAoRedor = (int**)malloc(numLinhas * sizeof(int*));
    for(int i = 0; i < numLinhas; i++)
        blocosNaoSelecionadosAoRedor[i] = (int*)calloc(numColunas, sizeof(int));

    numBombasJaCalculadasAoRedor = (int**)malloc(numLinhas * sizeof(int*));
    for(int i = 0; i < numLinhas; i++)
        numBombasJaCalculadasAoRedor[i] = (int*)calloc(numColunas, sizeof(int));




    for(int i=0;i<numLinhas;i++) //inicializamatrizes
        for(int j=0;j<numColunas;j++){
            //matrizPossiveisJogadas[i][j]=0;
            blocosNaoSelecionadosAoRedor[i][j]=0;
            numBombasJaCalculadasAoRedor[i][j]=0;
        }

    /*for(int i=0;i<numLinhas;i++){
        for(int j=0;j<numColunas;j++){

            if(j!=numColunas-1)//Direita
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i,j+1);

            if(j!=0)//Esquerda
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i,j-1);

            if(i!=numLinhas-1)//Baixo
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i+1,j);

            if(i!=0)//Cima
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i-1,j);

            if(j!=numColunas-1 && i!=0)//Direita-Cima
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i-1,j+1);

            if(j!=0 && i!=0)//Esquerda-Cima
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i-1,j-1);

            if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i+1,j+1);

            if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                condicaoMatrizPossiveisJogadas(matrizGeral,numLinhas,numColunas,matrizPossiveisJogadas,i,j,i+1,j-1);
        }
    }*/

        //testeDesenhaMatriz(matrizGeral,numLinhas,numColunas,bombasCalculadasBot);

    for(int i=0;i<numLinhas;i++) //Conta os espaços nao selecionados ao redor
        for(int j=0;j<numColunas;j++){
            if(matrizGeral[i][j].selecionado!=0 && matrizGeral[i][j].numBombasProximas!=0){
                if(j!=numColunas-1)//Direita
                    if(matrizGeral[i][j+1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(j!=0)//Esquerda
                    if(matrizGeral[i][j-1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(i!=numLinhas-1)//Baixo
                    if(matrizGeral[i+1][j].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(i!=0)//Cima
                    if(matrizGeral[i-1][j].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(j!=numColunas-1 && i!=0)//Direita-Cima
                    if(matrizGeral[i-1][j+1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(j!=0 && i!=0)//Esquerda-Cima
                    if(matrizGeral[i-1][j-1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                    if(matrizGeral[i+1][j+1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

                if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                    if(matrizGeral[i+1][j-1].selecionado==0)
                        blocosNaoSelecionadosAoRedor[i][j]+=1;

            }

        }


    for(int i=0;i<numLinhas;i++) //Calcula lugares que certamente tem bomba
        for(int j=0;j<numColunas;j++)
            if(blocosNaoSelecionadosAoRedor[i][j]!=0 && blocosNaoSelecionadosAoRedor[i][j]==matrizGeral[i][j].numBombasProximas){
                if(j!=numColunas-1)//Direita
                    if(matrizGeral[i][j+1].selecionado==0){

                        if(bombasCalculadasBot[i][j+1]!=1){
                            proximaJogadaBot[0]=i;
                            proximaJogadaBot[1]=j+1;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i][j+1]=1;
                            return;
                        }
                        bombasCalculadasBot[i][j+1]=1;
                    }

                if(j!=0)//Esquerda
                    if(matrizGeral[i][j-1].selecionado==0){

                        if(bombasCalculadasBot[i][j-1]!=1){
                            proximaJogadaBot[0]=i;
                            proximaJogadaBot[1]=j-1;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i][j-1]=1;
                            return;
                        }
                        bombasCalculadasBot[i][j-1]=1;
                    }
                if(i!=numLinhas-1)//Baixo
                    if(matrizGeral[i+1][j].selecionado==0){

                        if(bombasCalculadasBot[i+1][j]!=1){
                            proximaJogadaBot[0]=i+1;
                            proximaJogadaBot[1]=j;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i+1][j]=1;
                            return;
                        }
                        bombasCalculadasBot[i+1][j]=1;
                    }
                if(i!=0)//Cima
                    if(matrizGeral[i-1][j].selecionado==0){

                        if(bombasCalculadasBot[i-1][j]!=1){
                            proximaJogadaBot[0]=i-1;
                            proximaJogadaBot[1]=j;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i-1][j]=1;
                            return;
                        }
                        bombasCalculadasBot[i-1][j]=1;
                    }
                if(j!=numColunas-1 && i!=0)//Direita-Cima
                    if(matrizGeral[i-1][j+1].selecionado==0){

                        if(bombasCalculadasBot[i-1][j+1]!=1){
                            proximaJogadaBot[0]=i-1;
                            proximaJogadaBot[1]=j+1;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i-1][j+1]=1;
                            return;
                        }
                        bombasCalculadasBot[i-1][j+1]=1;
                    }
                if(j!=0 && i!=0)//Esquerda-Cima
                    if(matrizGeral[i-1][j-1].selecionado==0){

                        if(bombasCalculadasBot[i-1][j-1]!=1){
                            proximaJogadaBot[0]=i-1;
                            proximaJogadaBot[1]=j-1;
                            bombasCalculadasBot[i-1][j-1]=1;
                            return;
                        }
                        bombasCalculadasBot[i-1][j-1]=1;
                    }
                if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                    if(matrizGeral[i+1][j+1].selecionado==0){

                        if(bombasCalculadasBot[i+1][j+1]!=1){
                            proximaJogadaBot[0]=i+1;
                            proximaJogadaBot[1]=j+1;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i+1][j+1]=1;
                            return;
                        }
                        bombasCalculadasBot[i+1][j+1]=1;
                    }
                if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                    if(matrizGeral[i+1][j-1].selecionado==0){

                        if(bombasCalculadasBot[i+1][j-1]!=1){
                            proximaJogadaBot[0]=i+1;
                            proximaJogadaBot[1]=j-1;
                            *marcarBandeira=1;
                            bombasCalculadasBot[i+1][j-1]=1;
                            return;
                    }
                    bombasCalculadasBot[i+1][j-1]=1;
                    }
                }



        //testeDesenhaMatriz(matrizGeral,numLinhas,numColunas,bombasCalculadasBot);


    for(int i=0;i<numLinhas;i++) //verifica a quantidade de bombas ja calculada ao redor
        for(int j=0;j<numColunas;j++){

            if(matrizGeral[i][j].selecionado==1 && matrizGeral[i][j].numBombasProximas!=0){
                if(j!=numColunas-1)//Direita
                    if(bombasCalculadasBot[i][j+1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(j!=0)//Esquerda
                    if(bombasCalculadasBot[i][j-1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(i!=numLinhas-1)//Baixo
                    if(bombasCalculadasBot[i+1][j]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(i!=0)//Cima
                    if(bombasCalculadasBot[i-1][j]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(j!=numColunas-1 && i!=0)//Direita-Cima
                    if(bombasCalculadasBot[i-1][j+1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(j!=0 && i!=0)//Esquerda-Cima
                    if(bombasCalculadasBot[i-1][j-1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                    if(bombasCalculadasBot[i+1][j+1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }
                if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                    if(bombasCalculadasBot[i+1][j-1]==1){
                        numBombasJaCalculadasAoRedor[i][j]+=1;
                    }



            }









        }

    for(int i=0;i<numLinhas;i++){ //define proximo alvo
        for(int j=0;j<numColunas;j++){
            auxSaida=0;
            if(matrizGeral[i][j].selecionado!=0 && matrizGeral[i][j].numBombasProximas!=0 && numBombasJaCalculadasAoRedor[i][j]==matrizGeral[i][j].numBombasProximas){
                if(j!=numColunas-1)//Direita
                    if(matrizGeral[i][j+1].selecionado!=1 && bombasCalculadasBot[i][j+1]!=1){
                        proximaJogadaBot[0]=i;
                        proximaJogadaBot[1]=j+1;
                        auxSaida=1;
                        break;
                    }

                if(j!=0)//Esquerda
                    if(matrizGeral[i][j-1].selecionado!=1 && bombasCalculadasBot[i][j-1]!=1){
                        proximaJogadaBot[0]=i;
                        proximaJogadaBot[1]=j-1;
                        auxSaida=1;
                        break;
                    }

                if(i!=numLinhas-1)//Baixo
                    if(matrizGeral[i+1][j].selecionado!=1 && bombasCalculadasBot[i+1][j]!=1){
                        proximaJogadaBot[0]=i+1;
                        proximaJogadaBot[1]=j;
                        auxSaida=1;
                        break;
                    }

                if(i!=0)//Cima
                    if(matrizGeral[i-1][j].selecionado!=1 && bombasCalculadasBot[i-1][j]!=1){
                        proximaJogadaBot[0]=i-1;
                        proximaJogadaBot[1]=j;
                        auxSaida=1;
                        break;
                    }

                if(j!=numColunas-1 && i!=0)//Direita-Cima
                    if(matrizGeral[i-1][j+1].selecionado!=1 && bombasCalculadasBot[i-1][j+1]!=1){
                        proximaJogadaBot[0]=i-1;
                        proximaJogadaBot[1]=j+1;
                        auxSaida=1;
                        break;
                    }

                if(j!=0 && i!=0)//Esquerda-Cima
                    if(matrizGeral[i-1][j-1].selecionado!=1 && bombasCalculadasBot[i-1][j-1]!=1){
                        proximaJogadaBot[0]=i-1;
                        proximaJogadaBot[1]=j-1;
                        auxSaida=1;
                        break;
                    }

                if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                    if(matrizGeral[i+1][j+1].selecionado!=1 && bombasCalculadasBot[i+1][j+1]!=1){
                        proximaJogadaBot[0]=i+1;
                        proximaJogadaBot[1]=j+1;
                        auxSaida=1;
                        break;
                    }

                if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                    if(matrizGeral[i+1][j-1].selecionado!=1 && bombasCalculadasBot[i+1][j-1]!=1){
                        proximaJogadaBot[0]=i+1;
                        proximaJogadaBot[1]=j-1;
                        auxSaida=1;
                        break;
                    }

            }

        }//for j

        if(auxSaida==1)
            break;
    }//for i


    if(proximaJogadaBot[0]==-1 && proximaJogadaBot[1]==-1){
        //srand(time(NULL));
        auxSaida=0;
        while(auxSaida==0){
            proximaJogadaBot[1]=rand()%(numColunas-1);
            proximaJogadaBot[0]=rand()%(numLinhas-1);
            //if(matrizPossiveisJogadas[proximaJogadaBot[0]][proximaJogadaBot[1]]==1)
            if(matrizGeral[proximaJogadaBot[0]][proximaJogadaBot[1]].selecionado==0 && proximaJogadaBot[0]!=-1 && proximaJogadaBot[1]!=-1){
                auxSaida=1;
            }



        }

    }



    //Crio a Matriz "BombasCalculadasBot"[][]                                                                                   OK
    //Olho o Numero de Bombas Prox já selecionado                                                                               OK
    //Quantos Blocos Não Selecionados tem ao redor? (Divido BlocosNaoSelecionados/NumBombas)                                    OK
    //Marco 1 em "BombasCalculadasBot[][]" se a divisao for == 1                                                                OK

    //Crio uma variavel auxiliar
    //Olhando o numero de bombas proximas, contar na auxiliar a quantidade de bombas ja calculadas ao redor da posição
    //Se a quantidade for igual ao numero de bombas e alguma das posições ao redor estiver nao selecionada e sem bombacalculada
    //Jogar essa posição no proximaJogadaBot[] e dar break para sair dos ciclos
    //se nao houver proxima jogada colocar valor aleatorio


    //liberaAlocacaoMatriz(matrizPossiveisJogadas,numLinhas);
    liberaAlocacaoMatriz(blocosNaoSelecionadosAoRedor,numLinhas);
    liberaAlocacaoMatriz(numBombasJaCalculadasAoRedor,numLinhas);



}


void atualizaBandeiras(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int *bombasNaoMarcadas, int numBombas){

    for(int i=0; i<numLinhas;i++){
        for(int j=0; j<numLinhas;j++){
            if(matrizGeral[i][j].bandeira==1 && matrizGeral[i][j].selecionado==1){
                (*bombasNaoMarcadas)++;
                matrizGeral[i][j].bandeira=0;
            }


        }
    }

}

char movimentoComputador(int proximoAlvoComputador[2], int posicaoAsterisco[2]){

    if(proximoAlvoComputador[1]!=posicaoAsterisco[1]){
        if(proximoAlvoComputador[1]<posicaoAsterisco[1])
            return 'a';
        else if(proximoAlvoComputador[1]>posicaoAsterisco[1])
            return 'd';
    }
    if(proximoAlvoComputador[0]!=posicaoAsterisco[0]){
        if(proximoAlvoComputador[0]<posicaoAsterisco[0])
            return 'w';
        else if(proximoAlvoComputador[0]>posicaoAsterisco[0])
            return 's';
    }

}


