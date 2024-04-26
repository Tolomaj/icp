#include "libs.h"

#include "signed_texture.hpp"

#pragma once




class SceneEntity : public QObject {
Q_OBJECT
protected:
    SignedTexture* texture = nullptr;
    int object_id = 0;

private slots:

    void remove_entity(int id){
        if(id != object_id && id != ALL){ return;};
        delete this;
    }

public:

    int get_id(){
        return this->object_id;
    }

    SceneEntity(QGraphicsScene * scene,int id, int x, int y, int rotation = 0, char * texture_img = "img/box.png", int size = BOX_SIZE) : QObject(){

        this->object_id = id;
        texture = new SignedTexture(id,QPixmap(texture_img).scaled(QSize(size, size)));;
        texture->setOffset(-size/2,-size/2);
        
        texture->setPos(x,y);
        texture->setRotation(rotation);
        scene->addItem(texture);
        Mediator::get_instance().subscribe_unregistration(this, SLOT(remove_entity(int)));
    }

    ~SceneEntity(){
        delete texture;
    }


};


