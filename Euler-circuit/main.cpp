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
                DFS(u);
            }
        }
}

bool isConnected(int n){

    Init(n);

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

// No start node was found--> No edges are present in graph
    if(vertex == -1){
        return true;
    }

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

}

void findCycle(int n, int v){

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
                findCycle(n, u);
            }
            else{
                if (Degrees[u] != 0) {
                    Cycles.push_back(u);
                }
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

void writeResultToFile(int n, std::ofstream& out){

    for(int Cycle : Cycles){
        out << Cycle << " ";
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

    findEuler_Path_Cycle(n);

//        for(int i = 0; i < Cycles.size(); ++i){
//            cout << Cycles[i] << '\n';
//        }

        writeResultToFile(n, out);

        in.close();

    }

        return 0;
}
