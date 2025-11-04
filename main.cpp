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
};
Node* recursive_search(Node* r, int val){
    if (r == NULL) return nullptr;
    if (r->value == val) return r;
    if (val < r->value){
        return recursive_search(r->childLeft, val);
    } else {
        return recursive_search(r->childRight, val);
    }
}
Node* iterative_search(Node*r, int val){
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
    return 0;
}
