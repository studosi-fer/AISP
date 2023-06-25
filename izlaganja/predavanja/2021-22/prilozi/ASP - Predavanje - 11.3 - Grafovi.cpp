#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

template <class T> class Vertex {
    public:
        T data;
        bool visited = false;

        Vertex() {}
        Vertex(T data): data(data){}
};

struct MapComparator {
   bool operator()(Vertex<string> *a, Vertex<string> *b) {
      return a->data < b->data;
   }
};

template <class T> class Graph {
    //graf će biti mapa:
    // v1 -> lista susjeda
    // v2 -> lista susjeda
    public:
        map<Vertex<T>*, list<Vertex<T>*>, MapComparator> vertices;
        Vertex<T> *startingVertex = nullptr;

        //dodaj ključ (vrh) ili nađi odgovarajući zapis u mapi
        Vertex<T> *findOrAddVertex(T data) {
            Vertex<T> vv(data);
            auto it = vertices.find(&vv);
            //ako sam našao čvor
            if (it != vertices.end())
                return it->first; // iterator je pair<vertex,list<vertex>>
            
            //ako nisam našao čvor
            Vertex<T> *v = new Vertex<T>(data);
            list<Vertex<T>*> praznaLista;
            vertices.emplace(v, praznaLista);
            return v;
        }

        void readFromFile(string filename) {
            ifstream f(filename);
            string line, token;
            Vertex<string> v; //sve držim kao stringove
            while (getline(f, line)) {
                istringstream s(line);
                s >> token; //prvi token je vrh
                Vertex<string> *v = findOrAddVertex(token);
                if (startingVertex == nullptr)
                    startingVertex = v;
                //svi ostali tokeni su susjedi
                while (s >> token) {
                    Vertex<string> *n = findOrAddVertex(token);
                    vertices[v].push_back(n);
                }
            }
        }

        void print(){
            for (auto entry : vertices) {
                Vertex<T> *v = entry.first;
                cout << v->data << " -> ";
                for (auto n : entry.second)
                    cout << n->data << " ";
                cout << endl;
            }
        }

        void unvisit() {
            for (auto v : vertices)
                v.first->visited = false;
        }

        void DFSR() {
            cout << "DFS recursive: ";
            DFSRProcessSingleVertex(startingVertex);
            cout << endl;
        }

        void DFSRProcessSingleVertex(Vertex<T> *v) {
            v->visited = true;
            cout << v->data << " ";
            //lista susjeda
            auto neighbours = vertices[v];
            for (auto n : neighbours)
                if (!(n->visited))
                    DFSRProcessSingleVertex(n);
        }

        void DFS() {
            cout << "DFS: ";
            stack<Vertex<T>*> s;
            Vertex<T> *v;

            //početni čvor na stog
            s.push(startingVertex);

            while(!s.empty()) {
                //skinem element sa stoga
                v = s.top();
                s.pop();

                //ako još nisam obišao taj vrh
                if (!v->visited) {
                    v->visited = true;
                    cout << v->data << " ";
                    //sve susjede (neobiđene) stavi na stog
                    for (auto n : vertices[v]) {
                        if (!(n->visited))
                            s.push(n);
                    }
                }
            }
            cout << endl;
        }

        void BFS() {
            cout << "BFS: ";
            queue<Vertex<T>*> q;
            Vertex<T> *v;

            //početni čvor u red
            q.push(startingVertex);

            while (!q.empty()) {
                //izvadim jedan el iz reda
                v = q.front();
                q.pop();
                //ako ga još nisam obišao
                if (!(v->visited)) {
                    v->visited = true;
                    cout << v->data << " ";
                    //sve neobiđene susjede dodam u red
                    for (auto n : vertices[v])
                        if (!(n->visited))
                            q.push(n);
                }
            }
            cout << endl;
        }

};


int main(){
    Graph<string> g;
    g.readFromFile("internet2.txt");
    g.print();  
    g.DFSR();
    g.unvisit();
    g.DFS();
    g.unvisit();
    g.BFS();
    return 0;
}