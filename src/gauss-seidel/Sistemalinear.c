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

int gaussSaidel(Matriz *m, float erro, int iteracoes, float solucao[])
{
	/*
	Calcula a solucao do sistema linear representado pela matriz m
	e salva o resultado no array solucao, usando o metodo de Gauss-Saidel.
	Parametros de entrada da funcao:
	-- Matriz m: endereco da matriz extendida do sistema a ser resolvido
	-- float erro: o algoritmo encerra a sua execucao apos a solucao estar abaixo da margem de erro especificada
	-- int iteracoes: o algoritmo encerra a sua execucao apos n iteracoes
	-- float solucao[]: array onde sera salvo a solucao do sistema
	*/
	float nova_solucao[MAXSIZE];
	float vetor_erro[MAXSIZE];
	int pode_sair = 1;
	int li = 0;
	int co = 0;
	int pos = 0;

	/* Inicializacao dos arrays */
	for (pos = 0; pos < m->tam_matriz; pos++)
	{
		nova_solucao[pos] = 0;
		vetor_erro[pos] = 0;
	}

	while ((pode_sair != 0) && (iteracoes > 0))
	{
		// Calculo da solucao da iteracao
		// Calculo do erro entre as solucoes
		for (li = 0; li < m->tam_matriz; li++)
		{
			nova_solucao[li] = m->chave[li][m->tam_matriz];
			for (co = 0; co < m->tam_matriz; co++)
			{
				if (li != co)
				{
					nova_solucao[li] -= m->chave[li][co] * nova_solucao[co];
				}
			}
			nova_solucao[li] = nova_solucao[li]/m->chave[li][li];
			if (nova_solucao[li] > solucao[li])
			{
				vetor_erro[li] = nova_solucao[li] - solucao[li];
			}
			else
			{
				vetor_erro[li] = solucao[li] - nova_solucao[li];
			}
			solucao[li] = nova_solucao[li];
		}
		pode_sair = 0;

		/* DEBUG ONLY */
		int i;

		printf("I:%d ", iteracoes);

//		printf("S:");
//		for (i = 0; i < m->tam_matriz; i++)
//		{
//			printf("[ %4.6f ]", solucao[i]);
//		}

		printf(" E:");
		for (i = 0; i < m->tam_matriz; i++)
		{
			printf("[ %4.6f ]", vetor_erro[i]);
		}

		printf("\n");
		/* DEBUG ONLY */

		// Verifique se o criterio de erro foi atingido
		for (li = 0; li < m->tam_matriz; li++)
		{
			if (vetor_erro[li] > erro)
			{
				pode_sair = 1;
			}
		}
		iteracoes--;
	}
	// Encerre o programa e retorne para main.c
	return OK;
}