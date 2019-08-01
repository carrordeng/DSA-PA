#ifndef STACK_H
#define STACK_H

#include "List.h"

class Stack : public List
{
public:
    inline void push(const long &num) { insertAt(0, num); }
    inline long pop();
};

inline long Stack::pop()
{
    long backup = firstNode()->Num;
    deleteNode(firstNode());
    return backup;
}

#endif