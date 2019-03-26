#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>


struct itensDaMatriz{

    int bomba;
    int selecionado;
    int numBombasProximas;
    int zeroBombasProximas;
    int marcadoBandeira;
    int bandeira;
    int asterisco;

};

void limpaTela(){
    system("cls");
    //system("clear");

}

void lerChar(char *caracter){
    //scanf("%c",caracter);
    //*caracter=getchar();
    *caracter=getch();

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




void faltaDeMemoria(int *ponteiro){

    if(*ponteiro == NULL){
        printf("Falta de Memoria para Alocacao.");
        exit(1);
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




void inicializaValoresMatriz(struct itensDaMatriz **matrizGeral, int numLinhas, int numColunas){

        for(int i=0; i<numLinhas;i++){
            for(int j=0;j<numColunas;j++){
                matrizGeral[i][j].bomba=0;
                matrizGeral[i][j].selecionado=0;
                matrizGeral[i][j].numBombasProximas=0;
                matrizGeral[i][j].zeroBombasProximas=0;
                matrizGeral[i][j].marcadoBandeira=0;
                matrizGeral[i][j].asterisco=0;
                matrizGeral[i][j].bandeira=0;


        }
    }

    matrizGeral[0][0].asterisco=1;
}


void inicio(int *numBombas, int *numLinhas, int *numColunas, int *jogadorOuBot){

    int ok=0;
    int aux1,aux2;


    while(ok==0){
        printf("Defina o jogador (1 - Voce    2- Computador): ");
        scanf("%d", jogadorOuBot);
        ok=1;
        if(*jogadorOuBot != 1 && *jogadorOuBot != 2){
            printf("\nDigite um valor valido.\n");
            ok=0;
        }
    }
    ok=0;
    while(ok==0){
        printf("Defina o numero de colunas da matriz: ");
        scanf("%d", numColunas);
        ok=1;
        if(*numColunas<0){
            printf("\nDigite um valor valido.\n");
            ok=0;
        }
    }

    ok=0;
    while(ok==0){
        printf("Defina o numero de linhas da matriz: ");
        scanf("%d", numLinhas);
        ok=1;
        if(*numLinhas<0){
            printf("\nDigite um valor valido.\n");
            ok=0;
        }
    }
    aux1=*numLinhas;
    aux2=*numColunas;

    ok=0;
    while(ok==0){
        printf("Defina o numero de bombas do jogo: ");
        scanf("%d", numBombas);
        ok=1;
        if(*numBombas<0){
            printf("\nDigite um valor valido.\n");
            ok=0;
        }
        else if(*numBombas>(*numLinhas)*(*numColunas)){
            printf("\nValor digitado ultrapassa o total de espaços da matriz. Digite outro.\n");
            ok=0;
        }
    }

}

void colocarBombas (struct itensDaMatriz **matrizGeral, int numBombas, int numLinhas, int numColunas){

    int posicoesBombas[numBombas][2];
    int aux=0, aux2=0;

    srand(time(NULL));

    for(int i=0; i<numBombas;i++){
        aux=0;
        while(aux==0){

            posicoesBombas[i][0] = rand()%numLinhas;
            posicoesBombas[i][1] = rand()%numColunas;
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
        matrizGeral[aux][aux2].bomba = 1;
        //matrizGeral[posicoesBombas[i][0]][posicoesBombas[i][1]].bomba = 1;


    }//for

}


void colocarNumerosPosicoes(struct itensDaMatriz **matrizGeral, int c,int ce,int e,int be,int b,int bd,int d,int cd,int i,int j){
    if(c==1)
        if(matrizGeral[i][j-1].bomba==1)//cima
            matrizGeral[i][j].numBombasProximas++;
    if(ce==1)
        if(matrizGeral[i-1][j-1].bomba==1)//cima esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(e==1)
        if(matrizGeral[i-1][j].bomba==1)//esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(be==1)
        if(matrizGeral[i-1][j+1].bomba==1)//baixo esquerda
            matrizGeral[i][j].numBombasProximas++;
    if(b==1)
        if(matrizGeral[i][j+1].bomba==1)//baixo
            matrizGeral[i][j].numBombasProximas++;
    if(bd==1)
        if(matrizGeral[i+1][j+1].bomba==1)//baixo direita
            matrizGeral[i][j].numBombasProximas++;
    if(d==1)
        if(matrizGeral[i+1][j].bomba==1)//direita
            matrizGeral[i][j].numBombasProximas++;
    if(cd==1)
        if(matrizGeral[i+1][j-1].bomba==1)//cima direita
            matrizGeral[i][j].numBombasProximas++;


}

void colocarNumeros (struct itensDaMatriz **matrizGeral, int numLinhas, int numColunas){

    for (int i=0; i<numLinhas;i++){
        for(int j=0; j<numColunas;j++){
            if(matrizGeral[i][j].bomba==1)
                matrizGeral[i][j].numBombasProximas=-1;

            else{
                if(i!=0 && i!=(numLinhas-1) && j!=0 && j!=(numColunas-1))  //fora de qualquer borda
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,1,1,1,i,j);

                else if(i==0 && j==0)                                       //posicao 0,0
                    colocarNumerosPosicoes(matrizGeral,0,0,0,0,1,1,1,0,i,j);
                else if(i==0 && j==(numColunas-1))                          //posicao 0,final
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,0,0,1,1,i,j);
                else if(i==(numLinhas-1) && j==(numColunas-1))             //posicao final,final
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,0,0,i,j);
                else if(i==(numLinhas-1) && j==0)                          //posicao final,0
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,0,0,0,i,j);

                else if(i==0 && j>0 && j<(numColunas-1))                    //posicao borda da esquerda
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,1,1,1,1,i,j);
                else if(i>0 && i<(numLinhas-1) && j==(numColunas-1))       //posicao borda de baixo
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,1,1,i,j);
                else if(i==(numLinhas-1) && j>0 && j<(numColunas-1))       //posicao borda da direita
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,0,0,0,i,j);
                else if(i>0 && i<(numLinhas-1) && j==0)                    //posicao borda de cima
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,1,1,0,i,j);
            }


        }
    }






}



