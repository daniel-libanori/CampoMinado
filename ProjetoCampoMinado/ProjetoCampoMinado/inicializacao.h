#ifndef INICIALIZACAO_H_INCLUDED
#define INICIALIZACAO_H_INCLUDED

void colocarBombas (struct itensDaMatriz **matrizGeral, int numBombas, int numLinhas, int numColunas);
void colocarNumerosPosicoes(struct itensDaMatriz **matrizGeral, int c,int ce,int e,int be,int b,int bd,int d,int cd,int i,int j);
void colocarNumeros (struct itensDaMatriz **matrizGeral, int numLinhas, int numColunas);
void inicializaValoresMatriz(struct itensDaMatriz **matrizGeral, int numLinhas, int numColunas);

#endif // INICIALIZACAO_H_INCLUDED
