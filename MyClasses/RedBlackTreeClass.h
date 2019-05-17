#ifndef RedBlackTreeClass_h
#define RedBlackTreeClass_h

#include<iostream>
#include "listTemplate.h"
#include <stack>

//Перенести нужные значения в private

using namespace std;

template <class T, class V> class RedBlackTree;
template <class T, class V> class Node;

// Defiining the class RedBlack Tree
template <class T, class V>
class RedBlackTree {
private:
    Node<T, V> *root;
    void turnLeft(Node<T, V> *x);
    void turnRight(Node<T, V> *x);
    void insertFix(Node<T, V> *fixNode);
    void fixRemove(Node<T, V> *fixNode, Node<T, V> *fixParent);
public:
    RedBlackTree() {
		root = nullptr;
    }
    ~RedBlackTree() {
        clear();
    }
    void insert(T key, V value);
    void remove(T key);
    void clear();
    Node<T, V> *returnRoot(){
        return root;
    }
    MyList<T> *get_keys();
    MyList<V> *get_values();
    Node<T, V> *find(T key);
    Node<T, V> &maxOrder();
};

template <class T, class V>
class Node {
private:
    T key;
    bool color; //if true then color red, else color black
    Node *left;
    Node *right;
    Node *parent;
    void clearNode();
    MyList<T> get_keys_Node(MyList<T> keyList);
    MyList<T> get_values_Node(MyList<V> valueList);
    bool getColor();
public:
    V value;
    Node();
    Node(T key, V value, Node *parent);
    ~Node();
    T returnKey() {
        return key;
    }
    V returnValue() {
        return value;
    }
	friend class RedBlackTree<T, V>;
    friend class HaffmanAlgothrim;
};

//Defining Node methods

template <class T, class V>
Node<T, V>::Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = false;
    this->key = 0;
    this->value = 0;
}

template <class T, class V>
Node<T, V>::Node (T key, V value, Node *parent) {
    //this->left = Tree<T, V>->nullptr;
    //this->right = Tree<T, V>->nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = parent;
    this->key = key;
    this->color = true;
    this->value = value;
}

template <class T, class V>
Node<T, V>::~Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    key = 0;
    value = 0;
}

template <class T, class V>
void Node<T, V>::clearNode() {
    if (this != nullptr) {
        left->clearNode();
        right->clearNode();
        delete this;
    }
}

template <class T, class V>
MyList<T> Node<T, V>::get_keys_Node(MyList<T> keyList) {
    if (this != nullptr) {
        keyList = left->get_keys_Node(keyList);
        keyList = right->get_keys_Node(keyList);
        keyList.push_back(this->key);
    }
    return keyList;
}

template <class T, class V>
MyList<T> Node<T, V>::get_values_Node(MyList<V> valueList) {
/*    if (this != nullptr) {
        valueList = left->get_values_Node(valueList);
        valueList = right->get_values_Node(valueList);
        valueList.push_back(this->value);
    }
    return valueList;
*/
}

template <class T, class V>
bool Node<T, V>::getColor() {
	if (this != nullptr) {
		return this->color;
	}
	else
	{
		return false;
	}
}
//Defining RedBlackTree methods

template <class T, class V>
void RedBlackTree<T, V>::turnLeft (Node<T, V> *fixingNode) {
    Node<T, V> *rightSon = fixingNode->right;
    fixingNode->right = rightSon->left;
    if (rightSon->left != nullptr) {
        rightSon->left->parent = fixingNode;
    }
    if (rightSon != nullptr) {
        rightSon->parent = fixingNode->parent;
    }
    if (fixingNode->parent != nullptr) {
        if (fixingNode == fixingNode->parent->left) {
            fixingNode->parent->left = rightSon;
        }
        else {
            fixingNode->parent->right = rightSon;
        }
    }
    else {
        root = rightSon;
    }
    rightSon->left = fixingNode;
    if (fixingNode != nullptr) {
        fixingNode->parent = rightSon;
    }
}

template <class T, class V>
void RedBlackTree<T, V>::turnRight(Node<T, V> *turningNode) {
    Node<T, V> *leftSon = turningNode->left;
    turningNode->left = leftSon->right;
    if (leftSon->right != nullptr) {
        leftSon->right->parent = turningNode;
    }
    if (leftSon != nullptr) {
        leftSon->parent = turningNode->parent;
    }
    if (turningNode->parent != nullptr) {
        if (turningNode == turningNode->parent->right) {
            turningNode->parent->right = leftSon;
        }
        else {
            turningNode->parent->left = leftSon;
        }
    }
    else {
        root = leftSon;
    }
    leftSon->right = turningNode;
    if (turningNode != nullptr) {
        turningNode->parent = leftSon;
    }
}


template <class T, class V>
void RedBlackTree<T, V>::insert(T key, V value) {
    Node<T, V> *current, *parent = nullptr, *newNode;
    current = root;
    try {
        newNode = find(key);
        throw invalid_argument("This key already exist");
    }
    catch (out_of_range error) {
        while (current != nullptr) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        newNode = new Node<T, V>(key, value, parent);
        if (parent != nullptr) {
            if (key < parent->key) {
                parent->left = newNode;
            }
            else {
                parent->right = newNode;
            }
        }
        else {
            root = newNode;
        }
        insertFix(newNode);
    }
}

