/*Laboratory work №8
    Реализовать алгоритм Дейкстры поиска кратчайших путей из одной вершины, используя
    в качестве приоритетной очереди обычный массив.
    Implement Dijkstra's algorithm for finding shortest paths from a single vertex,
    using a regular array as a priority queue.
*/

#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph

typedef std::vector<int> VINT_t;
VINT_t Parent;
VINT_t Dist;

typedef std::vector<bool> VBOOL_t;
VBOOL_t used;

const int INF = INT_MAX;

int src = 0;

void Init(int n){
// Initialization of labels of each vertex by infinity
    for(int i = 0; i < n; ++i){
        Dist[i] = INF;
    }

    Dist[src] = 0;
    Parent[src] = src;
}

int getNearest(int n){
    int minDist = INF;
    int minDistVert = 0;

    for(int i = 0; i < n; ++i){
        if(!used[i] && Dist[i] < minDist){
            minDist = Dist[i];
            minDistVert = i;
        }
    }

    return minDistVert;
}

void findShortPathsDijkstra(int n){
    Init(n);

    for(int i = 0; i < n; ++i){

        int  minDistVert = getNearest(n);

        used[minDistVert] = true;

        for(int adj = 0; adj < n; ++adj){

// If sum of a label of the nearest vertex and weight of an incident edge less,
// than a label of its adjacent vertex
            if(Dist[minDistVert] + G[minDistVert][adj] < Dist[adj] && G[minDistVert][adj] != 0){
                Dist[adj] = Dist[minDistVert] + G[minDistVert][adj];
                Parent[adj] = minDistVert;
            }
        }
    }
}

void writeResultToFile(int n, std::ofstream& out){
    out<<"FROM "<<src<<" VERTEX \n";

    out<<"Node: \t\t\tCost :\t\t\tPath:\n";

    for(int i = 0; i < n; ++i){
        out<<i<<"\t\t\t\t\t"<< Dist[i] << "\t\t\t\t\t" << i << " ";

        int parVert = Parent[i];

        do {
            out<<" <- "<< parVert << " ";
            parVert = Parent[parVert];
        } while (parVert != src);

        out<<'\n';
    }
}

int main() {

    setlocale(LC_ALL, "rus");

//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\weighted\\m2.txt");
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

        findShortPathsDijkstra(n);
        writeResultToFile(n, out);
        
        in.close();
    }

        return 0;
}

