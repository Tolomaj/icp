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
#include <QTimer>

#include "mediator.hpp"

#pragma once


class SimulationData : public QObject {
Q_OBJECT

//todo zde bude pole objektů pro simulaci

int max_id = 0;//fixme dočasné na testování

private slots:
    // prozba o regstraci entity. je zadán typ a pozice kam je objekt požadován
    // aby se ovšem objekt zaregistroval je nuté aby byl poslán forvarded_registration signal
    void reqestEntity(ObjectType entity_type,int x, int y , int rotation){
        //todo // tady bude registrace objektu do dat simulace
        max_id++; //fixme dočasné na testování
        //todo // a také vybírání volného id
        Mediator::get_instance().notify_forvarded_registartion(entity_type, max_id,x , y , rotation);
    }


public:

    SimulationData() : QObject(){
       
        Mediator::get_instance().subscribe_registartion(this, SLOT(reqestEntity(ObjectType ,int , int , int )));
    }


};
