#include <iostream>
#include <fstream>

using namespace std;

ifstream f("z.in");
ofstream g("z.out");

int divide( int length, int a, int b)
{
   int x;

   if( length == 2 )            // daca am ajuns la o subproblema de lungime 2, atunci putem rezolva problema ( tabla va fi de 2*2 ,deci avem 4 cadrane)
   {
       if( a == 1 && b == 1)    // punctul se afla pe pozitia [1][1] in noul tabel, adica in cadranul 1
            return 1;
       if( a == 1 && b == 2)    // punctul se afla pe pozitia [1][2] in nou tabel, adica in cadranul 2
            return 2;
       if( a == 2 && b == 1)    // punctul se afla pe pozitia [2][1] in noul tabel, adica in cadranul 3
            return 3;
       if( a == 2 && b == 2)    // punctul se afla pe pozitia [2][2] in noul tabel, adica in cadranul 4
            return 4;           // Practi, returnam numarul cadranului in care se afla
   }

   x = length * length / 4;     // altfel, impartim cadranul in care se afla punctul in alte 4 noi cadrane

   if( a <= length/2 && b <= length/2)              // punctul se afla in noul cadran 1
        return 0 * x + divide( length/2, a, b);     // punctul se afla deja in cadranul 1, deci niciun alt cadran nu a mai fost numerotat.

    if ( a <= length/2 && b > length/2)             // punctul se afla in noul cadran 2, deci 1 cadran de lungime length * length / 4 a mai fost numerotat
        return 1 * x + divide( length/2, a, b-length/2);

    if( a > length/2 && b <= length/2)              // punctul se afla in noul cadran 3, deci 2 cadrane de lungime length * length /4 au mai fost numerotate
        return 2 * x + divide( length/2, a-length/2, b);

    if( a > length/2 && b > length/2 )               // punctul se afla in noul cadran 4, deci 3 cadrane de lungime length * length /4 au mai fost numerotate
        return 3 * x + divide( length/2, a-length/2, b-length/2 );

}

int main()
{
    int n, k, i, a, b, length=1;

    f >> n >> k;

    for( i = 1; i <= n ;i++)        // dimensiunea tablei va fi 2^n
        length = length * 2;


    for( i = 0; i < k; i++)
    {
        f >> a >> b;            // citim coordonatele punctelor

        g << divide( length, a, b ) <<endl;     //gasim numarul corespunzator

    }

    return 0;
}
