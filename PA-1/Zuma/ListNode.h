#ifndef LISTNODE_H
#define LISTNODE_H

struct ListNode
{
    char colorCode;
    ListNode *Pred;
    ListNode *Succ;

    ListNode();
    ListNode(char color, ListNode *pred, ListNode *succ);
    ListNode *insertAsPred(const char &color);
    ListNode *insertAsSucc(const char &color);
    ListNode *insertAtcurr(ListNode *&newNode);
};

inline ListNode::ListNode()
{
    colorCode = '0';
    Pred = nullptr;
    Succ = nullptr;
}

inline ListNode::ListNode(char color, ListNode *pred, ListNode *succ)
{
    colorCode = color;
    Pred = pred;
    Succ = succ;
}

ListNode *ListNode::insertAsPred(const char &color)
{
    ListNode *newNode = new ListNode(color, Pred, this);
    Pred->Succ = newNode;
    Pred = newNode;
    return newNode;
}

ListNode *ListNode::insertAsSucc(const char &color)
{
    ListNode *newNode = new ListNode(color, this, this->Succ);
    Succ->Pred = newNode;
    Succ = newNode;
    return newNode;
}

ListNode *ListNode::insertAtcurr(ListNode *&newNode)
{
    Pred->Succ = newNode;
    newNode->Pred = this->Pred;
    Pred = newNode;
    newNode->Succ = this;
    return newNode;
}

#endif