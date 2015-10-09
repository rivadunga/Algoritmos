#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

/**
* TECNICA DE DISEÑO = ALGORITMO AVIDO
* COMPLEJIDAD = O(N^2)
*               donde N es el número de
*               gasolineras
*/

int main()
{

    int totDist;
    int gasMil;
    int numGS;
    cin >> totDist >> gasMil >> numGS;
    int ubiGS[numGS];

    for (int i = 0; i < numGS; i++)
        cin >> ubiGS[i];

    sort(ubiGS, ubiGS + numGS+1);


    int it = 0;
    queue<int> nodesRes;
    nodesRes.push(0);
    bool found = false;

    do{
        //Busca la gasolinera más lejana a la que se pueda llegar con
        //el rendimiento de gasolina
        for (int i = numGS; i >= 0; --i){
            if (ubiGS[i]-nodesRes.back() <= gasMil){
                //Utiliza como soluciones parciales la última gasolinera que visitó
                nodesRes.push(ubiGS[i]);
                if (totDist-ubiGS[i] <= gasMil) found = true;
                break;
            }
        }
        it++;
    }while(!found && it < numGS);

    cout << "--- Mejor ruta ---" << endl;
    while (!nodesRes.empty())
    {
        cout << " - " << nodesRes.front() << endl;
        nodesRes.pop();
    }

    return 0;
}
