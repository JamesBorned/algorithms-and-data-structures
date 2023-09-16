/*Laboratory work №15
    Решить задачу о раскраске графа. (Даны граф G и число k.
    Необходимо проверить, правда ли, что можно раскрасить вершины графа
    в k цветов так, чтобы любые две вершины, соединённые ребром,
    имели разные цвета.)
    Solve the graph coloring problem. (The graph G and the number k are given.
    It is necessary to check whether it is true
    that it is possible to color the vertices of the graph in k colors so
    that any two vertices connected by an edge have different colors.)
*/

#include <iostream>
#include <vector>
#include <fstream>

using std::cin;
using std::cout;

int numOfColors = 0;

typedef std::vector<int> VINT_t;
VINT_t Color;
VINT_t ColoredVert;

typedef std::vector<VINT_t> VV_t;
VV_t ColoredG;
VV_t G;

void Init(int n){
    Color.assign(n, -1);
}

bool isSafeToAssign(int vertex, int currColor, int n){

    for (int j = 0; j < n; j++){
        // if j is adjacent to current vertex and have the same color
        if(G[vertex][j] == 1 && Color[j] == currColor){
            return false;
        }
    }

    return true;
}

bool isGraphColor(int numOfColors, int n, int vertex){
    if(vertex == n){
        return true;
    }

    //assign color
    for(int j = 0; j < numOfColors; ++j){

        if(isSafeToAssign(vertex, j, n)){
            Color[vertex] = j;

            // backtracking
            if(isGraphColor(numOfColors, n, vertex+1)){
                return true;
            }

            Color[vertex] = -1;
        }
    }

    return false;
}

void solveGColorProblem(int numOfColors, int n){

    Init(n);

    while(!isGraphColor(numOfColors, n, 0)){
        isGraphColor(numOfColors, n, 0);
        ++numOfColors;
    }

    cout << numOfColors << "-coloring of a given graph is minimal.\n";
    //if(isGraphColor(numOfColors, n, 0)){
        cout << numOfColors << "-coloring of a given graph exists.\n";

        for (int j = 0; j < numOfColors; ++j){
            for (int vertex = 0; vertex < n; vertex++) {
                if (Color[vertex] == j){
                    ColoredVert.push_back(vertex);
                }
            }
            ColoredG.push_back(ColoredVert);
            ColoredVert.clear();
            ColoredVert.shrink_to_fit();
        }

        for (int i = 0; i < numOfColors; ++i) {
            cout << i << "-color: ";
            for (int j = 0; j < ColoredG[i].size(); ++j) {
                cout << ColoredG[i][j] << "\t";
            }
            cout << "\n";
        }
   // }
//    else{
//        cout << numOfColors << "-coloring of a given graph doesn't exist.";
//    }
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
        Color.resize(n);
//        ColoredG.resize(n, VINT_t(n));
//        ColoredVert.resize(n);

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
//        cout << "Input number of colors: ";
//
//        cin >> numOfColors;

        solveGColorProblem(numOfColors, n);

        in.close();

    }

    return 0;
}


