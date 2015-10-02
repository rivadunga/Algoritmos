//
//  BNode.h
//  BinaryTree
//
//  Created by Vicente Cubells Nonell on 26/03/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#ifndef BNode_h
#define BNode_h

#include <iostream>
using namespace std;


template <class T>
class BNode {

    BNode<T> * parent = nullptr;
    BNode<T> * left = nullptr;
    BNode<T> * right = nullptr;

    T info;

    // Added color for Red-Black Tree. False is black, true is red.
    string color;

public:

    BNode() { }
    BNode(const T & _info) : info (_info) { }
    BNode(const BNode<T> & );

    virtual ~BNode();

    T getInfo() const { return info; }
    void setInfo(const T & value) { info = value; }

    // Functions for color. Red-Black Tree.
    string getColor() const { return color; }
    void setColor(string value) { color = value; }

    BNode<T> * getLeft() const { return left; }
    void setLeft(BNode<T> * value) { left = value; }

    BNode<T> * getRight() const { return right; }
    void setRight(BNode<T> * value) { right = value; }

    BNode<T> * getParent() const { return parent; }
    void setParent(BNode<T> * value) { parent = value; }

    template <typename Tn>
    friend std::ostream & operator << (std::ostream & os, const BNode<Tn>  & node);
};

template <class T>
BNode<T>::BNode(const BNode<T> & other)
{
    info = other.info;
    color = other.color;
    left = other.left;
    right = other.right;
    parent = other.parent;
}

template <class T>
BNode<T>::~BNode()
{
    info.~T();
    left = right = parent = nullptr;
}


template <class T>
std::ostream & operator << (std::ostream & os, const BNode<T>  & node)
{
    os << node.info;

    return os;
}

#endif
