#include <iostream>

using namespace std;

class Osoba{
public:
    string ime;
    unsigned short int starost;
    bool operator < (const Osoba &other){
        if (starost < other.starost) return true;
        else if (starost > other.starost) return false;
        else {
            if (ime.compare(other.ime) < 0) return true;
            else return false;
        }
    }
};

template <typename T> void InsertionSort(T A[], int N){
    int j;
    Osoba temp;
    for (int i = 1; i < N; ++i) {
        j = i;
        while (A[j] < A[j-1] && j > 0){
            swap(A[j], A[j-1]);
            j--;
        }
    }
}

int main() {

    Osoba osobe[10] = {{"Ana",20},
                       {"Ivo",9},
                       {"Marko",9},
                       {"Lidija",22},
                       {"Pero",19},
                       {"Joža", 15},
                       {"Gljivor", 20},
                       {"Lorena", 20},
                       {"Lorenaa", 20},
                       {"Lorna", 20}};

    cout << "prije sortiranja:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << osobe[i].ime << " " << osobe[i].starost << endl;
    }

    InsertionSort(osobe, 10);

    cout << "nakon sortiranja:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << osobe[i].ime << " " << osobe[i].starost << endl;
    }

    return 0;
}
