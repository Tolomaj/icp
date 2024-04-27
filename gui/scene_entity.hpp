#include "libs.h"

#include "signed_texture.hpp"
#include "focus_colector.hpp"

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



    SceneEntity(QGraphicsScene * scene,int id, int x, int y, int rotation = 0, const char * texture_img = "img/box.png",const char * select_texture_img = "img/box-sel.png" , int size = BOX_SIZE) : QObject(){

        this->object_id = id;

        selected = QPixmap(select_texture_img).scaled(QSize(size, size));
        notSelected = QPixmap(texture_img).scaled(QSize(size, size));

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


