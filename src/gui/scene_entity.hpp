#include "libs.h"

#include "signed_texture.hpp"
#include "focus_colector.hpp"
#include "../link/mediator.hpp"


#include "resources.hpp"

#pragma once




class SceneEntity : public QObject {
Q_OBJECT
protected:
    SignedTexture* texture = nullptr;
    QPixmap selected;
    QPixmap notSelected;

    int object_id = 0;

private slots:

    void remove_entity(int id){
        if(id != object_id && id != ALL){ return;};
        delete this;
    }

    void select(int id){
        if(id == this->object_id){
            texture->setPixmap(selected);
        }else{
            texture->setPixmap(notSelected);
        }
    }

public:

    int get_id(){
        return this->object_id;
    }

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

    ~SceneEntity(){
        delete texture;
    }


};


