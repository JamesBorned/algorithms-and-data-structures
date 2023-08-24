/*Laboratory work №10
    Реализовать алгоритм нахождения эйлерова цикла в неориентированном графе,
    заданном матрицей смежности.
    Implement an algorithm for finding an Euler circuit in an undirected graph
    given by adjacency matrix.
*/

#include <iostream>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;

typedef std::vector<int> VINT_t;
VINT_t Cycles;
VINT_t Degrees;
VINT_t OddDegrees;

typedef std::vector<bool> VBOOL_t;
VBOOL_t used;

typedef std::vector<VINT_t> VV_t;
VV_t G;

int numOfNonZeroDegrees = 0;

void Init(int n){
    used.resize(n);
    used.assign(n, false);

    Degrees.resize(n);
}

// Depth-first search
void DFS(int v) {
    used[v] = true; // the vertex is traversed
    for (int u = 0; u < G.size(); ++u) {
            // if u is not traversed and u is an adjacent to v vertex
            if (!used[u] && G[v][u] == 1) {
                //Cycles.push_back(u);
// Delete an edge
//                G[v][u] = 0;
//                G[u][v] = 0;
                DFS(u);
            }
        }
}

//void DFS(int curr, std::vector<bool>& visited){
//    visited[curr] = true;
//
//    for(auto it: adj[curr]){
//        if(!visited[it]){
//            DFS(it, visited);
//        }
//    }
//}

bool isConnected(int n){

    Init(n);

// Node to start DFS
    int vertex = -1;

//    for(int i = 0; i<V; ++i){
//        if(adj[i].size() > 0){
//            node = i;
//            break;
//        }
//    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if(G[i][j] != 0){
                vertex = j;
                break;
            }
        }
    }

// No start node was found--> No edges are present in graph
    if(vertex == -1){
        return true;
    }
//    else {
//        DFS(vertex);
//    }

    DFS(vertex);

// Check if all the non-zero vertices are visited
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!used[i] && G[i][j] == 1) {
// We have edges in multi-component
                return false;
            }
        }
    }

    return true;
}

int haveEvenDegrees(int n){

    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Degrees[i] += G[i][j];
        }
        if (Degrees[i] % 2 != 0) {
            OddDegrees.push_back(i);
        }
    }

    if (!OddDegrees.empty() && OddDegrees.size() != 2) {
        return 0;
    }
    else {
        return 1;
    }
}

int haveEulerPath (int n) {

// Multi-component edged graph
    if(!isConnected(n)){
// All non-zero degree vertices should be connected
        return 0;
    }

    if(!haveEvenDegrees(n)){
        return 0;
    }

    return 1;
// Count odd-degree vertices
 //   int odd = 0;
//    for (int i = 0; i<V; ++i){
//// The operation AND of each bit in adj[i].size() is performed
//// with each corresponding bit in 1
//        if(adj[i].size() & 1)
//            odd += 1;
//    }
//// Only start and end node can have odd degree
//    if(odd > 2){
//        return 0;
//    }
//// 1->Semi-Eulerian ... 2->Eulerian
//    return (odd==0)?2:1;

}

void findCycle(int n, int v){

    //Init(n);

    //used[v] = true; // the vertex is traversed


    //Cycles.push_back(v);

    for (int u = 0; u < G.size(); ++u) {
        if(Cycles[Cycles.size() - 1] != v && Degrees[v] == 2){
            Cycles.push_back(v);
        }
        // if u is not traversed and u is an adjacent to v vertex
        if (G[v][u] == 1) {
            Degrees[v]--;
            Degrees[u]--;

            Cycles.push_back(u);

// Delete an edge
            G[v][u] = 0;
            G[u][v] = 0;

            if (Degrees[u] % 2 != 0){
//                int tmp = 0;
//                for (int j = 0; j < Degrees.size();++j){
//                    if (Degrees[j] == 0)
//                        numOfNonZeroDegrees++;
//                    else
//                        cout << tmp << numOfNonZeroDegrees;
//                        tmp = j;
//                }
//                if(numOfNonZeroDegrees == n-1){
//                    Cycles.push_back(tmp);
//                }
                findCycle(n, u);
            }
            else{
                if (Degrees[u] != 0) {
                    Cycles.push_back(u);
                }
//                for (int i = 0; i < n; ++i) {
//                    for (int j = 0; j < n; ++j) {
//                        cout << G[i][j] << "\t";
//                    }
//                    cout << "\n";
//                }
                break;
            }
        }
    }
}

void findAllCycles(int n){
    // Node to start DFS
    int vertex = -1;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if(G[i][j] != 0){
                vertex = j;
                break;
            }
        }
    }

    Cycles.push_back(vertex);

    findCycle(n, vertex);

    //cout << Cycles.size();

//    for(int i = 0; i < Cycles.size(); ++i) {
//        if (Degrees[Cycles[i]] != 0) {
//            int tmp = Cycles[i];
//            cout << "<" << tmp << ">";
//            Cycles.push_back(tmp);
           // findCycle(n, Cycles[i]);
       // }

}

void findEuler_Path_Cycle(int n){

    if (!haveEulerPath(n)) {
        cout << "Graph is not a Euler graph\n";
    }
    else {
        if (OddDegrees.empty()){
            cout << "Graph is Eulerian (Euler circuit).\n";
            findAllCycles(n);
        }
        else {
            cout << "Graph is Semi-Eulerian.\n";
        }
    }
}

int main() {

    setlocale(LC_ALL, "rus");

//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\connected\\m5.txt");
    std::ofstream out("..\\output.txt");


    if (in.is_open()) {

        int count = 0; // the number of numbers in the file
        int temp;

        while (!in.eof()) {
            in >> temp; // reading numbers from the file
            count++;
        }
// First, let's move the carriage in the stream to the beginning of the file
// istream&seekg(streamoff offset, ios_base::seekdir) =>
//parameters: offset in the stream buffer, flow direction
// beg - offset from the beginning of the stream buffer, cur - offset from
// the current position, end - from the end
        in.seekg(0, std::ios::beg);
        in.clear();

        int count_space = 0; // a number of spaces
        char symbol;

        while (!in.eof()) {
            in.get(symbol); // reading the next character
            if (symbol == ' ')
                count_space++;
            if (symbol == '\n')
                break;
        }
// Jump to the beginning of the file
        in.seekg(0, std::ios::beg);
        in.clear();
// Matrix formation
        int n = count_space + 1; // число столбцов
// изменить размер вектора на n элементов типа vector<int>, каждый из которых имеет размер  n
        G.resize(n, VINT_t(n));
        //Degrees.resize(n);

// Reading the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in >> G[i][j];
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

//    adj[0].push_back(1);
//    adj[1].push_back(0);
//    adj[0].push_back(2);
//    adj[2].push_back(0);
//    adj[2].push_back(1);
//    adj[1].push_back(2);
//    adj[0].push_back(3);
//    adj[3].push_back(0);
//    adj[3].push_back(4);
//    adj[4].push_back(3);
//    findEuler_Path_Cycle();

    findEuler_Path_Cycle(n);

        for(int i = 0; i < Cycles.size(); ++i){
            cout << Cycles[i] << '\n';
        }

        return 0;
    }
}
