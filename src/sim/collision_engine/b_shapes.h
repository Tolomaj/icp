/*********************************************************************
 * @file b_shapes.h
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídy Point a Line, které se používají při různých výpočtech.
 *********************************************************************/


#include <cmath>


#ifndef COL_SHAPES_H
#define COL_SHAPES_H

/**
 * @class Point
 * @brief Bod v rovině.
 *
 * Bod v rovině, který má souřadnice x a y.
 */
class Point{
public:
    /// Souřadnice x.
    int x;
    /// Souřadnice y.
    int y;

    /**
     * @brief Konstruktor třídy Point.
     * @param x Souřadnice x.
     * @param y Souřadnice y.
     */
    Point(int x, int y){
        this->x = x;
        this->y = y; 
    };

    /**
     * @brief Bezparametrický konstruktor třídy Point.
     */
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

    /**
     * @brief Vypočítá délku vektoru.
     * @return Délka vektoru.
     */
    int vector_lenght(){
        return sqrt(x*x+y*y);
    }
};


/**
 * @class Line
 * @brief Úsečka.
 *
 * Úsečka, která je definována dvěma body.
 */
class Line{
public:
    /// Počáteční bod úsečky.
    Point a;
    /// Koncový bod úsečky.
    Point b;

    /**
     * @brief Konstruktor třídy Line.
     * @param a Počáteční bod úsečky.
     * @param b Koncový bod úsečky.
     */
    Line(Point a, Point b){
        this->a = a;
        this->b = b;
    };
};

#endif