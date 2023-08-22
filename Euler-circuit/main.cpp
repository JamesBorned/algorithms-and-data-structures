/*Laboratory work №10
    Реализовать алгоритм нахождения эйлерова цикла в неориентированном графе,
    заданном матрицей смежности.
    Implement an algorithm for finding an Euler circuit in an undirected graph
    given by adjacency matrix.
*/

#include <iostream>
//#include <vector>
//#include <unordered_map>

using 

unordered_map<int, vector<int>> adj;

const int V = 6;

void DFS(int curr, vector<bool>& visited){
    visited[curr] = true;

    for(auto it: adj[curr]){
        if(!visited[it]){
            DFS(it, visited);
        }
    }
}

bool Connected_Graph(){
    vector<bool> visited(V+1, false);

// Node to start DFS
    int node = -1;

    for(int i = 0; i<V; ++i){
        if(adj[i].size() > 0){
            node = i;
            break;
        }
    }

// No start node was found--> No edges are present in graph
    if(node == -1){
        return true;
    }

    DFS(node, visited);

// Check if all the non-zero vertices are visited
    for(int i=0; i<V; ++i){
        if(visited[i]==false and adj[i].size()>0){
// We have edges in multi-component
            return false;
        }
    }

    return true;
}

int find_Euler(){
// Multi-component edged graph
    if(!Connected_Graph()){
// All non-zero degree vertices should be connected
        return 0;
    }

// Count odd-degree vertices
    int odd = 0;
    for (int i=0; i<V; ++i){
// The operation AND of each bit in adj[i].size() is performed
// with each corresponding bit in 1
        if(adj[i].size() & 1)
            odd += 1;
    }
// Only start and end node can have odd degree
    if(odd > 2){
        return 0;
    }
// 1->Semi-Eulerian ... 2->Eulerian
    return (odd==0)?2:1;
}

void findEuler_Path_Cycle(){
    int ret = find_Euler();
    if (ret == 0){
        cout << "Graph is not a Euler graph\n";
    }
    else if(ret == 1){
        cout << "Graph is Semi-Eulerian\n";
    }
    else{
        cout << "Graph is Eulerian (Euler circuit)\n";
    }
}

int main() {
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[1].push_back(2);
    adj[0].push_back(3);
    adj[3].push_back(0);
    adj[3].push_back(4);
    adj[4].push_back(3);
    findEuler_Path_Cycle();

    return 0;
}
