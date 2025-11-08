#include <iostream>
using namespace std;

struct Node{
    int value;
    Node* childLeft;
    Node* childRight;
    Node(){
        childLeft = nullptr;
        childRight = nullptr;
    }
    Node(int val){
        value = val;
        childLeft = nullptr;
        childRight = nullptr;
    }
};

Node* recursive_insert(Node* r, int val);
Node* iterative_insert(Node* r, int val);
Node* recursive_search(Node* r, int val);
Node* iterative_search(Node* r, int val);
void preOrder(Node* r);
void inOrder(Node* r);
void postOrder(Node* r);
void deletenode(Node*& r, int value);

int main(){
    Node* n = new Node(5);
    Node* t;
    cout << recursive_insert(n, 4)->value << endl;
    cout << recursive_insert(n, 7)->value << endl;
    cout << recursive_insert(n, 5)->value << endl;

    cout << iterative_insert(n, 6)->value << endl;
    cout << iterative_insert(n, 8)->value << endl;
    cout << iterative_insert(n, 3)->value << endl;


    t = recursive_search(n, 5);
    if (t!= nullptr) cout << recursive_search(n, 5)->value << endl;
    t = recursive_search(n, 6);
    if (t!= nullptr) cout << recursive_search(n, 6)->value << endl;
    t = recursive_search(n, 2);
    if (t!= nullptr) cout << recursive_search(n, 2)->value << endl;
    preOrder(n);
    cout << endl << endl;
    inOrder(n);
    cout << endl << endl;
    postOrder(n);
    cout << endl << endl;

    deletenode(n, 5);
    cout << "deleted 5" << endl;
    inOrder(n);
    deletenode(n, 8);
    cout << "deleted 8" << endl;
    inOrder(n);
    deletenode(n, 4);
    cout << "deleted 4" << endl;
    inOrder(n);
    return 0;
}

Node* recursive_insert(Node* r, int val){
    if (r == NULL) return new Node(val);
    if (r->value == val) return r;
    if (r->value > val){
        r->childLeft = recursive_insert(r->childLeft, val);
    } else {
        r->childRight = recursive_insert(r->childRight, val);
    }
    return r;
}
Node* iterative_insert(Node* r, int val){
    Node* t = r;
    if (r == NULL) return new Node(val);
    while(t != nullptr){
        if (t->value == val) return t;
        if (t->value > val){
            if (t->childLeft == nullptr){
                t->childLeft = new Node(val);
                return t->childLeft;
            }
            t = t->childLeft;
            continue;
        } else {
            if (t->childRight == nullptr){
                t->childRight = new Node(val);
                return t->childRight;
            }
            t = t->childRight;
            continue;
        }
    }
    return t;
}
Node* recursive_search(Node* r, int val){
    if (r == NULL) return nullptr;
    if (r->value == val) return r;
    if (val < r->value){
        return recursive_search(r->childLeft, val);
    } else {
        return recursive_search(r->childRight, val);
    }
}
Node* iterative_search(Node* r, int val){
    Node* t = r;
    if (r == NULL) return nullptr;
    while (t != nullptr){
        if (t->value == val) return t;
        if (t->value > val){
            if (t->childLeft == nullptr){
                return nullptr;
            }
            t = t->childLeft;
            continue;
        } else {
            if (t->childRight == nullptr){
                return nullptr;
            }
            t = t->childRight;
            continue;
        }
    }
    return t;
}
void preOrder(Node* r){
    if (r == nullptr) return;
    cout << r->value << " ";
    preOrder(r->childLeft);
    preOrder(r->childRight);
}
void inOrder(Node* r){
    if (r == nullptr) return;
    inOrder(r->childLeft);
    cout << r->value << " ";
    inOrder(r->childRight);
}
void postOrder(Node* r){
    if (r == nullptr) return;
    postOrder(r->childLeft);
    postOrder(r->childRight);
    cout << r->value << " ";
}
void deletenode(Node*& r, int value){
    Node* t = recursive_search(r, value);
    if (t == nullptr) return;
    if (t->childLeft == nullptr && t->childRight == nullptr){                   //case no children
        t = r;                                                                      // set t as root
        while (t->childLeft || t->childRight){
            if (t->childLeft && t->childLeft->value == value){
                t->childLeft = nullptr;
                break; 
            }               
            if (t->childRight && t->childRight->value == value){
                t->childRight = nullptr;
                break;
            }
            if (t->value > value){
                t = t->childLeft;
            } else {
                t = t->childRight;
            }
        }
    } else {
        if (t->childLeft != nullptr && t->childRight != nullptr){               //case both children
            Node* successor = t->childRight;
            Node* succp = t;
            while (successor->childLeft != nullptr){                                //finding inorder successor and its parent
                succp = successor;
                successor = successor->childLeft;
            }
            if (succp->childLeft == successor) succp->childLeft = successor->childRight;
            else succp->childRight = successor->childRight;
            if (r->value == value){                                                 //if target is root
                successor->childLeft = r->childLeft;
                successor->childRight = r->childRight;
                r = successor;
                return;
            }
            t = r;
            while (t->childLeft->value != value && t->childRight->value != value){  //t becomes parent
                if (t->value > value){
                    t = t->childLeft;
                } else {
                    t = t->childRight;
                }
            }
            if (t->childLeft->value == value){                                      //target is parent's left
                successor->childLeft = t->childLeft->childLeft;
                successor->childRight = t->childLeft->childRight;
                delete t->childLeft;
                t->childLeft = successor;
            } else {                                                                //target is parent's right
                successor->childLeft = t->childRight->childLeft;
                successor->childRight = t->childRight->childRight;
                delete t->childRight;
                t->childRight = successor;
            }
        } else {                                                                //one child
            t = r;
            if (r->value == value){                                                 //if target is root
                if (r->childRight == nullptr){
                    r = t->childLeft;
                    t->childLeft = nullptr;
                } else {
                    r = t->childRight;
                    t->childRight = nullptr;
                }
                return;
            }
            while (t->childLeft->value != value && t->childRight->value != value){  //t becomes parent
                if (t->value > value){
                    t = t->childLeft;
                } else {
                    t = t->childRight;
                }
            }
            if (t->childLeft->value == value){                                      //target is parent's left
                Node* temp = t->childLeft;
                if (temp->childRight == nullptr){                               //target has left child
                    t->childLeft = temp->childLeft;
                    delete temp;
                } else {                                                                //target has right child
                    t->childLeft = temp->childRight;
                    delete temp;
                }
            } else {                                                                //target is parent's right
                Node* temp = t->childRight;
                if (temp->childRight == nullptr){
                    t->childRight = temp->childLeft;
                    delete temp;
                } else {
                    t->childRight = temp->childRight;
                    delete temp;
                }
            }
        }
    }
}