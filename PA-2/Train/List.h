#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include <iostream>

class List
{
private:
    long _size;
    ListNode *header;
    ListNode *trailer;

protected:
    void init();

public:
    List() { init(); };
    ~List();
    ListNode *insertAt(const long rank, const long &num);
    inline ListNode *firstNode() const { return header->Succ; }
    inline long size() const { return _size; }
    inline bool isEmpty() const { return size() == 0 ? true : false; }
    long deleteNode(ListNode *node);
    void print() const;
};

void List::init()
{
    _size = 0;
    header = new ListNode;
    trailer = new ListNode;
    header->Pred = header;
    header->Succ = trailer;
    trailer->Pred = header;
    trailer->Succ = trailer;
}

List::~List()
{
    while (_size > 0)
        deleteNode(header->Succ);
    deleteNode(header);
    deleteNode(trailer);
}

ListNode *List::insertAt(const long rank, const long &num)
{
    ListNode *newNode = new ListNode();
    newNode->Num = num;
    ListNode *currNode = header;
    long cnt = rank;
    while (cnt-- >= 0)
        currNode = currNode->Succ;
    ++_size;
    return currNode->insertAtCurr(newNode);
}

long List::deleteNode(ListNode *node)
{
    ListNode *backup = node;
    node->Pred->Succ = node->Succ;
    node->Succ->Pred = node->Pred;
    delete node;
    _size--;
    return backup->Num;
}

void List::print() const
{
    ListNode *tmp = firstNode();
    if (_size == 0)
        printf("-\n");
    else
    {
        while (tmp != trailer)
        {
            printf("%ld", tmp->Num);
            tmp = tmp->Succ;
        }
        printf("\n");
    }
}

#endif