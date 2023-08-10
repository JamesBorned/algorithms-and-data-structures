/*Laboratory work №6
    Реализовать алгоритм Крускала нахождения минимального покрывающего дерева.
    Implement the Kruskal algorithm for finding a minimum spanning tree.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int numberOfEdges = 0;
int numberOfLoops = 0;
int minWeight = 0;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph
VV_t MST; // only vertexes without edges
VV_t Edges;

typedef std::vector<int> VINT_t;
VINT_t Parent;
VINT_t Rank;

using std::cout;
using std::cin;
using std::sort;
using std::all_of;
// The comparator for sorting of edges by non-decreasing
bool cmp(VINT_t &a, VINT_t &b){
    return a[2] < b[2];
}
// Forming subsets of a single vertex:
// 1) a parent of a single vertex is this vertex;
// 2) a height of root node is 0
void makeSet(int n){
    for (int i=0; i<n; i++){
        Parent.push_back(i);
        Rank.push_back(0);
    }
}

VV_t convertAdjMatrixToListOfEdges (int n, VV_t &edges) {
    // Add all edges with its weights to 'edges'
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = i; j < n; ++j) {
            if (G[i][j] != 0) {
                edges[i].push_back(i);
                edges[i].push_back(j);
                edges[i].push_back(G[i][j]);
            }
        }
     }
    // Edges originating from the same vertex are in a same vector, which size is not equal 3.
    for (int i = 0; i < edges.size(); ++i) {
        // Delete zero vectors
        if (all_of(edges[i].begin(), edges[i].end(),  [](int k) { return k==0; } ) == 1){
            edges[i].clear();
            edges[i].shrink_to_fit();
        }
        // Divide vectors, which size is greater than 3, into sub-vectors
        else if (edges[i].size() != 3 && all_of(edges[i].begin(), edges[i].end(),  [](int k) { return k==0; } ) == 0){
                unsigned long long countOfSubvectors = edges[i].size() / 3;
               // cout <<  countOfSubvectors;
            // каждая итерация этого цикла обрабатывает следующий набор n элементов
            // Each iteration of this loop processes the following set of n elements
            for  (int j = 0; j < countOfSubvectors; ++j){

                // получаем диапазон для следующего набора n элементов
                // Get the range for the following set of elements
                auto start_itr = std::next(edges[i].cbegin(), j*3);
                auto end_itr = std::next(edges[i].cbegin(), j*3 + 3);

                //cout << "1: " << edges.size() << " ";

                // выделяем память для подвектора
                // Allocate memory for sub-vector
                edges.resize(edges.size() + countOfSubvectors - 1, VINT_t (edges[i].size())); // - 1 - т.к. учитывается память, выделенная под тот, длинный вектор
                edges[edges.size() - countOfSubvectors + 1].resize(3);

                //cout << "2: " << edges.size() << " ";

                edges.resize(edges.size(), VINT_t (edges[i].size()));

                // копируем элементы из входного диапазона в конец 'edges'
                // Copying elements from the input range to the end of 'edges'
                std::copy(start_itr, end_itr, edges[edges.size() - countOfSubvectors + 1].begin());
            }
            // Delete useless vectors
            edges[i].clear();
            edges[i].shrink_to_fit();
         }

   }
    // Delete empty vectors
    for (int i = 0; i < edges.size();){
        if (edges[i].empty()){
            edges.erase(edges.begin() + i);
        }
        else
            ++i;
    }

    //cout << "3: " << edges.size() << " ";

    return edges;
}

int findParent(int node){
    if(Parent[node] == node){
        return node;
    }
    // Path compression
    return Parent[node] = findParent(Parent[node]);
}

// Combining subsets of vertices
void Union(int u, int v){
    u = findParent(u);
    v = findParent(v);

    if (Rank[u] < Rank[v]) {
        Parent[u] = v;
    }
    else if (Rank[v] < Rank[u]) {
        Parent[v] = u;
    }
    else {
        Parent[v] = u;
        Rank[u]++;
    }
}
//
void findMinSpanTree(int n) {

    makeSet(n);

    Edges = convertAdjMatrixToListOfEdges (n, Edges);

    cout << "\n";
// Writing a list of edges
    for (int i = 0; i < Edges.size(); ++i){
        for (int j = 0; j < Edges[i].size(); ++j){
            cout << Edges[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\n";

    sort(Edges.begin(), Edges.end(), cmp);
// // Writing a list of edges after sorting
    for (int i = 0; i < Edges.size(); ++i){
        for (int j = 0; j < Edges[i].size(); ++j){
            cout << Edges[i][j] << "\t";
        }
        cout << "\n";
    }

    for (int i=0; i<Edges.size(); i++){
        int u = findParent(Edges[i][0]);
        int v = findParent(Edges[i][1]);

        int weight = Edges[i][2];
        // If edge doesn't belong to a cycle
        if (u != v){
            MST[Edges[i][0]][Edges[i][1]] = weight;
            MST[Edges[i][1]][Edges[i][0]] = weight;
            minWeight += weight;
            Union(u, v);
        }
    }
    cout << minWeight;

    cout << "\n";
// Writing the adjacency matrix of MST
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cout << MST[i][j] << "\t";
        }
        cout << "\n";
    }

}


int main() {
    setlocale(LC_ALL,  "rus");

//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\weighted\\m3.txt");
    std::ofstream out("..\\output.txt");


    if(in.is_open()){

        int count = 0; // the number of numbers in the file
        int temp;

        while(!in.eof()){
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

        while(!in.eof()) {
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
        int tmp;
// изменить размер вектора на m элементов типа vector<int> , каждый из которых имеет размер  m
        G.resize(n, VINT_t(n));
        MST.resize(n, VINT_t(n));

// Reading the matrix
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                in >> G[i][j];
                if (i != j && G[i][j] != 0){
                    ++numberOfEdges;
                }
                else if (i == j && G[i][j] != 0){
                    ++numberOfLoops;
                }
            }
        }

        Edges.resize(numberOfEdges / 2 + numberOfLoops, VINT_t(3));

        cout << Edges.size() << '\n';
// Creating an empty graph
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                MST[i][j] = 0;
            }
        }

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "\n";

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << MST[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "\n";

        for (int i = 0; i < Edges.size(); ++i){
            for (int j = 0; j < Edges[i].size(); ++j){
                cout << Edges[i][j] << "\t";
            }
            cout << "\n";
        }

        findMinSpanTree(n);

        in.close();
    }
    else {
        cout << "File is not found.";
    }

    // Writing to the file consist of the connected components and its number
    if(out.is_open()) {
        for (int i = 0; i < MST.size(); i++) {
            for (int j = 0; j < MST[i].size(); j++) {
                out << MST[i][j] << " ";
            }
            out << '\n';
        }
        out.close();
    }

    return 0;
}