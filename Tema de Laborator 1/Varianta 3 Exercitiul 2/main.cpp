#include <iostream>
#include <fstream>

using namespace std;

int v[1001], frunze[1001] ,depth[1001]   ;     // v este vectorul de "tati" , frunze este vectorul in care gasim frunzele

ifstream f("graf.in");

struct nod
{
    int x;
    nod * next;
}*prim[1001],*ultim[1001];

void adauga_sf(int x,int i)
{
    nod *p = new nod;
    if (!prim[i])
        prim[i] = ultim[i] = p;
    else
    {
        ultim[i]->next = p;
        ultim[i] = p;
    }

    p->x = x;
    p->next = 0;

}

int main()
{
    int n,x,y,i,cardinal=0,h;

    f >> n;             // n este numarul de varfuri al arborelui

    f >> x;             // x = radacina arborelui

    depth[x] = 1;       // radacina se afla pe nivelul 1

    f >> y;

    v[y] = x;

    depth [y] = depth [x] + 1;

    h = 2;                // arborele are cel putin 2 nivele ( radacina si o frunza )

    while(f >> x)
    {
        f >> y;
        v[y] = x;           //tatal lui y este x
        frunze[x] = 1;      //x nu poate fi frunza, x este tatal lui y
        depth [y] = depth [x] + 1;      // nivelul fiului este 1 + nivelul tatalui
    }

    for(i = 1 ; i <= n ; i++)
        {
            adauga_sf( i , depth[i] );          // vom face cate o lista simplu inlantuita corespunzatoare nivelelor arborelui
            if( depth[i] > h)
                h = depth[i];                 // h este nivelul maxim in arbore
        }

    for(i = h ; i >= 1; i--)        //mergem pe ultimul nivel al arborelui,unde sigur gasim frunze
    {
        nod * p = prim[i];
        while(p)                           // parcurgem arborele de la nivelul cel mai de jos.Cand gasim o frunza,o afisam
        {
            if( !frunze[p->x] )
            {
                cardinal ++;
                cout << p->x << " ";
                frunze[ v [ p->x ] ] = 1;          // tatal frunzei este adiacent cu frunza.Actiunea va fi echivalenta cu stergerea unui
                frunze[v[ v [ p->x ] ] ] = 0;       // element din lista de pe un nivel superior.
            }                               // "Pasam" atributul de frunza tatalui tatalui frunzei.Aceasta nu va fi adiacent cu frunza respectiva
        p = p->next;
        }
    }

    cout << endl << "Multimea maximala are cardinalul " << cardinal;
    return 0;
}
