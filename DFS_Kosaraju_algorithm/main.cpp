/*Laboratory work №5
 Найти в заданном орграфе количество и состав сильно связных
 компонент с помощью поиска в глубину.
Find the number and composition of strongly connected
components in a given directed graph using a depth-first search.
I use Kosaraju algorithm.*/

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

// Depth-first search on a source graph
void DFS1(int v) {
    used[v] = true; // the vertex is traversed
    for (int u = 0; u < IG[v].size(); ++u) {
        // if u is not traversed and u is an adjacent to v vertex
        if (!used[u] && IG[v][u] == 1) {
            //vertexes.push_back(u);
            DFS1(u);
        }
    }
    order.push_back (v);
}
// Depth-first search on an inverted graph
void DFS2(int v) {
    used[v] = true; // the vertex is traversed
    component.push_back(v);
    for (int u = 0; u < G[v].size(); ++u) {
        // if u is not traversed and u is an adjacent to v vertex
        if (!used[u] && G[v][u] == 1) {
            //vertexes.push_back(u);
            DFS2(u);
        }
    }
//    conComp.push_back(vertexes);
//    component.clear();
}
//    void SCoC(int n, int v) {
//        used.assign (n, false);
//
//        for (int i=0; i<n; ++i){
//            if (!used[i]){
//                DFS1(i);
//            }
//        }
//}

// Depth-first search
//void DFS(int v, int m, int n, int **A) {
//    used[v] = true; // the vertex is traversed
//    for(int u = 0; u < n; ++u){
//        // if u is not traversed and u is an adjacent to v vertex
//        if(!used[u] && A[v][u] == 1){
//            //vertexes.push_back(u);
//            DFS(u, m, n, A);
//        }
//    }
//    //conComp.push_back(vertexes);
//    //vertexes.clear();
//}

//void dfs1 (int v) {
//    used[v] = true; // посещена
//    for (size_t i = 0; i < g[v].size(); ++i){ // перебор смежных вершин
//        if (!used[g[v][i]]){ // если не посещена
//            dfs1(g[v][i]);
//        }
//    }
//    order.push_back (v); // add v in order vector
//}
//// dfs на инвертированный граф
//void dfs2(int v){
//    used[v] = true;
//    component.push_back(v); // компоненты связности
//    for (size_t i = 0; i < gr[v].size(); ++i){
//        if (!used[gr[v][i]]){
//            dfs2 (gr[v][i]);
//        }
//    }
//}*/

int main() {

    setlocale(LC_ALL,  "rus");

//Создаём файловый поток и связываем его с файлом
//Create a file stream and link it to the file
    std::ifstream in("..\\adjacency_matrices\\directed\\m1.txt");
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
        //int n = count / (count_space +1); // число строк
        int m = count_space + 1; // число столбцов
        int tmp;
// изменить размер вектора на m элементов типа vector<int> , каждый из которых имеет размер  m
G.resize(m, VINT_t(m));
IG.resize(m, VINT_t(m));
//        int **A;
//        A = new int*[m];
//        for (int i = 0; i < m; ++i)
//            A[i] = new int [m];
// Reading the matrix
for (int i=0; i<m; ++i){
    for (int j=0; j<m; ++j){
        in >> G[i][j];
    }
}
for (int i=0; i<m; ++i){
    for(int j=0; j<m; ++j){
        IG [i][j] = G[j][i];
    }
}
//        for (int i = 0; i < m; ++i){
//            for (int j = 0; j < m; ++j){
//                in >> A[i][j];
//           }
//        }
//        for (int i = 0; i < m; ++i){
//            //vec.push_back(in);
//            for (int j = 0; j < m; ++j){
//                in >> A[i][j];
//            }
//        }
// Matrix output
//       for (int i = 0; i < m; ++i){
//            for (int j = 0; j < m; ++j){
//                cout << A[i][j] << "\t";
//            }
//            cout << "\n";
//        }
       for (int i = 0; i < m; ++i){
            for (int j = 0; j < m; ++j){
                cout << G[i][j] << "\t";
            }
            cout << "\n";
        }
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < m; ++j){
                cout << IG[i][j] << "\t";
            }
            cout << "\n";
        }
        //ConComp(m, n, A);
//
//       for (int i = 0; i < m; i++){
//            delete[] A[i];
//        }
//        delete[] A;
        used.assign (m, false); // инициализация
        for (int i = 0; i < m; ++i){
            if (!used[i]){ // если не посещена
                DFS1 (i);
            }
        }
        used.assign (m, false);
        for (int i = 0; i < m; ++i) {
            int v = order[m - 1 - i]; // в обратном порядке с конца вектора
            if (!used[v]) {
                DFS2(v);
                SCC++;
                StrongConComp.push_back(component);
                //вывод очередной компонент
                component.clear();
            }
        }


        in.close();
    }
    else {
        cout << "File is not found.";
    }
/*// Writing to the file consist of the connected components and its number
    if(out.is_open()){
        for (int i = 0; i < conComp.size(); i++){
            for (int j = 0; j < conComp[i].size(); j++){
                out << conComp[i][j] << " ";
            }
            out << '\n';
        }
        out << "A number of connected components is " << numOfComp << '\n';
        out.close();
    }*/
    
    /*int n;
    // запросить все рёбра и добавить в g
    for (int i = 0; i < n; ++i){
        int a, b;
        // считать очередное ребро (a, b)
        // инвертировать граф
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    used.assign (n, false); // инициализация
    for (int i = 0; i < n; ++i){
        if (!used[i]){ // если не посещена
            dfs1 (i);
        }
    }
    used.assign (n, false);
    for (int i = 0; i < n; ++i){
        int v = order[n-1-i]; // в обратном порядке с конца вектора
        if (!used[v]){
            dfs2 (v);
            k++;
            //вывод очередной компонент
            component.clear();
        }
    }*/
    // Writing to the file consist of the connected components and its number
    if(out.is_open()) {
        for (int i = 0; i < StrongConComp.size(); i++) {
            for (int j = 0; j < StrongConComp[i].size(); j++) {
                out << StrongConComp[i][j] << " ";
            }
            out << '\n';
        }
        out << "A number of connected components is " << SCC << '\n';
        out.close();
    }


        return 0;
}





/*
VV_t conComp;
V_t vertexes;


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
    }*/
