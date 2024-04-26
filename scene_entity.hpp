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

#include "simu_info.hpp"
#include "mediator.hpp"

#pragma once


class SceneEntity : public QObject {
Q_OBJECT
protected:
    QGraphicsPixmapItem* texture = nullptr;
    int object_id = 0;

private slots:

    void remove_entity(int id){
        if(id != object_id && id != ALL){ return;};
        delete this;
    }

public:

    int get_id(){
        return this->object_id;
    }

    SceneEntity(QGraphicsScene * scene,int id, int x, int y, int rotation = 0, char * texture_img = "img/box.png", int size = BOX_SIZE) : QObject(){

        this->object_id = id;
        texture = new QGraphicsPixmapItem(QPixmap(texture_img).scaled(QSize(size, size)));
        //texture->setTransformOriginPoint(size/2, size/2);
        texture->setOffset(-size/2,-size/2);
        
        texture->setPos(x,y);
        texture->setRotation(rotation);
        scene->addItem(texture);
        Mediator::get_instance().subscribe_unregistration(this, SLOT(remove_entity(int)));
    }

    ~SceneEntity(){
        delete texture;
    }


};


