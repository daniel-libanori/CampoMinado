#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//#include <conio.h>

#include "funcoesAuxiliares.h"
#include "interfaces.h"
#include "inicializacao.h"
#include "jogando.h"




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
    clock_t inicioTempo, fimTempo;



    while(jogarDeNovo==1){



        aberturaJogo();
        inicio(&numBombas, &numLinhas, &numColunas,&jogadorOuBot);


        primeiraJogadaBot=1;
        bombasNaoMarcadas=numBombas;


        //Alocação Matriz
        matrizGeral = (struct itensDaMatriz**)malloc(numLinhas * sizeof(struct itensDaMatriz*));
        if (matrizGeral == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return;
        }

        for(int i = 0; i < numLinhas; i++){
            matrizGeral[i] = (struct itensDaMatriz*)calloc(numColunas, sizeof(struct itensDaMatriz));
            if (matrizGeral[i] == NULL) {
                printf ("** Erro: Memoria Insuficiente **");
                return;
            }
        }

        //Funções Inicialização do Jogo
        inicializaValoresMatriz(matrizGeral,numLinhas,numColunas);
        colocarBombas(matrizGeral,numBombas,numLinhas,numColunas);
        colocarNumeros(matrizGeral,numLinhas,numColunas);

        inicioTempo = clock();//Começa a contar o tempo

        while (acabarJogo==0){
            if(jogadorOuBot==1)
               interface(matrizGeral,numLinhas,numColunas,posicaoAsterisco,&acabarJogo,numBombas, &bombasNaoMarcadas);
            else
                interfaceComputador(matrizGeral,numLinhas,numColunas,posicaoAsterisco,&acabarJogo,numBombas,&primeiraJogadaBot,proximoAlvoBot, &bombasNaoMarcadas);
        }

        fimTempo = clock();//Para de contar o tempo



        tempoEspera(3);
        limpaTela();

        printf("\n\n\tCampo Minado (By:Daniel Libanori)\n\n");

        if(acabarJogo==1)
            printf("\tVoce Ganhou!");
        else if(acabarJogo==2)
            printf("\tVoce Perdeu.");
         printf("\n\tTempo de jogo: %.2f segundos\n", (double)(fimTempo-inicioTempo)/CLOCKS_PER_SEC);


        printf("\n\n\tDeseja jogar novamente? (1-Sim / 0-Nao)\n\tR: ");
        scanf("%d", &jogarDeNovo);
        acabarJogo=0;
        posicaoAsterisco[0]=0;
        posicaoAsterisco[1]=0;

        liberaAlocacaoMatrizStruct(matrizGeral, numLinhas);
    }

}

