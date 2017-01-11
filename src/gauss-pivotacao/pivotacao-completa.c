#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

float **A; // Matriz de coeficientes
float *B; // Matriz de resultados
float *X; // Matriz com os valores das incógnitas
int N; // Dimensão da matriz A

int main() {
	int i, j, c, c2, x, hline, hcol;
	float mult, temp, hval;

	printf("Entre com o valor N\n");
	scanf("%d", &N);

	B = (float*) malloc(sizeof(float) * N);
	A = (float**) malloc(sizeof(float*) * N);
	X = (float*) malloc(sizeof(float) * N);

	for (i = 0; i < N; i++) {
		A[i] = (float*) malloc(sizeof(float) *N);
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

	for (c = 0; c < N-1; c++) {
		hval = 0;
		hline = 0;
		hcol = 0;

		for (c2 = c; c2 < N; c2++) {
			for (j = 0; j < N; j++) {
				if (abs(A[c2][j]) > abs(hval)) {
					hval = A[c2][j];
					hline = c2;
					hcol = j;
				}
			}
		}

		if (c != hline) {
			for (x = 0; x < N; x++) {
				temp = A[hline][x];
				A[hline][x] = A[c][x];
				A[c][x] = temp;
			}

			temp = B[hline];
			B[hline] = B[c];
			B[c] = temp;
		}

		for (i = c+1; i < N; i++) {
			mult = A[i][hcol] / A[c][hcol];
			B[i] -= mult * B[c];
			for (j = 0; j < N; j++) {
				A[i][j] -= mult * A[c][j];
			}
		}
	}

	for (int i = 0; i < N-1; i++) {
		if (A[i][i] == 0) {
			for (j = i + 1; j < N; j++) {
				if (A[j][i] != 0) {
					for (x = 0; x < N; x++) {
						temp = A[i][x];
						A[i][x] = A[j][x];
						A[j][x] = temp;
					}

					temp = B[i];
					B[i] = B[j];
					B[j] = temp;
				}
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

	printf("Resultado:\n");
	for(i = 0; i < N; i++) {
		printf("x%d: %.4f\n", (i+1), X[i]);
	}

	free(A);
    free(B);
    free(X);

    return 0;
}