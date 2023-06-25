#include <iostream>

using namespace std;

class Red{
    static const int MAX = 10;
    double red[MAX];
    int pocetak = -1;
    int kraj = -1;

public:
    bool dodaj(double broj) {
        if (pocetak == -1 && kraj == -1) {
            pocetak++;
            kraj++;
            red[kraj] = broj;
            return true;
        } else {
            kraj++;
            if (kraj > 9) kraj = 0;
            if (pocetak == kraj) {
                if (kraj == 0) kraj = 9;
                else kraj--;
                return false;
            }
            red[kraj] = broj;
            return true;
        }
    }

    bool skini(double *broj){
        if (pocetak == -1 & kraj == -1) return false;
        if (pocetak == kraj){
            *broj = red[pocetak];
            pocetak = -1;
            kraj = -1;
            return true;
        }
        *broj = red[pocetak];
        pocetak++;
        if (pocetak > 9) pocetak = 0;
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
