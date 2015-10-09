#include<iostream>
#include<string>
using namespace std;

/**
* COMPLEJIDAD = O(N^2)
*               donde N es la longitud de la
*               cadena más larga
*/


int main()
{
    string A,B;
    getline(cin,A);
    getline(cin,B);

    if (B.length() > A.length())  swap(A,B);
    //A debe ser el mayor

    int maxLen = 0;
    string subStr = "";

    /*
        Algoritmo (comportamiento a grandes rasgos)
          - A B C D -
          D E
            D E
              D E
                D E
                  D E
    */

    for (int j = 0; j < 2*A.length(); j++)
    {
        string auxSubStr = "";
        int cmpJ = j - B.length();

        for (int i = 0; i < B.length(); i++){

            if (cmpJ+i < 0
                || cmpJ+i >= A.length()) continue;

            if (B[i] == A[cmpJ+i]){
                auxSubStr += B[i];
            }else{
                if (auxSubStr.length() > subStr.length()) subStr = auxSubStr;
                auxSubStr = "";
            }
        }
        if (auxSubStr.length() > subStr.length()) subStr = auxSubStr;
    }

    cout << "  * Subcadena mas larga: " << endl << subStr << "(" << subStr.length() << ") " << endl;
    return 0;
}
