#include <iostream>

using namespace std;

struct Zapis{
    int postanskibroj;
    string imemjesta;
};

void insertionSort (Zapis A[], int n, char smjer){
    if (smjer == '0'){
        for (int i = 1; i < n; ++i) {
            for (int j = i; j > 0; j--) {
                if (A[j].postanskibroj < A[j-1].postanskibroj){
                    swap(A[j], A[j-1]);
                } else continue;
            }
        }
    } else if (smjer == '1'){
        for (int i = 1; i < n; ++i) {
            for (int j = i; j > 0; j--) {
                if (A[j].postanskibroj > A[j-1].postanskibroj){
                    swap(A[j], A[j-1]);
                } else break;
            }
        }
    } else cerr << "nepravilan smjer, treba upisat 0 ili 1";
}


int main() {

    int n;
    char smjer;
    cout << "upisite broj Zapisa:";
    cin >> n;
    Zapis zapis[n];

    for (int i = 0; i < n; ++i) {
        cin >> zapis[i].postanskibroj;
        cin >> zapis[i].imemjesta;
    }

    cout << "upisite smjer sortiranja:";
    cin >> smjer;

    insertionSort(zapis, n, smjer);

    for (int i = 0; i < n; ++i) {
        cout << zapis[i].postanskibroj << " " << zapis[i].imemjesta
        << ", " << endl;
    }

    return 0;
}
