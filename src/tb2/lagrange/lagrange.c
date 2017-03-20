#include <stdio.h>

int main()
{
    float x[50],y[50],a,s=1,t=1,k=0;
    int n,i,j;

    printf("Entre como o tamanho da tabela ou -1 para sair\n");
    scanf("%d",&n);
    while(n != -1)
    {
        for(i=0; i<n; i++)
        {
            scanf ("%f",&x[i]);
            scanf("%f",&y[i]);
        }
        for(i=0; i<n; i++)
        {
            printf("%0.3f\t%0.3f\n",x[i],y[i]);
        }
        printf("\n");
        scanf("%f",&a);
        for(i=0; i<n; i++)
        {
            s=1;
            t=1;
            for(j=0; j<n; j++)
            {
                if(j!=i)
                {
                    s=s*(a-x[j]);
                    t=t*(x[i]-x[j]);
                }
            }
            k=k+((s/t)*y[i]);
        }
        printf("O valor de y é: %f\n",k);
        printf("Entre como o tamanho da tabela ou -1 para sair\n");
        scanf("%d", &n);
    }
}
