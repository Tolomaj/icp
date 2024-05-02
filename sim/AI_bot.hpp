#include "bot.hpp"

#pragma once

class AIBot : public Bot{
private:
int colide_rotation;
bool colision_direction;
public:

    bool get_rotation_direction(){
        return colision_direction;
    }
    
    int get_collide_rotation_angle(){
        return colide_rotation;
    }
    

    AIBot(int id, Point position, int rotation, int view,int colide_rotation, bool colision_direction) : Bot(id,position,rotation,view){
        this->colide_rotation = colide_rotation;
        this->colision_direction = colision_direction;
        type = AI_ROBOT;
        Mediator::get_instance().notify_forvarded_registartion(AI_ROBOT ,id ,position.x ,position.y ,rotation );
    };
    ~AIBot(){

    };

    void update() override {
        if(!move_and_colide()){
            rotation = (360 + rotation + colide_rotation*(1 + (-2*(!colision_direction))))%360;
            Mediator::get_instance().notify_states_change(id,COLIDED);
        }else{
            Mediator::get_instance().notify_states_change(id,MOVING);
        };
        Mediator::get_instance().notify_move(id,this->position.x,this->position.y,rotation);
    };
    
};

