#include <iostream>
#include <string>
#include <memory>

using namespace std;

template <typename T> class BinaryTree {
    private:
        struct Atom 
        {
                T data;
                shared_ptr<Atom> left;
                shared_ptr<Atom> right;

                Atom(const T &data) : data(data), left(nullptr), right(nullptr) {}
                Atom(const T &data, shared_ptr<Atom> left, shared_ptr<Atom> right) :
                    data(data), left(left), right(right) {}
        };

        shared_ptr<Atom> root; //private

        void insertR(shared_ptr<Atom> &node, T data) {
            //ako u node-u ima nešto, propadam lijevo ili desno
            if (node != nullptr){
                if (data < node->data)
                    insertR(node->left, data);
                else if (data > node->data)
                    insertR(node->right, data);
                else    // ako je podatak već u stablo - NEMEŽE! 
                    throw invalid_argument("Element već postoji u stablu");
            }
            else { //ako je node trenutno nullptr, tu stavljam novi podatak
                node = make_shared<Atom>(data);
            }
        }

        void printPreorderR(shared_ptr<Atom> &node) {
            if (node != nullptr) {
                cout << node->data << " ";
                printPreorderR(node->left);
                printPreorderR(node->right);
            }
        }

        void printInorderR(shared_ptr<Atom> &node) {
            if (node != nullptr) {
                printInorderR(node->left);
                cout << node->data << " ";
                printInorderR(node->right);
            }
        }

        void printPostorderR(shared_ptr<Atom> &node) {
            if (node != nullptr) {
                printPostorderR(node->left);
                printPostorderR(node->right);
                cout << node->data << " ";
            }
        }

    public:
        BinaryTree() : root(nullptr) {}

        //ubacivanje elemenata
        void insert(T data) {
            cout << "Dodajem element: " << data << endl;
            insertR(root, data);
        }

        //ispis - preorder
        void printPreorder() {
            cout << "Stablo preorder : ";
            printPreorderR(root);
            cout << endl;
        }

        void printInorder() {
            cout << "Stablo inorder  : ";
            printInorderR(root);
            cout << endl;
        }

        void printPostorder() {
            cout << "Stablo postorder: ";
            printPostorderR(root);
            cout << endl;
        }

        //pretraživanje
        bool search(T data) {
           return search(root, data);
        }

        bool search(shared_ptr<Atom> node, T data) {
            if (node) {
                if (node->data < data)
                    return search (node->right, data);
                else if (node->data > data)
                    return search (node->left, data);
                else 
                    return true;
            }
            return false;
        }

        bool remove(T data) {
            cout << "Removing element " << data << endl;
            return remove(root, data);
        }

        bool remove(shared_ptr<Atom> &node, T data) {
            if (!node)
                return false;
            
            //trazim element
            if (node->data < data) 
                return remove(node->right, data);
            else if (node->data > data)
                return remove(node->left, data);
            else {
                //našao sam el. koji želim izbaciti

                // ako je list
                //if (!node->left && !node->right) {
                //    node.reset();
                    //node = nullptr;
                //}
                //1. slučaj - list ili el. s jednim djetetom
                if(!node->left) {
                    node = node->right;
                }
                else if(!node->right)
                    node = node->left;
                else {
                    // node koji hoću obrisati ima oba djeteta
                    // a) nađi najveći el. u lijevom podstablu
                    shared_ptr<Atom> tmpnode = node->left;
                    shared_ptr<Atom> prevtmp = nullptr;
                    while (tmpnode->right) {
                        prevtmp = tmpnode;
                        tmpnode = tmpnode->right;
                    }
                    //sad mi je tmpnode najdesniji u lijevom podstablu
                    // b) kopiraj vrijednost iz tmpnode u onaj koji brišem
                    node->data = tmpnode->data;
                    //sad treba obrisati tmpnode
                    //ALI što ako on ima lijevo dijete? (desno nema)
                    if (prevtmp)
                        prevtmp->right = tmpnode->left;
                    else
                        node->left = tmpnode->left;
                }
            return true;
            }

        }

        int count() { return count(root); }

        int count(shared_ptr<Atom> &node) {
            if (node) {
                return 1 + count(node->left) + count(node->right);
            }
            return 0;
        }

        int depth() { return depth(root); }

        int depth(shared_ptr<Atom> &node) {
            if (node) {
                return 1 + std::max(depth(node->left),depth(node->right));
            }
            return 0;
        }

        int min() { return min(root); }

        int min(shared_ptr<Atom> &node) {
            if (node->left)
                return min(node->left);
            return node->data;
        }    

        int minNerek() {
            shared_ptr<Atom> curr = root;
            while (curr->left)
                curr = curr->left;
            return curr->data;
        }

        int maxNerek() {
            shared_ptr<Atom> curr = root;
            while (curr->right) {
                curr = curr->right;
            }
            return curr->data;
        }  

        void mirror() {
            return mirror(root);
        }

        void mirror(shared_ptr<Atom> &node) {
            shared_ptr<Atom> tmp;
            tmp = node->left;
            node->left = node->right;
            node->right = tmp;
            //rekurzivno za djecu
            if (node->left)
                mirror(node->left);
            if (node->right)
                mirror(node->right);
        }

        bool identical(BinaryTree bt2) {
            return identical(root, bt2.root);
        }

        bool identical(shared_ptr<Atom> &node1, shared_ptr<Atom> &node2) {
            if (!node1 && !node2)
                return true;
            else if ((node1 && !node2) || (!node1 && node2))
                return false;
            else {
                return ((node1->data == node2->data) &&
                        identical(node1->left, node2->left) &&
                        identical(node1->right, node2->right));
            }

        }
};

int main() {
    BinaryTree<int> bt;
    bt.insert(5);
    bt.insert(7);
    bt.insert(9);
    //bt.insert(8);
    //bt.insert(6);
    //bt.insert(3);
    //bt.insert(4);

    //bt.printPreorder();

    bt.printInorder();

    //bt.printPostorder();  

    //cout << "Broj 9 postoji u stablu? " << bt.search(9) << endl;

    //cout << "Broj 123 postoji u stablu? " << bt.search(123) << endl;

    bt.remove(5);

    bt.printInorder();

    cout << "Broj elemenata u stablu je " << bt.count() << endl;

    cout << "Broj elemenata: " << bt.count() << endl;
    cout << "Dubina: " << bt.depth() << endl;

    cout << "Min el: " << bt.min() << endl;
    cout << "Min el nerekurzivno: " << bt.minNerek() << endl;
    cout << "Max el nerekurzivno: " << bt.maxNerek() << endl;

    bt.mirror();
    cout << "Mirror! ";
    bt.printInorder();
    cout << "Mirror x2 ";
    bt.mirror();
    bt.printInorder();

    // cout << "bt.search(2): " << std::boolalpha << bt.search(2) << endl;
    // cout << "bt.search(8): " << std::boolalpha << bt.search(8) << endl;

    BinaryTree<int> bt1, bt2, bt3;
    bt1.insert(2);
    bt1.insert(5);
    bt1.insert(6);
    bt2.insert(2);
    bt2.insert(5);
    bt2.insert(6);
    bt3.insert(2);
    bt3.insert(6);
    bt3.insert(5);

    cout << "bt1 identical to bt2 " << std::boolalpha << bt1.identical(bt2)
        << endl;
    cout << "bt1 identical to bt3 " << std::boolalpha << bt1.identical(bt3)
        << endl;

    return 0;
}