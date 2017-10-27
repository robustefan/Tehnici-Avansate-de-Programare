#include <iostream>
#include <fstream>
#include <deque>
#include <random>
using namespace std;

ifstream f("joc.in");

int main()
{
    int i=1,suma_para=0,suma_impara=0,x,r,Suma1=0,Suma2=0;

    deque<int> d,p;             // Doua double ended queue : In d retinem numerele si in p pozitiile lor

    while(f >> x)
    {
        d.push_back(x);             //Citim numarul x si contorizam pozitia i
        p.push_back(i);
        if(i % 2)
            suma_impara = suma_impara + x;
        else
            suma_para = suma_para + x;
        i++;

    }

    cout<<"Suma elementelor de pe pozitiile pare este "<<suma_para<<endl<<"Suma elementelor de pe pozitii impare este "<<suma_impara<<endl;

    if(suma_para > suma_impara)          // Daca suma elementelor de pe pozitiile pare este mai mare decat cea a elementelor de pe pozitiile impare,
                                       // atunci trebuie sa oblig calculatorul sa mearga pe pozitiile impare ale secventei.Voi face asta alegand
    {                                  // doar numerele de pe pozitiile pare ale secventei.
        while(! d.empty() )
        {
            if( p.front() % 2 == 0)        //Alegem numarul de la inceputul/finalul secventei actuale,daca se afla pe o pozitie para
                {
                    Suma1 = Suma1 + d.front();
                    cout<< "Voi alege numarul " << d.front() << " de pe pozitia " << p.front() << endl <<endl;
                    d.pop_front();
                    p.pop_front();
                }
            else
                if(p.back() % 2 ==0)
            {
                Suma1 = Suma1 + d.back();
                cout << "Voi alege numarul " <<d.back() <<" de pe pozitia " << p.back() <<endl <<endl;
                d.pop_back();
                p.pop_back();
            }

         cout<<"Calculatorul va alege numarul ";        // Calculatorul va fi obligat sa aleaga un numar de pe o pozitie impara,fie de la inceputul,fie de la
                                                        // finalul secventei actuale
         r=rand() % 2;

         if(r)

         {
             Suma2 = Suma2 + d.back();
             cout << d.back() << " de pe pozitia " << p.back() << endl <<endl ;
             d.pop_back();
             p.pop_back();
         }
         else
         {
             Suma2 = Suma2 + d.front();
             cout << d.front() << " de pe pozitia " << p.front() << endl << endl;
             d.pop_front();
             p.pop_front();
         }

        }
    }

    else                                    // Daca suma elementelor de pe pozitiile impare este mai mare decat suma elementelor de pe pozitiile pare ale
    {                                       // secventei,atunci trebuie sa oblig calculatorul sa mearga pe pozitiile pare ale secventei.Voi face asta alegand
        while(!d.empty())                   // doar elementele de pe pozitiile impare ale secventei.
        {
            if(p.front() % 2 == 1)           // Alegem elementul de la inceputul/finalul secventei actuale,daca se afla pe o pozitie impara
                {
                    Suma1 = Suma1 + d.front();
                    cout<<"Voi alege numarul "<<d.front()<<" de pe pozitia "<<p.front()<<endl<<endl;
                    d.pop_front();
                    p.pop_front();
                }
            else
                if(p.back() % 2 ==1)
            {
                Suma1 = Suma1 + d.back();
                cout<<"Voi alege numarul "<<d.back()<<" de pe pozitia "<<p.back()<<endl<<endl;
                d.pop_back();
                p.pop_back();
            }

         cout<<"Calculatorul va alege numarul ";            // Calculatorul va fi obligat sa aleaga un numar de pe o pozitie para,fie de la inceputul,fie de
                                                            // la finalul secventei actuale
         r=rand() % 2;

         if(r)
         {
             Suma2 = Suma2 + d.back();
             cout<<d.back()<<" de pe pozitia "<<p.back()<<endl<<endl;
             d.pop_back();
             p.pop_back();
         }
         else
         {
             Suma2 = Suma2 + d.front();
             cout<<d.front()<<" de pe pozitia "<<p.front()<<endl<<endl;
             d.pop_front();
             p.pop_front();
         }

        }
    }


    cout<<"Am obtinut "<<Suma1<<" puncte,iar calculatorul a obtinut "<<Suma2<<" puncte";
    return 0;
}
