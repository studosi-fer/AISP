#include <iostream>

using namespace std;

template <typename T>
void marge(T A[], T pom[], int leftPos, int rightPos, int rightEnd){ // ovo su sve indexi, tj. UKLJUČIVE GRANICE!
    //leftPos - početak lijevog podniza
    //rightPos - početak desnog
    //rightEnd - kraj desnog podniza (leftEnd nam ne treba, to je rightPos-1)
    int leftEnd = rightPos - 1;
    int numOfElements = rightEnd - leftPos + 1; // od početka lijevog podniza do kraja desnog, +1 jer su UKLJUČIVE GRANICE!
    int pomPos = leftPos;

    //dok ima elemenata u oba podniza
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        //gledaj u oba podniza prvi el pa prepiši manji u pomocni niz, pomakni index tog niza pa opet uspoređuj...
        if (A[leftPos] < A[rightPos]) {
            pom[pomPos] = A[leftPos];
            pomPos++;
            leftPos++;
        }
        else 
            pom[pomPos++] = A[rightPos++]; //kraće zapisano ali isto kao i za left
    }
        
    //ovo gore se vrtilo dok god je bilo elemenata u oba podniza
    //sad je još u SAMO jednom od njih ostalo elemenata, ali ne znamo u kojem
    //te elemente sve prepišemo u pom, kako dolaze.. (jer se više nemaju s čim uspoređivati)
    //ako su u lijevom
    while (leftPos <= leftEnd)
        pom[pomPos++] = A[leftPos++];
    //ili ako su u desnom podnizu
    while (rightPos <= rightEnd)
        pom[pomPos++] = A[rightPos++];

    //vrati elemente iz pomoćnog polja natrag
    for (int i=0; i < numOfElements; i++) 
        //pazi, ovdje nemamo više originalne leftPos ili rightPos
        // ali imamo rightEnd i numOfElements pa ćemo iz njih izračunati što nam treba
        A[rightEnd-i] = pom[rightEnd-i];
}

template <typename T>
void margeSort(T A[], T pom[], int left, int right){
    int middle;
    if (left < right) {
        middle = (left + right) / 2;
        margeSort(A, pom, left, middle);
        margeSort(A, pom, middle+1, right);
        // spoji A[left...middle] i A[middle+1...right] u sortirani niz 
        marge(A, pom, left, middle+1, right); //polje, pom polje, poč 1. podniza, poč 2. podniza i kraj
    }
}

int main(){

    int polje[8]{2,5,4,8,7,1,3,6};
    int pom[8];

    cout << "start : ";
    for (int i=0; i<8; i++)
        cout << polje[i] << " ";
    cout << endl;

    margeSort(polje, pom, 0, 7); //pazi, indexi, dakle 0 i 7 (a ne 8)!!!

    cout << "end   : ";
    for (int i=0; i<8; i++)
        cout << polje[i] << " ";
    cout << endl;

    return 0;
}