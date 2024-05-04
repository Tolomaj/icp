/*********************************************************************
 * @file simulation.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Simulation, která se stará o průběh simulace.
 *********************************************************************/

#include <QtCore/QVariant>
#include <QString>
#include <QTimer>
#include <vector>

#include "../link/simu_info.hpp"
#include "../link/mediator.hpp"
#include "bot.hpp"

#include "collision_engine/collision_engine.hpp"
#include "collision_administrator.hpp"
#include "collision_engine/collider.hpp"
#include "collision_engine/arena.hpp"
#include "data_administrator.hpp"
#include "bot.hpp"
#include "MAN_Bot.hpp"
#include "AI_bot.hpp"
#include "box.hpp"

#pragma once

using namespace std;

/**
 * @class Simulation
 * @brief Stará se o průběh simulace.
 * 
 * Udržuje seznam všech botů a zajišťuje jejich aktualizaci.
 */
class Simulation : public QObject {
Q_OBJECT

private:
    /// Časovač pro průběh simulace.
    QTimer *timer;
    /// Seznam všech botů.
    vector<Bot*> list;
    /// Správce dat.
    DataAdministrator data_administrator;
    /// Nejvyšší použité ID.
    int max_id = 0;

private slots:
    /**
     * @brief Aktualizuje všechny boty.
     */
    void tick(){
        #if DEBUG_SAY
        qDebug("this is tick");
        #endif
        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);

        for (auto & element : list) {
            element->update();
        }
        
    }

public slots:
    /**
     * @brief Nastaví průběh simulace.
     * @param command Příkaz pro simulaci.
     */
    void simulation_set(SimuControll command){
        switch (command) {
        case RUN:
            timer->start();
            break;
        case STOP:
            timer->stop();
            break;
        case STEP:
            tick();
            break;
        }
    }

    /**
     * @brief Registruje nový objekt do simulace.
     * @param type Typ objektu.
     * @param x X-ová souřadnice objektu.
     * @param y Y-ová souřadnice objektu.
     * @param rotation Rotace objektu.
     * @param colide_rotation Úhel rotace po kolizi.
     * @param sence_lenght Délka dohledu.
     * @param rotation_direction Směr rotace po kolizi.
     */
void reqestEntity(ObjectType type,int x , int y , int rotation,int colide_rotation,int sence_lenght,bool rotation_direction){
        max_id++;

        SceneObject * obj_r;
        Bot * obj;

        switch (type){
            case AI_ROBOT:
                obj = new AIBot(max_id,Point(x,y),rotation,sence_lenght,colide_rotation,rotation_direction);
                obj_r = (SceneObject *)obj;
                list.push_back(obj);
                break;
                
            case MAN_ROBOT:
                obj = new MANBot(max_id,Point(x,y),rotation,sence_lenght);
                obj_r = (SceneObject *)obj;
                list.push_back(obj);
                break;
            
            case BOX:
                obj_r = new Box(max_id,Point(x,y),BOX_SIZE,rotation);
                break;

        }   
        data_administrator.registerObject(obj_r);
        ColisionAdministrator::get_instance().registerObject(obj_r);
    }

    /**
     * @brief Odstraní objekt ze simulace.
     * @param id ID objektu.
     */
    void unregisterEntity(int id){
        
        list.erase(remove_if(begin(list), end(list), [id](SceneObject * u){
            if(id == ALL){
                return true;
            }
            return u->get_id() == id;
        }), end(list));

        data_administrator.unregisterObject(id);
        SceneObject * obj = ColisionAdministrator::get_instance().unregisterObject(id, id == ALL);
        if(obj != nullptr){
            delete obj;
        } 

        if (id == ALL){
            max_id = 0;
        }
    }



public:

    Simulation() : QObject(){
        timer = new QTimer(this);
        timer->setInterval(SIMULATION_DELAY);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        
        Mediator::get_instance().subscribe_simulation_controll(this, SLOT(simulation_set(SimuControll)));
        Mediator::get_instance().subscribe_registartion(this, SLOT(reqestEntity(ObjectType ,int , int , int ,int ,int ,bool )));
        Mediator::get_instance().subscribe_unregistration(this, SLOT(unregisterEntity(int )));
    }


};
