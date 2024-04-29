#include "b_shapes.h"
#include "collider.hpp"

class Circle : public Colider{
private:
    Point p;
    int rad;
public:

    Point center(){
        return p;
    }

    int radius(){
        return rad;
    }

    void setPosition(Point p){
        this->p = p;
    }

    void setRadius(int radius){
        this->rad = radius;
    }

    Circle(Point p, int radius){
        this->type = CIRCLE;
        this->p = p;
        this->rad = radius;
    };

    Circle(){
    };

    void print(){
        
        Mediator::get_instance().notify_DBG_draw_line(p.x - rad,p.y,p.x + rad,p.y ,Qt::green);
        Mediator::get_instance().notify_DBG_draw_line(p.x,p.y - rad,p.x,p.y + rad,Qt::green);
    }
};