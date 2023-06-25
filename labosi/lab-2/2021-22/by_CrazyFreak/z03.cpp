#include <iostream>
#include <ctime>

using namespace std;

class Stog {
    static const int MAX = 100;
    int stog[MAX];
    int top = -1;

public:
    bool push(int element){
        if (++top < MAX){
            stog[top] = element;
            return true;
        }
        return false;
    }

    void ispis(){
        for (int i = 0; i < top; ++i) {
            cout << stog[i] << ", ";
        }
    }

};

int main() {

    Stog st;
    int num;
    bool prov;

    srand(time(0));
    for (int i = 0; i < 101; ++i) {
        num = rand();
        prov = st.push(num);
        if (!prov) cout << "Stog pun" << endl;
    }

    st.ispis();

    return 0;
}
