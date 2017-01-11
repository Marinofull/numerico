// UNIVERSIDADE FEDERAL DA BAHIA
// MAT174 - CALCULO NUMERICO
// PROFESSORA: RITA DE CASSIA NOVAES BARRETO

// TRABALHO PRATICO 2016.2 - PARTE 1

// Sistemalinear.c
// Codigo-fonte das funcoes para manipulacao de matrizes
// e resolucao de sistemas lineares

#include "Sistemalinear.h"

int initializeA(ma *m)
{
    /* Inicializa a matriz */
    m->tam = 0;
    return OK;
}

int initializeB(mb *m)
{
    /* Inicializa a matriz */
    m->tam = 0;
    return OK;
}

int appendA(ma *m, float linha[], int tamlinha)
{
    /* Insere um array de elementos na matriz */
    int li = m->tam;
    int pos;

    for (pos = 0; pos < tamlinha; pos++)
        m->chave[li][pos] = linha[pos];

    m->tam++;

    return OK;
}

int appendB(mb *m, float linha[], int tamlinha)
{
    /* Insere um array de elementos na matriz */
    int li = m->tam;
    int pos;

    for (pos = 0; pos < tamlinha; pos++)
        m->chave[li] = linha[pos];

    m->tam++;

    return OK;
}

//int swap(Matriz *m, int indice1, int indice2)
//{
//    /* Troca os elementos da linha indice1 pelos elementos da linha indice2 */
//    int pos;
//    int temp;
//    for (pos = 0; pos < MAXSIZE; pos++)
//    {
//        temp = m->chave[indice1][pos];
//        m->chave[indice1][pos] = m->chave[indice2][pos];
//        m->chave[indice2][pos] = temp;
//    }
//    return OK;
//}

int ler(ma *a, mb *b, mb *x, char *fileA, char *fileB, char *fileX){
    FILE *fpa, *fpb;                    // Ponteiro do arquivo de entrada

    char linha[255];             // String que guarda a ultima linha lida do arquivo
    char linha_ant[255];         // String que guarda a penultima linha lida do arquivo

    float linha_matriz[MAXSIZE]; // Linha dos inteiros extraidos do arquivo de entrada
    int tam_linha_matriz = 0;  // Guarda o tamanho da linha lida do arquivo de entrada

    //lê a matriz A
    int pos;
    for (pos = 0; pos < MAXSIZE; pos++)
        linha_matriz[pos] = 0;

    fpa = fopen(fileA, "r"); // Abra o arquivo de entrada

    if (!fpa)
    {
        // Verifique se o nome do arquivo corresponde a algum arquivo existente em disco
        // Se o arquivo nao existir, interrompa a execucao do programa
        printf("Erro: Arquivo de entrada nao existe.\n");
        return FAIL;
    }
    else
    {
        fgets(linha, 255, fpa);                                        // Leia uma linha do arquivo
        while (strcmp(linha, linha_ant))                               // Verifique se essa linha ja foi processada (chegou no fim do arquivo)
        {
            ha(linha, linha_matriz, &tam_linha_matriz);

            appendA(a, linha_matriz, tam_linha_matriz); // Insira os elementos extraidos na matriz
            strcpy(linha_ant, linha);                                  // Coloque essa linha como ja processada
            fgets(linha, 255, fpa);                                     // Leia a proxima linha
        }
        fclose(fpa);                                                    // Feche o arquivo
    }

    //lê o vetor b
    tam_linha_matriz = 0;
    for (pos = 0; pos < MAXSIZE; pos++)
        linha_matriz[pos] = 0;

    fpb = fopen(fileB, "r"); // Abra o arquivo de entrada

    if (!fpb)
    {
        printf("Erro: Arquivo de entrada nao existe.\n");
        return FAIL;
    }
    else
    {
        fgets(linha, 255, fpa);                                        // Leia uma linha do arquivo
        while (strcmp(linha, linha_ant))                               // Verifique se essa linha ja foi processada (chegou no fim do arquivo)
        {
            ha(linha, linha_matriz, &tam_linha_matriz);

            appendB(b, linha_matriz, tam_linha_matriz); // Insira os elementos extraidos na matriz B
            strcpy(linha_ant, linha);                                  // Coloque essa linha como ja processada
            fgets(linha, 255, fpa);                                     // Leia a proxima linha
        }
        fclose(fpb);                                                    // Feche o arquivo
    }

    //lê o vetor X
    tam_linha_matriz = 0;
    for (pos = 0; pos < MAXSIZE; pos++)
        linha_matriz[pos] = 0;

    fpb = fopen(fileX, "r"); // Abra o arquivo de entrada

    if (!fpb)
    {
        printf("Erro: Arquivo de entrada nao existe.\n");
        return FAIL;
    }
    else
    {
        fgets(linha, 255, fpa);                                        // Leia uma linha do arquivo
        while (strcmp(linha, linha_ant))                               // Verifique se essa linha ja foi processada (chegou no fim do arquivo)
        {
            ha(linha, linha_matriz, &tam_linha_matriz);

            appendB(x, linha_matriz, tam_linha_matriz); // Insira os elementos extraidos na matriz B
            strcpy(linha_ant, linha);                                  // Coloque essa linha como ja processada
            fgets(linha, 255, fpa);                                     // Leia a proxima linha
        }
        fclose(fpb);                                                    // Feche o arquivo
    }

    return OK;
}

