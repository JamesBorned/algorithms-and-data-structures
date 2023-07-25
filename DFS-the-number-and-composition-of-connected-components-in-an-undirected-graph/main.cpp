/*The laboratory work №4
 Найти в заданном графе количество и состав компонент связности
 с помощью поиска в глубину.
 Find the number and composition of connected components in a given
 graph using a depth-first search (DFS).*/

#include <iostream>
#include <vector>
#include <fstream>

const int N = 100;
int numOfComp = 0;
typedef std::vector<std::vector<int>> VV_t;
typedef std::vector<int> V_t;
VV_t conComp;
V_t vertexes;

using std::cout;
using std::cin;

bool used[N];
// Depth-first search
void DFS(int v, int m, int n, int **A) {
    used[v] = true; // the vertex is traversed
    for(int u = 0; u < n; ++u){
        // if u is not traversed and u is an adjacent to v vertex
        if(!used[u] && A[v][u] == 1){
            vertexes.push_back(u);
            DFS(u, m, n, A);
        }
    }
    conComp.push_back(vertexes);
    vertexes.clear();
}
// Search of a number of connected components in graph
void ConComp(int m,  int n, int **A){
    for (int v = 0; v < m; ++v){
        used[v] = false; // an initializing vertexes as not traversed
    }
    int comp = 0;
    for (int v = 0; v < m; ++v){
        if (!used[v]){ // if v is not traversed
            ++comp;
            vertexes.push_back(v);
            DFS(v, m, n, A);
        }
    }
    numOfComp = comp;
cout << "A number of connected components is " << comp << '\n';
}

int main() {

    setlocale(LC_ALL,  "rus");
//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\disconnected\\m3.txt");
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
        int n = count / (count_space +1); // число строк
        int m = count_space + 1; // число столбцов
        int **A;
        A = new int*[n];
        for (int i = 0; i < n; ++i)
            A[i] = new int [m];
// Reading the matrix
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; ++j){
                in >> A[i][j];
            }
        }
// Matrix output
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                cout << A[i][j] << "\t";
            }
            cout << "\n";
        }

        ConComp(m, n, A);

        for (int i = 0; i < n; i++){
            delete[] A[i];
        }
        delete[] A;

        in.close();
    }
    else {
        cout << "File is not found.";
    }
// Writing to the file consist of the connected components and its number
    if(out.is_open()){
        for (int i = 0; i < conComp.size(); i++){
            for (int j = 0; j < conComp[i].size(); j++){
                    out << conComp[i][j] << " ";
            }
            out << '\n';
        }
        out << "A number of connected components is " << numOfComp << '\n';
        out.close();
    }

    return 0;
}
