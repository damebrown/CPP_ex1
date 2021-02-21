//
// Created by user on 31/08/2018.
//

#include <w32api/mmcobj.h>
#include "my_set.h"


// --------------------------------------------------------------------------------------
// This file contains the implementation of the class my_set.
// --------------------------------------------------------------------------------------
//static fields defined here

// Constructors


my_set::~my_set()
{
    my_set::Node current = *_head;
    my_set::Node* next = current.my_set::Node::getNext();
    while (next != nullptr)
    {
        current = *next;
        next = current.my_set::Node::getNext();
        delete &current;
    }
    delete &current;
}


my_set::Node::~Node()
{
    delete _nodeData;
}


// ------------------ set methods ------------------------

bool my_set::is_in_set(const big_integer &searched)
{
    if (isSetEmpty())
    {
        return false;
    }
    my_set::Node& current = *_head;
    my_set::Node *next = current.my_set::Node::getNext();
    while (next != nullptr)
    {
        if (current.my_set::Node::getValue() == searched)
        {
            break;
        }
        current = *next;
        next = current.my_set::Node::getNext();
    }
    return (current.my_set::Node::getValue() == searched);
}

bool my_set::add(const big_integer &toAdd)
{
    my_set::Node* ptrToAdd = new Node(toAdd);
    my_set::Node nodeToAdd = *ptrToAdd;;
    if (this->isSetEmpty())
    {
        nodeToAdd.my_set::Node::setNextAsNull();
        _head = ptrToAdd;
        *_sum += toAdd;
        return true;
    }
    else if (is_in_set(toAdd))
    {
        return false;
    }
    if (nodeToAdd.my_set::Node::getValue() <= _head->my_set::Node::getValue())
    {
        setHead(nodeToAdd);
        *_sum += toAdd;
        return true;
    }
    my_set::Node current = *_head;
    my_set::Node *next = current.my_set::Node::getNext();
    while ((nodeToAdd.my_set::Node::getValue() > current.my_set::Node::getValue()) && (&next != nullptr))
    {
        current = *next;
        next = current.my_set::Node::getNext();
    }
    if (current.my_set::Node::getNext() == nullptr)
    {
        my_set::setTail(nodeToAdd, current);
        *_sum += toAdd;
        return true;
    }
    else
    {
        my_set::Node nextNode = *next;
        if ((current.my_set::Node::getValue() <= toAdd) && (nodeToAdd.my_set::Node::getValue() <= nextNode.my_set::Node::getValue()))
        {
            my_set::placeNode(nodeToAdd, *next, current);
            *_sum += toAdd;
            return true;
        }
    }
    return false;
}

bool my_set::remove(const big_integer &toRemove)
{
    if (!(is_in_set(toRemove)))
    {
        return false;
    }
    my_set::Node prev;
    my_set::Node next = *_head;
    while (&next != nullptr)
    {
        if (next.my_set::Node::getValue() == toRemove)
        {
            if (&next == _head)
            {
                _head = next.my_set::Node::getNext();
                next.my_set::Node::setNextAsNull();
            }
            else
            {
                displaceNode(next, prev);
            }
            *_sum -= toRemove;
            return true;
        }
        prev = next;
        next = *next.my_set::Node::getNext();
    }
    return false;
}

big_integer& my_set::sum_set()
{
    return *_sum;
}



// ------------------ Operator Overloading methods ------------------------

my_set my_set::operator-(const my_set &other)
{
    my_set newSet;
    my_set::Node thisCurrent = *this->_head;
    my_set::Node* thisNext = thisCurrent.my_set::Node::getNext();
    my_set::Node otherCurrent = *other._head;
    my_set::Node* otherNext = otherCurrent.my_set::Node::getNext();
    while (&thisNext != nullptr)
    {
        while (thisCurrent.my_set::Node::getValue() < otherCurrent.my_set::Node::getValue())
        {
            newSet.add(thisCurrent.my_set::Node::getValue());
            thisCurrent = *thisNext;
            thisNext = thisCurrent.my_set::Node::getNext();
        }
        if (thisCurrent.my_set::Node::getValue() >= otherCurrent.my_set::Node::getValue())
        {
            otherCurrent = *otherNext;
            otherNext = otherCurrent.my_set::Node::getNext();
        }
    }
    (is_in_set(thisCurrent.my_set::Node::getValue())) ?  : newSet.add(thisCurrent.my_set::Node::getValue());
    return newSet;
}

my_set my_set::operator|(const my_set &other)
{
    my_set newSet;
    my_set::Node thisCurrent = *this->_head;
    my_set::Node thisNext = *thisCurrent.my_set::Node::getNext();
    my_set::Node otherCurrent = *other._head;
    my_set::Node otherNext = *otherCurrent.my_set::Node::getNext();
    while ((&thisNext != nullptr) && (&otherNext != nullptr))
    {
        if (thisCurrent.my_set::Node::getValue() <= otherCurrent.my_set::Node::getValue())
        {
            newSet.add(thisCurrent.my_set::Node::getValue());
            thisCurrent = thisNext;
            thisNext = *thisCurrent.my_set::Node::getNext();
        }
        if (thisCurrent.my_set::Node::getValue() >= otherCurrent.my_set::Node::getValue())
        {
            newSet.add(otherCurrent.my_set::Node::getValue());
            otherCurrent = otherNext;
            otherNext = *otherCurrent.my_set::Node::getNext();
        }
    }
    newSet.add(thisCurrent.my_set::Node::getValue()), newSet.add(otherCurrent.my_set::Node::getValue());
    return newSet;
}

my_set my_set::operator&(const my_set &other)
{
    my_set newSet;
    my_set::Node thisCurrent = *this->_head;
    my_set::Node thisNext = *thisCurrent.my_set::Node::getNext();
    my_set::Node otherCurrent = *other._head;
    my_set::Node otherNext = *otherCurrent.my_set::Node::getNext();
    while ((&thisNext != nullptr) && (&otherNext != nullptr))
    {
        if (thisCurrent.my_set::Node::getValue() < otherCurrent.my_set::Node::getValue())
        {
            thisCurrent = thisNext;
            thisNext = *thisCurrent.my_set::Node::getNext();
        }
        if (thisCurrent.my_set::Node::getValue() > otherCurrent.my_set::Node::getValue())
        {
            otherCurrent = otherNext;
            otherNext = *otherCurrent.my_set::Node::getNext();
        }
        if (thisCurrent.my_set::Node::getValue() == otherCurrent.my_set::Node::getValue())
        {
            newSet.add(thisCurrent.my_set::Node::getValue());
            otherCurrent = otherNext;
            otherNext = *otherCurrent.my_set::Node::getNext();
            thisCurrent = thisNext;
            thisNext = *thisCurrent.my_set::Node::getNext();
        }
    }
    return newSet;
}

my_set& my_set::operator=(const my_set &other)
{
    big_integer newSum = *other._sum;
    *_sum = newSum;
    _head = other._head;
}


// ------------------ Access methods ------------------------

// ------------------ Other methods -------------------------