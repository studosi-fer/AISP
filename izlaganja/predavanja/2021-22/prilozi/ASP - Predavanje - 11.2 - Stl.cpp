#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;

class MojKomparatorZaGomilu { // ili struktura
    public: bool operator()(int &i, int &j) { return i>j; }
};

int main() {

    //dinamičko polje
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3); // "polje" 1,2,3

    for (int i: v)
        cout << i << " ";
    cout << endl;

    //dohvat
    cout << v[0] << endl;
    cout << v.at(2) << endl;
    //cout << v.at(9); // 'std::out_of_range'
    //cout << v[9]; //ne baca iznimku!

    //zamijena vrijednosti
    v[1] = 99;

    //ubaci el na poziciju (pomakni ostale)
    v.insert(v.begin()+1, 77);

    for (int i: v)
        cout << i << " ";
    cout << endl;

    //brisanje
    v.erase(v.begin()+1);

    for (int i: v)
        cout << i << " ";
    cout << endl;

    //lista
    list<string> l;
    l.push_back("aaa");
    l.push_back("bbb");
    l.push_back("ccc");
    //dodavanje na početak liste
    l.push_front("ddd");

    for (auto s: l)
        cout << s << " ";
    cout << endl;

    string zadnji = l.back();
    string prednji = l.front();

    //brisanje
    l.pop_back();
    l.pop_front();

    cout << "Izbrisali smo: " << prednji << " i " << zadnji << endl;

    for (auto s: l)
        cout << s << " ";
    cout << endl; 

    //stack
    stack<int> stog;
    stog.push(1);
    stog.push(2);
    stog.push(5);

    cout << "Na vrhu stoga je " << stog.top() << endl;
    stog.pop();
    cout << "Na vrhu stoga je " << stog.top() << endl;

    //queue
    queue<int> *q =new queue<int>();
    q->push(1);
    q->push(2);
    q->push(3);
    // BACK(WRITE) - 3 - 2 - 1 - FRONT(READ)

    cout << "Na izlazu je " << q->front() << endl;
    cout << "Zadnji ubacen je " << q->back() << endl;

    q->pop(); //izvadili smo jedan el (s izlaza/front-a)
    cout << "Na izlazu je " << q->front() << endl;

    //set - binarno stablo
    set<int> skup;

    skup.insert(1);
    skup.insert(1); // duplikat
    skup.insert(2);
    skup.insert(4);

    for (auto i: skup)
        cout << i << " ";
    cout << endl;
    
    //prioritetni red ili gomila (defaultno je max_heap - najveći el na vrhu)
    priority_queue<int> g; // isto kao da piše priority_queue<int, vector<int>, less<int>> g;

    g.push(1);
    g.push(3);
    g.push(10);
    g.push(2);
    g.push(7);

    cout << "Na vrhu gomile je " << g.top() << endl;
    g.pop();
    cout << "Na vrhu gomile je " << g.top() << endl;
    g.pop();
    cout << "Na vrhu gomile je " << g.top() << endl;

    //Min. heap? - s vlastitim komparatorom
    priority_queue<int, vector<int>, MojKomparatorZaGomilu> ming1;
    //ili koristimo ugrađen
    priority_queue<int, vector<int>, greater<int>> ming;
    ming.push(3);
    ming.push(5);
    ming.push(1);
    ming.push(10);

    cout << "Na vrhu min gomile je " << ming.top() << endl;
    ming.pop();
    cout << "Na vrhu min gomile je " << ming.top() << endl;  

    //mapa key-val parovi
    map<int, string> m;
    //ubacivanje parova key-value
    m.insert(std::pair<int,string>(1,"aaa"));
    m.insert({2,"bbb"});
    m.emplace(3,"ccc");

    for (auto p : m)
        cout << p.first << " : " << p.second << endl;

    m.insert({1,"ggg"}); //ne mijenja ništa jer već postoji taj key
    
    for (auto p : m)
        cout << p.first << " : " << p.second << endl;

    m[1] = "hhh"; // mijenja value uz key 1

    //m.insert_or_assign(1, "iii"); //C++17

    for (auto p : m)
        cout << p.first << " : " << p.second << endl; 
}