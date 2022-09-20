#include "InsertionStruct.h"

InsertionStruct::InsertionStruct(Action*action, Node*left, Node*right):
    action(action),
    left(left),
    right(right)
{}

InsertionStruct::~InsertionStruct()
{
    action = nullptr;
    left = right = nullptr;
}
