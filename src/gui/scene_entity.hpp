/*********************************************************************
 * @file scene_entity.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt entity ve scéně
 *
*********************************************************************/
#include "libs.h"

#include "signed_texture.hpp"
#include "focus_colector.hpp"
#include "../link/mediator.hpp"

#include "resources.hpp"

#pragma once

/// SceneEntity : objekt entity ve scéně
class SceneEntity : public QObject {
Q_OBJECT
protected:
    /// textura objektu použitá ve scéně
    SignedTexture* texture = nullptr;

    /// textura který se používá pro objekt když se přepne do vybrané
    QPixmap selected;
    /// textura který se používá pro objekt když se přepne do NEvybrané
    QPixmap notSelected;

    /// id objektu (stejné jako id podepsané textury)
    int object_id = 0;

private slots:

    /**
     * @brief odstraní entitu pokud se shoduje s id
     * 
     * @param id id entity která má být odstraněna
     */
    void remove_entity(int id){
        if(id != object_id && id != ALL){ return;};
        delete this;
    }


    /**
     * @brief označí entitu jako vybranou (pokud není id její tak se naopak odvybere)
     * 
     *  je napojený na FocusColector. označení je posláno všem
     *
     * @param id id entity kterou chceme označit
     */
    void select(int id){
        if(id == this->object_id){
            texture->setPixmap(selected);
        }else{
            texture->setPixmap(notSelected);
        }
    }

public:

    /// vrátí id objektu scény
    int get_id(){
        return this->object_id;
    }

    /**
     * @brief vytvoří objekt ve scéně
     * 
     * @param scene scéna do které objekt vytváříme
     * @param id id objektu ve scéně (a také jeho textury)
     * @param x pozice X ve scéně
     * @param y pozice Y ve scéně
     * @param rotation rotace objektu ve scéně
     * @param type  typ objektu, závisí na něm textura která se objektu dá
     */
    SceneEntity(QGraphicsScene * scene,int id, int x, int y, int rotation , ObjectType type) : QObject(){
        this->object_id = id;

        int size;
        switch (type){
        case BOX:
            size = BOX_SIZE;
            notSelected = SceneResources::get_instance().get_Texture(BOX_T);
            selected = SceneResources::get_instance().get_Texture(BOX_SELECTED_T);
            break;
        
        case AI_ROBOT:
            size=BOT_SIZE;
            notSelected = SceneResources::get_instance().get_Texture(AI_BOT_T);
            selected = SceneResources::get_instance().get_Texture(AI_BOT_SELECTED_T);
            break;
        
        case MAN_ROBOT:
            size=BOT_SIZE;
            notSelected = SceneResources::get_instance().get_Texture(MAN_BOT_T);
            selected = SceneResources::get_instance().get_Texture(MAN_BOT_SELECTED_T);
            break;
        }


        texture = new SignedTexture(id,notSelected);
        texture->setOffset(-size/2,-size/2);
        
        texture->setPos(x,y);
        texture->setRotation(rotation);
        scene->addItem(texture);

        

        Mediator::get_instance().subscribe_unregistration(this, SLOT(remove_entity(int)));
        FocusColector::get_instance().subscribe(this, SLOT(select(int)));
    }

    /// destruktor
    ~SceneEntity(){
        delete texture;
    }


};


