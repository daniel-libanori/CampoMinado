#ifndef JOGANDO
#define JOGANDO

//Geral
void revelarZerosProximos(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2]);
void selecionar(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int posicaoAsterisco[2]);
void acaoJogo(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, char acao, int posicaoAsterisco[2], int numBombas, int *bombasNaoMarcadas);
void atualizaBandeiras(struct itensDaMatriz** matrizGeral, int numLinhas, int numColunas, int *bombasNaoMarcadas, int numBombas);
char movimentoComputador(int proximoAlvoComputador[2], int posicaoAsterisco[2]);

//Computador
void condicaoMatrizPossiveisJogadas(struct itensDaMatriz** matrizGeral,int numLinhas,int numColunas, int** matrizPossiveisJogadas, int i, int j, int i2, int j2);
void analisarProbabilidades(struct itensDaMatriz** matrizGeral, int proximaJogadaBot[2], int numLinhas, int numColunas, int posicaoAsterisco[2], int *marcarBandeira, int **bombasCalculadasBot);


#endif // JOGANDO
