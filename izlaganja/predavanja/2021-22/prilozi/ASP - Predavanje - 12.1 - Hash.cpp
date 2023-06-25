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
};

ostream& operator<<(ostream &os, const Student &s) {
    os << s.jmbag << ":" << s.name;
    return os;
}

template <class T> class HashWithChaining {
    int M; //veličina hashing tablice
    list<pair<int,T>> *tablica;

    public:
    HashWithChaining(int size) {
        M = size;
        tablica = new list<pair<int,T>>[M]; //tablica je polje, svaki el je lista, svaki el liste je par
    }

    int hash(int key) {
        return key % M;
    }

    void insert(T object, int key) {
        int index = hash(key);
        tablica[index].push_front({key,object});
    }

    T get(int key) {

    }

    bool get(T &object, int key) {
        int idx = hash(key);
        for (auto p : tablica[idx])
            if (p.first == key) {
                object = p.second;
                return true;
            }
        return false;
    }

    bool remove(int key) {
        cout << "Brisem el s kljucem: " << key << endl;
        int idx = hash(key);
        for (auto it=tablica[idx].begin(); it != tablica[idx].end(); it++)
            if ((*it).first == key) {
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
                cout << " -> " << el.second;
            cout << endl;
        }
    }

};

int main() {
    HashWithChaining<Student> h(10);

    Student s1(1, "Marko");
    //cout << s1;
    h.insert(s1,s1.jmbag);
    h.insert({12,"Ana"},12);
    h.insert({32,"Ivo"}, 32);
    h.insert({52,"Mirko"},52);
    h.insert({55,"Slavko"},55);
    h.insert({INT_MAX, "Max"}, INT_MAX);
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