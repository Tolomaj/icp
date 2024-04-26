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

#include "scene_entity.hpp"
#include "mediator.hpp"
#include "simu_info.hpp"

#pragma once

class MovableEntity : public SceneEntity {
Q_OBJECT
public slots:

    void move_entity(int id, int x, int y, int rotation){
        if(id != this->object_id && id != ALL){ return;};
        texture->setPos(x,y);
        texture->setRotation(rotation);
    }

public:

    MovableEntity(QGraphicsScene * scene,int id, int x, int y, int rotation, char * texture_img = "img/bot.png", int size = BOT_SIZE) : SceneEntity(scene ,id ,x ,y ,rotation , texture_img , size ){
        Mediator::get_instance().subscribe_move(this, SLOT(move_entity(int,int,int,int)));
    }

    ~MovableEntity(){
    }

};


