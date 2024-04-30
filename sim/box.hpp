#include "scene_object.hpp"
#include "collision_engine/rect.hpp"

#pragma once

class Box : public SceneObject{
private:
    Rect rect;
public:
    Box(int id,Point a , Point b, int h) : SceneObject(id){
        rect = Rect(a,b,h);
    };
    Colider * get_colider() override{
        return &rect;
    };
};

