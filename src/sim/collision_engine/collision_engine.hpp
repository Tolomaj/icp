/*********************************************************************
 * @file collision_engine.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu CollisionEngine, která řeší detekci kolicí veškerých kombinací kolizních objektů.
 *********************************************************************/

#include <QDebug>
#include "b_shapes.h"
#include "collider.hpp"
#include "rect.hpp"
#include "circle.hpp"
#include "arena.hpp"
#include "../../link/simu_info.hpp"

#pragma once

/**
 * @class CollisionEngine
 * @brief Třída řešící detekci kolizí veškerých kombinací kolizních objektů.
 *
 */
class CollisionEngine{
private:
    /**
     * @brief Detekuje kolizi mezi obdélníkem a arénou.
     * @param A Aréna.
     * @param B Obdélník.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_arena_rect(Arena * A, Rect * B){

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

    /**
     * @brief Detekuje kolizi mezi kruhem a arénou.
     * @param A Aréna.
     * @param B Kruh.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_arena_circle(Arena * A, Circle * B){

        if(B->center().x < BOT_SIZE/2 || B->center().y < BOT_SIZE/2 || B->center().x > A->getWidth() - BOT_SIZE/2 || B->center().y > A->getHeight() - BOT_SIZE/2){
            return true;
        }   
       
        return false;
    }

    /**
     * @brief Detekuje kolizi mezi dvěma kruhy.
     * @param A První kruh.
     * @param B Druhý kruh.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_circle_circle(Circle * A, Circle * B){

        int min_distance = A->radius() + B->radius();
        Point vector = A->center() - B->center();
        int distance = sqrt(vector.x*vector.x + vector.y*vector.y);

        if(distance < min_distance){
            return true;
        }   
       
        return false;
    }

    /**
     * @brief Počítá znaménko vektoru.
     * @param p Vektor.
     * @return Znaménko vektoru (1 , -1).
     */
    static int dir_sign(Point p){
        if(p.x == 0){
            return (p.y > 0) - (p.y < 0);
        }else{
            return (p.x > 0) - (p.x < 0);
        }        
    }

    /**
     * @brief Počítá projekci bodu na přímku.
     * @param a Počáteční bod přímky.
     * @param b Koncový bod přímky.
     * @param p Bod, který se má projektnout.
     * @return Pozice bodu projektnutého na přímku.
     */
    static Point project(Point a, Point b, Point p){
        double lx = (b.x - a.x)*200;
        double ly = (b.y - a.y)*200;

        double vx = p.x - a.x;
        double vy = p.y - a.y;

        double ox = ( (vx*lx + vy*ly) / (lx*lx + ly*ly) ) * lx;
        double oy = ( (vx*lx + vy*ly) / (lx*lx + ly*ly) ) * ly;

        return Point((int)ox + a.x,(int)oy + a.y);
    }

    /**
     * @brief Jistí, jestli body kolidují s přímkou.
     * @param a První bod.
     * @param b Druhý bod.
     * @param c Třetí bod.
     * @param d Čtvrtý bod.
     * @param l Přímka.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool points_colide_line(Point a, Point b, Point c, Point d, Line l){ 
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

    /**
     * @brief Detekuje kolizi mezi přímkou a obdélníkem. Používá se pro detekci kolize mezi dvěma obdélníky.
     * @param la Počáteční bod přímky.
     * @param lb Koncový bod přímky.
     * @param B Obdélník.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_side_of_rect(Point la,Point lb, Rect * B){
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

    /**
     * @brief Detekuje kolizi mezi dvěma obdélníky.
     * @param A První obdélník.
     * @param B Druhý obdélník.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_rect_rect(Rect * A,Rect * B){
        if(collide_side_of_rect(B->b(),B->a(),A) &&
        collide_side_of_rect(B->d(),B->a(),A)    &&
        collide_side_of_rect(A->b(),A->a(),B)    &&
        collide_side_of_rect(A->d(),A->a(),B) ){
            //když není ani jedna škvíra
            return true;
        };
        return false;
    }

    /**
     * @brief Změní délku vektoru.
     * @param vec Vektor.
     * @param newLength Nová délka.
     * @return Vektor s novou délkou.
     */
    static Point scalePointToLength(Point& vec, double newLength) {
        double currentLength = vec.vector_lenght();
        double scaleFactor = newLength / currentLength;
        return {vec.x * scaleFactor, vec.y * scaleFactor};
    }

