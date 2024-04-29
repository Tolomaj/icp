#include <cmath>

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

class Rect{
private:
    Point p_a;
    Point p_b;
    float lineMultipliator;
public:
    Point a(){
        return p_a;
    }

    Point b(){
        return p_b;
    }

    Point c(){
        int fx = p_b.x-(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_b.y+(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
    }

    Point d(){
        int fx = p_a.x-(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_a.y+(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
        
    }



    Rect(Point a, Point b,int h){
        this->p_a = a;
        this->p_b = b;
        lineMultipliator = h/(sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x))); 

    };

    Rect(){
    };
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
