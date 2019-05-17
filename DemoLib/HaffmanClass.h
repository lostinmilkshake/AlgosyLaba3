#ifndef HaffmanClass_h
#define HaffmanClass_h

#include <iostream>
#include "\Users\Dogge!\source\repos\AlgosyLaba3\AlgosyLaba3\MyClasses\RedBlackTreeClass.h"
#include <iomanip>

using namespace std;

class HaffmanNode {
private:
    char symbol; 
    size_t frequence;
    HaffmanNode *right;
    HaffmanNode *left;
    string code;
public:
	HaffmanNode() {
        symbol = '\0';
        frequence = 0;
        code = "";
        right = nullptr;
        left = nullptr;
    }
    HaffmanNode(char symbol, size_t frequence, HaffmanNode *right = nullptr, HaffmanNode *left = nullptr) {
        this->symbol = symbol;
        this->frequence = frequence;
        this->right = right;
        this->left = left;
    }
    friend class HaffmanAlgothrim;
};


class HaffmanAlgothrim {
private:
	MyMap<char, size_t> myMap;
	string inputString;
	MyList<HaffmanNode*> priorityOrder;
	MyMap<char, string> mapCodes;
	void transform();
	void filling(Node<char, size_t>* element);
	void insertInOrder(HaffmanNode* newHaffmanNode);
	void fillCodes();
	void fillCode(HaffmanNode* top, string code);
public:
    HaffmanAlgothrim(string input) {
        Node<char, size_t> *helpNode;
        inputString = input;
        cout << "Input string is " << inputString << " weight " << 8 * inputString.size() << " bits" << endl;
        for (size_t i = 0; i < input.size(); i++) { //Filling the map
            try { //If it's new symbol, create new map element
                myMap.insert(input[i], 1);
            }
            catch (invalid_argument error) { //else increment the frequence of previous one
                helpNode = myMap.find(input[i]);
                helpNode->value++;
            }
        }
        transform();
    }

    string codding();
    string haffmanDecrypt(string encodedString);

};

void HaffmanAlgothrim::transform() { //Filling the elements from MyMap into MyList
    Node<char, size_t> *element = myMap.returnRoot();
    filling(element);
}

void HaffmanAlgothrim::filling(Node<char, size_t> *element) { //Going through every map element
    while (element != nullptr) {
        filling(element->left);
        filling(element->right);
        HaffmanNode *newHaffmanNode = new HaffmanNode(element->key, element->value); //Creating new haffman node
        insertInOrder(newHaffmanNode);
        return;
    }
 }

void HaffmanAlgothrim::insertInOrder (HaffmanNode *newHaffmanNode) { //Deciding where to put new element in list
    Element<HaffmanNode*> *helpNode = priorityOrder.getHead();
    size_t i = 0;
    while (helpNode != nullptr && helpNode->data->frequence < newHaffmanNode->frequence) { //Finding where to put this element
        helpNode=helpNode->next;
        i++;
    }
    if (helpNode == nullptr) { //If it is the end of the list, then insert in the end
        priorityOrder.push_back(newHaffmanNode);
    }
    else { //Else insert before element with higher priority
        priorityOrder.insert(newHaffmanNode, i);
    }
}

string HaffmanAlgothrim::codding() { //Encryptig message in saving codes for each elemenet
    HaffmanNode *right, *left, *top;
    string codedString = "";
    size_t weight = 0;
    while (priorityOrder.get_size() != 1) { //Creating Haffman tree using MyList
        Element<HaffmanNode*> helpElement;
        helpElement = priorityOrder.at(0);
        right = helpElement.data;
        priorityOrder.pop_front(); //Taking first element and putting it as a right son
        helpElement = priorityOrder.at(0);
        left = helpElement.data;
        priorityOrder.pop_front(); //Taking first element and putting it as a left son
        top = new HaffmanNode('\0', left->frequence + right->frequence, right, left);
        insertInOrder(top); //Insert this "subtree" in MyList
    }
    fillCodes(); //Finding the code of each element
    cout << "Encoded message: ";
    for (size_t i = 0; i < inputString.size(); i++) { //Encoding the message
		Node<char, string>* newNode;
		newNode = mapCodes.find(inputString[i]);
		codedString += newNode->returnValue();
		weight += newNode->returnValue().size();
    }
    cout << codedString << " weight " << weight << " bits" << endl;
    cout << "Compression ratio " <<   (( (double) weight )/ ((double) (8 * inputString.size())) ) * 100 << "%" << endl;
    return codedString;
}

void HaffmanAlgothrim::fillCodes() { //Finding the code of each element
    HaffmanNode *top = priorityOrder.getHead()->getData();
    //Displaying the frame of the table
    cout  << "|" << setw(7) << "Symbol " << "|" << setw(10) << "Frequence " << "|" << setw(10)  << "Code " << "|" << endl;
    cout   << setfill('_') << "|" << setw(7)  << "" << "|" << setw(10) << "" << "|" << setw(10)  << "" << "|" << endl;
    fillCode(top, ""); //Going through each element
}

void HaffmanAlgothrim::fillCode(HaffmanNode *top, string newCode) { //Going through each element
    while (top != nullptr) {
        fillCode(top->left, newCode + "0"); //Adding 0 to the left elements
        fillCode(top->right, newCode + "1"); //Adding 1 to the right elements
		//this->code = newCode;
        if (top->symbol != '\0') {
			mapCodes.insert(top->symbol, newCode);
            cout << setfill(' ') << "|"  << setw(7) << top->symbol << "|" << setw(10) 
				<< top->frequence << "|" << setw(10)  << newCode << "|" << endl;
        }
        return;
	}
}


string HaffmanAlgothrim::haffmanDecrypt(string encodedString) { //Decrypting the string
    HaffmanNode *top = priorityOrder.getHead()->getData();
    string decodedString = "";
    for (size_t i = 0; i<encodedString.size(); i++) { //Going through each element
        if (encodedString[i] == '0') { //If the element is 0, going left
            top = top->left;
        }
        else { //Else going to right
            top = top->right;
        }
        if (top->left == nullptr && top->right == nullptr) { //If the element is leaf, display the symbol
            decodedString += top->symbol;
            top = priorityOrder.getHead()->getData();
        }
    }
    cout << "Decrypted string says: " << decodedString << endl;
    return decodedString;
}

#endif /* HaffmanClass_h */
