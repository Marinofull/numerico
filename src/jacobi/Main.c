// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO

// TRABALHO PRATICO 2016.2 - PARTE 1

// Main.c
// Programa principal do trabalho pratico da disciplina CALCULO NUMERICO
// Para compilar use: make
// Para executar use: ./jacobi [fileA] [num_erro] [num_iteracoes]

#include "Sistemalinear.h"

#define MAX_ARGC 6 // Numero de argumentos de entrada esperado

int main(int argc, char *argv[])
{
    char fileA[255];             // String do nome do arquivo
    char fileB[255];             // String do nome do arquivo
    char fileX[255];             // String do nome do arquivo
    float erro;                  // O algoritmo interrompe a sua execucao apos as solucoes estiverem abaixo da margem de erro informada
    int iteracoes;           // O algoritmo interrompe a sua execucao apos n iteracoes

    ma a;     // Matriz A
    mb b, x;     // Mbtriz B
    float solucao[MAXSIZE];// Array que guarda a solucao do sistema linear

    int pos;
    /*
       ==============================================================================
       =====                                                                    =====
       =====                Inicializacao da matriz e arrays                    =====
       =====                                                                    =====
       ==============================================================================
       */
    initializeA(&a);
    initializeB(&b);
    initializeB(&x);
    for (pos = 0; pos < MAXSIZE; pos++)
        solucao[pos] = 0;

    /*
       ==============================================================================
       =====                                                                    =====
       =====                Tratamento dos parametros de entrada                =====
       =====                                                                    =====
       ==============================================================================
       */
    if (argc != MAX_ARGC)
    {
        // Verifique se o numero de parametros passados no prompt de comando esta correto
        // Interrompa a execucao caso contrario
        printf("Esperado %d parametros de entrada (apenas %d dado(s)). \n", MAX_ARGC-1, argc-1);
        printf("Para compilar use: make \n");
        printf("Para executar use: %s <fileA> <fileB> <fileX> <num_erro> <num_iteracoes> \n", argv[0]);
        return FAIL;
    }
    else
    {
        // Salve os parametros passados no console
        strcpy(fileA, argv[1]);
        strcpy(fileB, argv[2]);
        strcpy(fileX, argv[3]);
        erro = atof(argv[4]);
        iteracoes = atoi(argv[5]);
    }

    /*
       ==============================================================================
       =====                                                                    =====
       =====                        Execução do programa                        =====
       =====                                                                    =====
       ==============================================================================
       */

        ler(&a, &b, &x, fileA, fileB, fileX);
        //testeai(&a, &b, &x);

        // Faca a chamada da funcao para calcular a solucao do sistema
        jacobi(&a, &b, &x, erro, a.tam, solucao);
        resultado(&x);

        // Encerre o programa e retorne ao terminal
        return OK;
}
