#ifndef STACK_H
#define STACK_H

#include "List.h"

class Stack : public List
{
public:
    long depth;
    Stack() { depth = 0; }
    Stack(const long &dep) { depth = dep; }
    inline bool push(const long &num);
    inline long pop();
    inline long top() { return firstNode()->Num; }
};

inline bool Stack::push(const long &num)
{
    if (size() == depth)
        return false;
    else
    {
        insertAt(0, num);
        return true;
    }
}

inline long Stack::pop()
{
    long backup = firstNode()->Num;
    deleteNode(firstNode());
    return backup;
}

#endif