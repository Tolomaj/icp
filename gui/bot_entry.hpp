#include "libs.h"

#include "entry.hpp"

#pragma once

//todo přidat přepínání a měnení tlařítek na základě state robota

class BOT_Entry :public Entry{ 
Q_OBJECT
    QPushButton * goButton;
    QPushButton * leftButton;
    QPushButton * rightButton;
    QIcon go;
    QIcon left;
    QIcon right;
    QIcon stop;
    public slots:
    void setState(int i ,RoboState state){
        if(i != object_id){ return; }; // reagujeme na zmenu stavu jen objektu stejného id
        
        switch (state) {
            case MOVING:
                goButton->setIcon(stop);
                rightButton->setIcon(right);
                leftButton->setIcon(left);
                break;
            case ROTATING:
                goButton->setIcon(go);
                break;
            case COLIDED:
            case STOPED:
                goButton->setIcon(go);
                rightButton->setIcon(right);
                leftButton->setIcon(left);
                break;
            default:
                break;
        } 
    }
    void goButton_f(){
        Mediator::get_instance().notify_bot_controll(object_id , TOGGLE_MOVE);
    }

    void leftButton_f(){
        leftButton->setIcon(stop);
        rightButton->setIcon(right);
        Mediator::get_instance().notify_bot_controll(object_id , LEFT);
    }

    void rightButton_f(){
        rightButton->setIcon(stop);
        leftButton->setIcon(left);
        Mediator::get_instance().notify_bot_controll(object_id , RIGHT);
    }

public: 
    BOT_Entry(QWidget *parent = 0,int object_id = 0):Entry(parent,object_id) {

        entry_name->setText("Bot[" + QString::number(object_id) +"]");

        leftButton = new QPushButton(parent);
        left = QIcon("img/rleft.png");
        leftButton->setIcon(left);
        leftButton->setFixedSize(QSize(24, 24));
        leftButton->setToolTip(QString("turn robot left"));
        layout->addWidget(leftButton);
        connect(leftButton, SIGNAL(clicked()), this,SLOT(leftButton_f()));

        goButton = new QPushButton(parent);
        go = QIcon("img/go.png");
        stop = QIcon("img/stop.png");
        goButton->setIcon(go);
        goButton->setFixedSize(QSize(24, 24));
        goButton->setToolTip(QString("go with robot"));
        layout->addWidget(goButton);
        connect(goButton, SIGNAL(clicked()), this,SLOT(goButton_f()));

        rightButton = new QPushButton(parent);
        right = QIcon("img/rright.png");
        rightButton->setIcon(right);
        rightButton->setFixedSize(QSize(24, 24));
        rightButton->setToolTip(QString("turn robot right"));
        layout->addWidget(rightButton);
        connect(rightButton, SIGNAL(clicked()), this,SLOT(rightButton_f()));

        Mediator::get_instance().subscribe_states_changes(this, SLOT(setState(int,RoboState)));
    }

};