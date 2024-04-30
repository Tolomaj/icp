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



        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);

        for (auto & element : list) {
            qDebug("list entry ");
            element->update();
        }

        


/*
       

        bool collided = engine.collide(&crc2,&arena);
        bool collided3 = engine.collide(&rect4,&arena);
        bool collided2 = engine.collide(&rect4,&rect);
        //engine.collide(&rect2,&rect);

        if(collided || collided2 || collided3){
            qDebug("echo lomus");
            this->position = recover;
            rotation = (rotation + random()%50)%360;
            Mediator::get_instance().notify_states_change(1,COLIDED);
        }else{
            Mediator::get_instance().notify_states_change(1,MOVING);
            qDebug("echo presum");
        }

        //Mediator::get_instance().notify_move(1,this->position.x,this->position.y,rotation);

        //rect.colide(&rect2);


         */

        qDebug("this is tick");
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
                obj_r =  new Box(max_id,Point(x,y),Point(x+10,y+10),10); // todo 
                
                break;

        }   

        
        ColisionAdministrator::get_instance().registerOject(obj_r);
        
        Mediator::get_instance().notify_forvarded_registartion(type, max_id,x , y , rotation);
        
    }

public:

    Simulation() : QObject(){
        timer = new QTimer(this);
        timer->setInterval(20);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        
        Mediator::get_instance().subscribe_simulation_controll(this, SLOT(simulation_set(SimuControll)));
        Mediator::get_instance().subscribe_registartion(this, SLOT(reqestEntity(ObjectType ,int , int , int ,int ,int ,bool )));

    }


};
