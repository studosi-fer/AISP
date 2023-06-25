#include <iostream>
#include <ctime>

using namespace std;

class Stog {
    static const int MAX = 10;
    int stog[MAX];
    int top = -1;

public:
    bool push(int el){
        if (++top < MAX){
            stog[top] = el;
            return true;
        }
        return false;
    }

    bool pop(int &a){
        if (top == -1) return false;
        a = stog[top--];
        return true;
    }
};

int main() {

    Stog st, pom;
    srand(time(0));
    int num, zamj;

    cout << "stog: ";
    for (int i = 0; i < 10; ++i) {
        num = rand()%10 + 1;
        cout << num << ", ";
        st.push(num);
    }
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        st.pop(zamj);
        pom.push(zamj);
    }

    cout << "ispis: ";
    for (int i = 0; i < 10; ++i) {
        pom.pop(zamj);
        cout << zamj << ", ";
    }

    return 0;
}
























