#include "../link/mediator.hpp"
#include <QObject>
#include "collision_engine/collider.hpp"

#pragma once

class SceneObject : QObject{
protected:
    int id;
    ObjectType type;
public:
    SceneObject(int id){
        this->id = id;
    }

    int get_id(){
        return id;
    }
    ObjectType get_type(){
        return type;
    }
    virtual Colider * get_colider() = 0;
};

