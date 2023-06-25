#include <iostream>

using namespace std;

int kvaziBinomni (int n, int m){
    if ((n < 0) || (m > n))
        return 0;
    if ((m == 0) || (n == m))
        return 1;
    
    return kvaziBinomni(n - 1, m - 1) + m * kvaziBinomni(n - 1, m + 1);

}

int main (void){
    int n, m;
    cout << "Upisite n i m kvazi-binomnih koeficijenata: ";
    cin >> n;
    cin >> m;
    
    cout << "Rjesenje: " << kvaziBinomni(n, m) << endl;
    return 0;
}