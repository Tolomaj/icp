/*********************************************************************
 * @file box.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Box, který se dá položit do arény.
 *********************************************************************/

#include "scene_object.hpp"
#include "collision_engine/rect.hpp"
#include "../link/mediator.hpp"

#pragma once
#define PI 3.1415926535

/**
 * @class Box
 * @brief Box, který se dá položit do arény.
 */
class Box : public SceneObject{
private:
    /// Kolizní objekt boxu.
    Rect rect;
public:
    /**
     * @brief Konstruktor třídy Box.
     * @param id ID boxu.
     * @param p Pozice boxu.
     * @param h Výška boxu.
     * @param rotation Rotace boxu.
     */
    Box(int id,Point p , int h,int rotation) : SceneObject(id){
        this->position = p;
        this->rotation = rotation;
        float Arot = (0 - ((rotation/180.0) * PI)) + (PI)/4;
        float Brot = (0 - ((rotation/180.0) * PI)) - (PI)/4;
        int hs = sqrt(h*h+h*h) ;

        Point p1 = Point(p.x+sin(Arot)*(hs/2.0),p.y+cos(Arot)*(hs/2.0));
        Point p2 = Point(p.x+sin(Brot)*(hs/2.0),p.y+cos(Brot)*(hs/2.0));

        rect = Rect(p1,p2,h);
        type = BOX;
        
        Mediator::get_instance().notify_forvarded_registartion(type, id,p.x, p.y, rotation);

        #if DEBUG_DAW
        rect.print();
        #endif

    };

    /**
     * @brief Získává kolizní objekt boxu.
     * @return Kolizní objekt boxu.
     */
    Colider * get_colider() override{
        return &rect;
    };
};

