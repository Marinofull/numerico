#include "Sistemalinear.h"

int main(int argc, char *argv[])
{
	FILE *fp;                    // Ponteiro do arquivo de entrada
	char nome_arquivo[255];      // String do nome do arquivo
	float erro;                  // O algoritmo interrompe a sua execucao apos as solucoes estiverem abaixo da margem de erro informada
	int num_iteracoes;           // O algoritmo interrompe a sua execucao apos n iteracoes

	char linha[255];             // String que guarda a ultima linha lida do arquivo
	char linha_ant[255];         // String que guarda a penultima linha lida do arquivo
	char *pedaco;                // String para guardar os numeros contidos nas linhas do arquivo

	float num;                   // Inteiro para guardar a string pedaco apos conversao
	float linha_matriz[MAXSIZE]; // Linha dos inteiros extraidos do arquivo de entrada
	float tam_linha_matriz = 0;  // Guarda o tamanho da linha lida do arquivo de entrada

	Matriz matriz_extendida;     // Matriz extendida do sistema do arquivo de entrada
	float vetor_solucao[MAXSIZE];// Array que guarda a solucao do sistema linear

	int li = 0;                  // Indice da linha da matriz
	int co = 0;                  // Indice da coluna da matriz
	int pos = 0;                 // Indice temporario para o array linha_matriz

	int convergencia = 0; // Flag que indica se houve convergencia na solucao obtida

	/*
	==============================================================================
	=====                                                                    =====
	=====                Inicializacao da matriz e arrays                    =====
	=====                                                                    =====
	==============================================================================
	*/
	initializeMatriz(&matriz_extendida);
	for (pos = 0; pos < MAXSIZE; pos++)
	{
		linha_matriz[pos] = 0;
		vetor_solucao[pos] = 0;
	}
	pos = 0;

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
		printf("Esperado %d parametros de entrada (%d dado(s)). \n", MAX_ARGC-1, argc-1);
		printf("Para compilar use: make \n");
		printf("Para executar use: %s [nome_arquivo_entrada] [num_erro] [num_iteracoes]. \n", argv[0]);
		return FAIL;
	}
	else
	{
		// Salve os parametros passados no console
		strcpy(nome_arquivo, argv[1]);
		erro = atof(argv[2]);
		num_iteracoes = atoi(argv[3]);
	}

	/*
	==============================================================================
	=====                                                                    =====
	=====                        Execução do programa                        =====
	=====                                                                    =====
	==============================================================================
	*/

	// Monte a matriz extendida do sistema a partir desse arquivo
	fp = fopen(argv[1], "r"); // Abra o arquivo de entrada
	if (fp == NULL)
	{
		// Verifique se o nome do arquivo corresponde a algum arquivo existente em disco
		// Se o arquivo nao existir, interrompa a execucao do programa
		printf("Erro: Arquivo de entrada nao existe. \n");
		return FAIL;
	}
	else
	{
		fgets(linha, 255, fp);                                         // Leia uma linha do arquivo
		while (strcmp(linha, linha_ant) != 0)                          // Verifique se essa linha ja foi processada (chegou no fim do arquivo)
		{
			pedaco = strtok(linha, " ");                               // Extraia um dos numeros da linha usando essa funcao
			while (pedaco != NULL)                                     // Repita ate processar todos os numeros da linha
			{
				num = atof(pedaco);                                    // Converta a string lida em um inteiro
				linha_matriz[pos] = num;                               // Atribua a sua posicao correta na matriz
				pos++;                                                 // Incremente o indice de coluna
				pedaco = strtok(NULL, " ");                            // Extraia outro numero
			}
			tam_linha_matriz = pos;                                    // Salve a quantidade de elementos extraidos da linha do arquivo
			append(&matriz_extendida, linha_matriz, tam_linha_matriz); // Insira os elementos extraidos na matriz
			pos = 0;                                                   // Reinicie o indice da linha do arquivo
			strcpy(linha_ant, linha);                                  // Coloque essa linha como ja processada
			fgets(linha, 255, fp);                                     // Leia a proxima linha
		}
		fclose(fp);                                                  // Feche o arquivo

		// Faca a chamada da funcao para calcular a solucao do sistema
		convergencia = jacobi(&matriz_extendida, erro, num_iteracoes, vetor_solucao);

		// Verifique se houve divergencia na solucao calculada.
		// Se houve, rearrume a matriz e recalcule a solucao
		if (convergencia != 0)
		{
			rearrumaMatriz(&matriz_extendida);
			jacobi(&matriz_extendida, erro, num_iteracoes, vetor_solucao);
		}

		// Imprima na tela a solucao do sistema apos a execucao da funcao
		for (pos = 0; pos < matriz_extendida.tam_matriz; pos++)
		{
			printf("[ %4.6f ]", vetor_solucao[pos]);
		}
		printf("\n");

	// Encerre o programa e retorne ao terminal
	return OK;
	}
}
