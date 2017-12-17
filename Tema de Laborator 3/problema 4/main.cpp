#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

ifstream f("cuv.in");

int main()
{
    string s;
    int a[100][100], i, j, n, k = 2, cnt = 0;

    f >> s;
    n = s.size();

    for( i = 0 ; i < n ; i ++)
        {
            a[i][i] = 1;            // secventa de 1 litera este palindroma
            if ( s[i] == s[i+1])    // secventa de 2 litere care coincid este palindroma
                a[i][i+1] = 1;
            else
                a[i][i+1] = 0;
        }
                            // in acest moment am completat diagonala principala si diagonala principala + 1 a matricii
    while( k < n )
        {
            for( i = 0 ; i < n ; i ++)
                for ( j = i+k ; j < n ; j++)
                {
                    if( s[i] == s[j] and a[i+1][j-1])      // daca secventa de la i la j este palindroma si prima litera a secventei coincide cu ultima
                        a[i][j] = 1;                        // litera a secventei,atunci secventa este palindroma
                    else
                        a[i][j] = 0;
                }
            k++;
        }

    for( i = 0 ; i < n ; i++)
    {
        for( j = 0 ; j < n ; j++)       // numaram secventele palindrome
            if( a[i][j] )
                cnt++;
    }

    cout << "Cuvantul contine " << cnt << " secvente palindrome" << endl;

    if( a[0][n-1] )
    {
        cout << "Cuvantul este palindrom";
        return 0;
    }

    int c[n], sol[n];         //subp b)
    char v[2*n];

    for( i = 0 ; i < n ; i++)
        sol[i] = 0;

    for ( i = 0 ; i < n ; i++)
    {
        if( a[0][i] )       // secventa de la 0 la i este palindroma
            c[i] = 1;
        else
        {
            c[i] = INT_MAX;
            for( j = 0 ; j < i ; j++)
            {
                if( a[j+1][i] and c[i] > c[j] + 1)     // daca secventa de la j+1 la i este palindroma si secvente de la 0 la j se poate forma din mai putine
                    {                                  // cuvinte palindrome decat secventa de la 0 la i
                        c[i] = c[j] + 1;
                        sol[i] = j+1;
                    }
            }
        }
    }

    int nr = sol[n-1];
    j = n;
    k = 0;

    while(nr)
    {
        for( i = nr; i < j ; i++ )
            v[k++] = s[i];
        v[k++] = ' ';
        j = nr;
        nr = sol[nr-1];
    }

    for( i = nr; i < j ; i++ )
        v[k++] = s[i];

    for( i = k-1; i >= 0 ; i--)
        cout << v[i];

    return 0;
}
