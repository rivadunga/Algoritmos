#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


/**
* TECNICA DE DISEÑO = ALGORITMO AVIDO
* COMPLEJIDAD = O(NM) = O(N^2)
*               donde N es el número de palabras
*               y M la longitud más larga
*/


int L,B;

void printLine(string line, int Bin)
{
    string newLine;
    for (int j = 0; j < line.length()-1; j++)
    {
        //& es para identificar los espacios
        if (line.at(j) != '&' ) newLine += line.at(j);
        else{
            for (int i = 0; i < Bin; i++) newLine += "_";
            //Imprime Bin veces _
        }
    }
    //Balancea la cadena
    int newLen = newLine.length();
    for (int i = 0; i < abs(newLen - L); i++){
        if (newLine.find("_") != -1){
            if (newLen - L > 0) newLine = newLine.substr(0,newLine.find("_")-1) +  newLine.substr(newLine.find("_"), newLine.size());
            else newLine = newLine.substr(0,newLine.find("_")) + "_" + newLine.substr(newLine.find("_"), newLine.size());
        }
    }
    cout << newLine << endl;
}


// Determina si se inserta en la linea actual o en la siguiete dependiendo
// del gasto necesario

bool insertHere(string line, int num, int& newB, string last)
{
    int BAgregar = B;
    int BQuitar = B;

    int actLen = line.length() -num;
    int subLen = line.length() - last.length()-num;

    if (num == 2){ newB =B; return false; }

    while (subLen + (num-2)*(BQuitar) < L )
        BQuitar++;

    while (actLen + (num-1)*(BAgregar) > L && BAgregar > 1)
        BAgregar--;

    if (!(abs(B-BAgregar) > abs(B-BQuitar)) && !(actLen + (num-1)*(BAgregar) > L)){
        newB = BAgregar;
        return true;
    }
    else{
        newB = BQuitar;
        return false;
    }
}


int main()
{
    string text = "",word = "";
    cin >> L >> B;
    cin.ignore();
    getline(cin,text);

    vector<string> words;
    for (int i = 0; i < text.length(); i++){
        if (text[i] != ' ')
            word+= text[i];
        else{
            words.push_back(word);
            word = "";
        }
    }
    words.push_back(word);


    //Logica de la solucion

    string auxLine = "";
    int auxNum = 0;
    for (int j = 0; j < words.size(); j++)
    {
        auxLine += words[j] + "&";
        auxNum++;
        if (auxLine.length()-1 + (B-1)*(auxNum-1) >= L)
        {
            if (auxLine.length()-1 + (B-1)*(auxNum-1) == L){
                //No es necesario evaluar nada porque cabe perfectamente
                printLine(auxLine,B);
                auxLine = "";
                auxNum = 0;
            }
            else{
                int BAux = 0; //Nuevo espacio entre palabras

                if (insertHere(auxLine, auxNum, BAux, words[j])){
                    //Inserta en la imsma linea
                    printLine(auxLine,BAux);
                    auxLine = "";
                    auxNum = 0;
                }else{
                    //Quita de la linea actual e inserta en la siguiente
                    auxLine = auxLine.substr(0,auxLine.length()-(words[j].length()+1));
                    printLine(auxLine,BAux);
                    auxLine = words[j] + "&";
                    auxNum = 1;
                    if (j == words.size()-1) cout << auxLine << endl;
                }
            }
        }
    }
}
