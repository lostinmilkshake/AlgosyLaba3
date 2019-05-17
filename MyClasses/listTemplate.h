#ifndef listTemplate_h
#define listTemplate_h

#include<iostream>
using  namespace std;

template <class T> class  MyList;

template <class T>
class Element {
private:
    T data;
    Element *next;
public:
    Element<T>(){};
    Element<T>(T number) {
        this->data = number;
        this->next = nullptr;
    }
    ~Element() {
        data = 0;
    }
    T getData(){
        return data;
    }
    Element<T> getNext() {
        return next;
    }
    friend class MyList<T>;
    friend class HaffmanAlgothrim;
    friend class HaffmanNode;
};

// Объявление класса списка
template <class T>
class MyList {
private:
    Element<T> *head;
    Element<T> *tail;
    size_t size;
public:
    MyList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    MyList(std::initializer_list<T> t_list) {
        this->size = 0;
        for (auto elem : t_list) {
            push_back(elem);
        }
    };
    
    ~MyList() {
        Element<T> *p1 = head, *p2 = head;
        if (size != 0) {
            while (p2 != nullptr) {
                p2 = p1->next;
                delete p1;
                p1 = p2;
                size--;
            }
            head = nullptr;
            tail = nullptr;
        }
        size = 0;
    }
    
    Element<T> *getHead() {  //Returns pointer of the head
        return head;
    }
    Element<T> *getTail() { //Returns pointer of the tail
        return tail;
    }
    void push_front(T add);
    void push_back(T add);
    size_t get_size() const;
    void pop_front();
    void pop_back();
    Element<T> &at(int position);
    bool isEmpty() const;
    void insert(T add, int position);
    void remove(int position);
    void clear();
    void set(T add, int position);
    friend bool operator==(const MyList<T> &firstList, const MyList<T> &secondList)  {
        Element<T> *firstElement, *secondElement;
        size_t i = 0, listsSize = firstList.get_size();
        if (firstList.get_size() != secondList.get_size()) {
            return false;
        }
        else {
            firstElement = firstList.head;
            secondElement = secondList.head;
            while (i < listsSize && firstElement->data == secondElement->data) {
                firstElement = firstElement->next;
                secondElement = secondElement->next;
                i++;
            }
            if (i != listsSize) {
                return false;
            }
            else {
                return true;
            }
        }
    }
};

/*template <class T>
bool operator==(const MyList<T> &firstList, const MyList<T> &secondList) {

}*/

template <class T>
ostream &operator<<(ostream &os, const MyList<T> &lst) {
    Element<T> *element = lst.head;
    while (element != nullptr) {
        os << element->data << " ";
        
        element = element->next;
    }
    return os;
}

//Adding new element "add" to the end of the list
template <class T>
void MyList<T>::push_back(T add) {
    Element<T> *newElement;
    newElement = new Element<T>(add);
    if (size == 0) { //Checking is there any elements in list
        this->head = newElement;
        this->tail = newElement;
    }
    else {
        tail->next = newElement;
        this->tail = newElement;
    }
    size++;
}

//Adding new element "add" to the front of the list
template <class T>
void MyList<T>::push_front(T add) {
    Element<T> *newElement;
    newElement = new Element<T>(add);
    if (size == 0) { //Checking is there any elements in list
        head = newElement;
        tail = newElement;
    }
    else {
        newElement->next = head;
        head = newElement;
    }
    size++;
}

//Returning the size of list
template <class T>
size_t MyList<T>::get_size() const {
    return size;
}

//Deleting the first element of list
template <class T>
void MyList<T>::pop_back() {
    Element<T> *p1;
    if (size > 1) { //Checking is there more then one element
        p1 = head;
        while (p1->next != tail) { //Going to element, which stands before tail
            p1 = p1->next;
        }
        delete tail;
        size--;
        p1->next = nullptr;
        tail = p1;
    } else{
        if (size == 1) {
            delete head; //Just deleting the head
            size--;
        } else { //If there are no elements in the list
            throw out_of_range("There is no element to delete");
        }
    }
}

//Deleting the last element of list
template <class T>
void MyList<T>::pop_front() {
    Element<T> *begining = head;
    if (size != 0) { //Checking is there ane elements in the list
        head = head->next;
        delete begining; // deleting first element
        size--;
    }
    else { //If there are no elements
        throw out_of_range("There is no element to delete");
    }
}

//Searching for the element at "position" position (Numerations starts with 1)
template <class T>
Element<T> &MyList<T>::at(int position) {
    Element<T> *p1;
    if ((size > position) && (position >= 0)) {
        p1 = head;
        for (size_t i = 0; i < position; i++) { //Going to the element
            p1 = p1->next;
        }
        return *p1;
    } else { //If we try to get elment, which doesn't exist in the list
        throw out_of_range("Index is greater than list size");
    }
}

//Checking if the list empty
template <class T>
bool MyList<T>::isEmpty() const {
    return size == 0;
}

//Inserts new element "add" before "position" position
template <class T>
void MyList<T>::insert(T add, int position) {
    Element<T> *p1, *newElement;
    p1 = head;
    newElement = new Element<T>(add);
    if ((position < size) && (position >= 0)) {
        if (position == 0) { //If we want to add first element we just use push_front
            push_front(add);
        } else {
            if (position == size + 1) { //If we want to add last element we just use push_back
                push_back(add);
            } else {
                size++;
                for (size_t i = 0; i < position - 1; i++) {
                    //Going to the element, before which we going to insert
                    p1 = p1->next;
                }
                newElement->next = p1->next;
                p1->next = newElement;
            }
        }
    } else{ //If we try to go to the elment, which doesn't exist in the list
        throw out_of_range("Index is greater than list size");
    }
}

//Removes the element at "position" position
template <class T>
void MyList<T>::remove(int position) {
    Element<T> *p1, *p2;
    if (position == 0) {
        p1 = head;
        head = p1->next;
        delete p1;
    } else {
        if ((position < size) && (position > 0)) {
            p1 = head;
            for (size_t i = 0; i < position - 1; i++) {
                //Going to the element, before which we going to delete
                p1 = p1->next;
            }
            p2 = p1->next;
            p1->next = p2->next; //Changing pointers
            size--;
            delete p2;
        } else { //If we try to go to the elment, which doesn't exist in the list
            throw out_of_range("Index is greater than list size");
        }
    }
}

//Deleting all elements of list
template <class T>
void MyList<T>::clear() {
    Element<T> *p1, *p2 = head;
    p1 = head;
    while (p2 != nullptr) { //Going through each element and deleting all of them
        p2 = p1->next;
        delete p1;
        p1 = p2;
        size--;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

//Changing the data of element at "position" position to "add"
template <class T>
void MyList<T>::set(T add, int position) {
    Element<T> *p1;
    
    if ((position < size) && (position >= 0)) {
        p1 = head;
        for (size_t i = 0; i < position; i++) {
            //Going to the element, which data we want to change
            p1 = p1->next;
        }
        p1->data = add;
    } else{ //If we try to go to the elment, which doesn't exist in the list
        throw out_of_range("Index is greater than list size");
    }
}


#endif /* listTemplate_h */
