/*Laboratory work №9
    Реализовать алгоритм Беллмана-Форда поиска кратчайших путей из одной вершины.
    Implement Bellman-Ford algorithm for finding the shortest paths from a single vertex.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::all_of;

typedef std::vector<int> VINT_t;
VINT_t Dist;
VINT_t Parent;

typedef std::vector<VINT_t> VV_t;
VV_t G;
VV_t Edges;

const int INF = INT_MAX;

int numberOfEdges = 0;
int numberOfLoops = 0;

int src = 0;

void Init(int n){
    for (int i=0; i < n; ++i){
        Dist[i] = INF;
    }

    Dist[src] = 0;
    Parent[src] = src;
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

void findShortPathsBellmanFord(int n, VV_t& edges){
    Init(n);

    convertAdjMatrixToListOfEdges(n, edges);

    VV_t otherEdges;

    for (int i = 0; i < edges.size(); ++i){
        for (int j = 0; j < edges[i].size(); ++j){
            cout << edges[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\n";

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < edges.size(); ++j){
           if (Dist[edges[j][0]] < INF && (Dist[edges[j][1]] > Dist[edges[j][0]] + edges[j][2])){
                //Dist[edges[j][1]] = std::min(Dist[edges[j][1]], Dist[edges[j][0]] + edges[j][2]);

                Dist[edges[j][1]] = Dist[edges[j][0]] + edges[j][2];
                Parent[edges[j][1]] = edges[j][0];
           }
           // Inverse relaxation for a list of edges of an undirected graph
            if (Dist[edges[j][1]] < INF && (Dist[edges[j][0]] > Dist[edges[j][1]] + edges[j][2])){

                Dist[edges[j][0]] = Dist[edges[j][1]] + edges[j][2];
                Parent[edges[j][0]] = edges[j][1];
            }
        }
    }

    for(int i = 0; i < n; ++i){
        cout << Parent[i] << '\n';
    }

    cout << '\n';

    for(int i = 0; i < n; ++i){
        cout << Dist[i] << '\n';
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
    std::ifstream in("..\\adjacency_matrices\\weighted\\m3.txt");
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

// Reading the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in >> G[i][j];
                if (i != j && G[i][j] != 0) {
                    ++numberOfEdges;
                } else if (i == j && G[i][j] != 0) {
                    ++numberOfLoops;
                }
            }
        }

        Edges.resize(numberOfEdges / 2 + numberOfLoops, VINT_t(3));

        cout << Edges.size() << '\n';

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "Enter the number of the vertex,\n from which you want to find the shortest paths to other vertices:\t";

        cin >> src;

        cout << '\n';

        findShortPathsBellmanFord(n, Edges);

        writeResultToFile(n, out);

        }

        return 0;
   }
