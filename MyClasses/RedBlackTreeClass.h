//#pragma once
#ifndef RedBlackTreeClass_h
#define RedBlackTreeClass_h

#include<iostream>
#include "listTemplate.h"
#include <stack>


using namespace std;

template <class T, class V> class MyMap;
template <class T, class V> class Node;

// Defiining the class RedBlack Tree
template <class T, class V>
class MyMap {
private:
	Node<T, V>* root; //Pointer to the top of the tree
	void turnLeft(Node<T, V>* x); //Function for turning nodes left
	void turnRight(Node<T, V>* x); //Function for turning nodes right
	void insertFix(Node<T, V>* fixNode); //Fixing the balance after inserting new elemnt
	void fixRemove(Node<T, V>* fixNode, Node<T, V>* fixParent); //Fixing the balance after deleting element 
public:
	MyMap() { //Constuctor 
		root = nullptr;
	}
	~MyMap() { //Destructor
		clear();
	}
	void insert(T key, V value); //Insertnig new elements in map
	void remove(T key); //Removing elements from map
	void clear(); //Clearing the map
	Node<T, V>* returnRoot() {
		return root;
	}
	MyList<T>* get_keys(); //Getting all the keys from the map
	MyList<V>* get_values(); //Getting all the values from the map
	Node<T, V>* find(T key); //Finding the element with the key
	friend class HuffmanAlgothrim;
};

