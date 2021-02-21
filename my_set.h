//
// Created by user on 31/08/2018.
//

#ifndef EX1_MY_SET_H
#define EX1_MY_SET_H

#include "Big_Integer.h"

using namespace std;

/**
 * A class that represents a set of unique big_integers, whose size's limited only by the
 * computer's memory.
 */
class my_set
{

//--------------------------private fields and functions----------------
public:
    class Node
    {
    public:
        friend class my_set;

        Node() : _next(nullptr), _nodeData(new big_integer(0)) {};

        Node(const big_integer &_new) : _next(nullptr), _nodeData(new big_integer(_new)){};

        ~Node();

        Node* getNext()
        {
            return _next;
        };

        big_integer &getValue()
        {
            return *_nodeData;
        };

        void setNext(Node &newNext)
        {
            if (&newNext != nullptr)
            {
                _next = &newNext;
            }
        };

        void setNextAsNull()
        {
            _next = nullptr;
        };

        Node* _next;
        big_integer* _nodeData;
    };

    my_set::Node *_head;
    big_integer* _sum;

public:
    my_set() : _head(nullptr), _sum(new big_integer(0)){};

    my_set(const my_set &toCopy) : _head(toCopy._head)
    {
        big_integer newSum = *toCopy._sum;
        *_sum = newSum;
    };

    ~my_set();

    bool is_in_set(const big_integer& searched);

    bool add(const big_integer& toAdd);

    bool remove(const big_integer &toRemove);

    big_integer& sum_set();

    my_set operator-(const my_set& other);

    my_set operator|(const my_set &other);

    my_set operator&(const my_set &other);

    my_set& operator=(const my_set &other);

    /**
     * overloading the printing operator <<
     * @param os- reference to ostream object
     * @param set- the set to be printed
     * @return- the stream
     */
    friend ostream& operator<<(ostream& os, my_set set)
    {
        if (set.isSetEmpty())
        {
            return os<<"\n";
        }
        my_set::Node* currentPtr = set.my_set::getHead();
        my_set::Node current = *currentPtr;
        my_set::Node* next = current.my_set::Node::getNext();
        while (&next != nullptr)
        {
            os<<current.Node::getValue()<<endl;
        }
        return os;
    };

//------------------access functions----------------

    bool isSetEmpty()
    {
        return (this->_head == nullptr);
    }

    /**
     * getter for the head of the linked list.
     * @return
     */
    my_set::Node* getHead()
    {
        return _head;
    };

    void setHead(my_set::Node& newHead)
    {
        newHead.Node::setNext(*_head);
        *_head = newHead;
    };

    void setTail(my_set::Node &newTail, my_set::Node &oldTail)
    {
        oldTail.Node::setNext(newTail);
        newTail.Node::setNextAsNull();
    };

    void placeNode(my_set::Node nodeToAdd, my_set::Node &newNext, my_set::Node &newPrev)
    {
        nodeToAdd.Node::setNext(newNext);
        newPrev.Node::setNext(nodeToAdd);
    };

    void displaceNode(my_set::Node& toRemove, my_set::Node &prev)
    {
        prev.Node::setNext(*toRemove.Node::getNext());
        toRemove.Node::setNextAsNull();
        delete &toRemove;
    }

};


#endif //EX1_MY_SET_H
