#include "libs.h"

#include "scene_entity.hpp"

#pragma once

class MovableEntity : public SceneEntity {
Q_OBJECT
public slots:

    void move_entity(int id, int x, int y, int rotation){
        if(id != this->object_id && id != ALL){ return;};
        texture->setPos(x,y);
        texture->setRotation(rotation);
    }

public:

    MovableEntity(QGraphicsScene * scene,int id, int x, int y, int rotation, ObjectType type) : SceneEntity(scene ,id ,x ,y ,rotation , type ){
        Mediator::get_instance().subscribe_move(this, SLOT(move_entity(int,int,int,int)));
    }

    ~MovableEntity(){
    }

};

