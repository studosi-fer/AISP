#include <iostream>
#include <ctime>

using namespace std;

class Stog{
    struct StogElement{
        int item;
        StogElement *next;
    };

    StogElement *head = nullptr;

public:
    bool push(int el){
        StogElement *novi = new StogElement;
        if (novi == nullptr) return false;
        novi->item = el;
        novi->next = head;
        head = novi;
        return true;
    }

    void ispis(){
        StogElement *pok = head;
        while (pok != nullptr){
            cout << pok->item << ", ";
            pok = pok -> next;
        }
    }
};

int main() {

    Stog st;
    int num;
    bool prov;

    srand(time(0));
    for (int i = 0; i < 151; ++i) {
        num = rand();
        prov = st.push(num);
        if (!prov) cout << "Stog pun" << endl;
    }

    st.ispis();

    return 0;
}
