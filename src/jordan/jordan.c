#include <stdio.h>
#define MAX_LEN 50
//#define DEBUG__


void print(double matrix[MAX_LEN][MAX_LEN+1], int len) {
        for (int i = 0; i < len; i++) {
                for (int j = 0; j <= len; j++) {
                        printf("%lf ", matrix[i][j]);
                }
                printf("\n");
        }
        printf("\n");

}

void swap(double l1[MAX_LEN+1], double l2[MAX_LEN+1], int len) {
        double tmp;
        for (int i = 0; i <= len; i++) {
                tmp = l1[i];
                l1[i] = l2[i];
                l2[i] = tmp;
        }
}

int main (void) {

        double matrix[MAX_LEN][MAX_LEN+1], m;
        int len;

        scanf("%d", &len);

        for (int i = 0; i < len; i++) {
                for (int j = 0; j <= len; j++) {
                        scanf("%lf", &matrix[i][j]);
                }
        }

        for (int i = 0; i < len; i++) {
                if (matrix[i][i] == 0) {
                        swap(matrix[i], matrix[i+1], len);
                }

                for (int j = 0; j < len; j++) {
                        if (j == i) continue;
                        m = -matrix[j][i]/matrix[i][i];
                        for (int k = 0; k <= len; k++) {
                                matrix[j][k] = matrix[j][k] + (m*matrix[i][k]);
                        }
#ifdef DEBUG__
                        print(matrix, len);
#endif
                }
        }
        print(matrix, len);

        printf("x = [ ");
        for (int i = 0; i < len; i++) {
                printf("%lf ", matrix[i][len]/matrix[i][i]);
        }
        printf("]\n");

        return 0;
}