    /**
     * @brief Detekuje kolizi mezi kruhem a obdélníkem.
     * @param A Kruh.
     * @param B Obdélník.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool collide_rect_circle(Circle * A,Rect * B){
        std::array<Point, 4> points = {B->a(), B->b(), B->c(), B->d()};

        // Seřadí body podle y-ové souřadnice.
        std::sort(points.begin(), points.end(), [](Point a, Point b){
            return a.y < b.y;
        });

        std::array<Line, 4> lines = {Line(points[0], points[1]), Line(points[0], points[2]), Line(points[1], points[3]), Line(points[2], points[3])};

        // Určuje, zda je okraj kruhu za přímkou.
        std::array<bool, 4> rimIsPastLine = {false, false, false, false};
        // Určuje, zda je střed kruhu za přímkou.
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
            // Spodní dvě přímky (indexy 2, 3) potřebují použít opačný kolmý vektor.
            if (i > 1) per_vec = Point(ly, -lx);

            // Změní délku vektoru na poloměr kruhu.
            per_vec = scalePointToLength(per_vec, A->radius());

            // Spočítá bod na okraji kruhu.
            Point circleRim = A->center() + per_vec;
            
            // Vzdálenost okraje kruhu od přímky.
            auto rimDiff = circleRim.y - (fa * circleRim.x + fb);
            // Pokud je vzdálenost kladná pro horní dvě přímky (0, 1) nebo záporná pro dolní dvě přímky (2, 3), okraj kruhu je za přímkou.
            rimIsPastLine[i] = i < 2 ? rimDiff > 0 : rimDiff < 0;
            
            // To stejné pro střed kruhu.
            auto centerDiff = A->center().y - (fa * A->center().x + fb);
            centerIsPastLine[i] = i < 2 ? centerDiff > 0 : centerDiff < 0;

            #if DEBUG_DAW
            Mediator::get_instance().notify_DBG_draw_line(A->center().x, A->center().y, circleRim.x, circleRim.y, !centerIsPastLine[i] ? rimIsPastLine[i] ? Qt::yellow : Qt::green : Qt::red);
            #endif

        }
        if(rimIsPastLine[0] && rimIsPastLine[1] && rimIsPastLine[2] && rimIsPastLine[3]){
            return true;
        } else {
            // Pokud je centerIsPastLine alespoň dvakrát false, kruh je v rohu.
            if(centerIsPastLine[0] + centerIsPastLine[1] + centerIsPastLine[2] + centerIsPastLine[3] < 3){
                for (size_t i = 0; i < 4; i++){
                    // Pokud je rohový bod uvnitř kruhu.
                    if((A->center() - points[i]).vector_lenght() <= A->radius()){
                        return true;
                    }
                }
            }
        }
    
        return false;
    }


public:
    /**
     * @brief Detekuje kolizi mezi dvěma kolizními objekty.
     * @param A První kolizní objekt.
     * @param B Druhý kolizní objekt.
     * @return True, pokud došlo ke kolizi, jinak false.
     */
    static bool does_collide(Colider * A, Colider * B){
        // Kolize s okrajem arény.
        if (A->getType() == ARENA && B->getType() == RECT){
            return (collide_arena_rect((Arena*)A,(Rect*)B));
        }else if (A->getType() == RECT && B->getType() == ARENA){
            return (collide_arena_rect((Arena*)B,(Rect*)A));

        }else if (A->getType() == ARENA && B->getType() == CIRCLE){
            return (collide_arena_circle((Arena*)A,(Circle*)B));
        }else if (A->getType() == CIRCLE && B->getType() == ARENA){
            return (collide_arena_circle((Arena*)B,(Circle*)A));

        // Kolize mezi dvěma kruhy.
        }else if (A->getType() == CIRCLE && B->getType() == CIRCLE){
            return (collide_circle_circle((Circle*)A,(Circle*)B));

        // Kolize mezi kruhem a obdélníkem.
        }else if (A->getType() == CIRCLE && B->getType() == RECT){
            return (collide_rect_circle((Circle*)A,(Rect*)B));
        }else if (A->getType() == RECT && B->getType() == CIRCLE){
            return (collide_rect_circle((Circle*)B,(Rect*)A));

        // Kolize mezi dvěma obdélníky.
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