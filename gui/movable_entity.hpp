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

    MovableEntity(QGraphicsScene * scene,int id, int x, int y, int rotation, const char * texture_img = "img/bot.png",const char * select_texture_img = "img/bo-sel.png", int size = BOT_SIZE) : SceneEntity(scene ,id ,x ,y ,rotation , texture_img ,select_texture_img, size ){
        Mediator::get_instance().subscribe_move(this, SLOT(move_entity(int,int,int,int)));
    }

    ~MovableEntity(){
    }

};


