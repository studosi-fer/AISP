#include <iostream>

using namespace std;

int provjeri_sortiranost(int *niz, int n){
    if (n == 0 || n == 1)
        return 1; // niz od 0 ili jednog elementa se smatra sortiranim

    if (niz[n - 1] < niz[n - 2])
        return 0;
    return provjeri_sortiranost(niz, n - 1);
}

int main (void){
    int n = 0;
    cout << "Duljina niza: ";
    cin >> n;
    int *array = new int[n];

    // takoder se moze koristiti vector kao variable size array
    /* #include <vector>
    ...
    std::vector<int> vec; 
    cin >> n;
    vec.resize(n);
    */

    cout << "Elementi niza: ";
    for (int i = 0; i < n; i++){
        cin >> array[i];
    }

    string str = provjeri_sortiranost(array, n) ? "TRUE" : "FALSE";
    cout << "Uzlazno sortiran: " << str << endl;

    delete [] array;

    return 0;
}