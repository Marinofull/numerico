// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO
// ALUNO: SAULO RIBEIRO DE ANDRADE

// TRABALHO PRATICO 2016.2 - PARTE 1

// Sistemalinear.c
// Codigo-fonte das funcoes para manipulacao de matrizes
// e resolucao de sistemas lineares

#include "Sistemalinear.h"

int initializeMatriz(Matriz *m)
{
    /* Inicializa a matriz */
    m->tam_matriz = 0;
    return OK;
}

int append(Matriz *m, float linha[], int tamlinha)
{
    /* Insere um array de elementos na matriz */
    int li = m->tam_matriz;
    int pos;

    for (pos = 0; pos < tamlinha; pos++)
    {
        m->chave[li][pos] = linha[pos];
    }
    m->tam_matriz++;

    return OK;
}

int swap(Matriz *m, int indice1, int indice2)
{
    /* Troca os elementos da linha indice1 pelos elementos da linha indice2 */
    int pos;
    int temp;
    for (pos = 0; pos < MAXSIZE; pos++)
    {
        temp = m->chave[indice1][pos];
        m->chave[indice1][pos] = m->chave[indice2][pos];
        m->chave[indice2][pos] = temp;
    }
    return OK;
}


//int gaussJacobi(A, b) {
int jacobi(Matriz *m, float erro, int iteracoes, float solucao[]){
    var x = new Array();
    for (var k = 0; k < m.tam_matriz; k++)
    {
        solucao[k] = 0; //Math.floor((Math.random() * 10000) + 1);
    }

    var ni = 0;//Contador de iterações
    var continuar = true;

    while (continuar && ni < iteracoes) {
        for (var i=0; i < b.length; i++) {
            soma = 0;
            for (var j = 0; j < b.length; j++) {
                if (j != i) {
                    soma = soma + A[i][j]*solucao[j]/A[i][i];
                }
                x[i] = (b[i]/A[i][i]) - soma;
            }
        }
        if (Math.abs(norm(x) - norm(solucao)) < erro) {
            continuar = false;
        } else {
            solucao=x.slice(0);
        }
        ni = ni + 1;
    }
    return solucao;
}
