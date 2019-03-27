#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

struct itensDaMatriz{

    int bomba;
    int selecionado;
    int numBombasProximas;
    int zeroBombasProximas;
    int marcadoBandeira;
    int bandeira;
    int asterisco;

};

//Basicas
void limpaTela();
void lerChar(char *caracter);
void tempoEspera(int tempo);

//Usadas Para Auxiliar o Desenvolvedor
void testeDesenhaMatriz(struct itensDaMatriz **matrizGeral,int numLinhas, int numColunas);

//Matrizes
void liberaAlocacaoMatriz(int **ponteiro, int tam);
void liberaAlocacaoMatrizStruct(struct itensDaMatriz **ponteiro, int tam);


#endif // FUNCOESAUXILIARES_H_INCLUDED
