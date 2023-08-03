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
VV_t G; // directed graph
VV_t onlyV; // only vertexes without edges
VV_t Edges;

typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;
VINT_t Parent;
VINT_t Rank;

using std::cout;
using std::cin;
using std::sort;
using std::all_of;

bool cmp(VINT_t &a, VINT_t &b){
    return a[2] < b[2];
}

void makeSet(int n){
    for (int i=0; i<n; i++){
        Parent.push_back(i);
        Rank.push_back(0);
    }
}

VV_t convertAdjMatrixToListOfEdges (int n, VV_t &edges) {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = i; j < n; ++j) {
            if (G[i][j] != 0) {
                edges[i].push_back(i);
                edges[i].push_back(j);
                edges[i].push_back(G[i][j]);
            }
        }
     }
    for (int i = 0; i < edges.size(); ++i) {
        if (all_of(edges[i].begin(), edges[i].end(),  [](int k) { return k==0; } ) == 1){
            edges[i].clear();
            edges[i].shrink_to_fit();
        }
        else if (edges[i].size() != 3 && all_of(edges[i].begin(), edges[i].end(),  [](int k) { return k==0; } ) == 0){
                unsigned long long countOfSubvectors = edges[i].size() / 3;
               // cout <<  countOfSubvectors;
            // каждая итерация этого цикла обрабатывает следующий набор n элементов
            // и сохраняет его в векторе по j-ому индексу в
            for  (int j = 0; j < countOfSubvectors; ++j){
                // получаем диапазон для следующего набора n элементов
                auto start_itr = std::next(edges[i].cbegin(), j*3);
                auto end_itr = std::next(edges[i].cbegin(), j*3 + 3);
                //cout << "1: " << edges.size() << " ";
                // выделяем память для подвектора
                edges.resize(edges.size() + countOfSubvectors - 1, VINT_t (edges[i].size())); // - 1 - т.к. учитывается память, выделенная под тот, длинный вектор
                edges[edges.size() - countOfSubvectors + 1].resize(3);
                //cout << "2: " << edges.size() << " ";
                edges.resize(edges.size(), VINT_t (edges[i].size()));
                // копируем элементы из входного диапазона в подвектор
                std::copy(start_itr, end_itr, edges[edges.size() - countOfSubvectors + 1].begin());
            }
            edges[i].clear();
            edges[i].shrink_to_fit();
         }

   }
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
    return Parent[node] = findParent(Parent[node]);
}

//
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
////int findMinSpanTree(VV_t &edges, int n){
VV_t findMinSpanTree(int n, VV_t &edges) {

        makeSet(n);

        convertAdjMatrixToListOfEdges(n, Edges);

        std::sort(Edges.begin(), Edges.end(), cmp);
//
    int minWeight = 0;
//
    for (int i=0; i<Edges.size(); i++){
        int u = findParent(Edges[i][0]);
        int v = findParent(Edges[i][1]);

        int weight = Edges[i][2];

        if (u != v){
            minWeight += weight;
            Union(u, v);
        }
    }
    return minWeight;
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
                onlyV[i][j] = 0;
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
                cout << onlyV[i][j] << "\t";
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

        makeSet(n);

        VV_t edges = convertAdjMatrixToListOfEdges (n, Edges);
        cout << "\n";
        for (int i = 0; i < edges.size(); ++i){
            for (int j = 0; j < edges[i].size(); ++j){
                cout << edges[i][j] << "\t";
            }
            cout << "\n";

        }

        cout << "\n";

       sort(edges.begin(), edges.end(), cmp);

        for (int i = 0; i < edges.size(); ++i){
            for (int j = 0; j < edges[i].size(); ++j){
                cout << edges[i][j] << "\t";
            }
            cout << "\n";
        }

        for (int i=0; i<edges.size(); i++){
            int u = findParent(edges[i][0]);
            int v = findParent(edges[i][1]);

            int weight = edges[i][2];

            if (u != v){
                onlyV[edges[i][0]][edges[i][1]] = weight;
                onlyV[edges[i][1]][edges[i][0]] = weight;
                minWeight += weight;
                Union(u, v);
            }
        }
        cout << minWeight;

        cout << "\n";

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << onlyV[i][j] << "\t";
            }
            cout << "\n";
        }

        //findMinSpanTree(n);

        in.close();
    }
    else {
        cout << "File is not found.";
    }

    // Writing to the file consist of the connected components and its number
    if(out.is_open()) {
        for (int i = 0; i < onlyV.size(); i++) {
            for (int j = 0; j < onlyV[i].size(); j++) {
                out << onlyV[i][j] << " ";
            }
            out << '\n';
        }
        out.close();
    }

    return 0;
}