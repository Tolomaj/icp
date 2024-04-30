#include "b_shapes.h"
#include "collider.hpp"

#pragma once

class Arena : public Colider{
private:
    int width;
    int height;
public:

    int getHeight(){
        return height;
    }

    int getWidth(){
        return width;
    }

    Arena(int width, int height){
        this->type = ARENA;
        this->width = width;
        this->height = height;
    };

    Arena(){
    };
};