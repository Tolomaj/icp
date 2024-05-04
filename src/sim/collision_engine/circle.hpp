/*********************************************************************
 * @file circle.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Circle, která je typem kolizního objektu.
 *********************************************************************/

#include "b_shapes.h"
#include "collider.hpp"

#pragma once

/**
 * @class Circle
 * @brief Kolizní objekt kruhu.
 */
class Circle : public Colider{
private:
    /// Střed kruhu.
    Point p;
    /// Poloměr kruhu.
    int rad;
public:

    /**
     * @brief Získává střed kruhu.
     * @return Střed kruhu.
     */
    Point center(){
        return p;
    }

    /**
     * @brief Získává poloměr kruhu.
     * @return Poloměr kruhu.
     */
    int radius(){
        return rad;
    }

    /**
     * @brief Nastaví střed kruhu.
     * @param p Střed kruhu.
     */
    void setPosition(Point p){
        this->p = p;
    }

    /**
     * @brief Nastaví poloměr kruhu.
     * @param radius Poloměr kruhu.
     */
    void setRadius(int radius){
        this->rad = radius;
    }

    /**
     * @brief Konstruktor třídy Circle.
     * @param p Střed kruhu.
     * @param radius Poloměr kruhu.
     */
    Circle(Point p, int radius){
        this->type = CIRCLE;
        this->p = p;
        this->rad = radius;
    };

    Circle(){
    };

    /**
     * @brief Vypisuje informace o kruhu.
     */
    void print() override{
        
        Mediator::get_instance().notify_DBG_draw_line(p.x - rad,p.y,p.x + rad,p.y ,Qt::green);
        Mediator::get_instance().notify_DBG_draw_line(p.x,p.y - rad,p.x,p.y + rad,Qt::green);
    }
};