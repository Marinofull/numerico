#include <stdio.h>
#include <math.h>

int main()
{
  float x[10],y[10],sum=0,h,temp;
  int i,n,j,k=0,l=0;
  float fact(int);
  printf("N: ");
  scanf("%d",&n);
  for(i=0; i<n; i++)
  {
   printf("\n X%d: ",i);
   scanf("%f",&x[i]);
   printf("\n F(X%d): ",i);
   scanf("%f",&y[i]);
  }
  h=x[1]-x[0];
  n=n-1;
  sum = sum + y[0];
  for(i=1;i<n;i++)
  {
    if(k==0 || l==0)
    {
     sum = sum + 3 * y[i];
     if(k==1)
      {
       l=1;
      }
     k=1;
    }
    else
    {
     sum = sum + 2 * y[i];
     k=0;
     l=0;
    }
   }
   sum = sum + y[i];
   sum = sum * (3*h/8);
   printf("\n I = %f  ",sum);

   return 0;
}