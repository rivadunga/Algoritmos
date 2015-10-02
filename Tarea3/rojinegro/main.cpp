#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
#include "RedBlackTree.h"


using namespace std;

void readRandom(string,int[],int);


int main()
{


    /** EJEMPLO DE FUNCIONAMIENTO */

    RedBlackTree<int> * rbtree = new RedBlackTree<int>();
    int v;
    srand (time(NULL));
    for(int i = 0; i < 12; i++)
    {
        v = rand() % 1000;
        rbtree->insertRedBlack(v);
    }


    std::cout << "Imprimiendo en orden ascendente" << std::endl;
    rbtree->inOrder();
    std::cout << "Fin Imprimiendo en orden ascendente" << std::endl << std::endl;

    std::cout << "Imprimiendo en orden descendente" << std::endl;
    rbtree->orderDesc();
    std::cout << "Fin Imprimiendo en orden descendente" << std::endl;

    if(rbtree->search(20))
    {
        cout << "Si" << endl;
    } else {
        cout << "No" << endl;
    }
    if(rbtree->search(15))
    {
        cout << "Si" << endl;
    } else {
        cout << "No" << endl;
    }

    rbtree->isRedBlack(rbtree);




    /** PRUEBA DE BUSQUEDA */

    int N = 100000;
    int data[N];
    readRandom("data.txt",data,N);

    RedBlackTree<int> tree;
    for (int i = 0; i < N; i++)
        tree.insertRedBlack(data[i]);
    int M = 10;
    int data2[M];
    readRandom("search.txt",data2,M);

    for (int i = 0; i < M; i++){
        float start = clock();
        tree.search(data2[i]);
        cout << "TIME " << i+1 << " (" << data2[i] << "): " <<(clock() - start)/CLOCKS_PER_SEC << "s" << endl;
    }
}



void readRandom(string fileName,int data[],int N)
{
    ifstream read(fileName.c_str());
    int n,i;
    for(int i = 0; i < N; i++)
        read >> data[i];
}

