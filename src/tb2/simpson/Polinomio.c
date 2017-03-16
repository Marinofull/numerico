// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO
// ALUNO: SAULO RIBEIRO DE ANDRADE

// TRABALHO PRATICO 2016.2 - PARTE 2

// Polinomio.c
// Codigo fonte para manipulacoes de polinomios

#include "Polinomio.h"

int inicializaFatorEquacao(FatorEquacao *novoFator, float novoCoeficiente, float novoExpoente)
{
	novoFator->coeficiente = novoCoeficiente;
	novoFator->expoente = novoExpoente;
	return 0;
}

float potencia(float x, int n)
{
	int i;
	float resultado;

	resultado = 1.0;

	if (n == 0)
	{
		resultado = 1.0;
	}
	else if (n > 0)
	{
		for (i = 0; i < n; i++)
		{
			resultado = resultado * x;
		}
	}
	else
	{
		n = n * (-1);
		for (i = 0; i < n; i++)
		{
			resultado = resultado * x;
		}
		resultado = 1/resultado;
	}

	return resultado;
}

float simpson1(FatorEquacao pol_integral[], float a, float b, int n, int tam_pol_integral)
{
	/*
	Calcula pol_integral usando a regra de Simpson 1/3 (ou 1a Regra de Simpson)
	Entrada:
	-- pol_integral: vetor contendo os pares (coeficiente, expoente) a integral a ser calculado
	-- a: inicio do intervalo de integracao
	-- b: final do intervalo de integracao
	-- n: numero de subintervalos para divisao do intervalo de integracao
	-- tam_pol_integral: numero de fatores que compoem pol_integral
	Nota: para correta execucao do algoritmo, n deve ser par
	O algoritmo sera interrompido caso essa exigencia nao seja cumprida
	Retorna o resultado do calculo, ou zero (seguido de mensagem de erro) em caso de falha
	*/

	float somatorio; // Somatorio das imagens. Aplicado na formula para determinar o valor da integral
	float h; // "Altura" do trapezio. Usado para incrementar x a cada iteração do algoritmo
	float x; // Ponto do dominio da funcao. Usado para determinar imagens para somatorio
	float c; // Coeficiente da formula de simpson. Usado para determinar valores para somatorio
	float y; // Imagem de x na funcao. Usado para determinar valores para somatorio
	float resultado; // Resultado da integral, obtido pela aplicacao da formula de Simpson 1/3

	int i;   // Indice que registra o subintervalo de trabalho atual
	int pos; // Indice que navega pelo array pol_integral

	// Verifique se n eh par:
	if (n % 2 == 0)
	{
		// Se n for par, prossiga com a execucao do algoritmo:
		// 1. Determine h
		h = ((float)b - (float)a) / (float)n;

		// 2. Calcule o somatorio para a formula de Simpson 1/3
		somatorio = 0;
		x = (float)a;
		c = 0.0;

		// Calcule os "fragmentos" desse somatorio
		for (i = 0; i < n+1; i++)
		{
			// Determine o valor do coeficiente "c" conforme o valor da iteracao atual
			// Iteracao inicial/final (i = 0 ou i = n): c := 1
			// Iteracao par           (i % 2 = 0)     : c := 2
			// Iteracao impar         (else)          : c := 4
			if (i == 0 || i == n)
			{
				c = 1.0;
			}
			else if (i % 2 == 0)
			{
				c = 2.0;
			}
			else
			{
				c = 4.0;
			}

			// Determine o valor de f(x) na iteracao atual, conforme valores de "x" e "c"
			y = 0.0;
			for (pos = 0; pos < tam_pol_integral; pos++)
			{
				y += pol_integral[pos].coeficiente * potencia(x, pol_integral[pos].expoente);
			}

			/* === DEBUG ONLY === */
			printf("| I = %d | | X = %f | | Y = %f | | C = %f | \n", i, x, y, c);
			/* === DEBUG ONLY === */

			// Adicione o valor encontrado ao somatorio
			somatorio += y * c;

			// Incremente x e prossiga para a proxima iteracao
			x += h;
		}

		// Aplique a formula de Simpson e retorne o valor da integral encontrado
		resultado = (h * somatorio) / 3;
		return resultado;
	}
	else
	{
		// Se n nao for par, encerre imediatamente com mensagem de erro
		printf("Erro de execucao: numero de subintervalos deve ser par. \n");
		return 0;
	}
}