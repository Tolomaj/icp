#include <cmath>
#include <QDebug>
#include "shapes.h"

class RectColider: public Rect{
private:
    Rect rect;
    int x1,y1,x2,y2,h;


    // vrátí znaménko císla (1 , -1)
    int dir_sign(Point p){
        if(p.x == 0){
            return (p.y > 0) - (p.y < 0);
        }else{
            return (p.x > 0) - (p.x < 0);
        }        
    }

    // body v přímce spojí do jedné čáry
    Line points_to_line(Point a, Point b, Point c, Point d){ 
        Point vectorA[3];      
        vectorA[0] =  b - a ;
        vectorA[1] =  c - a;
        vectorA[2] =  d - a;

        Line l = Line(Point(0,0), Point(0,0));

        for (size_t i = 0; i < 3; i++){
            if(vectorA[i].vector_lenght() * dir_sign(vectorA[i])  > l.a.vector_lenght() * dir_sign(l.a)){
                l.a = vectorA[i];
            }
        }
        for (size_t i = 0; i < 3; i++){
             if(vectorA[i].vector_lenght() * dir_sign(vectorA[i])  < l.b.vector_lenght() * dir_sign(l.b)){
                l.b = vectorA[i];
            }
        }
        return Line(l.a + a, l.b + a);
    }

    // vrátí jestli body kolidují s linkou
    bool points_colide_line(Point a, Point b, Point c, Point d, Line l){ 
        Point vectorA[3];      
        vectorA[0] =  b - a;
        vectorA[1] =  c - a;
        vectorA[2] =  d - a;

        bool all_on_side = true;

        for (size_t i = 0; i < 3; i++){
            if(!( vectorA[i].vector_lenght() * dir_sign(vectorA[i])  > (l.a - a).vector_lenght() * dir_sign((l.a - a)) 
               && vectorA[i].vector_lenght() * dir_sign(vectorA[i])  > (l.b - a).vector_lenght() * dir_sign((l.b - a)) )){
                all_on_side = false;
                break;
            }
        }
        
        if(all_on_side && 0 > (l.a - a).vector_lenght() * dir_sign(l.a - a) && 0 > (l.b - a).vector_lenght() * dir_sign(l.b - a)){
            return false;
        }
        all_on_side = true;

        for (size_t i = 0; i < 3; i++){
            if(!( vectorA[i].vector_lenght() * dir_sign(vectorA[i])  < (l.a - a).vector_lenght() * dir_sign((l.a - a)) 
               && vectorA[i].vector_lenght() * dir_sign(vectorA[i])  < (l.b - a).vector_lenght() * dir_sign((l.b - a)) )){
                all_on_side = false;
                break;
            }
        }

        if(all_on_side && 0 < (l.a - a).vector_lenght() * dir_sign(l.a - a) && 0 < (l.b - a).vector_lenght() * dir_sign(l.b - a)){
            return false;
        }

        return true;
    }

    // vrátí pozici bodu projektnutého na přímku
    Point project(Point a, Point b, Point p){
        double lx = (b.x - a.x)*200;
        double ly = (b.y - a.y)*200;

        double vx = p.x - a.x;
        double vy = p.y - a.y;

        double ox = ( (vx*lx + vy*ly) / (lx*lx + ly*ly) ) * lx;
        double oy = ( (vx*lx + vy*ly) / (lx*lx + ly*ly) ) * ly;

        return Point((int)ox + a.x,(int)oy + a.y);
    }

    // vrátí projekci krabice na přímku definovanou 2ma body    
    Line project_box(Point a, Point b, Rect * box){
        Point pa = project(a,b,box->a());
        Point pb = project(a,b,box->b());
        Point pc = project(a,b,box->c());
        Point pd = project(a,b,box->d());

        return points_to_line(pa,pb,pc,pd);
    }

    bool same_line_intersept(){
        
    }

public:

    RectColider(int x1,int y1,int x2 ,int y2, int h) : Rect(Point(x1,y1),Point(x2,y2),h){
        //rect = Rect(Point(x1,y1),Point(x2,y2),h);
    };


    void colide(Rect * box){

        double lx = (this->b().x - this->a().x)*200;
        double ly = (this->b().y - this->a().y)*200;

        Mediator::get_instance().notify_DBG_draw_line(this->a().x - lx, this->a().y  - ly, this->b().x + lx ,this->b().y + ly,Qt::white);


        Line l = project_box(this->a(),this->b(),box);

        Point pa = project(this->a(),this->b(),box->a());
        Point pb = project(this->a(),this->b(),box->b());
        Point pc = project(this->a(),this->b(),box->c());
        Point pd = project(this->a(),this->b(),box->d());
        if(points_colide_line(pa,pb,pc,pd,Line(this->a(),this->b()))){
            Mediator::get_instance().notify_DBG_draw_line(l.a.x, l.a.y, l.b.x, l.b.y,QColorConstants::Svg::red);
        }else{
            Mediator::get_instance().notify_DBG_draw_line(l.a.x, l.a.y, l.b.x, l.b.y,QColorConstants::Svg::grey);
        }


        l = project_box(this->a(),this->d(),box);
        Mediator::get_instance().notify_DBG_draw_line(l.a.x, l.a.y, l.b.x, l.b.y,QColorConstants::Svg::grey);

        l = project_box(box->a(),box->b(),this);
        Mediator::get_instance().notify_DBG_draw_line(l.a.x, l.a.y, l.b.x, l.b.y,QColorConstants::Svg::grey);

        l = project_box(box->a(),box->d(),this);
        Mediator::get_instance().notify_DBG_draw_line(l.a.x, l.a.y, l.b.x, l.b.y,QColorConstants::Svg::grey);




        //project

    }

    ~RectColider(){

    };

};