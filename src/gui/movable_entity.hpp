/*********************************************************************
 * @file movable_entity.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt jakékoli pohyblivé entity scény.
 *
*********************************************************************/

#include "libs.h"

#include "scene_entity.hpp"

#pragma once

///MovableEntity : objekt jakékoli pohyblivé entity scény.
class MovableEntity : public SceneEntity {
Q_OBJECT
public slots:

    /**
     * @brief posune entitu ve scéně na danou pozici a rotaci
     * 
     * @param id id entity
     * @param x pozice X
     * @param y pozice Y
     * @param rotation rotace
     */
    void move_entity(int id, int x, int y, int rotation){
        if(id != this->object_id && id != ALL){ return;};
        texture->setPos(x,y);
        texture->setRotation(rotation);
    }

public:

    /**
     * @brief vytvoří entitu ve scéně
     * 
     * @param scene scéna ve které entitu vytvořit
     * @param id id entity
     * @param x pozice X ve scéně
     * @param y pozice Y ve scéně
     * @param rotation rotace ve scéně
     * @param type typ entity podle kterého se rozhodne o tom jak entita vypadá
     */
    MovableEntity(QGraphicsScene * scene,int id, int x, int y, int rotation, ObjectType type) : SceneEntity(scene ,id ,x ,y ,rotation , type ){
        Mediator::get_instance().subscribe_move(this, SLOT(move_entity(int,int,int,int)));
    }


};


