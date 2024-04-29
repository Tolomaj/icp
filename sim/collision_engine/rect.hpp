#include "b_shapes.h"
#include "collider.hpp"

class Rect : public Colider{
private:
    Point p_a;
    Point p_b;
    float lineMultipliator;
public:

    // vracení rohových bodů
    Point a(){
        return p_a;
    }

    Point b(){
        return p_b;
    }

    Point c(){
        int fx = p_b.x+(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_b.y-(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
    }

    Point d(){
        int fx = p_a.x+(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_a.y-(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
        
    }
    // nastaví rozměry už ecistujícímu objektu
    void set(Point a, Point b,int h){
        this->p_a = a;
        this->p_b = b;
        lineMultipliator = h/(sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x))); 
    };   

    Rect(Point a, Point b,int h){
        this->type = RECT;
        this->p_a = a;
        this->p_b = b;
        lineMultipliator = h/(sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x))); 

    };

    Rect(){
    };

    void print() override { // dbg
        Mediator::get_instance().notify_DBG_draw_line(this->a().x,this->a().y,this->b().x,this->b().y ,Qt::green);
        Mediator::get_instance().notify_DBG_draw_line(this->b().x,this->b().y,this->c().x,this->c().y ,Qt::red);
        Mediator::get_instance().notify_DBG_draw_line(this->c().x,this->c().y,this->d().x,this->d().y ,Qt::red);
        Mediator::get_instance().notify_DBG_draw_line(this->d().x,this->d().y,this->a().x,this->a().y ,Qt::red);
    }
};