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
int numberOfEdges = 0;
int numberOfLoops = 0;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // directed graph
VV_t onlyV; // only vertexes without edges
VV_t Edges;
VV_t IG; // inverted directed graph
VV_t StrongConComp; // strongly connected components

typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;
VINT_t order; // время выхода вершин
VINT_t component;
VINT_t Parent;
VINT_t Rank;

//typedef std::vector
using std::cout;
using std::cin;
using std::sort;
using std::all_of;

bool cmp(VINT_t &a, VINT_t &b){
    return a[2] < b[2];
}
//
void makeSet(int n){
    for (int i=0; i<n; i++){
        Parent[i] = i;
        Rank[i] = 0;
    }
}

VV_t convertAdjMatrixToListOfEdges (int n, VV_t &edges) {
    //int i = 0;
    //while (1) {
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
                cout << edges.size() << "1:  ";
                // выделяем память для подвектора
                edges.resize(edges.size() + countOfSubvectors - 1, VINT_t (edges[i].size())); // - 1 - т.к. учитывается память, выделенная под тот, длинный вектор
                edges[edges.size() - countOfSubvectors + 1].resize(3);
                cout << edges.size() << "2: ";
                edges.resize(edges.size(), VINT_t (edges[i].size()));
                // копируем элементы из входного диапазона в подвектор
                std::copy(start_itr, end_itr, edges[edges.size() - countOfSubvectors + 1].begin());
//
//
//
            }
         }
   }
    return edges;
}


//                int first = i;
//                int last = j;
//                int weight = G[i][j];
//                edges[i][0] = first;
//                edges[i][1] = last;
//                edges[i][2] = weight;
//                cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << "\t";
//                cout << "\n";




//        ++i;
//        if (i < n)
//            continue;
//        else
//            break;


//    for (int k = 0; k < 30; ++k) {
//        for (int j = 0; j < 3; ++j){
//            cout << Edges[k][j] << "\t";
//        }
//        cout << "\n";
//    }
//}

    //for (int i=0; i < n; ++i){
        //for (int j=n-1; j > i; --j){



//    for (int i = 0; i < 30; ++i){
//        for (int j = 0; j < 3; ++j){
//            cout << Edges[i][j] << "\t";
//        }
//        cout << "\n";
//    }


//}
//
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
int findMinSpanTree(int n) {
//    std::sort(edges.begin(), edges.end(), cmp);
//    VINT_t parent(n);
//    VINT_t rank(n);
//
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
        //Edges.resize(n*n, VINT_t(3));
        //IG.resize(n, VINT_t(n));

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

        cout << "\n";

        for (int i = 0; i < Edges.size(); ++i){
            for (int j = 0; j < Edges[i].size(); ++j){
                cout << Edges[i][j] << "\t";
            }
            cout << "\n";
        }

        //makeSet(n);

        VV_t edges = convertAdjMatrixToListOfEdges (n, Edges);
        cout << "\n";
        for (int i = 0; i < edges.size(); ++i){
            for (int j = 0; j < edges[i].size(); ++j){
                cout << edges[i][j] << "\t";
            }
            cout << "\n";

        }

//        sort(edges.begin(), edges.end(), cmp);
//
//        for (int i = 0; i < edges.size(); ++i){
//            for (int j = 0; j < edges[i].size(); ++j){
//                cout << edges[i][j] << "\t";
//            }
//            cout << "\n";
//        }

//        for (int i = 0; i < n; ++i) {
//            for (int j = i; j < n; ++j) {
//                if (G[i][j] != 0) {
//                cout << Edges[i][0] << " " << Edges[i][1] << " " << Edges[i][2] << "\t";
//                cout << "\n";
//                }
//            }
//
//        }

//        for (int i = 0; i < Edges.size(); ++i){
//            for (int j = 0; i < Edges.size(); ++i)
//        }
//        int i=0;
//        while (1){
//            cout << '\n';
//            cout << Edges[i][0] << " " << Edges[i][1] << " " << Edges[i][2] << "\t";
//            cout << '\n';
//            break;
//        }

//        cout << '\n';
//        cout << Edges[0][0] << " " << Edges[0][1] << " " << Edges[0][2] << "\t";
//        cout << '\n';
//        cout << Edges[1][0] << " " << Edges[2][1] << " " << Edges[3][2] << "\t";

//        int i = 0;
//        while (1) {
//            for (int j = i; j < n; ++j) {
//
//                    cout << Edges[i][0] << " " << Edges[i][1] << " " << Edges[i][2] << "\t";
//                    cout << "\n";
//
//            }
//            ++i;
//            if (i < n)
//                continue;
//            else
//                break;
//        }

//        for (int i=0; i<Edges.size();++i){
//            cout << Edges[i][0] << " " << Edges[i][1] << " " << Edges[i][2] << "\t";
//            cout << "\n";
//        }

        //sort(Edges.begin(), Edges.end(), cmp);

//        for (int i=0; i<Edges.size();++i){
//            cout << Edges[i][0] << " " << Edges[i][1] << " " << Edges[i][2] << "\t";
//            cout << "\n";
//        }


//
//        int minWeight = 0;
////
//        for (int i=0; i<Edges.size(); i++){
//            int u = findParent(Edges[i][0]);
//            int v = findParent(Edges[i][1]);
//
//            int weight = Edges[i][2];
//
//            if (u != v){
//                minWeight += weight;
//                Union(u, v);
//            }
//        }
//        cout << minWeight;
        //convertAdjMatrixToAdjList (n);



//        for (int i = 0; i < n; ++i){
//            for (int j = 0; j < n; ++j){
//                cout << IG[i][j] << "\t";
//            }
//            cout << "\n";
//        }
//
//        findStrongConComp(n);
        //findMinSpanTree(n);

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