template <class T, class V>
void RedBlackTree<T, V>::insertFix(Node<T, V> *fixNode) {
    Node<T, V> *uncle = nullptr;
    while ((fixNode != root) && (fixNode->parent->getColor() == true)) {
        if (fixNode->parent == fixNode->parent->parent->left) {
            uncle = fixNode->parent->parent->right;
            if (uncle->getColor() == true) {
                fixNode->parent->color = false;
                uncle->color = false;
                fixNode->parent->parent->color = true;
                fixNode = fixNode->parent->parent;
            }
            else {
                if (fixNode == fixNode->parent->right) {
                    fixNode = fixNode->parent;
                    turnLeft(fixNode);
                }
                fixNode->parent->color = false;
                fixNode->parent->parent->color = true;
                turnRight(fixNode->parent->parent);
            }
        }
        else {
            uncle = fixNode->parent->parent->left;
            if (uncle->getColor() == true) {
                fixNode->parent->color = false;
                uncle->color = false;
                fixNode->parent->parent->color = true;
                fixNode = fixNode->parent->parent;
            }
            else {
                if (fixNode == fixNode->parent->left) {
                    fixNode = fixNode->parent;
                    turnRight(fixNode);
                }
                fixNode->parent->color = false;
                fixNode->parent->parent->color = true;
                turnLeft(fixNode->parent->parent);
            }
        }
    }
    root->color = false;
}

template <class T, class V>
Node<T, V> *RedBlackTree<T, V>::find(T key) {
    Node<T, V> *findNode;
    findNode = root;
    while (findNode != nullptr && findNode->key != key) {
        if (key < findNode->key) {
            findNode = findNode->left;
        }
        else {
            findNode = findNode->right;
        }
    }
    if (findNode == nullptr) {
        throw out_of_range("There is no elements with this key");
    }
    return findNode;
}


template <class T, class V>
void RedBlackTree<T, V>::remove(T key){
    Node<T, V> *deleteNode, *deleteSon, *deleteObj;
    deleteNode = find(key);
    if (deleteNode->left == nullptr || deleteNode->right == nullptr) {
        deleteObj = deleteNode;
    }
    else {
        deleteObj = deleteNode->right;
        while (deleteObj->left != nullptr) {
            deleteObj = deleteObj->left;
        }
    }
    if (deleteObj->left != nullptr) {
        deleteSon = deleteObj->left;
    }
    else {
        deleteSon = deleteObj->right;
    }
    if (deleteObj->parent != nullptr) {
        if (deleteSon != nullptr) {
            deleteSon->parent = deleteObj->parent;
        }
        if (deleteObj == deleteObj->parent->left) {
            deleteObj->parent->left = deleteSon;
        }
        else {
            deleteObj->parent->right = deleteSon;
        }
    }
    else {
        deleteSon = root;
    }
    if (deleteObj != deleteNode) {
        deleteNode->key = deleteObj->key;
    }
    if (deleteObj->color == false) {
		fixRemove(deleteSon, deleteObj->parent);
    }
    if (deleteObj != root) {
        delete deleteObj;
    }
    else {
        clear();
    }
}

template <class T, class V>
void RedBlackTree<T, V>::fixRemove(Node<T, V> *fixNode, Node<T, V> *fixParent) {
    Node<T, V> *brother;
    while (fixNode != root && fixNode->getColor() == false) {
        if (fixNode == fixParent->left) {
            brother  = fixParent->right;
            if (brother->getColor() == true) {
                brother->color = false;
                fixParent->color = true;
                turnLeft(fixParent);
                brother = fixParent->right;
            }
            if (brother->left->getColor() == false && brother->right->getColor() == false) {
                brother->color = true;
                fixNode = fixParent;
            }
            else {
                if (brother->right->getColor() == false) {
                    brother->left->color = false;
                    brother->color = true;
                    turnRight(brother);
                    brother = fixParent->right;
                }
                brother->color = fixParent->color;
                fixParent->color = false;
                fixNode->right->color = false;
                turnLeft(fixParent);
                fixNode = root;
            }
        }
        else {
            brother = fixParent->left;
            if (brother->getColor() == true) {
                brother->color = false;
                fixParent->color = true;
                turnRight(fixParent);
                brother = fixParent->left;
            }
            if (brother->right->getColor() == false && brother->left->getColor() == false) {
                brother->color = true;
                fixNode = fixParent;
            }
            else {
                if (brother->left->getColor() == false ) {
                    if (brother->right != nullptr) {
                        brother->right->color = false;
                    }
                    brother->color = true;
                    turnLeft(brother);
                    brother = fixParent->left;
                }
                brother->color = fixParent->color;
                fixParent->color = false;
                brother->left->color = false;
                turnRight(fixParent);
                fixNode = root;
            }
        }
    }
}

template <class T, class V>
void RedBlackTree<T, V>::clear() {
    root->clearNode();
    root = nullptr;
}


template <class T, class V>
MyList<T> *RedBlackTree<T, V>::get_keys() {
    MyList<V> *keyList = new MyList<T>();
    Node<T, V> *helpNode = root;
    stack< Node<T, V> *> stackKey;
    while (!stackKey.empty() || helpNode != nullptr) {
        if (helpNode != nullptr) {
            keyList->push_back(helpNode->key);
            if (helpNode->right) {
                stackKey.push(helpNode->right);
            }
            helpNode = helpNode->left;
        }
        else {
            helpNode = stackKey.top();
            stackKey.pop();
        }
    }
    return keyList;
}



template <class T, class V>
MyList<V> *RedBlackTree<T, V>::get_values() {
    MyList<V> *valueList = new MyList<V>();
    Node<T, V> *helpNode = root;
    stack< Node<T, V> *> stackValues;
    while (!stackValues.empty() || helpNode != nullptr) {
        if (helpNode != nullptr) {
            valueList->push_back(helpNode->value);
            if (helpNode->right) {
                stackValues.push(helpNode->right);
            }
            helpNode = helpNode->left;
        }
        else {
            helpNode = stackValues.top();
            stackValues.pop();
        }
    }
    return valueList;
}


#endif /* RedBlackTreeClass_h */
