/*********************************************************************
 * @file AI_bot.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu AIBot, která je typem bota ovládaného umělou inteligencí.
 *********************************************************************/

#include "bot.hpp"

#pragma once

/**
 * @class AIBot
 * @brief Bot ovládaný umělou inteligencí.
 */
class AIBot : public Bot{
private:
/// Úhel rotace po kolizi.
int colide_rotation;
/// Směr rotace po kolizi (doleva, doprava).
bool colision_direction;
public:
    /**
     * @brief Získává směr rotace po kolizi.
     * @return Směr rotace po kolizi.
     */
    bool get_rotation_direction(){
        return colision_direction;
    }
    
    /**
     * @brief Získává hodnotu rotace po kolizi.
     * @return Hodnota rotace po kolizi.
     */
    int get_collide_rotation_angle(){
        return colide_rotation;
    }
    
    /**
     * @brief Konstruktor třídy AIBot.
     * @param id ID robota.
     * @param position Pozice robota.
     * @param rotation Rotace robota.
     * @param view Dohled robota.
     * @param colide_rotation Úhel rotace po kolizi.
     * @param colision_direction Směr rotace po kolizi.
     */
    AIBot(int id, Point position, int rotation, int view,int colide_rotation, bool colision_direction) : Bot(id,position,rotation,view){
        this->colide_rotation = colide_rotation;
        this->colision_direction = colision_direction;
        type = AI_ROBOT;
        Mediator::get_instance().notify_forvarded_registartion(AI_ROBOT ,id ,position.x ,position.y ,rotation );
    };
    ~AIBot(){

    };

    /**
     * @brief Aktualizuje stav robota.
     */
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