template <class T, class V>
class Node {
private:
	T key; //Key of node
	bool color; //if true then color red, else color black
	V value; //Value of the node
	Node* left; //Pointer to left son
	Node* right; //Pointer to right son
	Node* parent; //Pointer to parent
	void clearNode(); //Clearing the data from each node
	bool getColor(); //Getting the color of each node
public:
	Node(); //Constructor
	Node(T key, V value, Node* parent); //Constructor with values
	~Node(); //Destructor
	T returnKey() { //Returning the key of the element
		return key;
	}
	V returnValue() { //Returning the value of the element
		return value;
	}
	friend class MyMap<T, V>;
	friend class HuffmanAlgothrim;
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
Node<T, V>::Node(T key, V value, Node* parent) {
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
	//value = 0;
}

template <class T, class V>
void Node<T, V>::clearNode() {
	if (this != nullptr) {
		left->clearNode(); //Recursive traversal through the left son
		right->clearNode(); //Recursive traversal through the right son
		delete this; //Deleting this element
	}
}

template <class T, class V>
bool Node<T, V>::getColor() {
	if (this != nullptr) { //If this node isn't a leaf the return it's color
		return this->color;
	}
	else //Else return black
	{
		return false;
	}
}
//Defining MyMap methods

template <class T, class V>
void MyMap<T, V>::turnLeft(Node<T, V>* fixingNode) {
	Node<T, V>* rightSon = fixingNode->right;
	fixingNode->right = rightSon->left;
	if (rightSon->left != nullptr) { //If the rightSon  have a left child then it's parent will be fixingNode
		rightSon->left->parent = fixingNode;
	}
	if (rightSon != nullptr) { //If the rightSon isn't a leaf, than it's parent now fixingNode parent
		rightSon->parent = fixingNode->parent;
	}
	if (fixingNode->parent != nullptr) { //If the fixingNode have a parent then do the replacemenets
		if (fixingNode == fixingNode->parent->left) { //If fixingNode is the left son
			fixingNode->parent->left = rightSon; //Then replace fixingNode with rightSon
		}
		else { //If the fixingNode is the right son
			fixingNode->parent->right = rightSon; //Then replace fixingNode with rightSon
		}
	}
	else { //Else rightSon becoms the root of the tree
		root = rightSon;
	}
	rightSon->left = fixingNode;
	if (fixingNode != nullptr) { //If fixingNode isn't a leaf, the his parent now is rightSon
		fixingNode->parent = rightSon;
	}
}

template <class T, class V>
void MyMap<T, V>::turnRight(Node<T, V>* turningNode) {
	Node<T, V>* leftSon = turningNode->left;
	turningNode->left = leftSon->right;
	if (leftSon->right != nullptr) { //If the leftSon have a right child then it's parent will be turningNode
		leftSon->right->parent = turningNode;
	}
	if (leftSon != nullptr) { //If the leftSon isn't a leaf, than it's parent now turningNode parent
		leftSon->parent = turningNode->parent;
	}
	if (turningNode->parent != nullptr) { //If the turningNode have a parent then do the replacemenets
		if (turningNode == turningNode->parent->right) { //If turningNode is the right son
			turningNode->parent->right = leftSon; //Then replace turningNode with leftSon
		}
		else { //If turningNode is the left son
			turningNode->parent->left = leftSon;  //Then replace turningNode with leftSon
		}
	}
	else { //Else leftSon becoms the root of the tree
		root = leftSon;
	}
	leftSon->right = turningNode;
	if (turningNode != nullptr) { //If turningNode isn't a leaf, the his parent now is leftSon
		turningNode->parent = leftSon;
	}
}


template <class T, class V>
void MyMap<T, V>::insert(T key, V value) {
	Node<T, V>* current, * parent = nullptr, * newNode;
	current = root;
	try {
		newNode = find(key); //Finding the element with the new key
		throw invalid_argument("This key already exist"); //If this key already exist then throw the exepction
	}
	catch (out_of_range error) { //If we caught the expection from find method, then inserting new element
		while (current != nullptr) { //Finding the where to put new element
			parent = current;
			if (key < current->key) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		newNode = new Node<T, V>(key, value, parent); //Creating new node with given values
		if (parent != nullptr) { //Deciding where to put new element
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
		insertFix(newNode); //Fixing the balance
	}
}

template <class T, class V>
void MyMap<T, V>::insertFix(Node<T, V>* fixNode) {
	Node<T, V>* uncle = nullptr;
	while ((fixNode != root) && (fixNode->parent->getColor() == true)) { //Fixing until we hit the root or parent color will be red
		if (fixNode->parent == fixNode->parent->parent->left) { //If fixNode parent is the left son
			uncle = fixNode->parent->parent->right; //Then initialize the proper uncel
			if (uncle->getColor() == true) { //If uncle's color is red
				fixNode->parent->color = false; //Reverse grandparent's, parent's and uncle's colors
				uncle->color = false;
				fixNode->parent->parent->color = true;
				fixNode = fixNode->parent->parent; //Fixing regarding of grandparent
			}
			else {//If uncle's color is black
				if (fixNode == fixNode->parent->right) { //If fixNode is the right son
					fixNode = fixNode->parent; //Then turn Left regarding of it's parent
					turnLeft(fixNode);
				}
				fixNode->parent->color = false; //Change the fixNode's parent's and grandparent's color
				fixNode->parent->parent->color = true;
				turnRight(fixNode->parent->parent); //Turn right regarding of it's grandparent
			}
		}
		else { //If the fixNode's parent is the right son
			uncle = fixNode->parent->parent->left; //Then initialize the proper uncel
			if (uncle->getColor() == true) { //If uncle's color is red
				fixNode->parent->color = false; //Reverse grandparent's, parent's and uncle's colors
				uncle->color = false;
				fixNode->parent->parent->color = true;
				fixNode = fixNode->parent->parent; //Fixing regarding of grandparent
			}
			else { //If uncle's color is black
				if (fixNode == fixNode->parent->left) { //If fixNode is the left son
					fixNode = fixNode->parent; //Then turn right regarding of it's parent
					turnRight(fixNode);
				}
				fixNode->parent->color = false; //Change the fixNode's parent's and grandparent's color
				fixNode->parent->parent->color = true;
				turnLeft(fixNode->parent->parent); //Turn right regarding of it's grandparent
			}
		}
	}
	root->color = false; //Change root color to black
}

template <class T, class V>
Node<T, V>* MyMap<T, V>::find(T key) {
	Node<T, V>* findNode;
	findNode = root;
	while (findNode != nullptr && findNode->key != key) { //Finding where is the element
		if (key < findNode->key) {
			findNode = findNode->left;
		}
		else {
			findNode = findNode->right;
		}
	}
	if (findNode == nullptr) { //If we haven't found anything, then trow the exepction
		throw out_of_range("There is no elements with this key");
	}
	return findNode;
}


template <class T, class V>
void MyMap<T, V>::remove(T key) {
	Node<T, V>* deleteNode, * deleteSon, * deleteObj;
	deleteNode = find(key); //Finding wich element to remove
	if (deleteNode->left == nullptr || deleteNode->right == nullptr) { //Initialize the helper deleteObj
		deleteObj = deleteNode;
	}
	else {
		deleteObj = deleteNode->right;
		while (deleteObj->left != nullptr) {
			deleteObj = deleteObj->left;
		}
	}
	if (deleteObj->left != nullptr) { //Initialize the helper deleteSon
		deleteSon = deleteObj->left;
	}
	else {
		deleteSon = deleteObj->right;
	}
	if (deleteObj->parent != nullptr) { //If deleteObj doesn't have a parent
		if (deleteSon != nullptr) { //If deleteSon isn't a leaf then it's parent now deleteObj's parent
			deleteSon->parent = deleteObj->parent;
		}
		if (deleteObj == deleteObj->parent->left) { //deleteSon replacing the deleteObj
			deleteObj->parent->left = deleteSon;
		}
		else {
			deleteObj->parent->right = deleteSon;
		}
	}
	else {
		deleteSon = root; //Else it becomes root of the tree 
	}
	if (deleteObj != deleteNode) { //If deleteObj isn't equal to deleteNode
		deleteNode->key = deleteObj->key; //Then deleteObj copyes the deleteNode values
		deleteNode->value = deleteObj->value;
	}
	if (deleteObj->color == false) { //If deleteObj's color is black
		fixRemove(deleteSon, deleteObj->parent); //Then fix the balance
	}
	if (deleteObj != root) { //Deleting deleteObj
		delete deleteObj;
	}
	else {
		clear();
	}
}

template <class T, class V>
void MyMap<T, V>::fixRemove(Node<T, V>* fixNode, Node<T, V>* fixParent) {
	Node<T, V>* brother;
	while (fixNode != root && fixNode->getColor() == false) { //Fixing until we hit the root or fixNode's color will be red
		if (fixNode == fixParent->left) { //If fixNode is the left son
			brother = fixParent->right;  //Then initialize the proper uncel
			if (brother->getColor() == true) { //If brother's color is red
				brother->color = false; //Then reverse parent's and brother's color
				fixParent->color = true;
				turnLeft(fixParent); //Turn left regarding of it's parent
				brother = fixParent->right;
			}
			if (brother->left->getColor() == false && brother->right->getColor() == false) { //If brother's sons are leafs
				brother->color = true; //Then change the color
				fixNode = fixParent; //Fixing regarding of it's parent
			}
			else { //Else
				if (brother->right->getColor() == false) { //If brother's right son's color is black
					if (brother->left != nullptr) {
						brother->left->color = false;
					}//Chage the color's
					brother->color = true;
					turnRight(brother);  //Turn right regarding of it's brother
					brother = fixParent->right;
				}
				brother->color = fixParent->color; //Copy the parent's color
				fixParent->color = false; //Chage colors
				fixNode->right->color = false;
				turnLeft(fixParent); //Turn left regarding of it's parent
				fixNode = root; //Fixing regarding of root
			}
		}
		else { //If fixNode is the right son
			brother = fixParent->left;  //Then initialize the proper uncel
			if (brother->getColor() == true) { //If brother's color is red
				brother->color = false; //Then reverse parent's and brother's color
				fixParent->color = true;
				turnRight(fixParent);//Turn right regarding of it's parent
				brother = fixParent->left;
			}
			if (brother->right->getColor() == false && brother->left->getColor() == false) { //If brother's sons are leafs
				brother->color = true; //Then change the color
				fixNode = fixParent; //Fixing regarding of it's parent
			}
			else {
				if (brother->left->getColor() == false) { //If brother's right son's color is black
					if (brother->right != nullptr) {
						brother->right->color = false;
					}//Chage the color's
					brother->color = true;
					turnLeft(brother);  //Turn left regarding of it's brother
					brother = fixParent->left;
				}
				brother->color = fixParent->color; //Copy the parent's color
				fixParent->color = false; //Chage colors
				brother->left->color = false;
				turnRight(fixParent); //Turn right regarding of it's parent
				fixNode = root; //Fixing regarding of root
			}
		}
	}
}

template <class T, class V>
void MyMap<T, V>::clear() {
	root->clearNode(); //Clearing each node
	root = nullptr;
}


template <class T, class V>
MyList<T>* MyMap<T, V>::get_keys() {
	MyList<V>* keyList = new MyList<T>();
	Node<T, V>* helpNode = root;
	stack< Node<T, V>*> stackKey;
	while (!stackKey.empty() || helpNode != nullptr) {
		if (helpNode != nullptr) {
			keyList->push_back(helpNode->key); //Adding the element to the list
			if (helpNode->right) {
				stackKey.push(helpNode->right); //Adding the elemt to the stack
			}
			helpNode = helpNode->left;
		}
		else {
			helpNode = stackKey.top();
			stackKey.pop(); //Taking element from the stack
		}
	}
	return keyList;
}



template <class T, class V>
MyList<V>* MyMap<T, V>::get_values() {
	MyList<V>* valueList = new MyList<V>();
	Node<T, V>* helpNode = root;
	stack< Node<T, V>*> stackValues;
	while (!stackValues.empty() || helpNode != nullptr) {
		if (helpNode != nullptr) {
			valueList->push_back(helpNode->value);//Adding the element to the list
			if (helpNode->right) {
				stackValues.push(helpNode->right); //Adding the elemt to the stack
			}
			helpNode = helpNode->left;
		}
		else {
			helpNode = stackValues.top();
			stackValues.pop();  //Taking element from the stack
		}
	}
	return valueList;
}


#endif /* MyMapClass_h */
