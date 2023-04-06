#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

using std::cout;
using std::cin;
using std::vector;



struct Point {
    int x, y;
};

typedef vector<Point> pv_t;

struct Vector {
    int x, y;

    Vector(Point a, Point b){
        x=b.x-a.x;
        y=b.y-a.y;
    }
};

// модуль векторного произведения (определитель)
int cross(Vector a, Vector b){
    return a.x*b.y - b.x*a.y;
}

pv_t GetConvexHull(pv_t points) {
    // найти опорную точку, отсортировать по полярному углу по возрастанию
    for (int i = 1; i < points.size(); ++i) {
        //если y2<y1 or y2=y1, but x2<x1
        // самая нижняя точка или самая левая из самых нижних
        if (points[i].y < points[0].y || (points[i].y == points[0].y && points[i].x < points[0].x)) {
            std::swap(points[0], points[i]);
        }
    }
    for (auto& pt: points) {
        cout << pt.x << " " << pt.y << '\n';
    }
    sort(points.begin() + 1,
              points.end(),
            //лямбда-функция comparator
              [&points](Point a, Point b) -> bool {
        //if(sqrt(pow(a.x-points[0].x,2) + pow(a.y-points[0].y,2))
                  return cross( // положительный поворот
                          Vector(points[0], a),
                          Vector(points[0], b)
                  ) > 0
                  || (cross( // положительный поворот
                          Vector(points[0], a),
                          Vector(points[0], b)
                 ) == 0 && (sqrt(pow(a.x-points[0].x,2) + pow(a.y-points[0].y,2))<sqrt(pow(b.x-points[0].x,2) + pow(b.y-points[0].y,2))));
        }
    );

    for (auto& pt: points) {
        cout << pt.x << " " << pt.y << '\n';
    }
    // добавление в стек
    pv_t ch = {points[0], points[1]};


    for (int i = 2; i < points.size(); ++i) {
        while ((ch.size() >= 2 && cross(Vector(ch[ch.size() - 2], ch[ch.size() - 1]),
                                       Vector(ch[ch.size() - 1], points[i])) <= 0)){
            ch.pop_back();
        }
        ch.push_back(points[i]);
        //cout<<ch.size();
    }

    return ch;

}


int main() {
    int n;
    cin >> n; // amount of points
    pv_t points(n);
    // заполнение вектора точек
    for (auto &pt: points) {
        cin >> pt.x >> pt.y;
    }

    pv_t ch = GetConvexHull(points);

   // cout << ch.size() << '\n';

    for (auto pt: ch) {
        cout << pt.x << " " << pt.y << '\n';
    }

    return 0;
}
