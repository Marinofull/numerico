// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO
// ALUNO: SAULO RIBEIRO DE ANDRADE

// TRABALHO PRATICO 2016.2 - PARTE 2

// Polinomio.h
// Cabecalho das funcoes e definicoes

#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL 1
#define OK 0
#define MAX_ARGC 5
#define MAX_SIZE 20

typedef struct par
{
	float coeficiente;
	float expoente;
} FatorEquacao;

int inicializaFatorEquacao(FatorEquacao *novoFator, float novoCoeficiente, float novoExpoente);
float potencia(float x, int n);
float simpson1(FatorEquacao pol_integral[], float a, float b, int n, int tam_pol_integral);

#endif // POLINOMIO_H