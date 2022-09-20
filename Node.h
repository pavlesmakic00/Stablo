#ifndef NODE_H
#define NODE_H
#include <stack>
#include "InsertionStruct.h"
#include <iostream>
class Tree;
class Node
{
    public:
        Node();
        bool isLeaf() const;
        bool isEmpty() const;
        bool hasSpace() const;
        bool canDelete() const;
        bool canHelp() const;
        void deleteOne(InsertionStruct iStruct);
        void clear();
        Action* getRightAction(Node*child);
        Action* getLeftAction(Node*child);
        InsertionStruct getSiblings(Node* n);
        InsertionStruct takeFirst();
        InsertionStruct takeLast();
        void insertFirst(InsertionStruct iStruct);
        void insertLast(InsertionStruct iStruct);
        Action* replaceLeft(Node* child, Action* replacement);
        Action* replaceRight(Node* child, Action* replacement);
        virtual ~Node();
        void insert(InsertionStruct iStruct);
        InsertionStruct split(InsertionStruct iStruct);
        std::ostream& print(std::ostream&,int);
    private:
        int findNodeIndex(Node* n);
        int numberOfElements;
        Action* elements[5];
        Node* nodes[5];
    friend class Tree;
    friend std::ostream& operator<<(std::ostream&, Node const&);
    friend std::ostream& operator<<(std::ostream&, Tree const&);
};

#endif 
