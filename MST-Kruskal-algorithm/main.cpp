/*Laboratory work №6
    Реализовать алгоритм Крускала нахождения минимального покрывающего дерева.
    Implement the Kruskal algorithm for finding a minimum spanning tree.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

const int N = 100;
int SCC = 0; // количество сильно связных компонент связности

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // directed graph
VV_t onlyV; // only vertexes without edges
VV_t IG; // inverted directed graph
VV_t StrongConComp; // strongly connected components

typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;
VINT_t order; // время выхода вершин
VINT_t component;
VINT_t Parent;
VINT_t Rank;

typedef std::vector
using std::cout;
using std::cin;

//bool cmp(VINT_t &a, VINT_t &b){
//    return a[2] < b[2];
//}
//
void makeSet(int n){
    for (int i=0; i<n; i++){
        Parent[i] = i;
        Rank[i] = 0;
    }
}
//
//int findParent(VINT_t &parent, int node){
//    if(parent[node] == node){
//        return node;
//    }
//    return parent[node] = findParent(parent, parent[node]);
//}
//
//void unionSet(int u, int v, VINT_t &parent, VINT_t &rank){
//    u = findParent(parent, u);
//    v = findParent(parent, v);
//
//    if (rank[u] < rank[v]) {
//        parent[u] = v;
//    }
//    else if (rank[v] < rank[u]) {
//        parent[v] = u;
//    }
//    else {
//        parent[v] = u;
//        rank[u]++;
//    }
//}
//
////int findMinSpanTree(VV_t &edges, int n){
void findMinSpanTree(int n){
//    std::sort(edges.begin(), edges.end(), cmp);
//    VINT_t parent(n);
//    VINT_t rank(n);
//
    makeSet(n);
//
//    int minWeight = 0;
//
//    for (int i=0; i<edges.size(); i++){
//        int u = findParent(parent, edges[i][0]);
//        int v = findParent(parent, edges[i][1]);
//
//        int weight = edges[i][2];
//
//        if (u != v){
//            minWeight += weight;
//            unionSet(u, v, parent, rank);
//        }
//    }
//    return minWeight;
}

//int findparent(int element, VINT_t ds){
//    if(element==ds[element]) return element;
//    return ds[element] = findparent(ds[element],ds);
//}
//
////function to find sum of weights of edges of the minimum spanning tree
//int spanningTree(int V,  VV_t adj[]) {
//    VINT_t ds(V);
//    for (int i = 0; i < V; i++)ds[i] = i; //initialization
//    VINT_t rank(V, 1); //height?
//    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>pq;
//
//    for (int i = 0; i < V; i++) {
//        VV_t v = adj[i];
//        for (VINT_t x: v) {
//            {
//                pq.push({x[1], {i, x[0]}});
//            }
//        }
//    }
//
//    int count = 0;
//    int sum = 0;
//    while (count < V - 1) { //edges
//        int dist = pq.top().first;
//        int el1 = pq.top().second.first;
//        int el2 = pq.top().second.second;
//        pq.pop();
//        int p1 = findparent(el1, ds);
//        int p2 = findparent(el2, ds);
//        // if no cycles
//        if (p1 != p2) {
//            if (rank[p1] < rank[p2]) {
//                ds[p1] = p2;
//            } else if (rank[p2] < rank[p1]) {
//                ds[p2] = p1;
//            } else {
//                ds[p1] = p2;
//                rank[p2]++;
//            }
//            sum += dist;
//            count++;
//        }
//
//        return sum;
//    }
//}


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
// Вначале переведём каретку в потоке в начало файла
// istream&seekg(streamoff offset, ios_base::seekdir) =>
//параметры: смещение в буфере потока, направление потока
// beg - смещение от начала буфера потока, cur - смещение от
// текущей позиции, end - от конца
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
        onlyV.resize(n, VINT_t(n));
        //IG.resize(n, VINT_t(n));

// Reading the matrix
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                in >> G[i][j];
            }
        }
// Creating an empty graph
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                onlyV[i][j] = 0;
            }
        }
// Inverting the source graph
//        for (int i=0; i<n; ++i){
//            for(int j=0; j<n; ++j){
//                IG [i][j] = G[j][i];
//            }
//        }

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "\n";

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << onlyV[i][j] << "\t";
            }
            cout << "\n";
        }

//        for (int i = 0; i < n; ++i){
//            for (int j = 0; j < n; ++j){
//                cout << IG[i][j] << "\t";
//            }
//            cout << "\n";
//        }
//
//        findStrongConComp(n);
        findMinSpanTree(n);

        in.close();
    }
    else {
        cout << "File is not found.";
    }

    // Writing to the file consist of the connected components and its number
//    if(out.is_open()) {
//        for (int i = 0; i < StrongConComp.size(); i++) {
//            for (int j = 0; j < StrongConComp[i].size(); j++) {
//                out << StrongConComp[i][j] << " ";
//            }
//            out << '\n';
//        }
//        out << "A number of connected components is " << SCC << '\n';
//        out.close();
//    }

    return 0;
}


