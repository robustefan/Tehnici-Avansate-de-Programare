#include <iostream>

using namespace std;

int nr_inv;

void merge(int arr[], int l, int m, int r)          // l=left, m=middle, r=right
{
    int i, j, k, q=-1;
    int n1 = m - l + 1;         // vectorul 1 va avea middle - left +1 elemente ( adica inclusiv arr[m] )
    int n2 =  r - m;            // vectorul 2 va avea right - middle elemente

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];          // copiem vectorul arr in L incepand cu pozitia left pana la pozitia middle

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];        // copiem vectorul arr in R incepand cu pozitia middle+1 pana la pozitia right

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)         // cat timp nu am iesit din vectorul L si R
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];          // copiem elementul din L in vectorul sortat
            i++;
        }
        else
        {
            int p;
            for(p = max(q,i); p < n1 ; p++)     // cautam in vectorul L un element care sa fie > 2*R[j]
                if(L[p] >2*R[j])            // p este pozitia primei inversiuni semnificative
                    {
                        nr_inv = nr_inv + n1 - p;       // am gasit n1 - p inversiuni semnificative
                        q = p;                          // urmatoarele inversiuni vor fi cautate de la q
                        p = n1;
                    }
            arr[k] = R[j];          // copiem elementul din vectorul R in vectorul sortat
            j++;
        }
        k++;
    }

    while (i < n1)
    {                           // cat timp au ramas elemente in L , le copiem in vectorul sortat
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)              // cat timp au ramas elemente in R, le copiem in vectorul sortat
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
int main()
{
    int v[100],i,n;

    cin>>n;

    for(i=1;i<=n;i++)
    cin>>v[i];

    mergeSort(v,1,n);

    cout<<nr_inv<<endl;

    return 0;

}
