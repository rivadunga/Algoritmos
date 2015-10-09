#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
#include "AvlTree.h"

void readRandom(string,int[],int);
int main(){

      /** DEMOSTRACION DE FUNCIONALIDAD */
    ArbolBinarioDeBusquedaBalanceado<int> arbol;
	arbol.inserta(55);
	arbol.imprimirLevelOrder();
	arbol.inserta(25);
	arbol.imprimirLevelOrder();
	arbol.inserta(77);
	arbol.imprimirLevelOrder();
	arbol.inserta(32);
	arbol.imprimirLevelOrder();
	arbol.inserta(44);
	arbol.imprimirLevelOrder();
	arbol.inserta(17);
	arbol.imprimirLevelOrder();
	arbol.inserta(99);
	arbol.imprimirLevelOrder();
	arbol.inserta(1);
	arbol.imprimirLevelOrder();
	arbol.inserta(18);
	arbol.imprimirLevelOrder();
	arbol.inserta(102);
	arbol.imprimirLevelOrder();
	arbol.inserta(28);
	arbol.imprimirLevelOrder();
	arbol.inserta(90);
	arbol.imprimirLevelOrder();
	arbol.inserta(293);
	arbol.imprimirLevelOrder();
	arbol.inserta(123);
	arbol.imprimirLevelOrder();
	arbol.inserta(188);
	arbol.imprimirLevelOrder();
	arbol.inserta(1000);
	arbol.imprimirLevelOrder();
	arbol.inserta(45);
	arbol.imprimirLevelOrder();
	arbol.borra(44);
	arbol.imprimirLevelOrder();
	arbol.borra(55);
	arbol.imprimirLevelOrder();
	arbol.borra(32);
	arbol.imprimirLevelOrder();
	arbol.borra(17);
	arbol.imprimirLevelOrder();
	arbol.borra(25);
	arbol.imprimirLevelOrder();
	arbol.borra(1000);
	arbol.imprimirLevelOrder();
	arbol.borra(99);
	arbol.imprimirLevelOrder();
	arbol.borra(77);
	arbol.imprimirLevelOrder();
	arbol.borra(90);
	arbol.imprimirLevelOrder();
	arbol.borra(123);
	arbol.imprimirLevelOrder();
	arbol.borra(1);
	arbol.imprimirLevelOrder();
	arbol.borra(18);
	arbol.imprimirLevelOrder();
	arbol.borra(28);
	arbol.imprimirLevelOrder();
	arbol.borra(293);
	arbol.imprimirLevelOrder();
	arbol.borra(188);
	arbol.imprimirLevelOrder();
	arbol.borra(102);
	arbol.imprimirLevelOrder();

    /** PRUEBA DE BUSQUEDA */
    int N = 100000;
    int data[N];
    readRandom("data.txt",data,N);

    ArbolBinarioDeBusquedaBalanceado<int> tree;
    for (int i = 0; i < N; i++)
        tree.inserta(data[i]);


    int M = 10;
    int data2[M];
    readRandom("search.txt",data2,M);

    for (int i = 0; i < M; i++){
        float start = clock();
        tree.contains(data2[i]);
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
