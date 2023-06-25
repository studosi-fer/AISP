#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class Vertex {
    public:
        string name;
        bool visited = false;
        double distanceFromSource = __DBL_MAX__; //za dijkstru
        Vertex *prev; //za dijkstru

        Vertex() {}
        Vertex(string name): name(name){}
};

class Neighbour {
    public:
        Vertex *v;
        double distance;

        Neighbour(Vertex *v, double d): v(v), distance(d){}
};

struct MinHeapComparator {
   bool operator()(Vertex *a, Vertex *b) {
      return a->distanceFromSource > b->distanceFromSource;
   }
};

struct MapComparator {
   bool operator()(Vertex *a, Vertex *b) {
      return a->name < b->name;
   }
};

class Graph {
    //graf će biti mapa:
    // v1 -> lista susjeda
    // v2 -> lista susjeda
    public:
        map<Vertex*, list<Neighbour*>, MapComparator> vertices;
        Vertex *startingVertex = nullptr;

        //dodaj ključ (vrh) ili nađi odgovarajući zapis u mapi
        Vertex *findOrAddVertex(string name) {
            Vertex vv(name);
            auto it = vertices.find(&vv);
            //ako sam našao čvor
            if (it != vertices.end())
                return it->first; // iterator je pair<vertex,list<pair<vertex,double>>>
            
            //ako nisam našao čvor
            Vertex *v = new Vertex(name);
            list<Neighbour*> praznaLista;
            vertices.emplace(v, praznaLista);
            return v;
        }

        void readFromFile(string filename) {
            ifstream f(filename);
            string line, token;
            Vertex v;
            while (getline(f, line)) {
                istringstream s(line);
                s >> token; //prvi token je vrh
                Vertex *v = findOrAddVertex(token);
                if (startingVertex == nullptr)
                    startingVertex = v;
                //svi ostali parovi <STRING DOUBLE> su susjedi
                while (s >> token) { // ime vrha/susjeda
                    Vertex *n = findOrAddVertex(token);
                    //sljedeći token je udaljenost tog vrha/susjeda
                    s >> token;
                    double d = stod(token);
                    Neighbour *p = new Neighbour(n,d);
                    vertices[v].push_back(p);
                }
            }
        }

        void print(){
            for (auto entry : vertices) {
                Vertex *v = entry.first;
                cout << v->name << " -> ";
                for (auto n : entry.second)
                    cout << n->v->name << "(" << n->distance << ") ";
                cout << endl;
            }
        }

        void unvisit() {
            for (auto v : vertices) {
                v.first->visited = false;
                v.first->distanceFromSource = __DBL_MAX__;
                v.first->prev = nullptr;
            }
        }

        void dijkstra() {
            cout << endl << "Dijkstra : " << endl;
            priority_queue<Vertex*, vector<Vertex*>, MinHeapComparator> h;

            //prvo sve vrhove stavim u heap
            for (auto entry : vertices) {
                //ako je početni vrh (ili npr. //if (entry.first->name == "A"))
                if (entry.first == startingVertex)                
                    entry.first->distanceFromSource = 0;
                h.push(entry.first);
            }

            //dok god ima vrhova na heapu
            while (!h.empty()){
                //pročitaj min s heapa i označi ga kao visited
                Vertex *v = h.top();
                //PAZI - što će se dogoditi ako ovdje zovemo h.pop(); ?
                v->visited = true;
                cout << "Analiziram " << v->name << " susjedi: ";

                //za svakog susjeda od v
                for (auto n : vertices[v]) {
                    //ako je susjed obiđen, preskočim ga
                    if (n->v->visited)
                        continue;
                    
                    //inače: računam novu udaljenost susjeda n od početnog vrha
                    //to je: udaljenost vrha v od početnog plus udaljenost n od v
                    double novaUdaljenost = v->distanceFromSource + n->distance;
                    cout << n->v->name << "(" << novaUdaljenost << ") ";
                    //ako je nova udaljenost manja od trenutne, zapišem novu
                    if (novaUdaljenost < n->v->distanceFromSource) {
                        n->v->distanceFromSource = novaUdaljenost;
                        n->v->prev = v;
                    }
                }

                //e sad... mijenjao sam vrijednosti po kojima je složen heap
                //moram ga ponovno posložiti, to će mi se napraviti u sklopu fje pop()
                //zato gore nisam zvao pop() - jer bi presložio heap prije mojih promjena
                h.pop();

                cout << endl;
            }
            
            // ispis svih vrhova, udaljenosti i prethodnog vrha
            for (auto entry : vertices) {
                Vertex *v = entry.first;
                if (v==startingVertex)
                    cout << "A 0 (-)" << endl;
                else
                    cout << v->name << " " << v->distanceFromSource << " (" << v->prev->name << ")" << endl;
            
            }

        }

};

int main(){
    Graph g;
    g.readFromFile("internetDijkstra.txt");
    g.print();

    g.dijkstra();

    return 0;
}