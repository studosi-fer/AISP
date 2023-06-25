#include <iostream>
#include <ctime>

using namespace std;

class Red{
    static const int MAX = 10;
    int red[MAX];
    int pocetak = -1;
    int kraj = -1;

public:
    bool dodaj(int broj) {
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

    bool poljeURed (int polje[], int n){
        bool uspjeh;
        if (n == 0){
            return true;
        }
        cout << polje[n-1] << ", ";
        uspjeh = dodaj(polje[n-1]);
        if (!uspjeh) return false;
        return poljeURed(polje, n-1);
    }
};

int main() {

    Red r;
    int broj;
    int polje[10];
    srand(time(0));

    cout << "ispis polja prije dodavanja: ";
    for (int i = 0; i < 10; ++i) {
        broj = rand()%10 +1;
        polje[i] = broj;
        cout << polje[i] << ", ";
    }
    cout << endl << "dodavanje polja u red i paralelean ispis: ";

    r.poljeURed(polje, 10);

    return 0;
}
