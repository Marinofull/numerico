#include <stdio.h>
#include <math.h>
#include <cmath> // ou <math.h>
#include <iostream>
#include <cstdlib>
#define N 6
double Pi;
double lroots[N];
double weight[N];
double lcoef[N + 1][N + 1] = {{0}};

void lege_coef()
{
	int n, i;
	lcoef[0][0] = lcoef[1][1] = 1;
	for (n = 2; n <= N; n++) {
		lcoef[n][0] = -(n - 1) * lcoef[n - 2][0] / n;
		for (i = 1; i <= n; i++)
			lcoef[n][i] = ((2 * n - 1) * lcoef[n - 1][i - 1]
					 - (n - 1) * lcoef[n - 2][i] ) / n;
	}
}

double lege_eval(int n, double x)
{
	int i;
	double s = lcoef[n][n];
	for (i = n; i; i--)
		s = s * x + lcoef[n][i - 1];
	return s;
}

double lege_diff(int n, double x)
{
	return n * (x * lege_eval(n, x) - lege_eval(n - 1, x)) / (x * x - 1);
}

void lege_roots()
{
	int i;
	double x, x1;
	for (i = 1; i <= N; i++) {
		x = cos(Pi * (i - .25) / (N + .5));
		do {
			x1 = x;
			x -= lege_eval(N, x) / lege_diff(N, x);
		} while (x != x1);
		/*  x != x1 is normally a no-no, but this task happens to be
		 *  well behaved. */
		lroots[i - 1] = x;

		x1 = lege_diff(N, x);
		weight[i - 1] = 2 / ((1 - x * x) * x1 * x1);
	}
}

double lege_inte(double (*f)(double), double a, double b)
{
	double c1 = (b - a) / 2, c2 = (b + a) / 2, sum = 0;
	int i;
	for (i = 0; i < N; i++)
		sum += weight[i] * f(c1 * lroots[i] + c2);
	return c1 * sum;
}
double gaussiana(double x) {
	return	((log(x)+(x*x))/((x+3)*(x+3)));
}

int main()
{
	int i,a,b;


	printf("Extremo esquerdo do intervalo: ");
	scanf("%d", &a);
	printf("Extremo direito do intervalo: ");
	scanf("%d", &b);
	Pi = 3.14;

	lege_coef();
	lege_roots();

	printf("No: ");
	for (i = 0; i < N; i++)
		printf(" %g", lroots[i]);

	printf("\nPeso:");
	for (i = 0; i < N; i++)
		printf(" %g", weight[i]);

	printf("\nIntegracao sobre [%d, %d]:\n\t%10.8f,\n",a,b,-lege_inte(gaussiana, a, b));
	return 0;
}
