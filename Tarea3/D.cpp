#include<iostream>
using namespace std;

const int MAX_DATOS = 100;

int HPs[MAX_DATOS][MAX_DATOS];
int MPs[MAX_DATOS][MAX_DATOS];


/**
* TECNICA DE DISEÑO = BACKTRACKING
* COMPLEJIDAD = O(N^3 * N!)
*               donde N es el número de parejas
*/


bool checkPermutation(bool matrix[][MAX_DATOS], bool parH[MAX_DATOS], bool parM[MAX_DATOS],int N)
{
     for (int j = 0; j < N; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            if (matrix[i][j])
            {
                int indexH = j;
                int indexM = i;

                //Evalua primer condición
                for (int z = 0; z < N; z++)
                {
                    if (HPs[z][indexH] == indexM) break; //Si ya encontro a la pareja
                    int MP = HPs[z][indexH]; //Revisa las parejas que van antes

                    for (int w = 0; w < N; w++)
                    {
                        if (MPs[z][MP] == matrix[w][MP]) break; //Si su pareja va antes es valido y continua
                        if (MPs[z][MP] == indexH) return false; //CASO INVALIDO
                    }
                }

                //Segunda condición
                for (int z = 0; z < N; z++)
                {
                    if (MPs[z][indexM] == indexH) break; //Si ya encontro a la pareja
                    int HP = HPs[z][indexM]; //Revisa las parejas que van antes

                    for (int w = 0; w < N; w++)
                    {
                        if (HPs[z][HP] == matrix[HP][w]) break; //Si su pareja va antes es valido y continua
                        if (HPs[z][HP] == indexM) return false; //CASO INVALIDO
                    }
                }
            }
        }
    }

     cout << "--- COMBINACION PERFECTA :D ---" << endl;
     for (int j = 0; j < N; ++j)
        for (int i = 0; i < N; ++i)
            if (matrix[i][j])
                cout << " * H(" << j << ") * M(" << i << ")" << endl;

    return true;
}


bool isDone = false;
void getPermutations(int numPareja, bool matrix[][MAX_DATOS], bool parH[MAX_DATOS], bool parM[MAX_DATOS],int N)
{
    if (numPareja < N && !isDone)
    {
        for (int j = 0; j < N; ++j){
            if (parH[j]) continue; //Poda porque ya tiene pareja
            for (int i = 0; i < N; ++i){
                if (parM[i]) continue; //Poda porque ya tiene pareja
                matrix[i][j] = true;
                parH[j] = true;
                parM[i] = true;
                getPermutations(numPareja+1,matrix,parH,parM,N);
                matrix[i][j] = false; //Reinicia matrix, para que no afecte la siguiente iteración
                parH[j] = false;
                parM[i] = false;
            }
        }
    }else{
        if (!isDone)
            isDone = checkPermutation(matrix,parH, parM, N); //Cuando se termina el revisa cada permutacion
    }
}

int main()
{
    int N;
    cin >> N;

    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            cin >> HPs[i][j];

     for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            cin >> MPs[i][j];

    bool matriz[MAX_DATOS][MAX_DATOS];
    bool parH[MAX_DATOS];
    bool parM[MAX_DATOS];

    for (int j = 0; j < N; j++){
        for (int i = 0; i < N; i++){
            matriz[i][j] = false;
        }
        parH[j] = false;
        parM[j] = false;
    }
    getPermutations(0,matriz,parH, parM, N);
    return 0;
}
