#include <iostream>

using namespace std;

void Zamijeni(string *prvi, string *drugi){
    string temp;
    temp = *prvi;
    *prvi = *drugi;
    *drugi = temp;
}

void BubbleSortPoboljsani(string A[],int N, int smjer){
    bool zamjena;
    if (smjer == '0'){
        for (int i = 0; i < N-1; ++i) {
            zamjena = false;
            for (int j = 0; j < N-i-1; ++j) {
                if(A[j] > A[j+1]){
                    Zamijeni(&A[j], &A[j+1]);
                    zamjena = true;
                }
            }
            if (!zamjena) return;
        }
    } else if (smjer == '1'){
        for (int i = 0; i < N-1; ++i) {
            zamjena = false;
            for (int j = 0; j < N-i-1; ++j) {
                if(A[j] < A[j+1]){
                    Zamijeni(&A[j], &A[j+1]);
                    zamjena = true;
                }
            }
            if (!zamjena) return;
        }
    }
}

int main() {

    string *stringovi = new string[10];

    cout << "upišite smjer sortiranja:";
    char smjer;
    cin >> smjer;

    stringovi[0] = "srtgbw45bg";
    stringovi[1] = "80345cz";
    stringovi[2] = "ASEBW BRG";
    stringovi[3] = "RZJEZM";
    stringovi[4] = "ARVBQ34G ";
    stringovi[5] = "rergq34 jsbcc";
    stringovi[6] = "KDNIWBCWZF";
    stringovi[7] = "500";
    stringovi[8] = "KJWENIBWECWEF";
    stringovi[9] = "khbcvce";

    BubbleSortPoboljsani(stringovi, 10, smjer);

    cout << "sortirani stringovi:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << stringovi[i] << endl;
    }

    return 0;
}
