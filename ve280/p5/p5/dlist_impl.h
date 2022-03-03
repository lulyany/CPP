#ifndef _DIST_IMPL_H_
#define _DIST_IMPL_H_

#include "dlist.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

template <class T>
bool Dlist<T>::isEmpty() const
{
    return !(first);
}
// EFFECTS: returns true if list is empy, false otherwise

template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *np = new node;
    np->op = op;
    np->next = first;
    np->prev = nullptr;
    if (isEmpty())
    {
        first = np;
        last = np;
    }
    else
    {
        first->prev = np;
        first = np;
    }
}
// EFFECTS inserts o at the front of the list

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *np = new node;
    np->op = op;
    np->prev = last;
    np->next = nullptr;
    if (isEmpty())
    {
        first = np;
        last = np;
    }
    else
    {
        last->next = np;
        last = np;
    }
}
// EFFECTS inserts o at the back of the list

template <class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    node *victim = first;
    first = first->next;
    if (!first)
    {
        last = nullptr;
    }
    else
    {
        first->prev = nullptr;
    }
    T *result = victim->op;
    delete victim;
    //TODO:necessay?
    // victim = nullptr;
    return result;
}
// EFFECTS removes and returns first object from non-empty list
//         throws an instance of emptyList if empty

template <class T>
T *Dlist<T>::removeBack()
{
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    node *victim = last;
    last = last->prev;
    if (!last->prev)
    {
        first = nullptr;
    }
    else
    {
        last = nullptr;
    }
    T *result = victim->op;
    delete victim;
    //TODO:necessay?
    // victim = nullptr;
    return result;
}
// EFFECTS removes and returns last object from non-empty list
//         throws an instance of emptyList if empty

template <class T>
Dlist<T>::Dlist() : first(nullptr), last(nullptr) {}
// constructor

template <class T>
Dlist<T>::Dlist(const Dlist &l)
{
    first = last = nullptr;
    copyAll(l);
}
// copy constructor

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
    if (this != &l)
    {
        removeAll();
        copyAll(l);
    } // TODO: to be checked
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}
// destructor

template <class T>
void Dlist<T>::removeAll()
{
    while (!this->isEmpty())
    {
        removeFront();
    }
}
// TODO: to be checked

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    removeAll();
    //insertBack(l.removeFront());
    //wrong: no const
    if(!l.isEmpty()){
		node *it = l.first;
		while(it){
			T *op_ = new T(*it->op);
			insertBack(op_);
			it = it->next; 
             delete op_;
		}
	}
}
#endif