/*********************************************************************
 * @file bot_entry.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief Záznam v listu který poskytuje 3 tlačítka na ovládání robota spolu s jejich měněním ikon
*********************************************************************/


#include "libs.h"

#include "entry.hpp"

#pragma once

/** @brief BOT_Entry : záznam v pravém panelu entit scény pro ovládaného robota
 *
 *  Je rozšířený záznam který obsahjue tlačítka pro ovládání robota
 *  Příkazy na ovládání robota po stisku tlačítka odesílá přez mediatora
 *
 */
class BOT_Entry :public Entry{ 
Q_OBJECT
private:
    /// odkaz na talčítko aby se dala měnit jeho ikona
    QPushButton * goButton;
    /// odkaz na talčítko aby se dala měnit jeho ikona     
    QPushButton * leftButton;   
    /// odkaz na talčítko aby se dala měnit jeho ikona
    QPushButton * rightButton;  

    /// ikona pohybu robota
    QIcon go; 
    /// ikona otáčení robota v levo     
    QIcon left; 
    /// ikona otáčení robota v pravo   
    QIcon right; 
    /// ikona zasatvení robota  
    QIcon stop;    

public slots:

    /// pokud se změní stav objektu který má stejné id zápis v seznamu na to zareaguje
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

    ///handler pro odeslání příkazu robotovy aby se rozjel/zasatvil
    void goButton_f(){
        Mediator::get_instance().notify_bot_controll(object_id , TOGGLE_MOVE);
    }

    ///handler pro odeslání příkazu robotovy aby se otočil/zasatvil
    void leftButton_f(){
        leftButton->setIcon(stop);
        rightButton->setIcon(right);
        Mediator::get_instance().notify_bot_controll(object_id , LEFT);
    }

    ///handler pro odeslání příkazu robotovy aby se otočil/zasatvil
    void rightButton_f(){
        rightButton->setIcon(stop);
        leftButton->setIcon(left);
        Mediator::get_instance().notify_bot_controll(object_id , RIGHT);
    }

public: 

    /**
     * @brief vytvoří objekt a k talčítkům přiřadí funkce
     * 
     * @param parent rodič ke kterému se přiřadí tlačítka
     * @param object_id id oběktu ke kterému entry patří
     */
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