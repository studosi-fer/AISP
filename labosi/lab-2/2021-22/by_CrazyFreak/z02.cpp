/*Napišite parametriziranu klasu Lista te članske funkcije:

bool upis (T element);
void ispis();

Funkcija  upis  kao  argument  prima  element  koji  uvijek  treba  dodati  na  kraj  liste.  Funkcija 
vraća true, ako je novi čvor uspješno dodan u listu, a false  inače.  Potrebno  je  definirati 
strukturu cvor koji sadrži podatak tipa T te pokazivače na prethodni i sljedeći čvor u listi. 
U glavnom programu potrebno je s tipkovnice učitati n stringova (n ≤ 10) te ih dodati u listu 
korištenjem funkcije upis. Na kraju je potrebno ispisati sve članove liste. 
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
        Atom *tail;

    public:
        List() {head = tail = nullptr;}

        bool upis(T element){
            Atom *newAtom = new (nothrow) Atom;
            if(newAtom == nullptr) return false;
            
            newAtom->data = element;
            newAtom->next = nullptr;

            if(!head){
                head = tail = newAtom;
            }else{
                tail->next = newAtom;
                tail = newAtom;
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
    string element;
    int n;
    
    cout << "Upisite broj elemenata: ";
    cin >> n;

    List<string> *lista = new List<string>;

    cout << "Upisite elemente razdvojene razmakom: ";
    for(int i = 0; i < n; i++){
        cin >> element;
        lista->upis(element);
    }

    cout << "Lista poredana po redoslijedu unosa: "; 
    lista->ispis();
    delete lista;


    return 0;
}