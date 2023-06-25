#include <iostream>

using namespace std;

class Vozilo{
public:
    string name;
    int year;

    bool operator < (const Vozilo &other){
        if (name < other.name) return true;
        else if (name > other.name) return false;
        else {
            if (year > other.year) return true;
            else return false;
        }
    }
};

void Zamijeni(Vozilo &prvi, Vozilo &drugi){
    Vozilo temp;
    temp = prvi;
    prvi = drugi;
    drugi = temp;
}

template <typename T> void SelectionSort(T A[], int N){
    Vozilo najmanji;
    int najmanjIndex;
    for (int i = 0; i < N; ++i) {
        najmanji = A[i];
        najmanjIndex = i;
        for (int j = i; j < N; ++j) {
            if (A[j] < najmanji){
                najmanji = A[j];
                najmanjIndex = j;
            }
        }
        Zamijeni(A[i], A[najmanjIndex]);
    }
}

int main() {

    Vozilo vozila[] =  {{"Pauegot",1981},
                        {"Pauegot",1983},
                        {"Ranulet",1967},
                        {"Fait",1972},
                        {"BWM",1985},
                        {"Merdesec",1983},
                        {"Yugo", 1945},
                        {"Zastava101", 1949},
                        {"Lada", 1952},
                        {"Tesla", 2020}};

    cout << "Prije sortiranja:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << vozila[i].name << " " << vozila[i].year << endl;
    }

    SelectionSort(vozila, 10);

    cout << "nakon sortiranja:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << vozila[i].name << " " << vozila[i].year << endl;
    }

    return 0;
}
