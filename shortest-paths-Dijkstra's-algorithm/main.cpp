/*Laboratory work №8
    Реализовать алгоритм Дейкстры поиска кратчайших путей из одной вершины, используя
    в качестве приоритетной очереди обычный массив.
    Implement Dijkstra's algorithm for finding shortest paths from a single vertex,
    using a regular array as a priority queue.
*/

#include <iostream>

using namespace std;

#define INF 999

int V, src, cost[100][100];
int dist[100];
int parent[100];

bool used[100]  = {0};

void init(){
// инициализация меток каждой из вершин бесконечностью
    for(int i=0; i < V; ++i){
        dist[i] = INF;
        //parent[i] = i;
    }

    dist[src] = 0;
    parent[src] = src;
}

int getNearest(){
    int minvalue = INF;
    int minnode = 0;
    for(int i = 0; i < V; ++i){
        if(!used[i] && dist[i] < minvalue){
            minvalue = dist[i];
            minnode = i;
        }
    }
    return minnode;
}

void dijkstra(){
    for(int i=0; i < V; ++i){
        int nearest = getNearest();
        used[nearest] = true;

        for(int v = 0; v < V; ++v){
            if(dist[nearest] + cost[nearest][v] < dist[v] && cost[nearest][v] != 0){
                dist[v] = dist[nearest] + cost[nearest][v];
                parent[v] = nearest;
            }
        }
    }
}

void display(){
    cout<<"Node: \t\t\tCost :\t\t\tPath";

    for(int i = 0; i < V; ++i){
        cout<<i<<"\t\t\t"<< dist[i] << "\t\t\t" << " ";

        cout<<i<<" ";

        int parnode = parent[i];

        while (parnode != src){
            cout<<" <- "<< parnode << " ";
            parnode = parent[parnode];
        }
        cout<<endl;
    }

}

int main() {

    cin>>V;
    for(int i=0; i<V; ++i){
        for(int j=0; j<V; ++j){
            cin>>cost[i][j];
        }
    }
    cin>>src;
    init();
    dijkstra();
    display();



    return 0;
}

/*
 * 0 4 999 999 999 999 999 999 999
    4 0   8   999 999 999 999   8   999
  999 8 0 7 999  999 999 2
999 999 7 0 9 14 999 999 999
999 999 999 9 0 10 999 999 999
999 999 4 14 10 0 2 999 999
999 999 999 999 999 2 0 1 6
999 8 999 999 999 999 1 0 7
999 999 2 999 999 999 6 7 0*/
