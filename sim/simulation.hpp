#include <QtCore/QVariant>
#include <QString>
#include <QTimer>

#include "../link/simu_info.hpp"
#include "../link/mediator.hpp"

#include "collision_engine/collision_engine.hpp"

#pragma once


class Simulation : public QObject {
Q_OBJECT

private:
    QTimer *timer;
    
    int max_id = 0;//fixme dočasné na testování
    int index = 0;



private slots:
    //průbeh simulace 
    void tick(){

        CollisionEngine engine;

        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);

        index = (index + 20) % 200;
        

        ///Rect rect = Rect(Point(20,20),Point(110,60),100);
        //rect.print();

        //Rect rect2 = Rect(Point(250,290),Point(index-100,120),50);
        //rect2.print();

        Circle crc = Circle(Point(100-index,120),BOT_SIZE/2);
        crc.print();

        Circle crc2 = Circle(Point(index-100,120),BOT_SIZE/2);
        crc2.print();


        Arena arena = Arena(ARENA_SIZE_X,ARENA_SIZE_Y);

        bool collided = engine.collide(&crc,&crc2);

        if(collided){
            qDebug("echo lomus");
        }else{
            qDebug("echo presum");
        }

        //rect.colide(&rect2);


         

        qDebug("this is tick");
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
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
        Mediator::get_instance().notify_forvarded_registartion(type, max_id,x , y , rotation);
    }

public:

    Simulation() : QObject(){
        timer = new QTimer(this);
        timer->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        
        Mediator::get_instance().subscribe_simulation_controll(this, SLOT(simulation_set(SimuControll)));
        Mediator::get_instance().subscribe_registartion(this, SLOT(reqestEntity(ObjectType ,int , int , int ,int ,int ,bool )));

    }


};
