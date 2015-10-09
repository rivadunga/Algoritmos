#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
#include "TwoThreeTree.h"
using namespace std;

void readRandom(string,int[],int);

int main() {

    /** DEMOSTRACION DE FUNCIONALIDAD */
    TwoThreeTree<int> tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.remove(1);
    tree.search(3);
    tree.search(5);
    tree.printAsc();
    tree.printDes();



    /** PRUEBA DE BUSQUEDA */

    int N = 100000;
    int data[N];
    readRandom("data.txt",data,N);

    TwoThreeTree<int> ttTree;
    for (int i = 0; i < N; i++)
        ttTree.insert(data[i]);


    int M = 10;
    int data2[M];
    readRandom("search.txt",data2,M);

    for (int i = 0; i < M; i++){
        float start = clock();
        ttTree.search(data2[i]);
        cout << "TIME " << i+1 << " (" << data2[i] << "): " <<(clock() - start)/CLOCKS_PER_SEC << "s" << endl;
    }


    return 0;
}

void readRandom(string fileName,int data[],int N)
{
    ifstream read(fileName.c_str());
    int n,i;
    for(int i = 0; i < N; i++)
        read >> data[i];
}
