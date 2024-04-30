#include "scene_object.hpp"
#include "collision_engine/rect.hpp"
#include "collision_engine/circle.hpp"
#include "collision_administrator.hpp"


#pragma once

class Bot : public SceneObject{
protected:
    Circle boady;
    Rect radar;
    Point position;
    int rotation;
    int view;

    bool move_and_colide(){
        Point recover = this->position;
        this->position.x = this->position.x + cos(rotation*3.14159/180)*10;
        this->position.y = this->position.y + sin(rotation*3.14159/180)*10;

        boady = Circle(Point(this->position.x,this->position.y),BOT_SIZE/2);
        Point R1;
        R1.x = this->position.x + cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R1.y = this->position.y + sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Point R2;
        R2.x = this->position.x - cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R2.y = this->position.y - sin((rotation+90)*3.14159/180)*BOT_SIZE/2;
        radar = Rect(R1,R2,100);

        boady.print();
        radar.print();

        if(ColisionAdministrator::get_instance().collide(id,this)){
            this->position = recover;
            return false;
        };

        Mediator::get_instance().notify_move(id,this->position.x,this->position.y,rotation);

        return true;
    }

public:

    Bot(int id, Point position, int rotation, int view) : SceneObject(id){
        this->view = view;
        this->rotation = rotation;
        this->position = position;

        boady = Circle(Point(this->position.x,this->position.y),BOT_SIZE/2);
        Point R1;
        R1.x = this->position.x + cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R1.y = this->position.y + sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Point R2;
        R2.x = this->position.x - cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R2.y = this->position.y - sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        radar = Rect(R1,R2,view);
    };

    virtual void update()  = 0;

    Colider * get_colider() override{
        return &boady;
    };

    Colider * get_radar(){
        return &radar;
    };
};

