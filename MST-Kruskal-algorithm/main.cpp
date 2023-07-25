/*Laboratory work №6
    Реализовать алгоритм Крускала нахождения минимального покрывающего дерева.
    Implement the Kruskal algorithm for finding a minimum spanning tree.
*/

#include <iostream>
#include <fstream>
#include <vector>

const int N = 100;
int SCC = 0; // количество сильно связных компонент связности

typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // directed graph
VV_t IG; // inverted directed graph
VV_t StrongConComp; // strongly connected components

typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;
VINT_t order; // время выхода вершин
VINT_t component;

using std::cout;
using std::cin;

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
        //IG.resize(n, VINT_t(n));

// Reading the matrix
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                in >> G[i][j];
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

//        for (int i = 0; i < n; ++i){
//            for (int j = 0; j < n; ++j){
//                cout << IG[i][j] << "\t";
//            }
//            cout << "\n";
//        }
//
//        findStrongConComp(n);

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


