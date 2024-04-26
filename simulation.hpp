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

#include "simu_info.hpp"
#include "sim_data.hpp"
#include "mediator.hpp"

#pragma once


class Simulation : public QObject {
Q_OBJECT

private:
    QTimer *timer;
    SimulationData *data;


private slots:
    //průbeh simulace 
    void tick(){
        qDebug("this is tick");
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
        Mediator::get_instance().notify_move(random()%10,random()%ARENA_SIZE_X,random()%ARENA_SIZE_Y,random()%250);//fixme dočasné na testování
    }

public slots:
    //reagování na signál ovládání simulace
    void simulation_set(SimuControll command){
        switch (command) {
        case RUN:
            timer->start();
            break;
        case STOP:
            timer->stop();
            break;
        case STEP:
            tick();
            break;
        }
    }


public:

    Simulation() : QObject(){
        timer = new QTimer(this);
        timer->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        data = new SimulationData();

        Mediator::get_instance().subscribe_simulation_controll(this, SLOT(simulation_set(SimuControll)));

    }


};
