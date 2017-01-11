// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO

// TRABALHO PRATICO 2016.2 - PARTE 1

// Main.c
// Programa principal do trabalho pratico da disciplina CALCULO NUMERICO
// Para compilar use: make
// Para executar use: ./jacobi [fileA] [num_erro] [num_iteracoes]

#include "Sistemalinear.h"

#define MAX_ARGC 5 // Numero de argumentos de entrada esperado

int main(int argc, char *argv[])
{
    char fileA[255];             // String do nome do arquivo
    char fileB[255];             // String do nome do arquivo
    float erro;                  // O algoritmo interrompe a sua execucao apos as solucoes estiverem abaixo da margem de erro informada
    int num_iteracoes;           // O algoritmo interrompe a sua execucao apos n iteracoes

    ma a;     // Matriz A
    mb b;     // Mbtriz B
    float vetor_solucao[MAXSIZE];// Array que guarda a solucao do sistema linear

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
    for (pos = 0; pos < MAXSIZE; pos++)
        vetor_solucao[pos] = 0;

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
        printf("Para executar use: %s <fileA> <fileB> <num_erro> <num_iteracoes> \n", argv[0]);
        return FAIL;
    }
    else
    {
        // Salve os parametros passados no console
        strcpy(fileA, argv[1]);
        strcpy(fileB, argv[2]);
        erro = atof(argv[3]);
        num_iteracoes = atoi(argv[4]);
    }

    /*
       ==============================================================================
       =====                                                                    =====
       =====                        Execução do programa                        =====
       =====                                                                    =====
       ==============================================================================
       */

        ler(&a, &b, fileA, fileB);
        testeai(&a, &b);

        // Faca a chamada da funcao para calcular a solucao do sistema
        //jacobi(a, b, erro, iteracoes, solucao);

        // Imprima na tela a solucao do sistema apos a execucao da funcao
        //for (pos = 0; pos < matriz_extendida.tam; pos++)
        //{
        //    printf("[ %4.6f ]", vetor_solucao[pos]);
        //}
        //printf("\n");

        // Encerre o programa e retorne ao terminal
        return OK;
}
