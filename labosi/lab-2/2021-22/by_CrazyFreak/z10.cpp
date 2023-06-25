#include <iostream>

using namespace std;

void selection2Sort(int A[], int n, char smjer){
    if (smjer == '0'){
        int najmanji, najmanjiIndex, najveci, najveciIndex, i = 0, j = n-1;

        while (i < j){
            najmanji = A[i];
            najmanjiIndex = i;
            najveci = A[i];
            najveciIndex = i;

            for (int k = i; k <= j; ++k) {
                if (A[j] > najveci){
                    najveci = A[j];
                    najveciIndex = j;
                }
                if (A[j] < najmanji){
                    najmanji = A[j];
                    najmanjiIndex = j;
                }
            }
            swap(A[i], A[najmanjiIndex]);
            swap(A[j], A[najveciIndex]);
        }
    } else if (smjer == '1') {
        int najmanji, najmanjiIndex, najveci, najveciIndex;

        for (int i = 0; i < n; ++i) {
            najveci = A[i];
            najveciIndex = i;
            for (int j = i; j < n; ++j) {
                if (A[j] > najveci){
                    najveci = A[j];
                    najveciIndex = j;
                }
            }
            swap(A[i], A[najveciIndex]);
        }
    }
}

int main() {

    int n;
    int broj;
    char smjer;

    cout << "upisite broj clanova polja:";
    cin >> n;
    cout << "upisite smjer sortiranja:";
    cin >> smjer;
    int A[n];
    cout << "upišite podatke:\n";

    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    selection2Sort(A, n, smjer);

    cout << "ispis polja:";
    for (int i = 0; i < n; ++i) {
        cout << A[i] << ", ";
    }

    return 0;
}
