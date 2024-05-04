/*********************************************************************
 * @file property_picker.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt nastavování vkládaných entit do scény
 *
*********************************************************************/

#include "libs.h"

#include "signed_slider.hpp"

#pragma once

///PropertyPicker : objekt nastavování vkládaných entit do scény
class PropertyPicker :public QFrame{ 
Q_OBJECT
    ///slider pro vybírání rotace po nárazu vlkádaného robota
    SignedSlider * colision_rotation;
    ///slider pro vybírání dohledu robta
    SignedSlider * bot_sense;
    ///slider pro vybírání rotace vkládaného objektu
    SignedSlider * rotation;
    /// vybírač směru rotace při nárazu
    QComboBox *comboBox;

    ///polisek co se vybírá
    QLabel *labelc;

    /// proměnná vekteré se ukládá kam se robot bude otáčet po rotaci, aby se správně vykreslovala čára rotace
    bool colision_rotation_direction = true;

protected slots:

/**
 * @brief handler vybírání směru rotace nastavuje proměnnou kam se otáčí robot při nárazu
 * 
 * @param string název položky "DOPRVA" / "DOLEVA"
 */
void dropdown(QString string){
    if(string == QLatin1String("DOPRVA")){
        colision_rotation_direction = true;
    }else{
        colision_rotation_direction = false;
    }
}

public: 

    /// vrátí jak je nastavený slider rotace
    int get_rotation(){
        return rotation->getValue();
    }

    /// vrátí nastavenou hodnotu rotace po kolizi
    int get_colide_rotation(){
        return colision_rotation->getValue();
    }  

    /// vrátí nastavenou hodnotu dohledu robta
    int get_bot_vision(){
        return bot_sense->getValue();
    }  

    /// vrátí nastavený směr rotace
    bool get_rotation_direction(){
        return colision_rotation_direction;
    }  

    /**
     * @brief nastaví co vše se v pickovacím menu ukazje
     * 
     * @param full (true) ukáže celé menu
     * @param not_rotation (true) schová vše krom rotace v menu
     */
    void setFullMode(bool full, bool not_rotation = false){ // rotation only / full // or full without auto rotation
        if(full){
            if(not_rotation){
                colision_rotation->hide();
                comboBox->hide();
                labelc->hide();
            }else{
                colision_rotation->show();
                comboBox->show();
                labelc->show();
            }
            bot_sense->show();
        }else{
            colision_rotation->hide();
            comboBox->hide();
            bot_sense->hide();
            labelc->hide();
        }
    }


    /**
     * @brief vytvoření widgetu vybírání parametrů
     * 
     * @param parent widget ke kterému menu přidat
     */
    PropertyPicker(QWidget *parent = 0):QFrame(parent) {
        QVBoxLayout * pickerSection = new QVBoxLayout(this);
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        
        // vytvoření hejblátek
        colision_rotation = new SignedSlider(this, "Rotace při nárazu:",360,20);
        bot_sense = new SignedSlider(this, "Dohled bota:",200,BOT_SIZE/2 + 20,BOT_SIZE/2 + 1);
        rotation = new SignedSlider(this, "Rotace:",360);

        QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        labelc = new QLabel(this);
        labelc->setText("Při názaru otočit:");
        horizontalLayout_2->addWidget(labelc);
        comboBox = new QComboBox(this);
        comboBox->addItem(QString("DOPRVA"));
        comboBox->addItem(QString("DOLEVA"));
        horizontalLayout_2->addWidget(comboBox);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

        pickerSection->addLayout(horizontalLayout_2);
        pickerSection->addWidget((QWidget *)colision_rotation);
        pickerSection->addWidget((QWidget *)bot_sense);
        pickerSection->addWidget((QWidget *)rotation);

        connect(comboBox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(dropdown(const QString)));
    }

};