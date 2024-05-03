#include "libs.h"

#pragma once

class SignedSlider :public QWidget{ 
Q_OBJECT

    int value = 0;

protected slots:

    void onSliderValueChanged(int val){
        value = val;
    }
   
    
public: 

    int getValue(){
        return value;
    }

    SignedSlider(QWidget *parent, char * name,int scale, int startValue = 0, int minimalValue = 0):QWidget(parent) {
        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->setSpacing(0);
        QLabel *label = new QLabel(this);
        label->setText(name);
        layout->addWidget(label);
        QSlider * slider = new QSlider(Qt::Horizontal,this);
        slider->setRange(minimalValue, scale);
        value = startValue;
        slider->setValue(startValue);
        layout->addWidget(slider);
        layout->setContentsMargins(0, 0, 0, 0);
        connect(slider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged(int)));

    }

    


};