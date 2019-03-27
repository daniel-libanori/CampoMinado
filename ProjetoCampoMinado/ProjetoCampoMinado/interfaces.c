#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#include "jogando.h"
#include "funcoesAuxiliares.h"

void inicio(int *numBombas, int *numLinhas, int *numColunas, int *jogadorOuBot){

    int ok=0;
    int aux1,aux2;

    limpaTela();

    printf("\n\n\tCampo Minado (By:Daniel Libanori)\n\n");
    while(ok==0){
        printf("\tDefina o jogador (1 - Voce    2- Computador): ");
        scanf("%d", jogadorOuBot);
        ok=1;
        if(*jogadorOuBot != 1 && *jogadorOuBot != 2){
            printf("\n\tDigite um valor valido.\n");
            ok=0;
        }
    }
    ok=0;
    while(ok==0){
        printf("\tDefina o numero de colunas da matriz: ");
        scanf("%d", numColunas);
        ok=1;
        if(*numColunas<0){
            printf("\n\tDigite um valor valido.\n");
            ok=0;
        }
    }

    ok=0;
    while(ok==0){
        printf("\tDefina o numero de linhas da matriz: ");
        scanf("%d", numLinhas);
        ok=1;
        if(*numLinhas<0){
            printf("\n\tDigite um valor valido.\n");
            ok=0;
        }
    }
    aux1=*numLinhas;
    aux2=*numColunas;

    ok=0;
    while(ok==0){
        printf("\tDefina o numero de bombas do jogo: ");
        scanf("%d", numBombas);
        ok=1;
        if(*numBombas<0){
            printf("\n\tDigite um valor valido.\n");
            ok=0;
        }
        else if(*numBombas>(*numLinhas)*(*numColunas)){
            printf("\n\tValor digitado ultrapassa o total de espaços da matriz. Digite outro.\n");
            ok=0;
        }
    }

}

void aberturaJogo(){
    limpaTela();

    printf("\n\n\tCampo Minado (By:Daniel Libanori)\n");
    printf("\n\n");
    printf("\t\t\t-----------    ---------    -----         -----  ----------   -------------\n");
    printf("\t\t\t|         |   /   ___   \\   |    \\       /    |  |   ----  \\  |  -------  |\n");
    printf("\t\t\t|    ------  /   /   \\   \\  |     \\     /     |  |   |   |  | |  |     |  |\n");
    printf("\t\t\t|   |        |   |   |   |  |      \\   /      |  |   ----  /  |  |     |  |\n");
    printf("\t\t\t|   |	     |   -----   |  |   |\\  ---  /|   |  |   -----    |  |     |  |\n");
    printf("\t\t\t|   |        |   -----   |  |   | \\     / |   |  |   |        |  |     |  |\n");
    printf("\t\t\t|    ------  |   |   |   |  |   |  \\   /  |   |  |   |        |  |     |  |\n");
    printf("\t\t\t|         |  |	 |   |   |  |   |   ---   |   |  |   |        |  -------  |\n");
    printf("\t\t\t-----------  -----   -----  -----         -----  -----        -------------\n\n\n");

    printf("\t\t-----         -----  -----  -----    -----    ---------    -----------     -------------\n");
    printf("\t\t|    \\       /    |  |   |  |    \\   |   |   /   ___   \\   |  ------  \\    |  -------  |\n");
    printf("\t\t|     \\     /     |  |   |  |     \\  |   |  /   /   \\   \\  |  |     \\  \\   |  |     |  |\n");
    printf("\t\t|      \\   /      |  |   |  |      \\ |   |  |   |   |   |  |  |      |  |  |  |     |  |\n");
    printf("\t\t|   |\\  ---  /|   |  |   |  |   |\\  \\|   |  |   -----   |  |  |      |  |  |  |     |  |\n");
    printf("\t\t|   | \\     / |   |  |   |  |   | \\      |  |   -----   |  |  |      |  |  |  |     |  |\n");
    printf("\t\t|   |  \\   /  |   |  |   |  |   |  \\     |  |   |   |   |  |  |     /  /   |  |     |  |\n");
    printf("\t\t|   |   ---   |   |  |   |  |   |   \\    |  |	|   |   |  |  ------  /    |  -------  |\n");
    printf("\t\t-----         -----  -----  -----    -----  -----   -----  -----------     -------------\n");


    printf("\n\n\t\t\t\t\t\tPressione Enter para Comecar");
    getch();
}

void interface(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2],int *acabarJogo, int numBombas, int *bombasNaoMarcadas){
    int ganhar=0;
    int auxAcabar;
    char acao;

    limpaTela();

    atualizaBandeiras(matrizGeral,numLinhas,numColunas,bombasNaoMarcadas,numBombas);

    printf("\n\n\tCampo Minado (By:Daniel Libanori)\n");
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

   //testeDesenhaMatriz(matrizGeral,numLinhas,numColunas);




    printf("\n\n\n\tDigite sua acao: ");
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
    printf("\n\n\tCampo Minado (By:Daniel Libanori)\n");
    printf("\n\tPlayer: Computador\n\n");
    printf("\tPosicao Asterisco: (%d, %d)\n", posicaoAsterisco[0]+1,posicaoAsterisco[1]+1);
    printf("\tNumero de Bombas: %d\n", *bombasNaoMarcadas);
    printf("\tProximo Alvo: (%d, %d)\n", proximaJogadaBot[0]+1,proximaJogadaBot[1]+1);
    printf("\t\n");
    printf("\t\n");

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