void revelarZerosProximos(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2]){

    int a = posicaoAsterisco[0];
    int b = posicaoAsterisco[1];
    int sair=0, aux=0;

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


void desenhaMatriz(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int *auxAcabar){

    printf("\t\t\t ");
    for(int i=0;i<numColunas;i++)
        printf("---");

    printf("\n");

    for(int i=0; i<numLinhas;i++){
        printf("\t\t\t|");
        for(int j=0;j<numColunas;j++){

            if(matrizGeral[i][j].asterisco==0){
                if(matrizGeral[i][j].selecionado == 0){
                    if(matrizGeral[i][j].bandeira == 0)
                        printf(" - ");
                    else if(matrizGeral[i][j].bandeira ==1)
                        printf(" P ");
                }
                else{
                    if(matrizGeral[i][j].numBombasProximas==0)
                        printf("   ");
                    else if(matrizGeral[i][j].bomba==1){
                        printf(" B ");
                        *auxAcabar=-1;
                    }
                    else
                        printf(" %d ", matrizGeral[i][j].numBombasProximas);
                }
            }//asterisco==0


            if(matrizGeral[i][j].asterisco==1){
                if(matrizGeral[i][j].selecionado == 0){
                    if(matrizGeral[i][j].bandeira == 0)
                        printf(" -*");
                    else if(matrizGeral[i][j].bandeira ==1)
                        printf(" P*");
                }
                else{
                    if(matrizGeral[i][j].numBombasProximas==0)
                        printf("  *");
                    else if(matrizGeral[i][j].bomba==1){
                        printf(" B*");
                        *auxAcabar=-1;
                    }
                    else
                        printf(" %d*", matrizGeral[i][j].numBombasProximas);
                }
            }//asterisco==1



        }//for J
        printf("|\n");
    }//for i
    printf("\t\t\t ");
    for(int i=0;i<numColunas;i++)
        printf("---");

    printf("\n\n");


}


void condicaoMatrizPossiveisJogadas(struct itensDaMatriz** matrizGeral,int numLinhas,int numColunas, int** matrizPossiveisJogadas, int i, int j, int i2, int j2){

    if(matrizGeral[i][j].selecionado==1 && matrizGeral[i][j].numBombasProximas!=0 && matrizGeral[i2][j2].selecionado==0)
                    matrizPossiveisJogadas[i2][j2]=1;


}



void analisarProbabilidades(struct itensDaMatriz** matrizGeral, int proximaJogadaBot[2], int numLinhas, int numColunas, int posicaoAsterisco[2], int *marcarBandeira, int **bombasCalculadasBot){

    int **matrizPossiveisJogadas;
    int **blocosNaoSelecionadosAoRedor, **numBombasJaCalculadasAoRedor;


    int auxSaida=0;

    proximaJogadaBot[0]=-1;//Caso nao consiga calcular com certeza a proxima jogada terei o valor -1
    proximaJogadaBot[1]=-1;

    matrizPossiveisJogadas = (int**)malloc(numLinhas * sizeof(int*));
        for(int i = 0; i < numLinhas; i++)
            matrizPossiveisJogadas[i] = (int*)calloc(numColunas, sizeof(int));

    blocosNaoSelecionadosAoRedor = (int**)malloc(numLinhas * sizeof(int*));
        for(int i = 0; i < numLinhas; i++)
            blocosNaoSelecionadosAoRedor[i] = (int*)calloc(numColunas, sizeof(int));

    numBombasJaCalculadasAoRedor = (int**)malloc(numLinhas * sizeof(int*));
        for(int i = 0; i < numLinhas; i++)
            numBombasJaCalculadasAoRedor[i] = (int*)calloc(numColunas, sizeof(int));




    for(int i=0;i<numLinhas;i++) //inicializamatrizes
        for(int j=0;j<numColunas;j++){
            matrizPossiveisJogadas[i][j]=0;
            //bombasCalculadasBot[i][j]=0;
            blocosNaoSelecionadosAoRedor[i][j]=0;
            numBombasJaCalculadasAoRedor[i][j]=0;
        }

    for(int i=0;i<numLinhas;i++){
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
    }

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
        //testeDesenhaMatriz(matrizGeral,numLinhas,numColunas,blocosNaoSelecionadosAoRedor);

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


    liberaAlocacaoMatriz(matrizPossiveisJogadas,numLinhas);
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


void interface(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2],int *acabarJogo, int numBombas, int *bombasNaoMarcadas){
    int ganhar=0;
    int auxAcabar;
    char acao;

    limpaTela();

    atualizaBandeiras(matrizGeral,numLinhas,numColunas,bombasNaoMarcadas,numBombas);

    printf("\n\tTeclas:\n\n");
    printf("\tW - Cima\t\t\tE - Seleciona\n");
    printf("\tS - Baixo\t\t\tQ - Coloca Bandeira\n");
    printf("\tA - Esquerda\n");
    printf("\tD - Direita\t\t\t%d Bombas Restantes\n", *bombasNaoMarcadas);
    printf("\t\n\n");

    desenhaMatriz(matrizGeral,numLinhas,numColunas,&auxAcabar);

    fflush(stdin);

    if(auxAcabar==(numLinhas*numColunas)-numBombas){//se todas as posiçoes foram selecionadas menos as bombas ele ganha
        *acabarJogo=1;
        return;
    }
    else if(auxAcabar==-1){ //-1 define que ele perdeu
        *acabarJogo=2;
        return;
    }

   testeDesenhaMatriz(matrizGeral,numLinhas,numColunas);




    printf("\n\n\tDigite sua acao: ");
    lerChar(&acao);

    acaoJogo(matrizGeral,numLinhas,numColunas,acao,posicaoAsterisco,numBombas,bombasNaoMarcadas);


    for (int i=0;i<numLinhas;i++){
        for(int j=0;j<numColunas;j++){
            if(matrizGeral[i][j].selecionado==1)
                ganhar+=1;
        }
    }

    auxAcabar=ganhar;


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


void interfaceComputador(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2],int *acabarJogo, int numBombas, int *primeiraJogadaBot, int proximaJogadaBot[2], int *bombasNaoMarcadas){

    int ganhar=0;
    int auxAcabar;
    char acao;
    int marcarBandeira;
    //static int select;
    int **bombasCalculadasBot;

    atualizaBandeiras(matrizGeral,numLinhas,numColunas,bombasNaoMarcadas,numBombas);

    limpaTela();

    if(*primeiraJogadaBot==1){
        proximaJogadaBot[0] = rand()%numLinhas;
        proximaJogadaBot[1] = rand()%numColunas;
        *primeiraJogadaBot=0;
        marcarBandeira=0;


        bombasCalculadasBot = (int**)malloc(numLinhas * sizeof(int*));
        for(int i = 0; i < numLinhas; i++)
            bombasCalculadasBot[i] = (int*)calloc(numColunas, sizeof(int));

        for(int i=0;i<numLinhas;i++) //inicializamatrizes
            for(int j=0;j<numColunas;j++)
                bombasCalculadasBot[i][j]=0;

    }

    printf("\n\tPlayer: Computador\n\n");
    printf("\tPosicao Asterisco: (%d, %d)\n", posicaoAsterisco[0],posicaoAsterisco[1]);
    printf("\tNumero de Bombas: %d\n", *bombasNaoMarcadas);
    printf("\tProximo Alvo: (%d, %d)\n", proximaJogadaBot[0],proximaJogadaBot[1]);
    printf("\t\n");
    printf("\t\n");
    printf("\t\n\n");

    desenhaMatriz(matrizGeral,numLinhas,numColunas,&auxAcabar);



    if(auxAcabar==(numLinhas*numColunas)-numBombas){//se todas as posiçoes foram selecionadas menos as bombas ele ganha
        *acabarJogo=1;
        return;
    }
    else if(auxAcabar==-1){ //-1 define que ele perdeu
        *acabarJogo=2;
        liberaAlocacaoMatriz(bombasCalculadasBot,numLinhas);
        return;
    }

    if(proximaJogadaBot[0]==posicaoAsterisco[0] && proximaJogadaBot[1]==posicaoAsterisco[1] && marcarBandeira==1){
        acao='q';
        marcarBandeira=0;
        analisarProbabilidades(matrizGeral,proximaJogadaBot,numLinhas,numColunas,posicaoAsterisco, &marcarBandeira, bombasCalculadasBot);
    }
    else if(proximaJogadaBot[0]==posicaoAsterisco[0] && proximaJogadaBot[1]==posicaoAsterisco[1] && marcarBandeira==0){
        acao='e';
    }
    else
        acao = movimentoComputador(proximaJogadaBot,posicaoAsterisco);



    acaoJogo(matrizGeral,numLinhas,numColunas,acao,posicaoAsterisco,numBombas,bombasNaoMarcadas);

    tempoEspera(1);

    if(matrizGeral[proximaJogadaBot[0]][proximaJogadaBot[1]].selecionado==1)
        analisarProbabilidades(matrizGeral,proximaJogadaBot,numLinhas,numColunas,posicaoAsterisco, &marcarBandeira,bombasCalculadasBot);


    for (int i=0;i<numLinhas;i++){ //conta a quantidade de posicoes selecionadas
        for(int j=0;j<numColunas;j++){
            if(matrizGeral[i][j].selecionado==1)
                ganhar+=1;
        }
    }

    auxAcabar=ganhar;










}


void main(){

    int numBombas, numLinhas, numColunas;
    struct itensDaMatriz **matrizGeral;
    int posicaoAsterisco[2] = {0,0};
    int acabarJogo=0;
    int jogarDeNovo=1;
    int jogadorOuBot=0;
    int primeiraJogadaBot=1;
    int proximoAlvoBot[2];
    int bombasNaoMarcadas;
    clock_t inicio_tempo, fim_tempo;


    while(jogarDeNovo==1){
        inicio(&numBombas, &numLinhas, &numColunas,&jogadorOuBot);
        primeiraJogadaBot=1;
        bombasNaoMarcadas=numBombas;

        matrizGeral = (struct itensDaMatriz**)malloc(numLinhas * sizeof(struct itensDaMatriz*));

        for(int i = 0; i < numLinhas; i++){
            matrizGeral[i] = (struct itensDaMatriz*)calloc(numColunas, sizeof(struct itensDaMatriz));
        }
        //faltaDeMemoria(matrizGeral);
        inicializaValoresMatriz(matrizGeral,numLinhas,numColunas);

        colocarBombas(matrizGeral,numBombas,numLinhas,numColunas);
        colocarNumeros(matrizGeral,numLinhas,numColunas);

        inicio_tempo = clock();

        while (acabarJogo==0){
            if(jogadorOuBot==1)
               interface(matrizGeral,numLinhas,numColunas,posicaoAsterisco,&acabarJogo,numBombas, &bombasNaoMarcadas);
            else
                interfaceComputador(matrizGeral,numLinhas,numColunas,posicaoAsterisco,&acabarJogo,numBombas,&primeiraJogadaBot,proximoAlvoBot, &bombasNaoMarcadas);
        }

        fim_tempo = clock();

        printf("\tTempo de jogo: %.2f segundos\n", (double)(fim_tempo-inicio_tempo)/CLOCKS_PER_SEC);

        tempoEspera(4);
        limpaTela();

        if(acabarJogo==1)
            printf("\n\tVoce Ganhou");
        else if(acabarJogo==2)
            printf("\n\tVoce Perdeu");



        printf("\n\n\tDeseja jogar novamente? (1-Sim / 0-Nao)\n\tR: ");
        scanf("%d", &jogarDeNovo);
        acabarJogo=0;
        posicaoAsterisco[0]=0;
        posicaoAsterisco[1]=0;

        liberaAlocacaoMatrizStruct(matrizGeral, numLinhas);
    }

}

