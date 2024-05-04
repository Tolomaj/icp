/*********************************************************************
 * @file bot.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Bot, která je základním typem bota.
 *********************************************************************/

#include "scene_object.hpp"
#include "collision_engine/rect.hpp"
#include "collision_engine/circle.hpp"
#include "collision_administrator.hpp"

#pragma once

/**
 * @class Bot
 * @brief Základní třída pro všechny typy botů.
 */
class Bot : public SceneObject{
protected:
    /// Kolizní objekt těla robota.
    Circle body;
    /// Kolizní objekt radaru robota (dohled).
    Rect radar;
    /// Vzdlenost dohledu robota.
    int view;

    /**
     * @brief Pohne s botem pokud nedojde ke kolizi.
     * @return True, pokud nedošlo ke kolizi, jinak false.
     */
    bool move_and_colide(){
        Point recover = this->position;
        this->position.x = this->position.x + cos(rotation*3.14159/180)*BOT_SPEED;
        this->position.y = this->position.y + sin(rotation*3.14159/180)*BOT_SPEED;

        body = Circle(Point(this->position.x,this->position.y),BOT_SIZE/2);
        Point R1;
        R1.x = this->position.x + cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R1.y = this->position.y + sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Point R2;
        R2.x = this->position.x - cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R2.y = this->position.y - sin((rotation+90)*3.14159/180)*BOT_SIZE/2;
        radar = Rect(R1,R2,view);

        #if DEBUG_DAW
        body.print();
        #endif
        radar.print();
        

        if(ColisionAdministrator::get_instance().collide(this)){
            this->position = recover;
            return false;
        };

        return true;
    }

public:
    /**
     * @brief Získává vzdlenost dohledu robota.
     * @return Vzdlenost dohledu robota.
     */
    int get_view(){
        return view;
    }

    /**
     * @brief Konstruktor třídy Bot.
     * @param id ID robota.
     * @param position Pozice robota.
     * @param rotation Rotace robota.
     * @param view Dohled robota.
     */
    Bot(int id, Point position, int rotation, int view) : SceneObject(id){
        
        this->view = view;
        this->rotation = rotation;
        this->position = position;

        body = Circle(Point(this->position.x,this->position.y),BOT_SIZE/2);
        Point R1;
        R1.x = this->position.x + cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R1.y = this->position.y + sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Point R2;
        R2.x = this->position.x - cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R2.y = this->position.y - sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        radar = Rect(R1,R2,view);

        #if DEBUG_DAW
        body.print();
        radar.print();
        #endif

    };

    virtual void update()  = 0;

    /**
     * @return Kolizní objekt těla robota.
     */
    Colider * get_colider() override{
        return &body;
    };

    /**
     * @return Kolizní objekt radaru robota.
     */
    Colider * get_radar(){
        return &radar;
    };
};

