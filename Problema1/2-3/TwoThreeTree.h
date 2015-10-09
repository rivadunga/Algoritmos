#include "TwoThreeNode.h"
#include <iostream>
using namespace std;
template<class T>
class TwoThreeTree
{
    private:

    TwoThreeNode<T> *root;

    TwoThreeNode<T>* findSpot(TwoThreeNode<T> *node, int data)
    {
        if (node == nullptr) return nullptr;
        while (!node->isLeaf())
        {
            if (node->key[0] == data || node->key[1] == data)
            return nullptr;
            if (node->key[0] == -1 || data < node->key[0])
            node = node->child[0];
            else if (node->key[1] == -1 || data < node->key[1])
            node = node->child[1];
            else
            node = node->child[2];
        }
        if (node->key[0] == data) return nullptr;
        return node->parent;
    }

    void print(TwoThreeNode<T> *node,bool descAsc, int prof = 0)
    {
        for (int i = 0; i < prof; ++i)
        {
            cout << "\t";
        }
        if (node == nullptr)
        {
            cout << "-" << endl;
            return;
        }
        cout << node->key[0]  << endl;
        if (!node->isLeaf())
        {
            ++prof;
            if (descAsc)
            {
                for (int i = 0; i < 3; i++) print(node->child[i], descAsc,prof);
            }
            else
            {
                for (int i = 2; i >= 0; i--) print(node->child[i], descAsc,prof);
            }
        }
    }


    void findNode(TwoThreeNode<T> *node,T value, TwoThreeNode<T>*& found)
    {
        if (node == nullptr)
        return;
        if (node->key[0] == value)
        {
            found = node;
            return;
        }
        if (!node->isLeaf())
        for (int i = 0; i < 3; i++) findNode(node->child[i],value,found);
    }


    void getDeep(TwoThreeNode<T> *node,T value, int& deepFound, int deep = 0)
    {
        if (node != nullptr)
        {
            return;
        }
        if (node->key[0] == value)
        {
            deepFound = deep;
        }
        if (!node->isLeaf())
        {
            ++deep;
            for (int i = 0; i < 3; i++) getDeep(node->child[i],value,deepFound,deep);
        }
    }


    public:

    TwoThreeTree()
    {
        root = new TwoThreeNode<T>();
        root->child[0] = new TwoThreeNode<T>();
        root->child[0]->parent = root;
    }

    bool insert(T data)
    {
        TwoThreeNode<T> *newNode = new TwoThreeNode<T>(data);
        TwoThreeNode<T> *spot = root->child[0];
        if (spot->child[0] == nullptr)
        {
            newNode->parent = spot;
            spot->child[0] = newNode;
        }
        else
        {
            spot = findSpot(spot, data);
            if (spot == nullptr) return false;
            spot->insert(new TwoThreeNode<T>(data), data);
        }
        return true;
    }

    void remove(T data)
    {
        TwoThreeNode<T>* node;
        findNode(root->child[0],data,node);
        TwoThreeNode<T>* parent = node->parent;
        if (node == nullptr) return;
        if (node->isLeaf())
        {
            for (int i = 0; i < 3; i++)
            {
                if (node == parent->getChildAt(i))
                {
                    TwoThreeNode<T>* removed = parent->getChildAt(i);
                    parent->getChildAt(i) = nullptr;
                    delete removed;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (node == parent->getChildAt(i))
                {
                    TwoThreeNode<T>* removed = parent->getChildAt(i);
                    TwoThreeNode<T>* leftChild = removed->getChildAt(0);
                    parent->getChildAt(i) = leftChild;
                    removed->getChildAt(1)->parent = leftChild;
                    removed->getChildAt(2)->parent = leftChild;
                    leftChild->getChildAt(0) = removed->getChildAt(1);
                    leftChild->getChildAt(1) = removed->getChildAt(2);
                    delete removed;
                    break;
                }
            }
        }
    }

    void printAsc()
    {
        print(root->child[0],true);
        cout << endl;
    }

    void printDes()
    {
        print(root->child[0],false);
        cout << endl;
    }


    void search(T value)
    {
        TwoThreeNode<T>* node = nullptr;
        findNode(root->child[0],value,node);
        if (node != nullptr)
        cout << "Nodo encontrado" << endl;
        else
        cout << "Nodo no encontrado" << endl;
    }


    void getDeep(T value)
    {
        int deep = 0;
        getDeep(root->child[0], value,deep);
        cout << "Profundidad: " << deep << endl;
    }


    void getHigh(T value)
    {
        int deep = 0;
        getDeep(findNode(root->child[0],value),findNode(root->child[0],value)->getSmallest(),deep);
        cout << "Altura: " << deep;
    }


    void getLevel(T value)
    {
        cout << "Nivel: " << getDeep(root->child[0],root->getSmallest()) - getDeep(root->child[0],value);
    }


};
