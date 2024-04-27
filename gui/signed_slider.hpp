#include "libs.h"

#pragma once

class SignedSlider :public QWidget{ 
Q_OBJECT


   
    
public: 

    int getValue(){

    }

    SignedSlider(QWidget *parent, char * name,int scale):QWidget(parent) {
        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->setSpacing(0);
        QLabel *label = new QLabel(this);
        label->setText(name);
        layout->addWidget(label);
        QSlider * slid = new QSlider(Qt::Horizontal,this);
        layout->addWidget(slid);
        layout->setContentsMargins(0, 0, 0, 0);

    }


};