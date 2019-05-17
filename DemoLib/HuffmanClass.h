#ifndef HuffmanClass_h
#define HuffmanClass_h

#include <iostream>
#include "\Users\Dogge!\source\repos\AlgosyLaba3\AlgosyLaba3\MyClasses\RedBlackTreeClass.h"
#include <iomanip>

using namespace std;

class HuffmanNode {
private:
    char symbol; 
    size_t frequence;
    HuffmanNode *right;
    HuffmanNode *left;
public:
	HuffmanNode() {
        symbol = '\0';
        frequence = 0;
        right = nullptr;
        left = nullptr;
    }
    HuffmanNode(char symbol, size_t frequence, HuffmanNode *right = nullptr, HuffmanNode *left = nullptr) {
        this->symbol = symbol;
        this->frequence = frequence;
        this->right = right;
        this->left = left;
    }
    friend class HuffmanAlgothrim;
};


class HuffmanAlgothrim {
private:
	MyMap<char, size_t> myMap;
	string inputString;
	MyList<HuffmanNode*> priorityOrder;
	MyMap<char, string> mapCodes;
	void transform();
	void filling(Node<char, size_t>* element);
	void insertInOrder(HuffmanNode* newHuffmanNode);
	void fillCodes();
	void fillCode(HuffmanNode* top, string code);
public:
    HuffmanAlgothrim(string input) {
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
    string HuffmanDecrypt(string encodedString);

};

void HuffmanAlgothrim::transform() { //Filling the elements from MyMap into MyList
    Node<char, size_t> *element = myMap.returnRoot();
    filling(element);
}

void HuffmanAlgothrim::filling(Node<char, size_t> *element) { //Going through every map element
    while (element != nullptr) {
        filling(element->left);
        filling(element->right);
        HuffmanNode *newHuffmanNode = new HuffmanNode(element->key, element->value); //Creating new Huffman node
        insertInOrder(newHuffmanNode);
        return;
    }
 }

void HuffmanAlgothrim::insertInOrder (HuffmanNode *newHuffmanNode) { //Deciding where to put new element in list
    Element<HuffmanNode*> *helpNode = priorityOrder.getHead();
    size_t i = 0;
    while (helpNode != nullptr && helpNode->data->frequence < newHuffmanNode->frequence) { //Finding where to put this element
        helpNode=helpNode->next;
        i++;
    }
    if (helpNode == nullptr) { //If it is the end of the list, then insert in the end
        priorityOrder.push_back(newHuffmanNode);
    }
    else { //Else insert before element with higher priority
        priorityOrder.insert(newHuffmanNode, i);
    }
}

string HuffmanAlgothrim::codding() { //Encryptig message in saving codes for each elemenet
    HuffmanNode *right, *left, *top;
    string codedString = "";
    size_t weight = 0;
    while (priorityOrder.get_size() != 1) { //Creating Huffman tree using MyList
        Element<HuffmanNode*> helpElement;
        helpElement = priorityOrder.at(0);
        right = helpElement.data;
        priorityOrder.pop_front(); //Taking first element and putting it as a right son
        helpElement = priorityOrder.at(0);
        left = helpElement.data;
        priorityOrder.pop_front(); //Taking first element and putting it as a left son
        top = new HuffmanNode('\0', left->frequence + right->frequence, right, left);
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

void HuffmanAlgothrim::fillCodes() { //Finding the code of each element
    HuffmanNode *top = priorityOrder.getHead()->getData();
    //Displaying the frame of the table
    cout  << "|" << setw(7) << "Symbol " << "|" << setw(10) << "Frequence " << "|" << setw(10)  << "Code " << "|" << endl;
    cout   << setfill('_') << "|" << setw(7)  << "" << "|" << setw(10) << "" << "|" << setw(10)  << "" << "|" << endl;
    fillCode(top, ""); //Going through each element
}

void HuffmanAlgothrim::fillCode(HuffmanNode *top, string newCode) { //Going through each element
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


string HuffmanAlgothrim::HuffmanDecrypt(string encodedString) { //Decrypting the string
    HuffmanNode *top = priorityOrder.getHead()->getData();
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

#endif /* HuffmanClass_h */
