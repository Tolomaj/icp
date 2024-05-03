#include <cmath>


#ifndef COL_SHAPES_H
#define COL_SHAPES_H

class Point{
public:
    int x, y;

    Point(int x, int y){
        this->x = x;
        this->y = y; 
    };

    Point(){
        x = 0;
        y = 0;
    };

    Point operator - (Point const& opr) {
             Point temp;
              temp.x = x - opr.x;
              temp.y = y - opr.y;
              return temp;
    };


    Point operator + (Point const& opr) {
             Point temp;
              temp.x = x + opr.x;
              temp.y = y + opr.y;
              return temp;
    };

    int vector_lenght(){
        return sqrt(x*x+y*y);
    }
};


class Line{
public:
    Point a;
    Point b;

    Line(Point a, Point b){
        this->a = a;
        this->b = b;
    };
};

#endif