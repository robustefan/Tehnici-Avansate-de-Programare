#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream f("joculet.in");

int main()
{
    int n, i, j, k = 2;

    f >> n;

    int d[n+1][n+1];        // d[i][j] = tabela cu j elemente care incepe pe pozitia i

    for( i = 1 ; i <= n ; i++)
        f >> d[1][i];       // tabela formata dintr-un singur element.Jucatorul curent o poate castiga cu d[1][i] puncte

    for( i = 1 ; i < n ; i++)
        d[2][i] = abs( d[1][i] - d[1][i+1] );   // jucatorul curent poate castiga tabela cu | d[1][i] - d[1][i+1] | puncte

    for( i = 3 ; i <= n ; i++)
        {
            for( j = 1 ; j <= n-k; j++)
                d[i][j] = max( d[1][j] - d[i-1][j+1] , d[1][i+j-1] - d[i-1][j]);   // daca jucatorul alege primul element al tabelei curente,
            k++;                                                                    // ii lasa celuilalt jucator tabela cu 1 element mai putin care incepe
                                                                                    // de pe pozitia j+1
        }                                                                           // daca alege ultimul element,ii lasa celuilalt jucator tabela cu 1
                                                                                // element mai putin care incepe cu j
    k = 0;
    for ( i = 1 ; i <= n ; i++)
        {
            for( j = 1 ; j <= n - k; j++)
                cout << d[i][j] << " ";
            cout << endl;
            k++;
        }

    int cnt = 0, s1 = 0, s2 = 0 ,alegere;
    int primul = 1, ultimul = n;
    int p = 1, u = 2;
    i = n;

    int dif = d[n][1];          // primul jucator stie sigur ca va castiga cu minim aceasta diferenta

    if ( dif < 0 )
        {
            cout << "Calculatorul va pierde ";      // inseamna ca primul jucator va pierde daca al 2 jucator va juca optim
            return 0;
        }
    else
        cout << endl << "Calculatorul castiga cu minim " << dif <<" puncte " << endl;

    for ( i = 0 ; i <= n+1 ; i++)
        d[0][i] = 0;

    i = n;

    while(i)
    {
        if( !(cnt % 2 ) )
        {
            if( d[1][primul] - d[i-1][u] == d[i][p] )
                {
                    cout << "Calculatorul alege " << d[1][primul] << endl;
                    s1 = s1 + d[1][primul];
                    primul++;
                    p = u;
                    u++;
                }
            else
                if( d[1][ultimul] - d[i-1][p] == d[i][p])
            {
                cout << "Calculatorul alege " << d[1][ultimul] << endl;
                s1 = s1 + d[1][ultimul];
                ultimul --;
            }
            cnt++;

        }
        else
        {
                cin >> alegere;
                if( alegere % 2 )
                {
                    cout << "Jucatorul alege " << d[1][primul] << endl << endl;
                    s2 = s2 + d[1][primul];
                    primul++;
                    p = u;
                    u ++;
                }
                else
                {
                    cout << "Jucatorul alege " << d[1][ultimul] << endl << endl;
                    s2 = s2 + d[1][ultimul];
                    ultimul --;
                }

            cout << "Calculatorul castiga cu minim " << s1 - s2 + d[i-1][p] <<" puncte " << endl;

            cnt++;
        }

        i--;
    }

    cout << s1 << " " << s2;

    return 0;
}
