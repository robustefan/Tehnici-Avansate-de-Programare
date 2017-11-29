#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#define Nmax 100010
#define Inf 1<<30
using namespace std;
struct punct { int x, y;}  v[Nmax],w[Nmax];
int n;

int cmp (punct a, punct b)
{
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

double dist ( punct a, punct b)
{
    double difx=a.x-b.x;
    double dify=a.y-b.y;

    return sqrt ( difx*difx + dify*dify ) ;
}


double divide ( int st, int dr)
{
    if ( dr-st < 3 )
    {
        double D, Dmin=Inf;
        int i, j;

        for(i=st;i<dr;i++)
            for(j=i+1;j<=dr;j++)
            {
                D=dist(v[i],v[j]);
                if(D<Dmin) Dmin=D;
            }
        return Dmin;
    }


    int m=(st+dr)>>1;
    int d=v[m].x;

    double S1 = divide ( st, m ) ;
    double S2 = divide ( m+1, dr ) ;

    double S = S1;
    if(S2<S1) S=S2;

    int i,j=m+1,k=0;

    for(i=st;i<=m;i++)
        if( abs(v[i].x-d) <= S ) break;

    while( i <= m && j <= dr && abs(v[j].x-d) <= S )
        if( v[i].y < v[j].x ) w[++k]=v[i++];
        else                  w[++k]=v[j++];

    while ( i <= m ) w[++k]=v[i++];
    while ( j <= dr && abs(v[j].x-d) <= S ) w[++k]=v[j++];

    double D, Dmin=Inf;

    for(i=1;i<k;i++)
        for(j=i+1; j<=(i+7) && j<=k; j++)
        {
            D=dist(w[i],w[j]);
            if(D<Dmin) Dmin=D;
        }
    if(Dmin>S) Dmin=S;

    return Dmin;
}

int main()
{
    freopen("cmap.in","r",stdin);
    freopen("cmap.out","w",stdout);

    scanf("%d",&n);

    for(int i=1;i<=n;i++)
        scanf("%d %d",&v[i].x,&v[i].y);

    sort(v+1,v+n+1,cmp);

    printf("%0.6lf",divide(1,n));

    return 0;
}
