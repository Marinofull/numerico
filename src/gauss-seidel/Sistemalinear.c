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
	/* Insere um array de elementos como uma nova linha na matriz */
	int li = m->tam_matriz;
	int pos;

	for (pos = 0; pos < tamlinha; pos++)
	{
		m->chave[li][pos] = linha[pos];
	}
	m->tam_matriz++;

	return OK;
}

int swapLine(Matriz *m, int indice1, int indice2)
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

int swapCol(Matriz *m, int indice1, int indice2)
{
	/* Troca os elementos da coluna indice1 pelos elementos da coluna indice2 */
	int pos;
	int temp;
	for (pos = 0; pos < MAXSIZE; pos++)
	{
		temp = m->chave[pos][indice1];
		m->chave[pos][indice1] = m->chave[pos][indice2];
		m->chave[pos][indice2] = temp;
	}
	return OK;
}

int rearrumaMatriz(Matriz *m)
{
	/* Troca as colunas da matriz, na tentativa de atender aos criterios de convergencia. */
	float lista_matriz[MAXSIZE];      // Salva os elementos da matriz na forma de um array unidimensional
	int indice_lista_matriz[MAXSIZE]; // Salva os indices dos elementos da matriz
	float novadiagonal[MAXSIZE];      // Salva os N maiores elementos da matriz. Estes elementos irão compor a nova diagonal principal.
	int li_novadiagonal[MAXSIZE];     // Salva os indices das linhas de novadiagonal
	int co_novadiagonal[MAXSIZE];     // Salva os indices das colunas de novadiagonal

	int li = 0;    // Indice de navegacao das linhas
	int co = 0;    // Indice de navegacao das colunas
	int index = 0; // Valor do indice do elemento na matriz
	int pos = 0;   // Indice de navegacao da posicao do elemento

	int size = 0;  // Tamanho do vetor lista_matriz (numero de elementos da matriz)

	// Preencha os vetores
	for (li = 0; li < m->tam_matriz; li++)
	{
		for (co = 0; co < m->tam_matriz; co++)
		{
			index = li*10 + co;
			lista_matriz[pos] = abs(m->chave[li][co]);
			indice_lista_matriz[pos] = index;
			pos++;
		}
	}

	// Usa-se o quicksort para efetuar a ordenacao do vetor de elemntos da matriz
	size = pos;
	quicksort(lista_matriz, indice_lista_matriz, 0, size-1);

	// Extraia os N maiores elementos e seus indices com base no resultado da ordenacao
	for (pos = 1; pos <= m->tam_matriz; pos++)
	{
		novadiagonal[pos-1] = lista_matriz[size-pos];
		li_novadiagonal[pos-1] = indice_lista_matriz[size-pos] / 10;
		co_novadiagonal[pos-1] = indice_lista_matriz[size-pos] % 10;
	}

	// Troque as colunas da matriz, de forma que os maiores elementos facam parte da diagonal principal.
	for (li = 0; li < m->tam_matriz; li++)
	{
		for (co = 0; co < m->tam_matriz; co++)
		{
			swapLine(m, li_novadiagonal[li], co_novadiagonal[co]);
			li_novadiagonal[li] = li;
			co_novadiagonal[co] = co;
		}
	}

	// Encerre e retorne a funcao anterior
	return OK;
}

int quicksort(float vetor[], int vetor_indice[], int esquerda, int direita)
{
	/* Ordena vetor usando quicksort. Vetor_indice sera arrumado seguindo os passos de ordenacao de vetor. Codigo principal extraido da wikipedia e adaptado para este trabalho. */
	int pivo = esquerda;
	int i, j, ch, chi;

	for (i = esquerda+1; i <= direita; i++)
	{
		j = i;
		if (vetor[j] < vetor[pivo])
		{
			ch = vetor[j];
			chi = vetor_indice[i];
			while (j > pivo)
			{
				vetor[j] = vetor[j-1];
				vetor_indice[j] = vetor_indice[j-1];
				j--;
			}
			vetor[j] = ch;
			vetor_indice[j] = chi;
			pivo++;
		}
	}
	if (pivo-1 >= esquerda)
	{
		quicksort(vetor, vetor_indice, esquerda, pivo-1);
	}
	if (pivo+1 <= direita)
	{
		quicksort(vetor, vetor_indice, pivo+1, direita);
	}
}

int gaussSaidel(Matriz *m, float erro, int iteracoes, float solucao[])
{
	/*
	Calcula a solucao do sistema linear representado pela matriz m
	e salva o resultado no array solucao, usando o metodo de Gauss-Saidel.
	Gauss-Saidel usa as solucoes obtidas na iteracao atual para refinar as solucoes que serao obtidas futuramente.
	Parametros de entrada da funcao:
	-- Matriz m: endereco da matriz extendida do sistema a ser resolvido
	-- float erro: o algoritmo encerra a sua execucao apos a solucao estar abaixo da margem de erro especificada
	-- int iteracoes: o algoritmo encerra a sua execucao apos n iteracoes
	-- float solucao[]: array onde sera salvo a solucao do sistema
	*/
	float nova_solucao[MAXSIZE]; // Solucao do sistema na iteracao atual
	float vetor_erro[MAXSIZE]; // Diferenca entre solucao atual e solucao anterior. Usado como criterio de parada do algoritmo

	int pode_sair = 1; // Flag de encerramento do algoritmo [0: Sim / 1: Nao]

	int li = 0; // Indice de navegacao da linha da matriz
	int co = 0; // Indice de navegacao da coluna da matriz
	int pos = 0; // Indice de navegacao de um elemento da matriz

	/* Inicializacao dos arrays */
	for (pos = 0; pos < m->tam_matriz; pos++)
	{
		nova_solucao[pos] = 0;
		vetor_erro[pos] = 0;
	}

	// Continue calculando a solucao ate o erro da solucoes for menor que o erro especificado, ou ate o numero maximo de iteracoes for atingido.
	while ((pode_sair == 1) && (iteracoes > 0))
	{
		// Calculo da solucao da iteracao
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

			// Calculo do erro entre as solucoes
			if (nova_solucao[li] > solucao[li])
			{
				vetor_erro[li] = nova_solucao[li] - solucao[li];
			}
			else
			{
				vetor_erro[li] = solucao[li] - nova_solucao[li];
			}

			// Atualize a solucao obtida
			solucao[li] = nova_solucao[li];
		}

		pode_sair = 1;

		// Verifique se o criterio de erro foi atingido
		for (li = 0; li < m->tam_matriz; li++)
		{
			if (vetor_erro[li] < erro)
			{
				pode_sair = 0;
			}
			else
			{
				pode_sair = 1;
			}
		}
		iteracoes--;
	}

	// Verifique qual foi a condicao de parada atingida, determinando se a solucao obtida convergiu para a solucao real. Encerre o programa e retorne para main.c
	if (pode_sair == 0)
	{
		// Criterio de erro atingido
		// Solucao obtida convergiu.
		return OK;
	}
	else
	{
		// Criterio de iteracoes atingido
		// Solucao obtida divergiu.
		return FAIL;
	}
}
