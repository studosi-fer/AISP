#include <iostream>

using namespace std;

class Red{
    struct Cvor{
        double item;
        Cvor *next;
    };

    Cvor *ulaz = nullptr;
    Cvor *izlaz = nullptr;

public:
    bool dodaj(double broj){
        Cvor *novi = new (nothrow) Cvor;
        if (novi == nullptr) return false;
        novi->item = broj;
        novi->next = nullptr;

        if (ulaz == nullptr){
            izlaz = novi;
        } else {
            ulaz->next = novi;
        }
        ulaz = novi;
        return true;
    }

    bool skini(double *broj){
        if (izlaz == nullptr) return false;
        *broj = izlaz->item;
        Cvor *tmp = izlaz;
        izlaz=izlaz->next;
        if (izlaz == nullptr) ulaz = nullptr;
        delete tmp;
        return true;
    }
};

int main() {

    int n;
    double broj;
    Red r;
    cout << "upisite broj clanova: ";
    cin >> n;
    cout << "upisite clanove: ";

    for (int i = 0; i < n; ++i) {
        cin >> broj;
        r.dodaj(broj);
    }

    for (int i = 0; i < n; ++i) {
        r.skini(&broj);
        cout << broj << ", ";
    }


    return 0;
}
