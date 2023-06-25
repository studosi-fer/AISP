/*Napišite parametriziranu klasu Lista te članske funkcije:

bool upis (T element);
void ispis();

Funkcija upis kao argument prima element koji treba dodati u listu tako da lista bude uzlazno
sortirana prema vrijednostima elementa. Funkcija vraća true, ako je novi čvor uspješno dodan
u listu, a false inače. Funkcija ispis ispisuje cijelu listu od glave.

Pretpostavite da klasa (tip) T ima definirane sve potrebne operatore, konstruktore, destruktore i sl.

Potrebno je definirati strukturu cvor koji sadrži element te pokazivač na sljedeći čvor u listi.

U glavnom programu potrebno je s tipkovnice učitati n brojeva (n ≤ 10) te brojeve dodati u
listu korištenjem funkcije upis. Na kraju je potrebno ispisati članove liste.
*/

#include <iostream>

using namespace std;

template <typename T> class List{
private:
    struct Atom{
        T data;
        Atom *next;
    };

    Atom *head;

public:
    List() {head = nullptr;}

    bool upis(T element){
        Atom *newAtom = new (nothrow) Atom;
        if(newAtom == nullptr) return false;
        
        newAtom->data = element;
        newAtom->next = nullptr;

        if(!head || newAtom->data < head->data){
            newAtom->next = head;
            head = newAtom;
        }else{
            Atom *curr = head;
            Atom *prev;
            while(curr != nullptr && curr->data < element){
                prev = curr;
                curr = curr->next;
            }

            
            newAtom->next = curr;
            prev->next = newAtom;
        }
        return true;
    }

    void ispis(){
        cout << "HEAD -> ";
        for (auto curr = head; curr != nullptr; curr = curr->next)
            cout << curr->data << " -> ";
        cout << "NULLPTR" << endl;

        return;
    }
};

int main(void){
    int element;
    int n;
    
    cout << "Upisite broj elemenata: ";
    cin >> n;

    List<int> *lista = new List<int>;

    cout << "Upisite elemente razdvojene razmakom: ";
    for(int i = 0; i < n; i++){
        cin >> element;
        lista->upis(element);
    }

    cout << "Sortirana lista: ";
    lista->ispis();
    delete lista;


    return 0;
}