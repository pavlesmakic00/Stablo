#include "Node.h"
#include "InsertionStruct.h"
#include "Action.h"
#include <cstring>

Node::Node():
numberOfElements(0)
{
    for (int i = 0; i < 5; i++) {
        elements[i] = nullptr;
        nodes[i] = nullptr;
    }
}

Node::~Node() {
    for (int i = 0; i < 5; i++) {
        delete elements[i];
        delete nodes[i];
        elements[i] = nullptr;
        nodes[i] = nullptr;
    }
    numberOfElements = 0;
}
bool Node::isLeaf() const {
    for (int i = 0; i <= numberOfElements; i++) {
        if (nodes[i] != nullptr) {
            return false;
        }
    }
    return true;
}
bool Node::hasSpace() const {
    return numberOfElements < 3;
}
void Node::insert(InsertionStruct iStruct) {
    Action* action = iStruct.action;
    Node* left = iStruct.left;
    Node* right = iStruct.right;

    int index = -1;
    for (int i = 0; i < numberOfElements; i++) {
        if (*action < *elements[i]) {
            index = i;
            break;
        }
    }
    if (index == -1)
        index = numberOfElements;


    for (int i = 4; i > index; i--) {
        elements[i] = elements[i-1];
    }

    for (int i = 4; i > index; i--) {
        nodes[i] = nodes[i-1];
    }

    elements[index] = action;
    nodes[index+1] = right;
    nodes[index] = left;
    numberOfElements++;

}
InsertionStruct Node::split(InsertionStruct iStruct) {

    insert(iStruct);
    Action* action = elements[1];
    Node* left = new Node();
    Node* right = new Node();


    left->elements[0] = elements[0];
    left->nodes[0] = nodes[0];
    left->nodes[1] = nodes[1];


    right->elements[0] = elements[2];
    right->elements[1] = elements[3];
    right->nodes[0] = nodes[2];
    right->nodes[1] = nodes[3];
    right->nodes[2] = nodes[4];

    left->numberOfElements = 1;
    right->numberOfElements = 2;

    clear();
    return InsertionStruct(action, left, right);
}

std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << "|";
    for (int i = 0; i < node.numberOfElements; i++) {
        os << *node.elements[i] << "|";
    }
    return os;
}
bool Node::canDelete() const {
    return numberOfElements > 1;
}
void Node::deleteOne(InsertionStruct iStruct) {
    int index = 0;
    Action* a = iStruct.action;
    for (int i = 0; i < numberOfElements; i++) {
        if (*a == *elements[i]) {
            index = i;
            break;
        }
    }
    for (int i = index; i < 4; i++) {
        elements[i] = elements[i+1];
        nodes[i] = nodes[i+1];
    }
    nodes[index] = iStruct.left;
    numberOfElements--;
}
InsertionStruct Node::getSiblings(Node *n) {
    int index = findNodeIndex(n);
    if (index == 0) {
        return InsertionStruct(nullptr,nullptr,nodes[index+1]);
    } else if (index == numberOfElements) {
        return InsertionStruct(nullptr, nodes[index-1], nullptr);
    } else {
        return InsertionStruct(nullptr, nodes[index-1], nodes[index+1]);
    }
}
bool Node::canHelp() const {
    return numberOfElements > 1;
}
InsertionStruct Node::takeFirst() {
    InsertionStruct is(elements[0],nodes[0],nullptr);
    for (int i = 0; i < 4; i++) {
        elements[i] = elements[i+1];
        nodes[i] = nodes[i+1];
    }
    numberOfElements--;
    return is;
}
InsertionStruct Node::takeLast() {
    InsertionStruct is(
        elements[numberOfElements-1],
        nodes[numberOfElements],
        nullptr
    );
    elements[numberOfElements - 1] = nullptr;
    nodes[numberOfElements] = nullptr;
    numberOfElements--;
    return is;
}

Action* Node::replaceRight(Node* child, Action* replacement) {
    int i = findNodeIndex(child);
    Action* ret = elements[i];
    elements[i] = replacement;
    return ret;
}
Action* Node::replaceLeft(Node* child, Action* replacement) {
    int i = findNodeIndex(child);
    Action* ret = elements[i - 1];
    elements[i - 1] = replacement;
    return ret;
}
int Node::findNodeIndex(Node* n) {
    int index = -1;
    for (int i = 0; i <= numberOfElements; i++) {
        if (nodes[i] == n) {
            index = i;
            break;
        }
    }
    return index;
}
void Node::insertFirst(InsertionStruct iStruct) {
    for (int i = 4; i > 0; i--) {
        nodes[i] = nodes[i-1];
        elements[i] = elements[i-1];
    }
    elements[0] = iStruct.action;
    nodes[0] = iStruct.left;
    numberOfElements++;
}
void Node::insertLast(InsertionStruct iStruct) {
    elements[numberOfElements] = iStruct.action;
    nodes[numberOfElements+1] = iStruct.left;
    numberOfElements++;
}
void Node::clear() {
    for (int i = 0; i < 5; i++) {
        elements[i] = nullptr;
        nodes[i] = nullptr;
    }
    numberOfElements = 0;
}
Action* Node::getRightAction(Node*child) {
    int i = findNodeIndex(child);
    return elements[i];
}
Action* Node::getLeftAction(Node*child) {
    int i = findNodeIndex(child);
    return elements[i-1];
}
bool Node::isEmpty() const {
    return numberOfElements == 0;
}
std::ostream& Node::print(std::ostream&os, int level) {
    std::string spacing = "      ";
    if (numberOfElements == 1) {
        if (nodes[1] != nullptr) {
            nodes[1]->print(os, level + 1);
        }
        for (int i = 0; i < level; i++)
            std::cout << spacing;
        os << *elements[0] << "[B]" << std::endl;
        if (nodes[0] != nullptr) {
            nodes[0]->print(os, level + 1);
        }


    } else if (numberOfElements > 1) {

        if (numberOfElements == 3) {
            if (nodes[3] != nullptr) {
                nodes[3]->print(os, level + 2);
            }
            for (int i = 0; i < level + 1; i++)
                std::cout << spacing;
            os << *elements[2] << "[R]" << std::endl;
            if (nodes[2] != nullptr) {
                nodes[2]->print(os, level + 2);
            }

        }
        if (numberOfElements == 2) {
            if (nodes[2] != nullptr) {
                nodes[2]->print(os, level + 1);
            }
        }
        for (int i = 0; i < level; i++)
            std::cout << spacing;
        os << *elements[1] << "[B]" << std::endl;

        if (nodes[1] != nullptr) {
            nodes[1]->print(os, level + 2);
        }

        for (int i = 0; i < level + 1; i++)
            std::cout << spacing;
        os << *elements[0] << "[R]" << std::endl;


        if (nodes[0] != nullptr) {
            nodes[0]->print(os, level + 2);
        }

    }

    return os;
}
