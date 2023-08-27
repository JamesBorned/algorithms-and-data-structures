/*The laboratory work №2
 Найти в заданном графе количество и состав компонент связности
 с помощью поиска в ширину.
 Find the number and composition of connected components in a given
 graph using a breadth-first search (BFS).*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using std::cout;
using std::cin;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph
VV_t ConComp;

typedef std::vector<int> VINT_t;
VINT_t Parent;
VINT_t Dist;
VINT_t vecOfVertexes;

typedef std::vector<std::string> VSTR_t;
VSTR_t used; // if graph contains cycles

typedef std::queue<int> QINT_t;
QINT_t Vertexes;

const int INF = INT_MAX;

int src = 0;
int numOfComp = 0;

void Init(int n){
// Initialization of labels of each vertex by infinity
    for(int i = 0; i < n; ++i){
        used[i] = "white";
        Dist[i] = INF;
        Parent[i] = i;
    }
}

// Search of a number of connected components in graph
void findConComp(int n){

    Init(n);

    int comp = 0;
    for (int i = 0; i < n; ++i){

        if (used[i] != "black" && used[i] != "grey"){ // if v is not traversed

            Dist[i] = 0;
            Parent[i] = i;

            Vertexes.push(i);
            vecOfVertexes.push_back(i);

            while(!Vertexes.empty()){

                int u = Vertexes.front();

                for(int v = 0; v < n; ++v){

                    if(G[u][v] != 0 && used[v] == "white"){
                        used[v] = "grey";
                        Parent[v] = u;
                        Dist[v] = Dist[u] + 1;

                        Vertexes.push(v);
                        vecOfVertexes.push_back(v);
                    }
                }
                Vertexes.pop();
                used[u] = "black";
            }
            comp++;
        }
        ConComp.push_back(vecOfVertexes);
        vecOfVertexes.clear();
        vecOfVertexes.shrink_to_fit();
    }
    numOfComp = comp;
    cout << "A number of connected components is " << numOfComp << '\n';

// Delete empty vectors
    for (int i = 0; i < ConComp.size();){
        if (ConComp[i].empty()){
            ConComp.erase(ConComp.begin() + i);
        }
        else
            ++i;
    }
}

void writeResultToFile(int n, std::ofstream& out){
    if(out.is_open()){
        for (int i = 0; i < ConComp.size(); i++){
            for (int j = 0; j < ConComp[i].size(); j++){
                out << ConComp[i][j] << " ";
            }
            out << '\n';
        }
        out << "A number of connected components is " << numOfComp << '\n';
        out.close();
    }
}

int main() {

    setlocale(LC_ALL, "rus");

//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\disconnected\\m3.txt");
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

        findConComp(n);
        writeResultToFile(n, out);

        in.close();
    }

    return 0;
}
