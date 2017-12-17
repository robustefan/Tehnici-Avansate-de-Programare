#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
ifstream f("cuv.in");

struct mat          // linia matricii corespunde unei litere si coloana unei alte litere,astfel, in ul[i][j] contorizam numarul de
{                   // cuvinte care se termina in char(i+'a')char(j+'a')
    int x,indice;
}ul[30][30];

int main()
{
    string s,v[100],sol[100];        // in v citim cuvintele din fisier
    int i = 0 , length[100],prev[100],n;     // length[i] = 1 + max{ length[j] cu j<i si ultimele 2 cuvinte ale lui v[j] coincid cu primele 2 litere
                                                // ale lui v[i]
    while( f >> v[i] )
    {
        ul[ v[i][ v[i].size() - 2 ] -'a'][ v[i][ v[i].size() - 1 ] -'a'].x ++;         // contorizam perechea formata din ultimele 2 litere ale cuvantului

        if(!ul[ v[i][ v[i].size() - 2 ] -'a'][ v[i][ v[i].size() - 1 ] -'a'].indice)
            ul[ v[i][ v[i].size() - 2 ] -'a'][ v[i][ v[i].size() - 1 ] -'a'].indice = i;   // tinem minte prima aparitie a grupului de cuvinte
        i++;
    }

    n = i;

    for ( i = 0 ; i < n ; i++)
        {
            length[i] = 1;          // lungimea subsirului maxim este initial 1
            prev[i]=-1;             // niciun element nu are predecesor
        }

    for( i = 1 ; i < n ; i++)
        if(  ul[ v[i][0] -'a'][ v[i][1] -'a'].x and ul[ v[i][0] -'a'][ v[i][1] -'a'].indice < i )
            {
                length[i] = length[ ul[ v[i][0] -'a'][ v[i][1] -'a'].indice ] + 1;      // daca elementul lungeste un subsir existent,atunci lungimea acelui
                prev[i] = ul[ v[i][0] -'a'][ v[i][1] -'a'].indice + 1;                  // subsir va creste cu 1; actualizam predecesorul elementului curent

                if( length[i] > length[ ul[ v[i][ v[i].size() - 2 ] -'a'][ v[i][ v[i].size() - 1 ] -'a'].indice] )
                    ul[ v[i][ v[i].size() - 2 ] -'a'][ v[i][ v[i].size() - 1 ] -'a'].indice = i;        // actualizam subsirul maxim curent de care un viitor
                                                                                                        // element se poate lega
            }

    int maxi = 0,nr;

    for( i = 0 ; i < n ; i++ )
    {
        if( length[i] > maxi )
            maxi = length[i];       // aflu lungimea subsirului maxim
    }

    for( i = 0 ; i < n ; i++ )
    {
        if( length[i] == maxi )
        {
            nr = i;             // subsirul maxim se termina pe pozitia nr
            break;
        }
    }

    sol[0] = v[nr];

    int k = 1;

    while( prev[nr] != -1 )         // pun solutia in ordinea aparitiei in vectorul solutie
    {
        sol[k++] = v[ prev[nr] -1 ] ;
        nr = prev[nr] -1;

    }

    for( i = k-1; i >= 0 ; i --)        //afisez solutia
        cout << sol[i]<<" ";
    return 0;
}
