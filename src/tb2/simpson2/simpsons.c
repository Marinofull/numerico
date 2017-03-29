#include <stdio.h>
#include <math.h>

int main()
{
  float x[11],y[11],sum=0,h,temp;
  int i,n,j,k=0;
  float fact(int);
  printf("\nN: ");
  scanf("%d",&n);
  for(i=0; i<n; i++)
  {
   printf("\nValor X%d: ",i);
   scanf("%f",&x[i]);
   printf("\nValor f(x%d): ",i);
   scanf("%f",&y[i]);
  }
  h=x[1]-x[0];
  n=n-1;
  sum = sum + y[0];
  for(i=1;i<n;i++)
  {
    if(k==0)
    {
     sum = sum + 4 * y[i];
     k=1;
    }
    else
    {
     sum = sum + 2 * y[i];
     k=0;
    }
   }
   sum = sum + y[i];
   sum = sum * (h/3);
   printf("\n\n  I = %f  ",sum);

   return 0;
}
