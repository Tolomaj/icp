/*
/   Objekt který když je stvořený naslouchá všemu co se odehrává mezi gui a simualcí
*/

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

#include "mediator.hpp"

#pragma once

class Test_Probe : public QObject {
Q_OBJECT

public slots:
    void tstFiles(FileOP operation, QString str){
        if(operation == SAVE){
            qDebug(QString("EVENT_PROBE saving to file: " + str).toStdString().c_str());
        }else{
             qDebug(QString("EVENT_PROBE loading file: " + str).toStdString().c_str());           
        }
        
    }

    void tstSimControll(SimuControll command){
        switch (command) {
        case RUN:
            qDebug("EVENT_PROBE comand RUN recorded");
            break;
        case STEP:
            qDebug("EVENT_PROBE comand STEP recorded");
            break;
        case STOP:
            qDebug("EVENT_PROBE comand STOP recorded");
            break;
        default:
            break;
        } 
    }

    void tstRemove(int id){
        qDebug((QString("EVENT_PROBE deleting object id: ") + QString::number(id)).toStdString().c_str());
    }

    void tstMove(int id,int x , int y , int r){
        qDebug((QString("EVENT_PROBE moving object id: ") + QString::number(id) + QString(" to ") + QString::number(x) + QString(",") + QString::number(y) + QString(",°")+ QString::number(r)).toStdString().c_str());
    }
    

    void tstState(int id,RoboState state){
        switch (state) {
            case STOPED:
                qDebug((QString("EVENT_PROBE state STOPED recorded for ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case MOVING:
                qDebug((QString("EVENT_PROBE state MOVING recorded for ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case ROTATING:
                qDebug((QString("EVENT_PROBE state ROTATING recorded forID:") + QString::number(id)).toStdString().c_str());
                break;
            case COLIDED:
                qDebug((QString("EVENT_PROBE state COLIDED recorded forID:")+ QString::number(id)).toStdString().c_str());
                break;
            default:
                break;
        } 
    };

    void tstFWregistration(ObjectType bject,int id){
        switch (bject) {
            case AI_ROBOT:
                qDebug((QString("EVENT_PROBE adding AI_ROBOT with ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case MAN_ROBOT:
                qDebug((QString("EVENT_PROBE adding MAN_ROBOT with ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case BOX:
                qDebug((QString("EVENT_PROBE adding BOX with ID:") + QString::number(id)).toStdString().c_str());
                break;
            default:
                break;
        } 
    } 

    void tstregistration(ObjectType bject,int x , int y , int rotation,int colide_rotation,int sence_lenght,bool rotation_direction){
        QString s;
        switch (bject) {
            case AI_ROBOT:

                s = QString("EVENT_PROBE requesting AI_ROBOT °");
                s = s + QString::number(rotation);
                s = s+ QString(" - ");
                s = s + QString::number(colide_rotation);
                s = s+ QString(" - ");
                s = s + QString::number(sence_lenght);
                s = s+ QString(" - ");
                s = s + QString::number(rotation_direction);
                s = s+ QString(";");
                qDebug(s.toStdString().c_str());
                break;
            case MAN_ROBOT:
                s = QString("EVENT_PROBE requesting MAN_ROBOT °");
                s = s + QString::number(rotation);
                s = s+ QString(";");
                qDebug(s.toStdString().c_str());
                break;
            case BOX:
                qDebug((QString("EVENT_PROBE requesting BOX °") + QString::number(rotation)).toStdString().c_str());
                break;
            default:
                break;
        } 
    } 

    void tstControll(int id ,ControllComand bject){
        switch (bject) {
            case LEFT:
                qDebug((QString("EVENT_PROBE LEFT go bot ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case RIGHT:
                qDebug((QString("EVENT_PROBE RIGHT go bot ID:")+ QString::number(id)).toStdString().c_str());
                break;
            case TOGGLE_MOVE:
                qDebug((QString("EVENT_PROBE TOGGLE_MOVE go bot ID:") + QString::number(id)).toStdString().c_str());
                break;
            default:
                break;
        } 
    } 

public:

Test_Probe():QObject(){
    qDebug("instancing");


//


    Mediator::get_instance().subscribe_bot_controll(this, SLOT(tstControll(int, ControllComand)));
    Mediator::get_instance().subscribe_registartion(this, SLOT(tstregistration(ObjectType,int , int , int ,int ,int ,bool))); 
    Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(tstFWregistration(ObjectType,int))); 
    Mediator::get_instance().subscribe_states_changes(this, SLOT(tstState(int,RoboState))); 
    Mediator::get_instance().subscribe_move(this, SLOT(tstMove(int,int,int,int))); 
    Mediator::get_instance().subscribe_unregistration(this, SLOT(tstRemove(int)));
    Mediator::get_instance().subscribe_simulation_controll(this, SLOT(tstSimControll(SimuControll)));
    Mediator::get_instance().subscribe_load_save(this, SLOT(tstFiles(FileOP,QString)));
    qDebug("done trigerng");
}


};
