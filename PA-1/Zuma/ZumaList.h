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
    int findEqual(ListNode *targetNode, ListNode *&leftNode, ListNode *&rightNode) const;
    void print() const;
    void deleteInterval(ListNode *leftEnd, ListNode *rightEnd);
    void zumaDelete(ListNode *targetNode);
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
    ListNode *tmp = header;
    while (rank-- >= 0)
        tmp = tmp->Succ;
    return tmp->colorCode;
}

ListNode *ZumaList::insertAt(const int &rank, const char &color)
{
    ListNode *newNode = new ListNode();
    newNode->colorCode = color;
    ListNode *currNode = header;
    int cnt = rank;
    while (cnt-- >= 0)
        currNode = currNode->Succ;
    ++_size;
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

int ZumaList::findEqual(ListNode *targetNode, ListNode *&leftNode, ListNode *&rightNode) const
{
    int equalCnt = 0;
    //Left
    ListNode *currNode = targetNode->Pred;
    while (currNode != header && (currNode->colorCode == targetNode->colorCode))
    {
        currNode = currNode->Pred;
        ++equalCnt;
    }
    leftNode = currNode->Succ;
    //Right
    currNode = targetNode->Succ;
    while (currNode != trailer && (currNode->colorCode == targetNode->colorCode))
    {
        currNode = currNode->Succ;
        ++equalCnt;
    }
    rightNode = currNode->Pred;
    return equalCnt;
}

void ZumaList::deleteInterval(ListNode *startNode, ListNode *endNode)
{
    ListNode *tmp, *leftEnd, *rightEnd;
    while (startNode != endNode)
    {
        tmp = startNode->Succ;
        deleteNode(startNode);
        startNode = tmp;
    }
    leftEnd = startNode->Pred;
    rightEnd = startNode->Succ;
    deleteNode(startNode);
}

void ZumaList::zumaDelete(ListNode *targetNode)
{
    ListNode *leftNode = new ListNode;
    ListNode *rightNode = new ListNode;
    int equalCnt = 0;
    equalCnt = findEqual(targetNode, leftNode, rightNode);
    if (equalCnt > 1)
    {
        ListNode *llNode = leftNode->Pred;
        ListNode *rrNode = rightNode->Succ;
        deleteInterval(leftNode, rightNode);
        if (llNode != header && rrNode != trailer && (llNode->colorCode == rrNode->colorCode))
            zumaDelete(llNode);
    }
}

void ZumaList::print() const
{
    ListNode *tmp = firstNode();
    if (_size == 0)
        printf("-\n");
    else
    {
        while (tmp != trailer)
        {
            printf("%c", tmp->colorCode);
            tmp = tmp->Succ;
        }
        printf("\n");
    }
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