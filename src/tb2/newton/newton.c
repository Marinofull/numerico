#include <iostream>

using namespace std;

int main()
{
    int n,i,j;
    float x[10],f[10],a,sum=0,mult;

    cout << "Numero de pontos: ";
    cin >> n;

    cout<<"Valores X: ";
    for(i=0;i<n;i++)
		cin>>x[i];

	cout<<"Valores f(X): ";
	for(i=0;i<n;i++)
		cin>>f[i];

    cout<<"X para calcular: ";
    cin>>a;

    for(j=0;j<n-1;j++) {
        for(i=n-1;i>j;i--)
            f[i]=(f[i]-f[i-1])/(x[i]-x[i-j-1]);
    }

    for(i=n-1;i>=0;i--) {
        mult=1;
        for(j=0;j<i;j++)
            mult*=(a-x[j]);

        mult*=f[j];
        sum+=mult;
    }

    cout << "Resultado: " << sum << endl;

    return 0;
}
