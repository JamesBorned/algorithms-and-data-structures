/*The laboratory work №2
 Найти в заданном графе кратчайшие пути из заданной вершины до всех
 остальных вершин с помощью поиска в ширину.
 Find the shortest paths from a given vertex to all other vertices
 in a given graph, using a breadth-first search (BFS).*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using std::cout;
using std::cin;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph

typedef std::vector<int> VINT_t;
 VINT_t Parent;
 VINT_t Dist;

 typedef std::vector<std::string> VSTR_t;
 VSTR_t used; // if graph contains cycles

 typedef std::queue<int> QINT_t;
 QINT_t Vertexes;

const int INF = INT_MAX;

int src = 0;

void Init(int n){
// Initialization of labels of each vertex by infinity
    for(int i = 0; i < n; ++i){
        used[i] = "white";
        Dist[i] = INF;
        Parent[i] = i;
    }

    Dist[src] = 0;
    Parent[src] = src;

// Put the start vertex in the queue
    Vertexes.push(src);
}

void findShortPathsBFS(int n){
    Init(n);

    while(!Vertexes.empty()){

        int u = Vertexes.front();

        for(int v = 0; v < n; ++v){

            if(G[u][v] != 0 && used[v] == "white"){
                used[v] = "grey";
                Parent[v] = u;
                Dist[v] = Dist[u] + 1;

                Vertexes.push(v);
            }
        }
        Vertexes.pop();
        used[u] = "black";
    }
}

void writeResultToFile(int n, std::ofstream& out){
    out<<"FROM "<<src<<" VERTEX \n";

    out<<"Node: \t\t\tCost :\t\t\tPath:\n";

    for(int i = 0; i < n; ++i){
        out<<i<<"\t\t\t\t\t"<< Dist[i] << "\t\t\t\t\t" << i << " ";

        int parVert = Parent[i];

        while (parVert != src) {
            out<<" <- "<< parVert << " ";
            parVert = Parent[parVert];
        }

        out<<'\n';
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
        Parent.resize(n);
        Dist.resize(n);
        used.resize(n);

// Reading the matrix
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                in >> G[i][j];
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "Enter the number of the vertex,\n from which you want to find the shortest paths to other vertices:\t";

        cin >> src;

        findShortPathsBFS(n);
        writeResultToFile(n, out);

        in.close();
    }

    return 0;
}
