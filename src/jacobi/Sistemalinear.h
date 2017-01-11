// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO

// TRABALHO PRATICO 2016.2 - PARTE 1

// Sistemalinear.h
// Cabecalho das funcoes e definicoes

#ifndef SISTEMALINEAR_H
#define SISTEMALINEAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL 1     // Retorno do programa em caso de erro
#define OK 0       // Retorno do programa em caso de exito
#define MAXSIZE 50 // Tamanho maximo da matriz

typedef struct ma
{
    float chave[MAXSIZE][MAXSIZE];
    int tam;
} ma;

typedef struct mb
{
    float chave[MAXSIZE];
    int tam;
} mb;

int initializeA(ma *m);
int initializeB(mb *m);
int appendA(ma *m, float linha[], int tamlinha);
int appendB(mb *m, float linha[], int tamlinha);
//int swap(Matriz *m, int num_linha1, int num_linha2);
int ler(ma *a, mb *b, mb *x, char *fileA, char *fileB, char *fileX);
int ha(char linha[], float linha_matriz[], int *tam_linha_matriz);
int jacobi(ma *a, mb *b, mb *x, float erro, int iteracoes, float solucao[]);
void testeai(ma *a, mb *b, mb *x);

#endif // SISTEMALINEAR_H
