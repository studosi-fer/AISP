/*
 * Slično kao i hash.cpp, osim što smo u klasu Student ubacili metodu getKey();
 * To je pojednostavilo implementaciju hash-a, ali sad svaki objekt koji ubacujemo
 * u tablicu mora imati metodu getKey() - to možemo osigurati sa sučeljem
 */

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Student {
    public:
        int jmbag;
        string name; //ovdje može biti puno drugih podataka
        Student(){}
        Student(int jmbag, string name): jmbag(jmbag), name(name) {}
        int getKey() { return jmbag; }
};

ostream& operator<<(ostream &os, const Student &s) {
    os << s.jmbag << ":" << s.name;
    return os;
}

template <class T> class HashWithChaining {
    int M; //veličina hashing tablice
    list<T> *tablica;

    public:
    HashWithChaining(int size) {
        M = size;
        //tablica je polje veličine M, svaki element polja je lista
        //a svaki element liste je objekt tipa T (nama "Student")
        tablica = new list<T>[M]; 
    }

    int hash(int key) {
        return key % M;
    }

    void insert(T object) {
        int index = hash(object.getKey());
        tablica[index].push_front(object);
    }

    bool get(T &object, int key) {
        int idx = hash(key);
        for (auto el : tablica[idx])
            if (el.getKey() == key) {
                object = el;
                return true;
            }
        return false;
    }

    bool remove(int key) {
        cout << "Brisem el s kljucem: " << key << endl;
        int idx = hash(key);
        for (auto it=tablica[idx].begin(); it != tablica[idx].end(); it++)
            if ((*it).getKey() == key) {
                //brisem taj element, tj. taj par
                tablica[idx].erase(it);
                cout << "obrisan!" << endl;
                return true;
            }
        return false;
    }

    void print() {
        for (int i=0; i<M; i++) {
            cout << i << " :  ";
            for (auto el : tablica[i])
                cout << " -> " << el;
            cout << endl;
        }
    }

};

int main() {
    HashWithChaining<Student> h(10);

    Student s1(1, "Marko");
    //cout << s1;
    h.insert(s1);
    h.insert({12,"Ana"});
    h.insert({32,"Ivo"});
    h.insert({52,"Mirko"});
    h.insert({55,"Slavko"});
    h.insert({INT_MAX, "Max"});
    h.print();


    Student s2;
    int key;
    cout << "Trzim kljuc: ";
    cin >> key;
    if (h.get(s2,key))
        cout << "Nasao: " << s2 << endl;
    else
        cout << "Nema objekta s tim kljucem" << endl;

    h.remove(32);
    h.print();

    return 0;

}