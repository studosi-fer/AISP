#include <iostream>

using namespace std;

float kamrac(float g, int n, float p, float rez) {
    if (n <= 0)
        return g * rez;
    else
        return kamrac(g, n - 1, p, rez * (1 + p / 100));
}

int main (void){
    int g, n, p;
    cout << "Upisite glavnicu, godine i kamatnu stopu u postocima: ";
    cin >> g;
    cin >> n;
    cin >> p;
    
    cout << "Rjesenje: " << kamrac(g, n, p, 1) << endl;
    return 0;
}