/*********************************************************************
 * @file rect.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Rect, která je typem kolizního objektu.
 *********************************************************************/

#include "b_shapes.h"
#include "collider.hpp"
#include <QtCore>

#pragma once

/**
 * @class Rect
 * @brief Kolizní objekt obdélníku.
 */
class Rect : public Colider{
private:
    /// Bod a.
    Point p_a;
    /// Bod b.
    Point p_b;
    /// Pomocný parametr pro výpočet bodů c a d.
    float lineMultipliator;
public:

    /// Získává bod a.
    Point a(){
        return p_a;
    }

    /// Získává bod b.
    Point b(){
        return p_b;
    }

    /// Získává bod c.
    Point c(){
        int fx = p_b.x+(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_b.y-(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
    }

    /// Získává bod d.
    Point d(){
        int fx = p_a.x+(p_a.y-p_b.y)*lineMultipliator;
        int fy = p_a.y-(p_a.x-p_b.x)*lineMultipliator;
        return Point(fx,fy);
        
    }

    /**
     * @brief Nastaví rozměry už existujícímu objektu.
     * @param a Bod a.
     * @param b Bod b.
     * @param h Výška obdélníku.
     */
    void set(Point a, Point b,int h){
        this->p_a = a;
        this->p_b = b;
        lineMultipliator = h/(sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x))); 
    };   

    /**
     * @param a Bod a
     * @param b Bod b
     * @param h Výška
     */
    Rect(Point a, Point b,int h){
        this->type = RECT;
        this->p_a = a;
        this->p_b = b;
        lineMultipliator = h/(sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x)));

    };

    Rect(){
    };

    
    /**
     * @brief Vykresluje obdélník.
     * 
     * Tato funkce vykresluje obdélník tím, že kreslí jeho čtyři strany různými barvami.
     * 
     * @note Tato funkce slouží pro účely ladění.
     */
    void print() override { // dbg
        Mediator::get_instance().notify_DBG_draw_line(this->a().x,this->a().y,this->b().x,this->b().y ,Qt::green);
        Mediator::get_instance().notify_DBG_draw_line(this->b().x,this->b().y,this->c().x,this->c().y ,Qt::red);
        Mediator::get_instance().notify_DBG_draw_line(this->c().x,this->c().y,this->d().x,this->d().y ,Qt::red);
        Mediator::get_instance().notify_DBG_draw_line(this->d().x,this->d().y,this->a().x,this->a().y ,Qt::red);
    }
};