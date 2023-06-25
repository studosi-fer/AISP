#include <iostream>

using namespace std;

void okreniOduzmi(int *polje, int n) {
    if (n == 0)
        return;

    cout << polje[n-1] - polje[0] << " ";
    okreniOduzmi(polje, n-1); 
}

int main (void){
    int A[] = {2, 6, 8, 11, -3, 100};
    int n;
    cout << "Broj clanova za ispisat obrnutim redoslijedom umanjenih za 0. element: ";
    cin >> n;
    
    okreniOduzmi(A, n);

    return 0;
}