int ha(char linha[], float linha_matriz[], int *tam_linha_matriz){
    char *pedaco;                // String para guardar os numeros contidos nas linhas do arquivo
    float num;                   // Inteiro para guardar a string pedaco apos conversao
    int pos = 0;                 // Indice temporario para o array linha_matriz

    pedaco = strtok(linha, " ");                               // Extraia um dos numeros da linha usando essa funcao
    while (pedaco)                                             // Repita ate processar todos os numeros da linha
    {
        num = atof(pedaco);                                    // Converta a string lida em um inteiro
        linha_matriz[pos] = num;                               // Atribua a sua posicao correta na matriz
        pos++;                                                 // Incremente o indice de coluna
        pedaco = strtok(NULL, " ");                            // Extraia outro numero
    }
    *tam_linha_matriz = pos;                                   // Salve a quantidade de elementos extraidos da linha do arquivo

    return OK;
}

mb* jacobi(ma *a, mb *b, mb *x, float erro, int iteracoes, float solucao[]){
    int continuar = 1, ni = 0, i, j, n = a->tam, soma;
    float nx[n], erros[n];

    while (continuar && ni<iteracoes){
        for (i =0; i<n; i++){
            soma = 0;
            for (j=0; j<n; j++){
                if (i!=j)
                    soma += a->chave[i][j] * x->chave[j] / a->chave[i][i];
                nx[i] = (b->chave[i]/a->chave[i][i]) - soma;
            }
            erros[i] = nx[i] - x->chave[i];
            //modulo do erro
            if (erros[i] < 0)
                erros[i] = erros[i] * -1;
        }
        for (i=0; i<n; i++)
            if (erros[i] < erro)
                continuar = 0;
        ni++;
    }

    mb *res;
    res = (mb*) malloc(sizeof(mb));
    initializeB(res);
    for (i=0; i < a->tam; i++)
        res->chave[i] = nx[i];
    res->tam = a->tam;
    printf("rodei %d vezes\n", ni);

    return res;
}

/*
int jacobi(ma *a, mb *b, mb *x, float erro, int iteracoes, float solucao[]){
    float novoVetorX[iteracoes], erros[iteracoes];
    int continuar = 1;

    //TODO
    //iteracoes = a->tam;
    //rever se o N do pseudocodigo é o numero de equacoes ou iteracoes
    //int qtd=0;
    while(continuar){
        int i, j;
        for(i=0; i<iteracoes; i++){
            novoVetorX[i]=b->chave[i];
            for(j=0; j<iteracoes; j++)
                if (i!=j)
                    novoVetorX[i] = novoVetorX[i] - (a->chave[i][j] * x->chave[i]);
            novoVetorX[i] = novoVetorX[i] / a->chave[i][i];
            erros[i] = novoVetorX[i] - x->chave[i];

            //modulo do erro
            if (erros[i] < 0)
                erros[i] = erros[i] * -1;

            x->chave[i] = novoVetorX[i];
        }

        for(i=0; i<iteracoes; i++)
        printf("erros[%d] %f\n", i, erros[i]);
        printf("erro %f\n", erro);
        //if (qtd > 5)
        //    return 0;

        for(i=0; i<iteracoes; i++)
            if (erros[i] < erro)
                continuar = 0;
        //if (podesair)
        //    return OK;
        //qtd++;
    }

    return OK;
}
*/

void testeai(ma *a, mb *b, mb *x){
    int i, j;

    for(i=0; i< a->tam; i++){
        for(j=0; j< a->tam; j++)
            printf("%f ", a->chave[i][j]);
        printf("\n");
    }

    for(i=0; i< b->tam; i++){
            printf("%f ", b->chave[i]);
        printf("\n");
    }

    for(i=0; i< x->tam; i++){
            printf("%f ", x->chave[i]);
        printf("\n");
    }
}

void resultado(mb *x){
    int i;
    for(i=0; i< x->tam; i++){
            printf("[%4.6f] ", x->chave[i]);
        printf("\n");
    }
}
