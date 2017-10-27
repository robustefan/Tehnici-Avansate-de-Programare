#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <list>
using namespace std;

ifstream f("date.in");

class interval
{
    int ei,ef,sala;                     //clasa interval,unde avem si sala corespunzatoare intervalului

public:
    interval(){sala=0;};                //constructorul fara parametrii,necesar si pentru vector,setam sala cu 0
    friend bool operator >(interval,interval);                      //avem nevoie de overload pe operatori pentru functiile din STL Precum sort
    friend bool operator <(interval const&,interval const&);
    int get_ei() const{return ei;};                 //avem get si set pentru fiecare variabila privata
    int get_ef() const{return ef;};
    int get_sala() const{return sala;};
    void set_sala(int x){sala=x;};
    void set_ei(int x){ei=x;};
    void set_ef(int x){ef=x;};
    friend istream& operator>>(istream& in,interval& a);        //overload pe citirea si afisarea intervalelor
    friend ostream& operator<<(ostream& out,const interval a);
    friend struct compare;                                          //clasa prietena cu o "clasa",de fapt un struct,necesara pentru priority queue cu structura de minheap
};

struct compare
 {
   bool operator()(const interval & l, const interval& r)
   {
       return l.get_ef() > r.get_ef();
   }
 };

bool operator>(interval a,interval b)
{
    if( a.get_ei() > b.get_ei())
        return 1;
    else
        return 0;
}

bool operator<(interval const& a,interval const& b)
{
    if(a.get_ei() < b.get_ei())
        return 1;
    else
        return 0;
}


istream& operator >> (istream& in,interval &a)
{
    in >> a.ei >> a.ef;
    return in;
}

ostream& operator<<(ostream& out,const interval a)
{
    out << a.get_ei() << " " << a.get_ef() << endl;
    return out;
}

bool cmp(interval& a,interval& b)
{
    if(a.get_ei() < b.get_ei())
        return 1;
    return 0;
}

int main()
{
    priority_queue< interval , vector<interval> , compare > p;  //priority queue.Pe prima pozitie va fi mereu intervalul cu extremitatea finala minima
    int n,i=0;                                            //n= numarul intervalelor
    f>>n;
    interval x,a[100];                                  //avem un vector de intervale

    while(f>>x)
        a[i++]=x;                       //stocam intervalele intr-un vector


    std::sort(a,a+i);                   //se sorteaza crescator dupa extremitatea initiala vectorul (avem redefinit operatorul < )

    a[0].set_sala(1);                   //setam sala primului element cu 1
    p.push(a[0]);                       //punem in priority queue primul interval

    int k = 1;                            //k= numarul de clase de care avem nevoie

    for(i = 1; i < n ; i++)
        {
            if(a[i].get_ei() >= p.top().get_ef())        // daca extremitatea initiala este mai mare decat cea mai mica extremitate finala care exista intr-o
            {                                           // sala de clasa,atunci o putem adauga in acea sala de clasa si actualizam priority queue-ul
                a[i].set_sala( p.top().get_sala() );        // intervalul actual poate fi setat in aceeasi sala de clasa cu primul interval din queue
                p.pop();
                p.push(a[i]);                       // acum se reactualizeaza cea mai mica extremitate finala a unui interval dintr-o sala de clasa existenta
            }
            else
            {                       // inseamna ca va fi nevoie de o noua sala de clasa pentru acest interval
                k ++;
                a[i].set_sala(k);      // setam o noua sala de clasa pentru interval
                p.push(a[i]);           // adaugam intervalul in queue
            }
        }

    for(int j = 1; j <= k ; j++)           // acest pas nu este relevant,deoarece complexitatea poate ajunge mai mare decat O(n*log(n)),dar facem o afisare
    {
        for(i = 0 ; i < n ; i++)
            if(a[i].get_sala() == j)
                cout << "(" << a[i].get_ei() <<"," << a[i].get_ef() <<") ";
        cout<<endl;
    }
    return 0;
}
