#ifndef LISTNODE_H
#define LISTNODE_H

struct ListNode
{
    long Num;
    ListNode *Pred;
    ListNode *Succ;

    ListNode();
    ListNode(const long &num, ListNode *pred, ListNode *succ);
    ListNode *insertAtCurr(ListNode *&NewNode);
};

inline ListNode::ListNode()
{
    Num = -1;
    Pred = nullptr;
    Succ = nullptr;
}

inline ListNode::ListNode(const long &num, ListNode *pred, ListNode *succ)
{
    Num = num;
    Pred = pred;
    Succ = succ;
}

ListNode *ListNode::insertAtCurr(ListNode *&NewNode)
{
    this->Pred->Succ = NewNode;
    NewNode->Pred = this->Pred;
    NewNode->Succ = this;
    this->Pred = NewNode;
    return NewNode;
}

#endif