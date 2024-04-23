#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QString>

#include "entry.hpp"

#pragma once

class AI_Entry :public Entry{ 
Q_OBJECT

QLabel * stateLabel;

protected slots:
    void setState(int i ,RoboState state){
        if(i != object_id){ return; };
        qDebug("state");
        
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
        stateLabel->setText("[STATE]");
        stateLabel->setMargin(5);
        layout->addWidget(stateLabel);
        
        Mediator::get_instance().subscribe_states_changes(this, SLOT(setState(int,RoboState)));
    }

};