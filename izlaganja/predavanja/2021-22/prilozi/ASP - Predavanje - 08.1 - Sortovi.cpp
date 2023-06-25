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
void selectionSort(T A[], int n) {
    //nadji najmanji pa ga zamijeni s prvim u polju...
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (A[j] < A[minIdx])
                minIdx = j;
        swapElements(A[i], A[minIdx]);

        //ispis - test
        cout << "i = " << i << " : ";
        for (int k=0; k<n; k++)
            cout << A[k] << " ";
        cout << endl;
    }
}

template <typename T>
void bubbleSort(T A[], int n) {
    //uspoređujemo 2 po 2 elementa i mijenjamo
    //svaki korak vanjske petlje sigurno na "kraj" stavi najveći
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (A[j] > A[j+1])
                swapElements(A[j], A[j+1]);
        }

        //ispis - test
        cout << "i = " << i << " : ";
        for (int k=0; k<n; k++)
            cout << A[k] << " ";
        cout << endl;
    }
}

//kako promijeniti smjer? dodatni parametar
template <typename T> 
void bubbleSortDir(T A[], int n, char d) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++)
            if (((d == '<') && (A[j + 1] < A[j])) ||
               ((d == '>') && (A[j + 1] > A[j])))
                swapElements(A[j], A[j + 1]);
        //ispis - test
        cout << "i = " << i << " : ";
        for (int k=0; k<n; k++)
            cout << A[k] << " ";
        cout << endl;
   }
}

template <typename T>
void bubbleSortImproved(T A[], int n) {
    bool swapHappened = true;
    //for (int i = 0; i < n-1; i++) {
    for (int i = 0; swapHappened == true; i++) {
        swapHappened = false;
        for (int j = 0; j < n-1-i; j++) {
            if (A[j] > A[j+1]) {
                swapElements(A[j], A[j+1]);
                swapHappened = true;
            }
        }

        //ispis - test
        cout << "i = " << i << " : ";
        for (int k=0; k<n; k++)
            cout << A[k] << " ";
        cout << endl;
    }
}

template <typename T>
void insertionSort(T A[], int n) {
    //"sortirani" i "nesortirani" dio niza
    T tmp;
    int i,j;
    for (i = 1; i < n; i++) {
        tmp = A[i];
        for (j = i; j >=1 && A[j-1] > tmp; j--)
            A[j] = A[j-1];
        A[j] = tmp;

        //ispis - test
        cout << "i = " << i << " : ";
        for (int k=0; k<n; k++)
            cout << A[k] << " ";
        cout << endl;
    }

}

template <typename T> 
void shellSort(T A[], int n) {
   int i, j, step;
   T tmp;
   for (step = n / 2; step > 0; step /= 2) {
      for (i = step; i < n; i++) {
         tmp = A[i];
         for (j = i; j >= step && A[j - step] > tmp; j -= step) {
            A[j] = A[j - step];
         } // for j
         A[j] = tmp;
         //ispis - test - step+i
         cout << "s" << step << ",i" << i << " : ";
         for (int k = 0; k < n; k++)
            cout << A[k] << " ";
         cout << endl;
      } // for i
   } // for step
}

int main() {
    int polje[8]{2,5,4,8,7,1,3,6};
    int A[] = {4, 3, 5, 2, 1, 6, 7, 8};
    int B[] = {6, 4, 1, 8, 7, 5, 3, 2};

    cout << "start : ";
    for (int k=0; k<8; k++)
        cout << polje[k] << " ";
    cout << endl;

    //selectionSort(polje, 8);
    //bubbleSort(polje, 8);
    //bubbleSortDir(polje,8, '<');
    //bubbleSortImproved(polje, 8);
    //insertionSort(polje, 8);
    shellSort(B, 8);

    cout << "end   : ";
    for (int k=0; k<8; k++)
        cout << polje[k] << " ";
    cout << endl;




    return 0;
}