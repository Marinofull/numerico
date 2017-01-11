#include "stdio.h"
#include "stdlib.h"

float **A; // Matriz de coeficientes
float *B; // Matriz de resultados
float *X; // Matriz com os valores das incógnitas
int N; // Dimensão da matriz A


int main() {
	int i, j, p;

	printf("Entre com o valor N\n");
	scanf("%d", &N);

    A = (float**) malloc(sizeof(float*) * N);
	B = (float*) malloc(sizeof(float) * N);
    X = (float*) malloc(sizeof(float) * N);

	for (i = 0; i < N; i++) {
		A[i] = (float*) malloc(sizeof(float) * N);
		X[i] = 0;
	}

	printf("Entre com a matriz A\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			scanf("%f", &A[i][j]);
		}
	}

	printf("Entre com a matriz B\n");
	for (i = 0; i < N; i++) {
		scanf("%f", &B[i]);
	}

	for (p = 0; p < N; p++) {

        int max = p;
        for (i = p + 1; i < N; i++) {
            if (abs(A[i][p]) > abs(A[max][p])) {
                max = i;
            }
        }

        if (p != max) {
            float temp;
            for (i = 0; i < N; i++) {
                temp = A[p][i];
                A[p][i] = A[max][i];
                A[max][i] = temp;
            }

            temp = B[p];
            B[p] = B[max];
            B[max] = temp;
        }

        for (i = p + 1; i < N; i++) {
            float alpha = A[i][p] / A[p][p];
            B[i] -= alpha * B[p];
            for (j = p; j < N; j++) {
                A[i][j] -= alpha * A[p][j];
            }
        }
    }

    for (i = N - 1; i >= 0; i--) {
        float sum = 0.0;
        for (j = i + 1; j < N; j++) {
            sum += A[i][j] * X[j];
        }
        X[i] = (B[i] - sum) / A[i][i];
    }

    printf("Resultado\n");
    for (i = 0; i < N; i++) {
        printf("X%d: %.4f\n", (i+1), X[i]);
    }

    free(A);
    free(B);
    free(X);

    return 0;
}