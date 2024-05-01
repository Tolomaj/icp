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
#include "bot.hpp"
#include "MAN_Bot.hpp"
#include "AI_bot.hpp"
#include "box.hpp"

#pragma once

using namespace std;

class Simulation : public QObject {
Q_OBJECT

private:
    QTimer *timer;
    vector<Bot*> list;
    
    int max_id = 0;//fixme dočasné na testování
    int index = 0;
    Point position = Point(100,100);
    int rotation = rand();


private slots:
    //průbeh simulace 
    void tick(){
        qDebug("this is tick");
        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);

        for (auto & element : list) {
            element->update();
        }
        
    }

public slots:
    //reagování na signál ovládání simulace
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

void reqestEntity(ObjectType type,int x , int y , int rotation,int colide_rotation,int sence_lenght,bool rotation_direction){
        //todo // tady bude registrace objektu do dat simulace
        max_id++; //fixme dočasné na testování
        //todo // a také vybírání volného id

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
        
        ColisionAdministrator::get_instance().registerObject(obj_r);
    }

    void unregisterEntity(int id){
        
        list.erase(remove_if(begin(list), end(list), [id](SceneObject * u){
            return u->get_id() == id;
        }), end(list));

        SceneObject * obj = ColisionAdministrator::get_instance().unregisterObject(id);
        if(obj != nullptr){
            delete obj;
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
