#ifndef ZUMALIST_H
#define ZUMALIST_H

#include "ListNode.h"
#include <string>

class ZumaList
{
private:
    int _size;
    ListNode *header;
    ListNode *trailer;

protected:
    void init();

public:
    ZumaList() { init(); };
    ZumaList(std::string colorSeq);
    const char &operator[](int rank) const;
    inline int size() const { return _size; }
    inline ListNode *firstNode() const { return header->Succ; }
    inline ListNode *lastNode() const { return trailer->Pred; }
    ListNode *insertAt(const int &rank, const char &color);
    void print() const;
    char deleteNode(ListNode *node);
    ~ZumaList();
};

void ZumaList::init()
{
    _size = 0;
    header = new ListNode;
    trailer = new ListNode;
    header->Pred = header;
    header->Succ = trailer;
    trailer->Pred = header;
    trailer->Succ = trailer;
}

const char &ZumaList::operator[](int rank) const
{
    ListNode *tmp = firstNode();
    while (rank-- > 0)
        tmp = tmp->Succ;
    return tmp->colorCode;
}

ListNode *ZumaList::insertAt(const int &rank, const char &color)
{
    ListNode *newNode = new ListNode();
    newNode->colorCode = color;
    ListNode *currNode = firstNode();
    int cnt = rank;
    while (cnt-- > 0)
        currNode = currNode->Succ;
    return currNode->insertAtcurr(newNode);
}

ZumaList::ZumaList(std::string colorSeq)
{
    init();
    ListNode *tmp = header;
    for (auto c : colorSeq)
    {
        tmp = tmp->insertAsSucc(c);
        ++_size;
    }
}

void ZumaList::print() const
{
    ListNode *tmp = firstNode();
    while (tmp != trailer)
    {
        printf("%c", tmp->colorCode);
        tmp = tmp->Succ;
    }
    printf("\n");
}

char ZumaList::deleteNode(ListNode *node)
{
    char backup = node->colorCode;
    node->Pred->Succ = node->Succ;
    node->Succ->Pred = node->Pred;
    _size--;
    delete node;
    return backup;
}

ZumaList::~ZumaList()
{
    while (_size-- > 0)
        deleteNode(header->Succ);
    delete header;
    delete trailer;
}

#endif