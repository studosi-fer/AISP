#include <iostream>

using namespace std;

int poljeEkstrema(int *niz, int n){
    if (n <= 2)
        return 1;

    if (!( ((niz[n - 2] > niz[n - 1]) && (niz[n - 2] > niz[n - 3])) 
        || ((niz[n - 2] < niz[n - 1]) && (niz[n - 2] < niz[n - 3])) ))
        return 0;

    return poljeEkstrema(niz, n - 1);
}

int main (void){
    int A[] = {2, 5, 3, 7, -3, -2};
    int n = sizeof(A) / sizeof(int);

    cout << "Polje " << (poljeEkstrema(A, n) ? "je" : "nije") <<  " ekstremno";

    return 0;
}