#include "libs.h"

#include "signed_slider.hpp"

#pragma once


class PropertyPicker :public QFrame{ 
Q_OBJECT
    SignedSlider * colision_rotation;
    SignedSlider * bot_sense;
    SignedSlider * bot_rotartion;

    bool colision_rotation_direction = false;

public: 


    int get_rotation(){
        return bot_rotartion->getValue();
    }

    int get_colide_rotation(){
        return colision_rotation->getValue();
    }  

    int get_bot_vision(){
        return bot_sense->getValue();
    }  

    bool get_rotation_direction(){
        
    }  

    void setMode(){ // rotation only / full

    }

    PropertyPicker(QWidget *parent = 0):QFrame(parent) {
        QVBoxLayout * pickerSection = new QVBoxLayout(this);
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        

        colision_rotation = new SignedSlider(this, "Rotace při nárazu:",360);
        bot_sense = new SignedSlider(this, "Dohled bota:",200);
        bot_rotartion = new SignedSlider(this, "Rotace:",360);

        QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        QLabel *labelc = new QLabel(this);
        labelc->setText("Při názaru otočit:");
        horizontalLayout_2->addWidget(labelc);
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItem(QString("DOPRVA"));
        comboBox->addItem(QString("DOLEVA"));
        horizontalLayout_2->addWidget(comboBox);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

        pickerSection->addLayout(horizontalLayout_2);
        pickerSection->addWidget((QWidget *)colision_rotation);
        pickerSection->addWidget((QWidget *)bot_sense);
        pickerSection->addWidget((QWidget *)bot_rotartion);

    }


};