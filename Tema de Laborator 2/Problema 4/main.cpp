#include<iostream>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<iomanip>

using namespace std;

ifstream f("cmap.in");
ofstream g("cmap.out");

#define Nmax 100010

struct punct
{
    int x, y;
}v[Nmax],w[Nmax],z[Nmax];           // in v vom tine minte toate punctele iar in w vom tine minte punctele aflate la distanta <= d fata de dreapta verticala

int n;      // numarul de puncte

bool cmpx (punct a, punct b)
{
    return a.x < b.x;           // folosita pentru a sorta punctele crescator dupa abscisa
}

bool cmpy(punct a, punct b)
{
    return a.y < b.y;       // folosita pentru a sorta punctele crescator dupa ordonata
}

long long dist ( punct a, punct b)
{
    long long difx = 1LL * (a.x - b.x );
    long long dify = 1LL * ( a.y - b.y );

    return  difx * difx + dify * dify ;         // calculeaza distanta euclidiana la patrat dintre 2 puncte
}


long long divide ( int st, int dr, punct y[])
{
    if( dr - st == 1)
        return dist( v[st], v[dr] );        // daca subproblema este de dimensiune 2, returnam distanta dintre cele 2 puncte

    if ( dr-st == 2 )                       // daca subproblema este de dimensiune 3, returnam distanta minima dintre cele 3 puncte
        return min(dist(v[st], v[st+1]),min(dist(v[st+1], v[dr]),dist(v[st], v[dr])));

    int m=( st + dr ) / 2;                  // impartim problema in 2 subprobleme

    punct yst[dr-st+10],ydr[dr-st+10];

    int i,p=0,q=0;

    for( i = st; i <= dr ; i++)
        if( y[i].x < y[m].x)
            yst[p++] = y[i];
        else
            ydr[q++] = y[i];

    long long S1 = divide ( st, m, yst ) ;
    long long S2 = divide ( m+1, dr ,ydr ) ;

    long long d = min( S1, S2);         // d va fi minimul dintre distanta minima a punctelor din stanga verticalei si distanta minima a punctelor din dreapta ei

    int j,k=0;

    long long delta = ceil(sqrt(d));


    for( i = st; i <= dr; i++)          // consideram toate punctele din subproblema actuala
    {
        if( abs( y[i].x - v[m].x ) <= delta )          // daca punctul v[i] se afla la distanta <= delta fata de verticala,atunci poate contribui la
            w[k++] = y[i];
                                                        // distanta minima a 2 puncte din plan; il adaugam in vectorul w
    }


    for(i = 0; i < k ; i++)             // pentru fiecare punct i consideram alte 7 puncte cu care ar putea avea distanta minima
        for(j = i + 1 ; j <= (i+7) && j < k; j++)
        {
            d = min(d,dist(w[i],w[j]));     // daca distanta dintre w[i] si w[j] <= distanta minima gasita pana acum,atunci reactualizam distanta minima
        }
    return d;           // returnam distanta minima
}

int main()
{
    f >> n;

    for ( int i = 0; i < n ;i++)            // citim cele n puncte
        {
            f >> v[i].x >> v[i].y;
            z[i].x = v[i].x;
            z[i].y = v[i].y;
        }

    sort(v,v+n,cmpx);           // sortam punctele dupa absicsa
    sort(z,z+n,cmpy);           // sortam punctele dupa ordonata

    g << fixed << setprecision(6) << sqrt(divide(0,n-1,z));       // afisam radical din distanta obtinuta
    return 0;
}
