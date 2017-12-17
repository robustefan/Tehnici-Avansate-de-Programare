#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ifstream f("date.in");
int main()
{
    int n, m, i, j, a[100][100], b[100][100] ,coord1 = -1, coord2 = -1, dim = 0;

    f >> n >> m;
    for( i = 1 ; i <= n ; i++)
        for( j = 1 ; j <= m ; j++)
            {
                f >> a[i][j];                   // citim matricea
                a[i][j] = abs( a[i][j] - 1);    // transformam fiecare 0 in 1 si fiecare 1 in 0
            }

    for( i = 1 ; i <=n ; i++)
    {
        b[i][0] = 0;                //bordam matricea b cu 0 pe linia si coloana 0
        b[0][i] = 0;
    }

    for( i = 1 ; i <= n ; i++)
        for( j = 1 ; j <= m ; j++)
            if( !a[i][j] )              // daca a[i][j] este 0 ,atunci copiem 0 in matricea b
                b[i][j] = 0;
            else
            {
                b[i][j] = min( b[i-1][j], b[i-1][j-1]);     // daca a[i][j] este 1,atunci b[i][j] = min{ b[i-1][j],b[i-1][j-1],b[i][j-1]}+1
                b[i][j] = min( b[i][j], b[i][j-1]) + 1;     // deci ,daca vecinul din Nord, Nord-Vest si cel din Vest sunt diferiti de 0,atunci sigur
            }                                               // b[i][j] inchide un patrat de latura min{...} + 1

    int maxi = 0;
    for( i = 0 ; i <= n ; i++)
        {
            for( j = 0 ; j <= m ; j++)
                if( b[i][j] > maxi )            //cautam latura maxima in matricea b
                    {
                        maxi = b[i][j];
                        coord1 = i - maxi + 1;      // gasim coordonatele din stanga sus a patratului
                        coord2 = j - maxi + 1;
                    }
        }

    cout << maxi << endl << coord1 << " " << coord2 << endl;

    int k, cnt = 0;
    f >> k;

    for( i = 1 ; i <= n ; i++)
        for( j = 1 ; j <= m ; j++)          // vedem cate patrate cu latura >=k exista
            if( b[i][j] >= k )
                cnt = cnt + b[i][j] - k + 1;

    cout << "Matricea contine " << cnt << " patrate de latura >= " << k ;


    return 0;
}
