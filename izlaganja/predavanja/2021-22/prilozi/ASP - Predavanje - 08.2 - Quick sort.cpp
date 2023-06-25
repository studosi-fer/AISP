#include <iostream>
#include <string>

using namespace std;

template <typename T>
void swapElements(T &a, T &b) {
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
int calculatePivot(T A[], int left, int right) {
    //nađi srednji el.
    int middle = (left+right) / 2;

    //sortiraj ta tri elementa
    if (A[left] > A[middle])
        swapElements(A[left], A[middle]);
    if (A[left] > A[right])
        swapElements(A[left], A[right]);
    if (A[middle] > A[right])
        swapElements(A[middle], A[right]);
    
    cout << "Stozer: " << A[middle] << endl;

    return middle;
}

template <typename T>
void quickSort(T A[], int left, int right) {
    int pivotIdx = calculatePivot(A, left, right);
    T pivot = A[pivotIdx];

    // KRAJ: ako ima 3 ili manje el - sortirano u calculatePivot
    if (right-left < 3)
        return;
    
    //skrivanje pivota
    swapElements(A[pivotIdx], A[right-1]);

    int i = left; //idx prvog elementa u nizu
    int j = right-1; //idx skrivenog pivota

    //prebacujem elemente veće od pivota na desno, a manje na lijevo
    while (true) {

        while (A[++i] < pivot) {} //ne radim ništa, samo povećavam i

        while (A[--j] > pivot) {} //samo smanjujem j

        //indexi su stali na el. koje treba zamijeniti
        if (i<j) { //ako je i<j mijenjam elemente
            swapElements(A[i], A[j]);
        }
        else //indexi su se sreli, kraj zamjena
            break;
    }

    //vratim pivot na i-to mjesto
    swapElements(A[right-1], A[i]);

    // pozovi quicksort za svaki podniz
    quickSort(A, left, i-1); //indexi
    quickSort(A, i+1, right); // "i" ne spada nigdje jer je na dobrom mjestu
}


int main() {
    int polje[10]{8,1,4,9,6,3,5,2,7,0};
    int pom[8];

    cout << "start : ";
    for (int k=0; k<10; k++)
        cout << polje[k] << " ";
    cout << endl;

    quickSort(polje, 0, 9); //0 i 9 su indexi!

    cout << "end   : ";
    for (int k=0; k<10; k++)
        cout << polje[k] << " ";
    cout << endl;

    return 0;
}