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
        //TO-DO
};

int main() {
    BinaryTree<int> bt;
    bt.insert(5);
    bt.insert(7);
    bt.insert(9);
    bt.insert(8);
    bt.insert(6);
    bt.insert(3);
    bt.insert(4);

    bt.printPreorder();

    bt.printInorder();

    bt.printPostorder();   

    return 0;
}