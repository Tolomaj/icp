/*********************************************************************
 * @file  ai_entry.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief Záznam v listu který zobrazuje i stav robota 
*********************************************************************/


#include "libs.h"

#include "entry.hpp"

#pragma once

/** @brief AI_Entry : záznam v pravém panelu entit scény pro AI robota
 *
 *  Je rozšířený záznam který obsahjue status ve kterém se robot nachází
 *  Tento status je aktualiztovaný přez mediator
 *
 */
class AI_Entry :public Entry{ 
Q_OBJECT

QLabel * stateLabel;

protected slots:

    /// pokud se změní stav objektu který má stejné id zápis v seznamu na to zareaguje vypsáním stavu
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
    /**
     * @brief kontruktor pouze rozšíření základní zapis o stav ve kterém se bot nachází
     * 
     * @param parent rodič ke kterému se přiřadí tlačítka
     * @param object_id id oběktu ke kterému entry patří
     */
    AI_Entry(QWidget *parent = 0,int object_id = 0):Entry(parent,object_id) {

        entry_name->setText("AI Bot[" + QString::number(object_id) +"]");

        layout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed));

        stateLabel = new QLabel;
        stateLabel->setText("[SLEEP]");
        stateLabel->setMargin(5);
        layout->addWidget(stateLabel);
        
        Mediator::get_instance().subscribe_states_changes(this, SLOT(setState(int,RoboState)));
    }

};