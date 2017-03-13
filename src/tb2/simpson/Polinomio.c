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
	int resultado;

	resultado = 1;

	for (i = 0; i < n; i++)
	{
		resultado = resultado * x;
	}

	return resultado;
}

float simpson1(FatorEquacao pol_integral[], int a, int b, int n, int tam_pol_integral)
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

	float somatorio; // Somatorio das imagens
	float h; // "Altura" do trapezio
	float x; // Ponto do dominio da funcao
	float c; // Coeficiente da formula de simpson
	float y; // Imagem de x na funcao
	float resultado; // Resultado da integral

	int i;
	int pos;

	// Verifique se n eh par:
	if (n % 2 == 0)
	{
		// Calcule h
		h = ((float)b - (float)a) / (float)n;

		// Calcule o somatorio
		somatorio = 0;
		x = (float)a;
		c = 0;

		for (i = 0; i < n+1; i++)
		{
			if (i == 0 || i == n)
			{
				c = 1;
			}
			else if (i % 2 == 0)
			{
				c = 2;
			}
			else
			{
				c = 4;
			}
			y = 0;
			for (pos = 0; pos < tam_pol_integral; pos++)
			{
				y = pol_integral[pos].coeficiente * potencia(x, pol_integral[pos].expoente);
			}
			somatorio += y * c;
			x += h;
		}

		// Aplique a formula de Simpson
		resultado = (h * somatorio) / 3;
		return resultado;
	}
	else
	{
		printf("Erro de execucao: numero de subintervalos deve ser par. \n");
		return 0;
	}
}