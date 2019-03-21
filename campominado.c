#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>


struct itensDaMatriz{

    int bomba;
    int selecionado;
    int numBombasProximas; //Max 8 - Se for 0 deve liberar os espaços de 0 proximos
    int zeroBombasProximas;
    int marcadoBandeira;
    char status[1];
    int asterisco;

};

void limpaTela(){
    system("cls");

}

void lerChar(char *caracter){
    //scanf("%c",caracter);
    //*caracter=getchar();
    *caracter=getch();

}


void tempoEspera(int tempo){
    sleep(tempo);
}


void desenhaMatriz(struct itensDaMatriz **matrizGeral,int numColunas, int numLinhas){

    for(int i=0;i<numColunas;i++){
        for(int j=0;j<numLinhas;j++){
            if(j!=numLinhas-1)
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

void inicializaValoresMatriz(struct itensDaMatriz **matrizGeral, int numColunas, int numLinhas){

        for(int i=0; i<numColunas;i++){
            for(int j=0;j<numLinhas;j++){
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


void inicio(int *numBombas, int *numColunas, int *numLinhas){

    printf("Defina o numero de colunas da matriz: ");
    scanf("%d", numLinhas);
    printf("Defina o numero de linhas da matriz: ");
    scanf("%d", numColunas);


    printf("Defina o numero de bombas do jogo: ");
    scanf("%d", numBombas);

}

void colocarBombas (struct itensDaMatriz **matrizGeral, int numBombas, int numColunas, int numLinhas){

    int posicoesBombas[numBombas][2];
    int aux=0, aux2=0;

    srand(time(NULL));

    for(int i=0; i<numBombas;i++){
        aux=0;
        while(aux==0){

            posicoesBombas[i][0] = rand()%numColunas;
            posicoesBombas[i][1] = rand()%numLinhas;
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

void colocarNumeros (struct itensDaMatriz **matrizGeral, int numColunas, int numLinhas){

    for (int i=0; i<numColunas;i++){
        for(int j=0; j<numLinhas;j++){
            if(matrizGeral[i][j].bomba==1)
                matrizGeral[i][j].numBombasProximas=-1;

            else{
                if(i!=0 && i!=(numColunas-1) && j!=0 && j!=(numLinhas-1))  //fora de qualquer borda
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,1,1,1,i,j);

                else if(i==0 && j==0)                                       //posicao 0,0
                    colocarNumerosPosicoes(matrizGeral,0,0,0,0,1,1,1,0,i,j);
                else if(i==0 && j==(numLinhas-1))                          //posicao 0,final
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,0,0,1,1,i,j);
                else if(i==(numColunas-1) && j==(numLinhas-1))             //posicao final,final
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,0,0,i,j);
                else if(i==(numColunas-1) && j==0)                          //posicao final,0
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,0,0,0,i,j);

                else if(i==0 && j>0 && j<(numLinhas-1))                    //posicao borda da esquerda
                    colocarNumerosPosicoes(matrizGeral,1,0,0,0,1,1,1,1,i,j);
                else if(i>0 && i<(numColunas-1) && j==(numLinhas-1))       //posicao borda de baixo
                    colocarNumerosPosicoes(matrizGeral,1,1,1,0,0,0,1,1,i,j);
                else if(i==(numColunas-1) && j>0 && j<(numLinhas-1))       //posicao borda da direita
                    colocarNumerosPosicoes(matrizGeral,1,1,1,1,1,0,0,0,i,j);
                else if(i>0 && i<(numColunas-1) && j==0)                    //posicao borda de cima
                    colocarNumerosPosicoes(matrizGeral,0,0,1,1,1,1,1,0,i,j);
            }


        }
    }






}


void perderJogo(int situacao,int *acabarJogo){
// situacao
// 0 - Avisar a funcao que perdeu
// 1 - Mostrar que perdeu na tela (após atualizar a tela

    static int a=0;
    char jogarDeNovo;

    if(situacao==0){
        a=1;
    }
    if(situacao==1 && a==1){
        *acabarJogo=2;
    }




}

void ganharJogo(struct itensDaMatriz **matrizGeral, int numColunas,int numLinhas, int **acabarJogo){

    int ganhou=1;

    for(int i=0;i<numColunas-1;i++)
        for(int j=0;j<numLinhas-1;j++);




}

void revelarZerosProximos(struct itensDaMatriz** matrizGeral, int numColunas, int numLinhas, int posicaoAsterisco[2]){

    int a = posicaoAsterisco[0];
    int b = posicaoAsterisco[1];
    int sair=0, aux=0;

    while(sair==0){

        sair=1;

        for (int i=0;i<numColunas;i++){//direita
            for(int j=0;j<numLinhas;j++){
                if(j!=numLinhas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i][j+1].selecionado==0){
                        matrizGeral[i][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }
        for (int i=0;i<numColunas;i++){//esquerda
            for(int j=numLinhas-1;j>0;j--){
                if(j!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i][j-1].selecionado==0){
                        matrizGeral[i][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }

        for (int i=0;i<numColunas;i++){//baixo
            for(int j=0;j<numLinhas;j++){
                if(i!=numColunas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j].selecionado==0){
                        matrizGeral[i+1][j].selecionado=1;
                        sair=0;
                    }
            }
        }
        for (int i=numColunas-1;i>0;i--){//cima
            for(int j=0;j<numLinhas;j++){
                if(i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j].selecionado==0){
                        matrizGeral[i-1][j].selecionado=1;
                        sair=0;
                    }

            }
        }


        for (int i=0;i<numColunas;i++){//baixo-direita
            for(int j=0;j<numLinhas;j++){
                if(j!=numLinhas-1 && i!=numColunas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j+1].selecionado==0){
                        matrizGeral[i+1][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }

        for (int i=0;i<numColunas;i++){//baixo-esquerda
            for(int j=numLinhas-1;j>0;j--){
                if(j!=0 && i!=numColunas-1)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i+1][j-1].selecionado==0){
                        matrizGeral[i+1][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }



        for (int i=0;i<numColunas;i++){//cima-esquerda
            for(int j=numLinhas-1;j>0;j--){
                if(j!=0 && i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j-1].selecionado==0){
                        matrizGeral[i-1][j-1].selecionado=1;
                        sair=0;
                    }

            }
        }


        for (int i=0;i<numColunas-1;i++){//cima-direita
            for(int j=numLinhas-1;j>0;j--){
                if(j!=numLinhas-1 && i!=0)
                    if(matrizGeral[i][j].numBombasProximas==0 && matrizGeral[i][j].selecionado==1 && matrizGeral[i-1][j+1].selecionado==0){
                        matrizGeral[i-1][j+1].selecionado=1;
                        sair=0;
                    }

            }
        }



















    }//while


}

void selecionar(struct itensDaMatriz** matrizGeral, int numColunas, int numLinhas, int posicaoAsterisco[2]){

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
            revelarZerosProximos(matrizGeral,numColunas,numLinhas,posicaoAsterisco);
        }
   }










}




void acaoJogo(struct itensDaMatriz** matrizGeral, int numColunas, int numLinhas, char acao, int posicaoAsterisco[2]){

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
    desenhaMatriz(matrizGeral,numColunas,numLinhas);
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
            selecionar(matrizGeral,numColunas,numLinhas,posicaoAsterisco);
            break;
        case 'w':
            if(posicaoAsterisco[0]!=0)
                posicaoAsterisco[0]--;
            break;

        case 's':
            if(posicaoAsterisco[0]!=numColunas-1)
                posicaoAsterisco[0]++;
            break;
        case 'a':
            if(posicaoAsterisco[1]!=0)
                posicaoAsterisco[1]--;
            break;
        case 'd':
            if(posicaoAsterisco[1]!=numLinhas-1)
                posicaoAsterisco[1]++;
            break;
        case 'e':
            selecionar(matrizGeral,numColunas,numLinhas,posicaoAsterisco);
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


void interface(struct itensDaMatriz** matrizGeral, int numColunas, int numLinhas, int posicaoAsteristico[2],int *acabarJogo, int numBombas){
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

    printf("\t\t\t ");
    for(int i=0;i<numLinhas;i++)
        printf("---");

    printf("\n");

    for(int i=0; i<numColunas;i++){
        printf("\t\t\t|");
        for(int j=0;j<numLinhas;j++){

            if(matrizGeral[i][j].asterisco==0){
                if(matrizGeral[i][j].selecionado == 0)
                    printf(" - ");
                else{
                    if(matrizGeral[i][j].numBombasProximas==0)
                        printf("   ");
                    else if(matrizGeral[i][j].bomba==1){
                        printf(" B ");
                        auxAcabar=-1;
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
                        auxAcabar=-1;
                    }
                    else
                        printf(" %d*", matrizGeral[i][j].numBombasProximas);
                }
            }//asterisco==1



        }//for J
        printf("|\n");
    }//for i
    printf("\t\t\t ");
    for(int i=0;i<numLinhas;i++)
        printf("---");

    printf("\n\n");

    //desenhaMatriz(matrizGeral,numColunas,numLinhas);

    fflush(stdin);

    //printf("\n\n%d\n\n",*acabarJogo);
    //printf("ganhar = %d    conta=%d",auxAcabar,(numColunas*numLinhas)-numBombas);


    if(auxAcabar==(numColunas*numLinhas)-numBombas){
        *acabarJogo=1;
        return;
    }
    else if(auxAcabar==-1){
        *acabarJogo=2;
        return;
    }

    printf("\n\n\tDigite sua acao: ");
    lerChar(&acao);

    //ganharJogo(matrizGeral,numColunas,numLinhas,acabarJogo);
    acaoJogo(matrizGeral,numColunas,numLinhas,acao,posicaoAsteristico);


    for (int i=0;i<numColunas;i++){
        for(int j=0;j<numLinhas;j++){
            if(matrizGeral[i][j].selecionado==1)
                ganhar+=1;
        }
    }

    auxAcabar=ganhar;


}


void main(){

    int numBombas, numColunas, numLinhas;
    struct itensDaMatriz **matrizGeral;
    int posicaoAsteristico[2] = {0,0};
    int acabarJogo=0;
    int jogarDeNovo=1;

    while(jogarDeNovo==1){
        inicio(&numBombas, &numColunas, &numLinhas);


        matrizGeral = (struct itensDaMatriz**)malloc(numColunas * sizeof(struct itensDaMatriz*));
        for(int i = 0; i < numColunas; i++){
            matrizGeral[i] = (struct itensDaMatriz*)calloc(numLinhas, sizeof(struct itensDaMatriz));
        }

        inicializaValoresMatriz(matrizGeral,numColunas,numLinhas);

        colocarBombas(matrizGeral,numBombas,numColunas,numLinhas);
        colocarNumeros(matrizGeral,numColunas,numLinhas);



        while (acabarJogo==0)
            interface(matrizGeral,numColunas,numLinhas,posicaoAsteristico,&acabarJogo,numBombas);



        if(acabarJogo==1)
            printf("\n\nVoce Ganhou");
        else if(acabarJogo==2)
            printf("\n\nVoce Perdeu");

        tempoEspera(2);
        limpaTela();
        printf("Deseja jogar novamente? (1-Sim / 0-Nao)\nR: ");
        scanf("%d", &jogarDeNovo);
        acabarJogo=0;
        posicaoAsteristico[0]=0;
        posicaoAsteristico[1]=0;
    }

}

