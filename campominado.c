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
    char status[1];
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

void liberaAlocacaoMatriz(int **ponteiro, int tam){

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
                //strcpy(matrizGeral[i][j].status,"O");

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
            for(int j=numColunas-1;j>0;j--){
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

        if(matrizGeral[a][b].bomba==1){
            //Perder o Jogo
        }
        if(matrizGeral[a][b].numBombasProximas==0){
            revelarZerosProximos(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
        }
   }










}




void acaoJogo(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, char acao, int posicaoAsterisco[2]){

    int a=0,b=0;

    a=posicaoAsterisco[0];
    b=posicaoAsterisco[1];
    matrizGeral[a][b].asterisco = 0;

    //printf("\n\nPosicao Ast Ants: %d e %d\n", posicaoAsterisco[0],posicaoAsterisco[1]);

    switch(acao){

        case 'W':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;
printf("\n\n");
    desenhaMatriz(matrizGeral,numLinhas,numColunas);
        case 'S':
            if(posicaoAsterisco[0]!=numColunas-1)
                posicaoAsterisco[0]++;
            break;
        case 'A':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'D':
            if(posicaoAsterisco[1]!=numLinhas-1)
                posicaoAsterisco[1]++;
            break;
        case 'E':
            selecionar(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
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
            selecionar(matrizGeral,numLinhas,numColunas,posicaoAsterisco);
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


void desenhaMatriz(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int *auxAcabar){

    printf("\t\t\t ");
    for(int i=0;i<numColunas;i++)
        printf("---");

    printf("\n");

    for(int i=0; i<numLinhas;i++){
        printf("\t\t\t|");
        for(int j=0;j<numColunas;j++){

            if(matrizGeral[i][j].asterisco==0){
                if(matrizGeral[i][j].selecionado == 0)
                    printf(" - ");
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
                if(matrizGeral[i][j].selecionado == 0)
                    printf(" -*");
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


void condicaoMatrizPossiveisJogadas(struct itensDaMatriz** matrizGeral,int numLinhas,int numColunas, int matrizPossiveisJogadas[numColunas][numLinhas], int i, int j, int i2, int j2){

    if(matrizGeral[i][j].selecionado==1 && matrizGeral[i][j].numBombasProximas!=0 && matrizGeral[i2][j2].selecionado==0)
                    matrizPossiveisJogadas[i2][j2]=1;


}



void analisarProbabilidades(struct itensDaMatriz** matrizGeral, int proximaJogadaBot[2], int numLinhas, int numColunas){

    int matrizPossiveisJogadas[numColunas][numLinhas], bombasCalculadasBot[numColunas][numLinhas];
    int blocosNaoSelecionadosAoRedor[numColunas][numLinhas];

    for(int i=0;i<numLinhas;i++) //inicializamatriz
        for(int j=0;j<numColunas;j++){
            matrizPossiveisJogadas[i][j]=0;
            bombasCalculadasBot[i][j]=0;
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


    for(int i=0;i<numLinhas;i++) //Conta os espaços nao selecionados ao redor
        for(int j=0;j<numColunas;j++){
            blocosNaoSelecionadosAoRedor=0
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
        for(int j=0;j<numColunas;j++){
            blocosNaoSelecionadosAoRedor=0
            if(blocosNaoSelecionadosAoRedor[i][j]==matrizGeral[i][j].numBombasProximas){
                if(j!=numColunas-1)//Direita
                    if(matrizGeral[i][j+1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(j!=0)//Esquerda
                    if(matrizGeral[i][j-1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(i!=numLinhas-1)//Baixo
                    if(matrizGeral[i+1][j].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(i!=0)//Cima
                    if(matrizGeral[i-1][j].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(j!=numColunas-1 && i!=0)//Direita-Cima
                    if(matrizGeral[i-1][j+1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(j!=0 && i!=0)//Esquerda-Cima
                    if(matrizGeral[i-1][j-1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(j!=numColunas-1 && i!=numLinhas-1)//Direita-Baixo
                    if(matrizGeral[i+1][j+1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;

                if(j!=0 && i!=numLinhas-1)//Esquerda-Baixo
                    if(matrizGeral[i+1][j-1].selecionado==0)
                        bombasCalculadasBot[i][j]=1;




            }









        }




    //Crio a Matriz "BombasCalculadasBot"[][]                                                                                   OK
    //Olho o Numero de Bombas Prox já selecionado                                                                               OK
    //Quantos Blocos Não Selecionados tem ao redor? (Divido BlocosNaoSelecionados/NumBombas)                                    OK
    //Marco 1 em "BombasCalculadasBot[][]" se a divisao for == 1                                                                OK

    //Crio uma variavel auxiliar
    //Olhando o numero de bombas proximas, contar na auxiliar a quantidade de bombas ao redor da posição
    //Se a quantidade for igual ao numero de bombas e alguma das posições ao redor estiver nao selecionada e sem bombacalculada
    //Jogar essa posição no proximaJogadaBot[] e dar break para sair dos ciclos
    //se nao houver proxima jogada colocar valor aleatorio





    /*printf("\n\n");

    for(int i=0;i<numLinhas;i++){
        for(int j=0;j<numColunas;j++){
            if(j!=numColunas-1)
                printf(" %d -",matrizPossiveisJogadas[i][j]);
            else
                printf(" %d\n",matrizPossiveisJogadas[i][j]);

        }
    }*/













































}





void interface(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsteristico[2],int *acabarJogo, int numBombas){
    int ganhar=0;
    int auxAcabar;
    char acao;

    limpaTela();

    printf("\n\tTeclas:\n");
    printf("\tW - Cima\n");
    printf("\tS - Baixo\n");
    printf("\tA - Esquerda\n");
    printf("\tD - Direita\n");
    printf("\tE - Seleciona\n\n");

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

    analisarProbabilidades(matrizGeral,numLinhas,numColunas);

    printf("\n\n\tDigite sua acao: ");
    lerChar(&acao);

    acaoJogo(matrizGeral,numLinhas,numColunas,acao,posicaoAsteristico);


    for (int i=0;i<numLinhas;i++){
        for(int j=0;j<numColunas;j++){
            if(matrizGeral[i][j].selecionado==1)
                ganhar+=1;
        }
    }

    auxAcabar=ganhar;


}



char movimentoComputador(int proximoAlvoComputador[2], int posicaoAsteristico[2]){

    if(proximoAlvoComputador[0]<posicaoAsteristico[0])
        return 'a';
    else if(proximoAlvoComputador[0]>posicaoAsteristico[0])
        return 'd';
    else if(proximoAlvoComputador[1]<posicaoAsteristico[1])
        return 'w';
    else if(proximoAlvoComputador[1]>posicaoAsteristico[1])
        return 's';


}


void interfaceComputador(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsteristico[2],int *acabarJogo, int numBombas, int *primeiraJogadaBot, int proximaJogadaBot[2]){

    int ganhar=0;
    int auxAcabar;
    char acao;

    limpaTela();

    if(*primeiraJogadaBot==1){
        srand(time(NULL));
        proximaJogadaBot[0] = rand()%numLinhas;
        proximaJogadaBot[1] = rand()%numColunas;
        *primeiraJogadaBot=0;
    }

    printf("\n\tPlayer: Computador\n\n");
    printf("\tPosição Asteristico: (%d, &d)\n", posicaoAsteristico[0],posicaoAsteristico[1]);
    printf("\tTempo entre cada movimento: 1s\n");
    printf("\tProximo Alvo: (%d, %d)\n", proximaJogadaBot[0],proximaJogadaBot[1]);
    printf("\t\n");
    printf("\t\n");
    printf("\t\n\n");

    desenhaMatriz(matrizGeral,numLinhas,numColunas,&auxAcabar);

    //fflush(stdin);

    if(auxAcabar==(numLinhas*numColunas)-numBombas){//se todas as posiçoes foram selecionadas menos as bombas ele ganha
        *acabarJogo=1;
        return;
    }
    else if(auxAcabar==-1){ //-1 define que ele perdeu
        *acabarJogo=2;
        return;
    }



    if(proximaJogadaBot[0]==posicaoAsteristico[0] && proximaJogadaBot[1]==posicaoAsteristico[1])
        acao='e';
    else
        acao = movimentoComputador(proximaJogadaBot,posicaoAsteristico);

    acaoJogo(matrizGeral,numLinhas,numColunas,acao,posicaoAsteristico);

    tempoEspera(1);

    //Analisar Probabilidades
    //Definir Proximo alvo


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
    int posicaoAsteristico[2] = {0,0};
    int acabarJogo=0;
    int jogarDeNovo=1;
    int jogadorOuBot;
    int primeiraJogadaBot=1;
    int proximoAlvoBot[2];


    while(jogarDeNovo==1){
        inicio(&numBombas, &numLinhas, &numColunas,&jogadorOuBot);
        primeiraJogadaBot=1;

        matrizGeral = (struct itensDaMatriz**)malloc(numLinhas * sizeof(struct itensDaMatriz*));

        for(int i = 0; i < numLinhas; i++){
            matrizGeral[i] = (struct itensDaMatriz*)calloc(numColunas, sizeof(struct itensDaMatriz));
        }
        faltaDeMemoria(matrizGeral);
        inicializaValoresMatriz(matrizGeral,numLinhas,numColunas);

        colocarBombas(matrizGeral,numBombas,numLinhas,numColunas);
        colocarNumeros(matrizGeral,numLinhas,numColunas);



        while (acabarJogo==0)
            interface(matrizGeral,numLinhas,numColunas,posicaoAsteristico,&acabarJogo,numBombas);



        if(acabarJogo==1)
            printf("\n\nVoce Ganhou");
        else if(acabarJogo==2)
            printf("\n\nVoce Perdeu");

        tempoEspera(2);
        limpaTela();
        printf("\n\nDeseja jogar novamente? (1-Sim / 0-Nao)\nR: ");
        scanf("%d", &jogarDeNovo);
        acabarJogo=0;
        posicaoAsteristico[0]=0;
        posicaoAsteristico[1]=0;

        liberaAlocacaoMatriz (matrizGeral, numLinhas);
    }

}

