#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <map>
#include "Snap.h"
#define INF 1000000
using namespace std;

const int NUM_NODES = 15;
PNGraph graph ;
int vVal[NUM_NODES][NUM_NODES];

void insertNode(int);
void insertVertex(int, int, int);
void removeNode(int);
void removeVertex(int, int);
void printDFS(bool[], int);
void printBFS(int);
void printPrim();
void printKrustal();
void printDijkstra(int);
void printFloyd();

vector<pair<int,int> > getChildIds(int);



int main(int argc, char* argv[])
{
    //Inicializar grafo
    graph = TNGraph::New();
	for (int i = 1; i < NUM_NODES; ++i)
        insertNode(i);

    insertVertex(1 ,3 ,8);
    insertVertex(1 ,4 ,8);
    insertVertex(2 ,5 ,7);
    insertVertex(3 ,2 ,7);
    insertVertex(3 ,5 ,8);
    insertVertex(3 ,10,4);
    insertVertex(4 ,5 ,1);
    insertVertex(4 ,7 ,3);
    insertVertex(4 ,8 ,2);
    insertVertex(5 ,6 ,9);
    insertVertex(6 ,13,4);
    insertVertex(7 ,4 ,6);
    insertVertex(8 ,7 ,3);
    insertVertex(8 ,9 ,3);
    insertVertex(9 ,10,2);
    insertVertex(9 ,12,4);
    insertVertex(10,3 ,10);
    insertVertex(10,6 ,6);
    insertVertex(11,12,6);
    insertVertex(12,9 ,2);
    insertVertex(12,11,8);
    insertVertex(12,14,9);
    insertVertex(13,14,6);
    insertVertex(14,13,2);

    //Ejecutar algoritmos
    bool visited[NUM_NODES];
    fill(visited, visited+NUM_NODES, false);
    cout << endl << "--- DFS ---" << endl;
    printDFS(visited,1);
    cout << endl << "--- BFS ---" << endl;
    printBFS(1);
    cout << endl << "--- Prim ---" << endl;
    printPrim();
    cout << endl << "--- Krustal ---" << endl;
    printKrustal();
    cout << endl << "--- Dijkstra ---" << endl;
    printDijkstra(1);
    cout << endl << "--- Floyd ---" << endl;
    printFloyd();
}

void printDFS(bool visited[], int actId)
{
    if (!visited[actId]){
        cout << actId << endl;
        visited[actId] = true;
        vector<pair<int,int> > childs = getChildIds(actId);

        for (int i = 0; i < childs.size(); i++)
            printDFS(visited,childs.at(i).first);
    }
}

void printBFS(int startId)
{
    queue<pair<int,int>> q;
    bool visited[NUM_NODES];
    fill(visited, visited+NUM_NODES, false);
    q.push(make_pair(startId,0));

    while (!q.empty()){
        int actId = q.front().first;
        q.pop();
        if (!visited[actId]){
            cout << actId << endl;
            vector<pair<int,int> > childs = getChildIds(actId);
            for (int i = 0; i < childs.size(); i++){
                q.push(childs.at(i));
            }
        }
        visited[actId] = true;
    }
}

void printPrim()
{
    queue<pair<int,int>> q;
    bool visited[NUM_NODES];
    int distances[NUM_NODES];
    fill(visited, visited+NUM_NODES, false);
    fill(distances, distances+NUM_NODES,INF);
    int startId = 4;
    q.push(make_pair(startId,0));
    distances[startId] = 0;

    while (!q.empty()){

        int actId = q.front().first;
        q.pop();
        if (!visited[actId]){
            vector<pair<int,int> > childs = getChildIds(actId);

            for (int i = 0; i < childs.size(); i++){
                q.push(childs.at(i));
            }
            cout << actId << " ";
        }
        visited[actId] = true;
    }
    cout << endl;

}


bool findInVector(vector<int> v, int val)
{
    for (int i = 0; i < v.size(); i++)
        if (v.at(i) == val)
            return true;
    return false;
}

bool isInVector(vector<int> c, vector<int> v){
     for (int i = 0; i < v.size(); i++)
        if (findInVector(c,v.at(i))) return true;
    return false;
}

void joinCluster(vector<int>& c, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        if (!findInVector(c,v.at(i)))
            c.insert(c.begin(),v.at(i));
}


