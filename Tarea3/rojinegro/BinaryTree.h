#include <iostream>
#include "BNode.h"

template <class T>
class BinaryTree
{
protected:
    BNode<T> * root = nullptr;

public:
    BinaryTree();
    BinaryTree(BNode<T> * info);

    ~BinaryTree();
    void clear();
    void clear(BNode<T> * node);

    bool empty();
    BNode<T> * getRoot();
    void setRoot(BNode<T> * node);

    void inOrder();
    void inOrder(BNode<T> * node);

    void orderDesc();
    void orderDesc(BNode<T> * node);

    BNode<T> * getNode (T info);
    BNode<T> * getNode (T info, BNode<T> * node);
};

template <class T>
BinaryTree<T>::BinaryTree() {}

template <class T>
BinaryTree<T>::BinaryTree(BNode<T> * info)
{
    root = info;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    clear(root);
}

template <class T>
void BinaryTree<T>::clear()
{
    clear(root);
}

template <class T>
void BinaryTree<T>::clear(BNode<T> * node)
{
    if (node)
    {
        clear(node->getLeft());
        clear(node->getRight());

        delete node;
    }
}

template <class T>
bool BinaryTree<T>::empty()
{
    return (root == nullptr);
}

template <class T>
BNode<T> * BinaryTree<T>::getRoot()
{
    return root;
}

template <class T>
void BinaryTree<T>::setRoot(BNode<T> * node)
{
    root = node;
}

template <class T>
void BinaryTree<T>::inOrder()
{
    inOrder(root);
}

template <class T>
void BinaryTree<T>::inOrder(BNode<T> * node)
{
    if (node)
    {
        inOrder(node->getLeft());
        std::cout << *node << " / " << node->getColor() << endl;
        inOrder(node->getRight());
    }
}

template <class T>
void BinaryTree<T>::orderDesc()
{
    orderDesc(root);
}

template <class T>
void BinaryTree<T>::orderDesc(BNode<T> * node)
{
    if (node)
    {
        orderDesc(node->getRight());
        std::cout << *node << " / " << node->getColor() << endl;
        orderDesc(node->getLeft());
    }
}

template <class T>
BNode<T> * BinaryTree<T>::getNode(T info)
{
    return getNode(info, root);
}

template <class T>
BNode<T> * BinaryTree<T>::getNode(T info, BNode<T> * node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (info == node->getInfo())
        {
            return node;
        }
        else if (info < node->getInfo())
        {
            return getNode(info, node->getLeft());
        }
        else
        {
            return getNode(info, node->getRight());
        }
    }
}

