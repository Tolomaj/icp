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
    Point position = Point(100,100);
    int rotation = rand();


private slots:
    //průbeh simulace 
    void tick(){

        CollisionEngine engine;

        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);

        index = (index + 20) % 200;
        

        //Rect rect2 = Rect(Point(150,230),Point(index+100,220),50);
        //rect2.print();

        //Circle crc = Circle(Point(100-index,120),BOT_SIZE/2);
        //crc.print();

        Point recover = this->position;

        this->position.x = this->position.x + cos(rotation*3.14159/180)*10;
        this->position.y = this->position.y + sin(rotation*3.14159/180)*10;



        Circle crc2 = Circle(Point(this->position.x,this->position.y),BOT_SIZE/2);
        
        Point R1;
        R1.x = this->position.x + cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R1.y = this->position.y + sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Point R2;
        R2.x = this->position.x - cos((rotation+90)*3.14159/180)*BOT_SIZE/2;
        R2.y = this->position.y - sin((rotation+90)*3.14159/180)*BOT_SIZE/2;

        Rect rect4 = Rect(R1,R2,100);
        rect4.print();
        crc2.print();

        Rect rect = Rect(Point(200,200),Point(310,160),100);
        rect.print();



        Arena arena = Arena(ARENA_SIZE_X,ARENA_SIZE_Y);

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

        Mediator::get_instance().notify_move(1,this->position.x,this->position.y,rotation);

        //rect.colide(&rect2);


         

        qDebug("this is tick");
       /* Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování*/
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
        timer->setInterval(10);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        
        Mediator::get_instance().subscribe_simulation_controll(this, SLOT(simulation_set(SimuControll)));
        Mediator::get_instance().subscribe_registartion(this, SLOT(reqestEntity(ObjectType ,int , int , int ,int ,int ,bool )));

    }


};
