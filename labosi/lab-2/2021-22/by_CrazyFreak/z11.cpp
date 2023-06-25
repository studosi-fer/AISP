#include <iostream>

using namespace std;

struct zapis {
    int sifra;
    string naziv;
};

void obicanBubbleSort(zapis A[], int n, char smjer){
    if (smjer == '0'){
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < n-i-1; ++j) {
                if (A[j].sifra > A[j+1].sifra){
                    swap(A[j], A[j+1]);
                }
            }
        }
    } else if (smjer == '1'){
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < n-i-1; ++j) {
                if (A[j].sifra < A[j+1].sifra){
                    swap(A[j], A[j+1]);
                }
            }
        }
    }
}

int main() {

    int n;
    zapis podatak;
    char smjer;

    cout << "upisite broj clanova polja:";
    cin >> n;
    cout << "upisite smjer sortiranja:";
    cin >> smjer;
    zapis A[n];
    cout << "upisite podatke:\n";

    for (int i = 0; i < n; ++i) {
        cin >> A[i].sifra;
        cin >> A[i].naziv;
    }

    obicanBubbleSort(A, n, smjer);

    cout << "ispis polja:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << A[i].sifra << " " << A[i].naziv << endl;
    }

    return 0;
}
