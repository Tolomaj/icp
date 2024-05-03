#include <QDebug>
#include "b_shapes.h"
#include "collider.hpp"
#include "rect.hpp"
#include "circle.hpp"
#include "arena.hpp"
#include "../../link/simu_info.hpp"

#pragma once

class CollisionEngine{
private:

    bool collide_arena_rect(Arena * A, Rect * B){

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

    bool collide_arena_circle(Arena * A, Circle * B){

        if(B->center().x < BOT_SIZE/2 || B->center().y < BOT_SIZE/2 || B->center().x > A->getWidth() - BOT_SIZE/2 || B->center().y > A->getHeight() - BOT_SIZE/2){
            return true;
        }   
       
        return false;
    }

    bool collide_circle_circle(Circle * A, Circle * B){

        int min_distance = A->radius() + B->radius();
        Point vector = A->center() - B->center();
        int distance = sqrt(vector.x*vector.x + vector.y*vector.y);

        if(distance < min_distance){
            return true;
        }   
       
        return false;
    }


    // vrátí znaménko císla (1 , -1)
    int dir_sign(Point p){
        if(p.x == 0){
            return (p.y > 0) - (p.y < 0);
        }else{
            return (p.x > 0) - (p.x < 0);
        }        
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

    bool collide_side_of_rect(Point la,Point lb, Rect * B){
        int lx = (lb.x - la.x)*200;
        int ly = (lb.y - la.y)*200;

        #if DEBUG_DAW
        Mediator::get_instance().notify_DBG_draw_line(la.x - lx, la.y  - ly, lb.x + lx ,lb.y + ly,Qt::white);
        #endif

        Point pa = project(la,lb,B->a());
        Point pb = project(la,lb,B->b());
        Point pc = project(la,lb,B->c());
        Point pd = project(la,lb,B->d());
        if(points_colide_line(pa,pb,pc,pd,Line(la,lb))){
            #if DEBUG_DAW
            Mediator::get_instance().notify_DBG_draw_line(pa.x, pa.y, pa.x, pa.y,QColorConstants::Svg::red);
            Mediator::get_instance().notify_DBG_draw_line(pb.x, pb.y, pb.x, pb.y,QColorConstants::Svg::red);
            Mediator::get_instance().notify_DBG_draw_line(pc.x, pc.y, pc.x, pc.y,QColorConstants::Svg::red);
            Mediator::get_instance().notify_DBG_draw_line(pd.x, pd.y, pd.x, pd.y,QColorConstants::Svg::red);
            #endif
            return true;
        }else{
            #if DEBUG_DAW
            Mediator::get_instance().notify_DBG_draw_line(pa.x, pa.y, pa.x, pa.y,QColorConstants::Svg::magenta);
            Mediator::get_instance().notify_DBG_draw_line(pb.x, pb.y, pb.x, pb.y,QColorConstants::Svg::magenta);
            Mediator::get_instance().notify_DBG_draw_line(pc.x, pc.y, pc.x, pc.y,QColorConstants::Svg::magenta);
            Mediator::get_instance().notify_DBG_draw_line(pd.x, pd.y, pd.x, pd.y,QColorConstants::Svg::magenta);
            #endif
            return false;
        }
    }

    bool collide_rect_rect(Rect * A,Rect * B){
        if(collide_side_of_rect(B->b(),B->a(),A) &&
        collide_side_of_rect(B->d(),B->a(),A)    &&
        collide_side_of_rect(A->b(),A->a(),B)    &&
        collide_side_of_rect(A->d(),A->a(),B) ){
            //když není ani jedna škvíra
            return true;
        };
        return false;
    }

Point scalePointToLength(Point& vec, double newLength) {
        double currentLength = vec.vector_lenght();
        double scaleFactor = newLength / currentLength;
        return {vec.x * scaleFactor, vec.y * scaleFactor};
    }

    bool collide_rect_circle(Circle * A,Rect * B){
        std::array<Point, 4> points = {B->a(), B->b(), B->c(), B->d()};

        // sort poins by y
        std::sort(points.begin(), points.end(), [](Point a, Point b){
            return a.y < b.y;
        });

        std::array<Line, 4> lines = {Line(points[0], points[1]), Line(points[0], points[2]), Line(points[1], points[3]), Line(points[2], points[3])};

        // represents if rim of circle is past a respective line
        std::array<bool, 4> rimIsPastLine = {false, false, false, false};
        // represents if center of circle is past a respective line
        std::array<bool, 4> centerIsPastLine = {false, false, false, false};

        for (size_t i = 0; i < 4; i++){
            if (lines[i].b.x < lines[i].a.x){
                std::swap(lines[i].a, lines[i].b);
            }
            float lx = (lines[i].b.x - lines[i].a.x)*20;
            float ly = (lines[i].b.y - lines[i].a.y)*20;

            #if DEBUG_DAW
            Mediator::get_instance().notify_DBG_draw_line(lines[i].a.x - lx, lines[i].a.y  - ly, lines[i].b.x + lx ,lines[i].b.y + ly,Qt::white);
            #endif

            float fa = ly / lx;
            float fb = lines[i].a.y - fa * lines[i].a.x;

            Point per_vec(-ly, lx);
            // bottom two lines (indexes 2, 3) need to use the other perpendicular vector
            if (i > 1) per_vec = Point(ly, -lx);

            // scale the vector to be the same length as the radius
            per_vec = scalePointToLength(per_vec, A->radius());

            // calculate the point on the circle rim
            Point circleRim = A->center() + per_vec;
            
            // get the distance of the circle rim from the line
            auto rimDiff = circleRim.y - (fa * circleRim.x + fb);
            // if the distance is positive for top two lines (0, 1), or negative for bottom two lines (2, 3), the circle rim is past the line
            rimIsPastLine[i] = i < 2 ? rimDiff > 0 : rimDiff < 0;
            
            // same for the center of the circle
            auto centerDiff = A->center().y - (fa * A->center().x + fb);
            centerIsPastLine[i] = i < 2 ? centerDiff > 0 : centerDiff < 0;

            #if DEBUG_DAW
            Mediator::get_instance().notify_DBG_draw_line(A->center().x, A->center().y, circleRim.x, circleRim.y, !centerIsPastLine[i] ? rimIsPastLine[i] ? Qt::yellow : Qt::green : Qt::red);
            #endif

        }
        if(rimIsPastLine[0] && rimIsPastLine[1] && rimIsPastLine[2] && rimIsPastLine[3]){
            return true;
        } else {
            // if at least two centerIsPastLine is false, the circle is at a corner
            if(centerIsPastLine[0] + centerIsPastLine[1] + centerIsPastLine[2] + centerIsPastLine[3] < 3){
                for (size_t i = 0; i < 4; i++){
                    // if point is inside circle
                    if((A->center() - points[i]).vector_lenght() <= A->radius()){
                        return true;
                    }
                }
            }
        }
    
        return false;
    }


public:

    bool collide(Colider * A, Colider * B){
        // border colisions
        if (A->getType() == ARENA && B->getType() == RECT){
            return (collide_arena_rect((Arena*)A,(Rect*)B));
        }else if (A->getType() == RECT && B->getType() == ARENA){
            return (collide_arena_rect((Arena*)B,(Rect*)A));

        }else if (A->getType() == ARENA && B->getType() == CIRCLE){
            return (collide_arena_circle((Arena*)A,(Circle*)B));
        }else if (A->getType() == CIRCLE && B->getType() == ARENA){
            return (collide_arena_circle((Arena*)B,(Circle*)A));

        // CIRCLE TO CIRCLE
        }else if (A->getType() == CIRCLE && B->getType() == CIRCLE){
            return (collide_circle_circle((Circle*)A,(Circle*)B));

        // RECT CIRCLE
        }else if (A->getType() == CIRCLE && B->getType() == RECT){
            return (collide_rect_circle((Circle*)A,(Rect*)B));
        }else if (A->getType() == RECT && B->getType() == CIRCLE){
            return (collide_rect_circle((Circle*)B,(Rect*)A));

        // RECT RECT
        }else if (A->getType() == RECT && B->getType() == RECT){
            return (collide_rect_rect((Rect*)A,(Rect*)B));
        }

        qDebug() << "unknown colision pair!" << A->getType() << " - " << B->getType();
        return false;
    };


    CollisionEngine(/* args */){

    };
    ~CollisionEngine(){

    };
};