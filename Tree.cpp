#include "Tree.h"
#include "Action.h"
#include <stack>
#include <deque>
#include <vector>
#include "InsertionStruct.h"
Tree::Tree():root(new Node())
{}

Tree::~Tree()
{
    delete root;
    root = nullptr;
}

std::stack<Node*> Tree::getInsertionStack(Action* a) {
    std::stack<Node*> stack;
    Node* n = root;
    stack.push(n);
    while (!n->isLeaf()) {
        int index = -1;
        for (int i = 0; i < n->numberOfElements; i++) {
            if (*a < *n->elements[i]) {
                index = i;
                break;
            } else if (*a == *n->elements[i]) {
                return stack;
            }
        }
        if (index == -1) {
            index = n->numberOfElements;
        }

        n = n->nodes[index];
        stack.push(n);
    }
    return stack;
}
void Tree::insert(Action* a) {
    if (findNode(a) != nullptr) {
        return;
    }
    std::stack<Node*>&& stack = getInsertionStack(a);

    InsertionStruct iStruct(a,nullptr,nullptr);
    bool finished = false;
    while (!finished && !stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->hasSpace()) {
            node->insert(iStruct);
            finished = true;
        } else {
            iStruct = node->split(iStruct);
            delete node;
        }
    }
    if (!finished) {
        root = new Node();
        root->elements[0] = iStruct.action;
        root->nodes[0] = iStruct.left;
        root->nodes[1] = iStruct.right;

        root->numberOfElements = 1;
    }


    while (!stack.empty()) {
        stack.pop();
    }

}
Action* Tree::find(int priority) {

    Node* n = root;
    while (n != nullptr) {
        bool updated = false;
        for (int i = 0; i < n->numberOfElements; i++) {
            if (n->elements[i]->getPriority() == priority) {
                return n->elements[i];
            }
            if (priority < n->elements[i]->getPriority()) {
                n = n->nodes[i];
                updated = true;
                break;
            }
        }
        if (!updated)
            n = n->nodes[n->numberOfElements];
    }
    return nullptr;
}
Action* Tree::findNode(Action* action) {
    Node* n = root;
    while (n != nullptr) {
        bool updated = false;
        for (int i = 0; i < n->numberOfElements; i++) {
            if (*n->elements[i] == *action) {
                return n->elements[i];
            }
            if (*action  < *n->elements[i]) {
                n = n->nodes[i];
                updated = true;
                break;
            }
        }
        if (!updated)
            n = n->nodes[n->numberOfElements];
    }
    return nullptr;
}
std::ostream& operator<<(std::ostream&os, Tree const&t) {
    if (t.root->isEmpty()) {
        return os;
    }
    std::deque<Node*> d;
    d.push_back(t.root);
    d.push_back(nullptr);
    while (!d.empty()) {
        Node* n = d.front();
        d.pop_front();
        if (n == nullptr) {
            os << "\n";
            if (!d.empty()) {
                d.push_back(nullptr);
            }
        } else {
            os << *n;
            if (!n->isLeaf()) {
                for (int i = 0; i <= n->numberOfElements; i++) {
                    d.push_back(n->nodes[i]);
                }
            }
            os << "\t";
        }
    }
    return os;
}
int Tree::findNumberOfElementsWithPriority(int priority) const {
    int count = 0;
    std::deque<Node*> d;
    d.push_back(root);
    while (!d.empty()) {
        Node* n = d.front();
        d.pop_front();
        if (!n->isLeaf()) {
            for (int i = 0; i <= n->numberOfElements; i++) {
                d.push_back(n->nodes[i]);
            }
        }
        for (int i = 0; i < n->numberOfElements; i++) {
            if (n->elements[i]->getPriority() == priority) {
                count++;
            }
        }
    }
    return count;
}
Action* Tree::remove(int priority) {
    if (root->isEmpty())
        return nullptr;
    Action* a = find(priority);
    if (a == nullptr) {

        return nullptr;
    }
    std::stack<Node*>&& stack = getInsertionStack(a);

    return removeHelper(a, stack);
}
Action* Tree::removeMax() {
    if (root->isEmpty()) {
        return nullptr;
    }

    std::stack<Node*> stack;
    Node*n = root;
    while (!n->isLeaf()) {
        stack.push(n);
        n = n->nodes[n->numberOfElements];
    }
    stack.push(n);
    Action *a = n->elements[n->numberOfElements-1];
    return removeHelper(a, stack);
}
Action* Tree::removeHelper(Action* a, std::stack<Node*> stack ) {

    Node*n  = stack.top();

    if (!n->isLeaf()) {

        Node* old = n;
        int index = -1;
        for (int i = 0; i < n->numberOfElements; i++) {
            if (*n->elements[i] == *a) {
                index = i + 1;
                break;
            }
        }
        if (index == -1) {
            index = n->numberOfElements;
        }
        n = n->nodes[index];
        while (n != nullptr) {
            stack.push(n);
            n = n->nodes[0];
        }
        n = stack.top();
        Action* temp = n->elements[0];
        n->elements[0] = old->elements[index-1];
        old->elements[index-1] = temp;


    }
    bool finished = false;
    InsertionStruct iStruct(a, nullptr,nullptr);
    while (!finished && !stack.empty()) {
        Node* n = stack.top();
        stack.pop();
        Action* a = iStruct.action;
        if (n->canDelete()) {

            finished = true;
            n->deleteOne(iStruct);
        } else if (!stack.empty()) {
            Node* parent = stack.top();
            InsertionStruct siblings = parent->getSiblings(n);
            Node* leftSibling = siblings.left;
            Node* rightSibling = siblings.right;
            if ((rightSibling != nullptr) && (rightSibling->canHelp())) {

                InsertionStruct is = rightSibling->takeFirst();
                is.action = parent->replaceRight(n,is.action);
                finished = true;
                n->deleteOne(iStruct);
                n->insertLast(is);
            } else if ((leftSibling != nullptr) && (leftSibling->canHelp())) {
                //std::cout << "RIGHT TURN\n";
                InsertionStruct is = leftSibling->takeLast();
                is.action = parent->replaceLeft(n,is.action);
                finished = true;
                n->deleteOne(iStruct);
                n->insertFirst(is);
            } else {

                Node* ret;
                Action* action;
                if (rightSibling != nullptr) {
                    action = parent->getRightAction(n);
                    ret = new Node();
                    ret->elements[0] = action;
                    ret->elements[1] = rightSibling->elements[0];
                    ret->nodes[0] = iStruct.left;
                    ret->nodes[1] = rightSibling->nodes[0];
                    ret->nodes[2] = rightSibling->nodes[1];
                    ret->numberOfElements = 2;
                    n->clear();
                    delete n;
                } else {
                    action = parent->getLeftAction(n);
                    ret = new Node();
                    ret->elements[0] = leftSibling->elements[0];
                    ret->elements[1] = action;
                    ret->nodes[0] = leftSibling->nodes[0];
                    ret->nodes[1] = leftSibling->nodes[1];
                    ret->nodes[2] = iStruct.left;
                    n->clear();
                    delete n;
                }
                ret->numberOfElements = 2;
                iStruct = InsertionStruct(action, ret, nullptr);
            }
        } else {
            root->clear();
            delete root;
            finished = true;

            root = iStruct.left;
            if (root == nullptr) {
                root = new Node();
            }
        }
    }
    return a;
}

std::ostream& Tree::print(std::ostream& os) {
    return root->print(os,0);
}
void Tree::changePriority(std::string actionName, int oldP, int newP) {
    Action* a = new Action(actionName, oldP);
    Action* original = findNode(a);
    if (original == nullptr) {
        delete a;
        return;
    }
    std::stack<Node*> stack  = getInsertionStack(a);
    Action* ret = removeHelper(a, stack);
    if (ret != nullptr) {
        delete ret;
        delete original;
        insert(new Action(actionName, newP));
    }

}
