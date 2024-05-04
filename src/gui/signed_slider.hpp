/*********************************************************************
 * @file signed_slider.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt posouvátka které má vedle sebe jméno
 *
*********************************************************************/

#include "libs.h"

#pragma once

/// SignedSlider : objekt posouvátka které má vedle sebe jméno
class SignedSlider :public QWidget{ 
Q_OBJECT
    /// hodnota na kterou je posouvátko nastaveno
    int value = 0;

protected slots:
    /// handler když uživatel posune posouvátkem
    void onSliderValueChanged(int val){
        value = val;
    }
   
    
public: 
    /// vrací hodnotu jak je posouvátko nastaveno
    int getValue(){
        return value;
    }

    /**
     * @brief vytvoří slider se jménem vedle sebe
     * 
     * @param parent nadřazený objekt kterému se přiřadí widget
     * @param name jméno slideru
     * @param scale maximální hodnota slideru
     * @param startValue defaultní hodnota na kterou je slider nastaven
     * @param minimalValue minimální hodnota na kterou jde slider posunout
     */
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