#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>{

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    virtual BNode<T>* insert(T value);

    bool search(const T item) const;
    bool search(const T item, BNode<T> * node) const;
    BNode<T> * searchGetNode(const T item, BNode<T> * node) const;


};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>()
{

}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    this->clear();
}

template<class T>
BNode<T>* BinarySearchTree<T>::insert(T value)
{
    BNode<T> * node = new BNode<T>(value);
    BNode<T> * parent;

    node->setRight(nullptr);
    node->setLeft(nullptr);
    parent = node->getParent();

    if(this->empty())
    {
        this->setRoot(node);
    }
    else
    {
        BNode<T> * tmp = new BNode<T>();
        tmp = this->getRoot();
        while (tmp)
        {
            parent = tmp;
            if(node->getInfo() >= tmp->getInfo())
            {
                tmp = tmp->getRight();
            }
            else
            {
                tmp = tmp->getLeft();
            }
        }
        if(node->getInfo() >= parent->getInfo())
        {
            parent->setRight(node);
            node->setParent(parent);
        }
        else
        {
            parent->setLeft(node);
            node->setParent(parent);
        }
    }
    return node;
}

template <class T>
bool BinarySearchTree<T>::search(const T item) const
{
    return search(item, BinaryTree<T>::root);
}

template <class T>
bool BinarySearchTree<T>::search(const T item, BNode<T> * node) const
{
    BNode<T> * output = searchGetNode(item, node);
    if (output == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <class T>
BNode<T> * BinarySearchTree<T>::searchGetNode(const T item, BNode<T> * node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        T nodeValue = node->getInfo();
        if (item == nodeValue)
        {
            return node;
        }
        else if (item < nodeValue)
        {
            return searchGetNode(item, node->getLeft());
        }
        else {
            return searchGetNode(item, node->getRight());
        }
    }
}

#endif
