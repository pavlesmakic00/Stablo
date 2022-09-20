#ifndef INSERTIONSTRUCT_H
#define INSERTIONSTRUCT_H

class Node;
class Action;

class InsertionStruct
{
    public:
        InsertionStruct(Action*, Node*, Node*);
        virtual ~InsertionStruct();
        Action* action;
        Node* left;
        Node* right;
};

#endif
