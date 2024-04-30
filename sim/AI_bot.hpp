#include "bot.hpp"

class AIBot : public Bot{
private:
int colide_rotation;
bool colision_direction;
public:
    AIBot(int id, Point position, int rotation, int view,int colide_rotation, bool colision_direction) : Bot(id,position,rotation,view){
        this->colide_rotation = colide_rotation;
        this->colision_direction = colision_direction;
    };
    ~AIBot(){

    };

    void update() override {
        if(!move_and_colide()){
            rotation = (rotation + random()%50)%360;
            Mediator::get_instance().notify_states_change(id,COLIDED);
        }else{
            Mediator::get_instance().notify_states_change(id,MOVING);
        };
    };
    
};

