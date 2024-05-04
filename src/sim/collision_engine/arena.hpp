/*********************************************************************
 * @file arena.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Arena, která se používá při detekci kolize hráče s okrajem arény.
 *********************************************************************/

#include "b_shapes.h"
#include "collider.hpp"

#pragma once

/**
 * @class Arena
 * @brief Kolizní objekt arény.
 *
 * Používá se při detekci kolice hráče s okrajem arény.
 
 */
class Arena : public Colider{
private:
    /// Šířka arény.
    int width;
    /// Výška arény.
    int height;
public:
    /**
     * @brief Získává výšku arény.
     * @return Výška arény.
     */
    int getHeight(){
        return height;
    }

    /**
     * @brief Získává šířku arény.
     * @return Šířka arény.
     */
    int getWidth(){
        return width;
    }

    /**
     * @brief Konstruktor třídy Arena.
     * @param width Šířka arény.
     * @param height Výška arény.	
     */
    Arena(int width, int height){
        this->type = ARENA;
        this->width = width;
        this->height = height;
    };

    Arena(){
    };
};