#ifndef SISTEMALINEAR_H
#define SISTEMALINEAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL 1     // Retorno do programa em caso de erro
#define OK 0       // Retorno do programa em caso de exito
#define MAX_ARGC 4 // Numero de argumentos de entrada esperado
#define MAXSIZE 50 // Tamanho maximo da matriz

typedef struct listamatriz
{
	float chave[MAXSIZE][MAXSIZE];
	int tam_matriz;
} Matriz;

int initializeMatriz(Matriz *m);
int append(Matriz *m, float linha[], int tamlinha);
int swapLine(Matriz *m, int num_linha1, int num_linha2);
int swapCol(Matriz *m, int num_linha1, int num_linha2);
int rearrumaMatriz(Matriz *m);
int quicksort(float vetor[], int vetor_indice[], int esquerda, int direita);
int jacobi(Matriz *m, float erro, int iteracoes, float solucao[]);

#endif // SISTEMALINEAR_H
