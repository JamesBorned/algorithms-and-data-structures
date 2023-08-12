/*Laboratory work №7
    Реализовать алгоритм Прима нахождения минимального покрывающего дерева.
    Implement Prim's algorithm for finding a minimum spanning tree.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph
VV_t MST;

typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;

int minWeight = 0;

int findSpanTree(int n){
    //Initialize all positions as false initially
    used.resize(n);

    used.assign(n, false);

    used[0] = true;

    for (int k = 0; k < n - 1; ++k){ // E = V - 1
//Variable to choose minimum value according to Prim's algorithm
        int min = INT_MAX;

        int numOfRow = 0, numOfColumn = 0;

//Traversal along the row to pick every vertex
        for(int i = 0; i < n;++i){
            //After picking a vertex check if it is inside the visited array
            if(used[i]){
                //Traverse along columns
                for(int j = 0;j < n; ++j){
                    if(min > G[i][j]){
                        if(!used[j] && G[i][j]){
                            min = G[i][j];
                            numOfRow = i;
                            numOfColumn = j;
                        }
                    }
                }
            }
        }

        MST[numOfRow][numOfColumn] = G[numOfRow][numOfColumn];
        MST[numOfColumn][numOfRow] = G[numOfRow][numOfColumn];

        minWeight += G[numOfRow][numOfColumn];

        used[numOfColumn]=true;
    }

    return minWeight;
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
        int tmp;
// изменить размер вектора на n элементов типа vector<int>, каждый из которых имеет размер  n
        G.resize(n, VINT_t(n));
        MST.resize(n, VINT_t(n));

// Reading the matrix
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                in >> G[i][j];
            }
        }
// Creating an empty graph
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                MST[i][j] = 0;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }

        cout << "\n";

        cout << findSpanTree(n) <<'\n';

        cout << "\n";
    }

    for (int i = 0; i < MST.size(); ++i){
        for (int j = 0; j < MST.size(); ++j){
            cout << MST[i][j] << "\t";
        }
        cout << "\n";
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