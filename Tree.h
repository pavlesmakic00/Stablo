#ifndef TREE_H
#define TREE_H

#include "Action.h"
#include "Node.h"
#include <iostream>
class Tree
{
    public:
        Tree();
        virtual ~Tree();
        void insert(Action* action);
        Action* find(int priority);
        int findNumberOfElementsWithPriority(int priority) const;
        Action* remove(int priority);
        void changePriority(std::string actionName, int oldP, int newP);
        Action* removeMax();
        std::ostream& print(std::ostream&);
    private:
        std::stack<Node*> getInsertionStack(Action* a);
        Action* findNode(Action* action);
        Action* removeHelper(Action* a, std::stack<Node*> stack);
        Node* root;

    friend std::ostream& operator<<(std::ostream&, Tree const&);
};

#endif 
