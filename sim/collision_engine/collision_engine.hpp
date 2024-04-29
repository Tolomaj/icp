#include <QDebug>
#include "b_shapes.h"
#include "collider.hpp"
#include "rect.hpp"
#include "circle.hpp"
#include "arena.hpp"

class CollisionEngine{
private:

    bool colide_arena_rect(Arena * A, Rect * B){

        if(B->a().x < 0 || B->a().y < 0 || B->a().x > A->getWidth() || B->a().y > A->getHeight()){
            return true;
        }  
        if(B->b().x < 0 || B->b().y < 0 || B->b().x > A->getWidth() || B->b().y > A->getHeight()){
            return true;
        }  
        if(B->c().x < 0 || B->c().y < 0 || B->c().x > A->getWidth() || B->c().y > A->getHeight()){
            return true;
        }  
        if(B->d().x < 0 || B->d().y < 0 || B->d().x > A->getWidth() || B->d().y > A->getHeight()){
            return true;
        }  
       
        return false;
    }

    bool colide_arena_circle(Arena * A, Circle * B){

        if(B->center().x < BOT_SIZE/2 || B->center().y < BOT_SIZE/2 || B->center().x > A->getWidth() - BOT_SIZE/2 || B->center().y > A->getHeight() - BOT_SIZE/2){
            return true;
        }   
       
        return false;
    }

    bool colide_circle_circle(Circle * A, Circle * B){

        int min_distance = A->radius() + B->radius();
        Point vector = A->center() - B->center();
        int distance = sqrt(vector.x*vector.x + vector.y*vector.y);


        if(distance < min_distance){
            return true;
        }   
       
        return false;
    }


public:

    bool collide(Colider * A, Colider * B){
        // border colisions
        if (A->getType() == ARENA && B->getType() == RECT){
            return (colide_arena_rect((Arena*)A,(Rect*)B));
        }else if (A->getType() == RECT && B->getType() == ARENA){
            return (colide_arena_rect((Arena*)B,(Rect*)A));

        }else if (A->getType() == ARENA && B->getType() == CIRCLE){
            return (colide_arena_circle((Arena*)A,(Circle*)B));
        }else if (A->getType() == CIRCLE && B->getType() == ARENA){
            return (colide_arena_circle((Arena*)B,(Circle*)A));

        // CIRCLE TO CIRCLE
        }else if (A->getType() == CIRCLE && B->getType() == CIRCLE){
            return (colide_circle_circle((Circle*)A,(Circle*)B));
        }else if (A->getType() == CIRCLE && B->getType() == CIRCLE){
            return (colide_circle_circle((Circle*)B,(Circle*)A));

        // RECT CIRCLE
        }else if (A->getType() == RECT && B->getType() == CIRCLE){
            return (colide_circle_circle((Circle*)A,(Circle*)B));
        }else if (A->getType() == CIRCLE && B->getType() == RECT){
            return (colide_circle_circle((Circle*)B,(Circle*)A));

        // RECT RECT
        }else if (A->getType() == RECT && B->getType() == RECT){
            return (colide_circle_circle((Circle*)A,(Circle*)B));
        }else if (A->getType() == RECT && B->getType() == RECT){
            return (colide_circle_circle((Circle*)B,(Circle*)A));
        }

        qDebug("unknown colision pair!");
        return false;
    };


    CollisionEngine(/* args */){

    };
    ~CollisionEngine(){

    };
};