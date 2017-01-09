#include "stdio.h"
#define MAX 200
float matrix[MAX][MAX],x[MAX],ml;
int omatrix;
void scan();
void gauss();
void print();
void solution();


int main(int argc, char const *argv[])
{
  scan();
  gauss();
  solution();
  return 0;
}
void scan()
{
  scanf("%d",&omatrix);
  for (int i = 1; i <= omatrix; i++) {
    for (int j = 1; j <= (omatrix+1); j++) {
      scanf("%f", &matrix[i][j]);
    }
  }
  //  print();
}
void gauss()
{

  for (int i = 1; i <= omatrix; i++){
    for (int j = i+1; j <= omatrix; j++) {
        ml = -1*(matrix[j][i]/matrix[i][i]);
        for (int y = 1; y <= omatrix+1; y++) {
          // printf("Linha: %d Coluna: %d\n",j,y );
          // printf("%f = (%f * %f) + %f\n",  matrix[j][y],ml,matrix[i][y],matrix[j][y]);
          matrix[j][y] =  (ml *  matrix[i][y]) + matrix[j][y];

          }
        }
      }
      // print();
  }
void solution(){
  x[omatrix]=matrix[omatrix][omatrix+1]/matrix[omatrix][omatrix ];
  for(int i=omatrix-1; i>=1; i--)
      {
          int sum=0;
          for(int j=i+1; j<=omatrix; j++)
          {
              sum=sum+matrix[i][j] * x[j];
          }
          x[i]=(matrix[i][omatrix+1]-sum)/matrix[i][i];
      }

      for(int i=1; i<=omatrix; i++)
      {
          printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
      }
}
void print()
{
  printf("\n");
  for (int i = 1; i <= omatrix; i++) {
    for (int j = 1; j <= (omatrix+1); j++) {
      printf("%f ", matrix[i][j]);
    }
    printf("\n");
  }
}
