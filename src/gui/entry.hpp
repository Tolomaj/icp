#include "libs.h"
#include "focus_colector.hpp"

#pragma once

/// @brief Entry : záznam v pravém panelu entit scény
class Entry :public QFrame{ 
Q_OBJECT

protected:
    QLabel *entry_name;
    QHBoxLayout* layout;
    int object_id = 0;
    bool selected = false;

protected slots:

    /// funkce přiřazená tlačítku na smazání entity
    void removeButton_f(){
        Mediator::get_instance().notify_unregistration(object_id);
    }

    /**
     * @brief funkce volaná když z mediátoru přijde správa o smazání
     * 
     *  funkce filtruje aby byl smazán jen odpovídající záznam
     *  @param id id mazané entity (& záznamu se stejným id)
     */
    void remove_entry(int id){
        if(id != object_id && id != ALL){ return;};// call is not for ass
        delete this;
    }

    
    void select(int id){
        if(id == object_id){
            this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            selected = true;
        }else{
            this->setFrameStyle(QFrame::Panel | QFrame::Raised);
            selected = false;
        }

    }
    
public: 

    int get_id(){
        return object_id;
    }



    Entry(QWidget *parent = 0,int object_id = 0):QFrame(parent) {
        this->object_id = object_id;
        layout = new QHBoxLayout(this);
        layout->setContentsMargins(2, 2, 2, 2);

        QPushButton * delButton = new QPushButton(parent);
        delButton->setIcon(QIcon("img/wbasket.png"));
        delButton->setFixedSize(QSize(24, 24));
        delButton->setToolTip(QString("Remove object from scene"));
        layout->addWidget(delButton);
        connect(delButton, SIGNAL(clicked()), this,SLOT(removeButton_f()));

        entry_name = new QLabel;
        entry_name->setText("Obsticle[" + QString::number(object_id) +"]");
        layout->addWidget(entry_name);

        this->setFrameStyle(QFrame::Panel | QFrame::Raised);
        this->setLineWidth(3);

        this->setFocusPolicy(Qt::ClickFocus);
        
        Mediator::get_instance().subscribe_unregistration(this, SLOT(remove_entry(int)));
        FocusColector::get_instance().subscribe(this, SLOT(select(int)));
    }

void mousePressEvent(QMouseEvent * e)  {
   FocusColector::get_instance().focus_object(this->object_id);
}

};