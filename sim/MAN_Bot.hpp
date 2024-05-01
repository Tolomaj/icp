#include <QObject>
#include "bot.hpp"
#include "../link/mediator.hpp"


class MANBot : public Bot{
Q_OBJECT
private:
    bool rotation_direction = false;
    RoboState state = STOPED;
    
public slots:
    void controll(int id, ControllComand command){
        if(id != this->id){ return; };

        switch (command) {
        case TOGGLE_MOVE:
            if(state == MOVING){
                state = STOPED;
            }else{
                state = MOVING;
            }
            break;
        case LEFT:
            if(state == ROTATING && !rotation_direction){
                state = STOPED;
            }else{
                rotation_direction = false;
                state = ROTATING;
            }
            break;
        case RIGHT:
            if(state == ROTATING && rotation_direction){
                state = STOPED;
            }else{
                rotation_direction = true;
                state = ROTATING;
            }     
        break;
        }
        Mediator::get_instance().notify_states_change(id,state);
    }

public:
    MANBot(int id, Point position, int rotation, int view) : Bot(id,position,rotation,view){
        type = MAN_ROBOT;
        Mediator::get_instance().notify_forvarded_registartion(MAN_ROBOT ,id ,position.x ,position.y ,rotation );
        Mediator::get_instance().subscribe_bot_controll(this, SLOT(controll(int, ControllComand)));
    };
    virtual ~MANBot(){

    };

    void update() override {
        switch (state) {

        case MOVING:
            if(move_and_colide()){
                Mediator::get_instance().notify_move(id,this->position.x,this->position.y,rotation);
            }else{
                state = COLIDED;      
                Mediator::get_instance().notify_states_change(id,COLIDED);    
            }
            break;
        case ROTATING:
            rotation = (360 + rotation + (4)*(1 + (-2*(!rotation_direction))))%360;
            Mediator::get_instance().notify_move(id,this->position.x,this->position.y,rotation);
            break;
        case COLIDED:
        case STOPED:
            /* code */
            break;
        }

        //todo
    };

};

