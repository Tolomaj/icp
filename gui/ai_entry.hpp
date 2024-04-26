#include "libs.h"

#include "entry.hpp"

#pragma once

class AI_Entry :public Entry{ 
Q_OBJECT

QLabel * stateLabel;

protected slots:
    void setState(int i ,RoboState state){
        if(i != object_id){ return; }; // reagujeme na zmenu stavu jen objektu stejného id
        
        switch (state) {
            case STOPED:
                stateLabel->setText("[STOPED]");
                break;
            case MOVING:
                stateLabel->setText("[MOVING]");
                break;
            case ROTATING:
                stateLabel->setText("[ROTATING]");
                break;
            case COLIDED:
                stateLabel->setText("[COLIDED]");
                break;
            default:
                break;
        } 
    }

public: 
    AI_Entry(QWidget *parent = 0,int object_id = 0):Entry(parent,object_id) {

        entry_name->setText("AI Bot[" + QString::number(object_id) +"]");

        layout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed));

        stateLabel = new QLabel;
        stateLabel->setText("[UNKNOWN]");
        stateLabel->setMargin(5);
        layout->addWidget(stateLabel);
        
        Mediator::get_instance().subscribe_states_changes(this, SLOT(setState(int,RoboState)));
    }

};