void printKrustal()
{
    vector<vector<int> > q;
    vector<vector<int> > clusters;

    for (int j = 1; j < NUM_NODES; j++){
        for (int i = 1; i < NUM_NODES; i++){
            if (vVal[i][j] != 0){
                vector<int> cluster;
                cluster.push_back(i);
                cluster.push_back(j);
                clusters.push_back(cluster);
            }
        }
    }
    //Ordenar clusters
     for (int j = 0; j < clusters.size(); j++){
        for (int i = 0; i < clusters.size(); i++){
            if (vVal[clusters.at(i).at(0)][clusters.at(i).at(1)] > vVal[clusters.at(j).at(0)][clusters.at(j).at(1)]){
                vector<int> auxC = clusters.at(i);
                clusters.at(i) = clusters.at(j);
                clusters.at(j) = auxC;
            }
        }
    }

    //Agregar a la cola
    for (int i = 0; i < clusters.size(); i++){
        q.push_back(clusters.at(i));
    }

    vector<int> res;
    int it = 0;
    while (q.size() > 1)
    {
        vector<int> l  = q.at(0);
        bool join = false;
        for (int i = 1; i < q.size() && !join; i++)
        {
             vector<int> ll = q.at(i);
             if (isInVector(l,ll)){
                cout << "{";
                for (int i = 0; i < l.size(); i++)
                    cout << l.at(i) << (i < l.size() -1 ? "," : "");
                cout << "} {";
                 for (int i = 0; i < ll.size(); i++)
                    cout << ll.at(i) << (i < l.size() -1 ? "," : "");
                cout << "} ";

                joinCluster(l,ll);
                q.erase(q.begin());
                q.erase(q.begin());
                q.push_back(l);
                cout << " ::  {";
                for (int i = 0; i < l.size(); i++)
                    cout << l.at(i) << (i < l.size() -1 ? "," : "");
                cout << "} " << endl;
                join = true;
             }

        }
        it++;

    }
    cout << endl;

}

void printDijkstra(int startId)
{
    queue<pair<int,int>> q;
    bool visited[NUM_NODES];
    int distances[NUM_NODES];
    fill(visited, visited+NUM_NODES, false);
    fill(distances, distances+NUM_NODES,INF);

    q.push(make_pair(startId,0));
    distances[startId] = 0;

    while (!q.empty()){
        int actId = q.front().first;
        q.pop();
        if (!visited[actId]){
            vector<pair<int,int> > childs = getChildIds(actId);
            for (int i = 0; i < childs.size(); i++){
                if (distances[actId] + childs.at(i).second < distances[childs.at(i).first])
                {
                    distances[childs.at(i).first] = distances[actId] + childs.at(i).second;
                    q.push(childs.at(i));
                }
            }
        }
        visited[actId] = true;
    }

    for (int i = 1; i < NUM_NODES; i++){
        cout << "(" << i << ") ";
        if (distances[i] == INF) cout << "INF";
        else cout << distances[i];
        cout << endl;
    }
}

void printFloyd()
{
    int table[NUM_NODES][NUM_NODES];
    for (int j = 1; j < NUM_NODES; j++){
        for (int i = 1; i < NUM_NODES; i++){
            table[i][j] = vVal[i][j];
            if (table[i][j] == 0) table[i][j] = INF;
            if (i == j) table[i][j] = 0;
        }
    }

    for (int z = 1; z < NUM_NODES; z++){
        for (int j = 1; j < NUM_NODES; j++){
            for (int i = 1; i < NUM_NODES; i++){
                if (table[z][j] + table[i][z]< table[i][j]){
                    table[i][j] = table[z][j] + table[i][z];
                }
            }
        }
    }

    for (int j = 1; j < NUM_NODES; j++){
        for (int i = 1; i < NUM_NODES; i++){
            if (table[i][j] == INF) cout << "||";
            else{
                if (table[i][j] == 0) cout << "  ";
                else cout << setfill('0') << setw(2) << table[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }

}




void sortChilds(vector<pair<int,int> >& childs)
{
    sort(childs.begin(), childs.end(),
        [](const pair<int,int> & a, const pair<int,int> & b) -> bool
    {
    return a.second > b.second;
    });
}

vector<pair<int,int> > getChildIds(int id)
{
   vector<pair<int,int> > childs;
    TNGraph::TNodeI nodeI = graph->GetNI(id);
    for (int i = 1; i < NUM_NODES; i++){
        if (nodeI.IsOutNId(i)){
            childs.push_back(make_pair(i,vVal[id][i]));
        }
    }
    sortChilds(childs);
    return childs;
}


void insertNode(int id)
{
    graph->AddNode(id);
}

void insertVertex(int srcId, int desId, int value)
{
    graph->AddEdge(srcId, desId);
    vVal[srcId][desId] = value;
}

void removeNode(int id)
{
    graph->DelNode(id);
}
void removeVertex(int srcId, int desId)
{
    graph->DelEdge(srcId, desId);
    vVal[srcId][desId] = 0;
}
