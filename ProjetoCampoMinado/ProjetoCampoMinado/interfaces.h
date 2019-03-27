#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

//Inicio Jogo
void inicio(int *numBombas, int *numLinhas, int *numColunas, int *jogadorOuBot);
void aberturaJogo();

//Player
void interface(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2],int *acabarJogo, int numBombas, int *bombasNaoMarcadas);

//Computador
void interfaceComputador(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2],int *acabarJogo, int numBombas, int *primeiraJogadaBot, int proximaJogadaBot[2], int *bombasNaoMarcadas);

//Geral
void desenhaMatriz(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int *auxAcabar);

#endif // INTERFACES_H_INCLUDED
