// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO
// ALUNO: SAULO RIBEIRO DE ANDRADE

// TRABALHO PRATICO 2016.2 - PARTE 2

// Main.c
// Programa principal do trabalho pratico da disciplina CALCULO NUMERICO
// Para compilar use: make
// Para executar use: ./Main <arquivo_entrada> <A> <B> <N> onde
// <arquivo_entrada>: nome do arquivo que contem a definicao da integral a ser calculada
// <A>              : valor inicial do intervalo de integracao
// <B>              : valor final do intervalo de integracao
// <N>              : numero de subintervalos

#include "Polinomio.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	char nome_arquivo[256];
	float intA;
	float intB;
	int num_intervalos;

	char linha[256];
	char linha_ant[256];
	char *pedaco;

	FatorEquacao equacao[MAX_SIZE];
	int tam_equacao = 0;

	float num;
	float novoCoeficiente;
	float novoExpoente;

	float resultado = 0;

	int flag_coeficiente = 0;

	int pos = 0;

	if (argc != MAX_ARGC)
	{
		// Verifique se o numero de parametros passados no prompt de comando esta correto
		// Interrompa a execucao caso contrario
		printf("===================================================================================== \n");
		printf("Esperado %d parametros de entrada (%d dado(s)). \n", MAX_ARGC-1, argc-1);
		printf("Para compilar use: make \n");
		printf("Para executar use: %s <arquivo_entrada> <A> <B> <N> onde \n", argv[0]);
		printf("<arquivo_entrada>: nome do arquivo que contem a definicao da integral a ser calculada \n");
		printf("<A>              : valor inicial do intervalo de integracao \n");
		printf("<B>              : valor final do intervalo de integracao \n");
		printf("<N>              : numero de subintervalos \n");
		printf("===================================================================================== \n");
		return FAIL;
	}
	else
	{
		// Salve os parametros passados no console
		strcpy(nome_arquivo, argv[1]);
		intA = atof(argv[2]);
		intB = atof(argv[3]);
		num_intervalos = atoi(argv[4]);

	}

	fp = fopen(nome_arquivo, "r"); // Abra o arquivo de entrada
	if (fp == NULL)
	{
		// Verifique se o nome do arquivo corresponde a algum arquivo existente em disco
		// Se o arquivo nao existir, interrompa a execucao do programa
		printf("Erro: Arquivo de entrada nao existe. \n");
		return FAIL;
	}
	else
	{
		fgets(linha, 256, fp);
		while (strcmp(linha, linha_ant) != 0)
		{
			pedaco = strtok(linha, " ");
			while (pedaco != NULL)
			{
				num = atof(pedaco);
				if (flag_coeficiente == 0)
				{
					novoCoeficiente = num;
					flag_coeficiente = 1;
				}
				else
				{
					novoExpoente = num;
					flag_coeficiente = 0;
				}
				pedaco = strtok(NULL, " ");
			}
			inicializaFatorEquacao(&equacao[pos], novoCoeficiente, novoExpoente);
			pos++;
			strcpy(linha_ant, linha);
			fgets(linha, 255, fp);
		}
		tam_equacao = pos;
		fclose(fp);

		resultado = simpson1(equacao, intA, intB, num_intervalos, tam_equacao);
		printf("%f \n", resultado);
	}
	return OK;
}
