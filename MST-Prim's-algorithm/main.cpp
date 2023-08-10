/*Laboratory work №7
    Реализовать алгоритм Прима нахождения минимального покрывающего дерева.
    Implement the Prim algorithm for finding a minimum spanning tree.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using std::cout;
using std::cin;

//#define V 5
//#define HIGH 999999



typedef std::vector<std::vector<int>>  VV_t;
VV_t G; // graph
VV_t MST;
VV_t Edges;


typedef std::vector<bool> VBOOL_t;
VBOOL_t used; // traversed vertexes

typedef std::vector<int> VINT_t;

int main(){

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
// изменить размер вектора на n элементов типа vector<int>, каждый из которых имеет размер  n
        G.resize(n, VINT_t(n));
        MST.resize(1,VINT_t(n));
    /*int G[V][V] = {
            {0,4,0,5,2},
            {4,0,1,3,0},
            {0,1,0,8,0},
            {5,3,8,0,2},
            {2,0,0,2,0}
    };*/
    //Array that takes care of visited vertices
    //int visit_array[V];

    //Initialize all positions as false initially
    //memset(visit_array,false,sizeof(visit_array));
    used.assign (n, false);
    used[0]=true;

    cout<<"EDGE : WEIGHT\n";

    int n_edges = 0;
    while(n_edges<n-1){
        //Variable to choose minimum value according to Prim's algorithm
        int min = HIGH;

        //Initialize r and c that will display the edge in output
        int r = 0, c = 0;

        //Traversal along the row to pick every vertex
        for(int i=0; i<5;++i){
            //After picking a vertex check if it is inside the visited array
            if(used[i]){
                //Now traverse along columns
                for(int j=0;j<5;++j){
                    if(min>G[i][j]){
                        if(!used[j] && G[i][j]){
                            min = G[i][j];
                            r = i;
                            c = j;
                        }
                    }
                }
            }
        }
        cout<<" "<<r<<"-"<<c<<":"<<G[r][c];
        cout<<std::endl;
        used[c]=true;
        n_edges++;
    }
    return 0;
}




