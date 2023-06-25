#include <iostream>
#include <math.h>
#include <string>
using namespace std;

template <typename T> 
class Heap {
    private:
        int size;
        T *elements;
        int j; //idx za ubacivanje novog elementa

    public:
        Heap(int n) {
            this->size = n;
            this->j = 1; //prvo dodajemo na idx 1
            this->elements = new T[n+1]; //indexi kreću od 1 pa zato n+1
        }

        ~Heap() { delete[] this->elements; }

        void print() {
            cout << "HEAP: ";
            for (int i=1; i<this->j; i++) // elementi su na indexima od 1 do j
                cout << this->elements[i] << " ";
            cout << endl;
        }

        bool addOne(T el) { // dodajem jedan element u gomilu i čuvam svojstvo
            //dodajem element na j-to mjesto
            if (this->j > this->size)
                //pogreška ili return false
                return false;
            this->elements[this->j] = el;
            this->adjustOne();
            this->j++;
            return true;
        }

        void adjustOne() {
            //provjerava je li novo ubačeni el na dobrom mjestu i ako nije, podešava heap
            int idxNew = this->j; //index novog elementa
            int idxParent = idxNew/2; //idx roditelja
            T newEl = this->elements[idxNew]; //vrijednost novog el

            //ideja: provjeri je li novo ubačeni el. veći od roditelja, ako je - zamijeni
            //ali možda je veći i od njegovog roditelja, zato ovako:
            //dok god postoji neki predak i vrijednost mu je manja od novog el.
            while (idxParent > 0 && this->elements[idxParent] < newEl) {
                //spusti roditelja na mjesto djeteta
                //ovdje smo mogli raditi i swap, ali je to malo skuplji način
                this->elements[idxNew] =  this->elements[idxParent];
                
                //izračunaj nove indexe - svaki na svog roditelja
                idxNew = idxParent;     // new ide na svog roditelja
                idxParent = idxParent / 2;  // a roditelj na svog roditelja
            }
            //sad na mjesto najvišeg roditelja kojeg treba podesiti ide newEl
            //pazi: u ovom trenutku to je idxNew! idxParent je na "prvom dobrom" roditelju
            this->elements[idxNew] = newEl;
        }

        //metoda za dodavanje i podešavanje SVIH elemenata
        void addAll(T A[], int n) {
            //fali provjera stanu li svi elementi polja u heap
            for (int i = 0; i < n; i++)
                this->elements[this->j++] = A[i];
            //podesi sve
            this->adjustAll();
        }

        void adjustAll() {
            //krećemo od zadnjeg roditelja, tj. čvora koji je korijen nekog podstabla
            for (int i= this->j/2; i>=1; i--)
                this->adjustSubtree(i);
        }

        void adjustSubtree(int idxRoot) {
            int idxChild = 2*idxRoot; //lijevo dijete, desno (ako postoji) je na 2*idxRoot+1
            T rootEl = this->elements[idxRoot];
            
            while (idxChild <= this->size) {
                //prvo nađemo veće od dva djeteta, ako uopće postoje
                if ((idxChild+1 < this->j) && 
                    (this->elements[idxChild] < this->elements[idxChild + 1]))
                        idxChild++;

                // sad mi je idxChild na vecem djetetu
                // ako je korijen >= djeteta, gotov sam!
                if (rootEl >= this->elements[idxChild])
                    break;

                //inače - zamijenim roditelja i (veće) dijete
                //i ovdje nije prava zamjena, nego nešto nalik na "insertion sort"
                this->elements[idxChild / 2] = this->elements[idxChild];
                //pomaknem dijete 
                idxChild *=2;
            }

            //sad konačno zapišem 
            this->elements[idxChild / 2] = rootEl;
        }

        bool pop(T &el) {
            if (this->j < 1 )
                return false;
            el = this->elements[1];
            this->elements[1] = this->elements[j-1];
            j--;
            size--;
            this->adjustSubtree(1);
            return true;
        }
    template <typename TT>
    friend void heapsort(TT A[], int n); 
};

template <typename T> void swapEl(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void heapsort(T A[], int n) {
    //NAPOMENA: ova fja koristi postojeću klasu Heap, koja ima neka pojednostavljenja
    //Zato radimo dodatne korake, npr. dodavanje elemenata u Heap ili vraćanje u polje
    //bolje bi bilo da smo napisali kod koji stvara heap direktno u polju A (i to od idx 0)
    
    //prvo stvorimo gomilu - nije dio sorta!
    Heap<int> h(n);
    h.addAll(A, n); // O(n)

    h.print();

    //KLJUČNI DIO:
    //sad vrh gomile zamijenim sa zadnjim elementom i smanjim gomilu za 1
    for (int i = n; i >= 2; i--) {      //O(n)
        swapEl(h.elements[1], h.elements[i]);
        h.size--;
        h.j--;
        h.adjustSubtree(1); //O(logn)
    }
    //kraj ključnog dijela

    //gotovo, u internom polju od heapa su mi dobro složeni elementi
    //mogu ih npr. prepisati nazad u početno polje - nije dio sorta!
    for (int i = 1; i <= n; i++) {
        A[i-1] = h.elements[i];
        //A[n-i] = h.elements[i];
    }

}

int main(void) {
    //int A[] = {13, 26, 31, 75, 46, 6};
    int A[] = {10,63,18,71,7,51,32};

    int n = sizeof(A) / sizeof(A[0]);
    Heap<int> g(n);
    g.print();
    g.addOne(13);
    g.print();
    g.addOne(26);
    g.print();
    g.addOne(31);
    g.print();
    g.addOne(75);
    g.print();
    g.addOne(46);
    g.print();
    g.addOne(6);
    g.print();    

    Heap<int> h1(n);
    for (int i = 0; i < n; i++)
        h1.addOne(A[i]);
    h1.print();

    Heap<int> h2(n);
    h2.addAll(A, n);
    h2.print();

    int broj;
    h2.pop(broj);
    cout << "S gomile sam skinuo " << broj << endl;
    h2.print();
    h2.pop(broj);
    cout << "S gomile sam skinuo " << broj << endl;
    h2.print();
    h2.pop(broj);
    cout << "S gomile sam skinuo " << broj << endl;
    h2.print();
    
    int p[]{3,5,4,7,1,6,8,2}; 
    for (int i = 0; i < 8; i++)
        cout << p[i] << " ";
    cout << endl;

    heapsort(p,8);

    for (int i = 0; i < 8; i++)
        cout << p[i] << " ";
    cout << endl;

    return 0;
}