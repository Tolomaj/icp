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
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include "mediator.hpp"

#include "movable_entity.hpp"
#include "scene_entity.hpp"

#pragma once

enum PickingCursor{ // lehce nevhodně pojmenované 
    MAN_BOT_PICKING,
    AI_BOT_PICKING,
    BOX_PICKING,
    SELECTING,
    DELETING
};


class Scene :public QGraphicsScene{ 
Q_OBJECT

    virtual ~Scene() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

private:

    PickingCursor pickmode = SELECTING;

    QGraphicsRectItem *rectangle;
    QGraphicsPixmapItem* box_cursor = nullptr;
    QGraphicsPixmapItem* bot_cursor = nullptr;
    QGraphicsPixmapItem* ai_bot_cursor = nullptr;

    QGraphicsPixmapItem* momental_cursor = nullptr; // actuali used cursor

    bool cursor_hiden = true;

public:

    void setClickAction(PickingCursor cursor){
        pickmode = cursor;
        if(!cursor_hiden){
            this->removeItem(momental_cursor);
        }
        switch (cursor){
            case MAN_BOT_PICKING:
                momental_cursor = bot_cursor;
                break;
            case AI_BOT_PICKING:
                momental_cursor = ai_bot_cursor;
                break;
            case BOX_PICKING:
                momental_cursor = box_cursor;
                break;
            case SELECTING:
                momental_cursor = nullptr;
                break;
            case DELETING:
                momental_cursor = nullptr;
                break;
        }

        if(momental_cursor != nullptr && !cursor_hiden){
            this->addItem(momental_cursor);
        }
        
    }

public slots:

    void create_entyty(ObjectType type,int id, int x , int y , int rotation){
        switch (type){
        case BOX:
            new SceneEntity(this,id,x,y,rotation);
            break;
        
        case MAN_ROBOT:
            new MovableEntity(this,id,x,y,rotation);
            break;
    
        case AI_ROBOT:
            new MovableEntity(this,id,x,y,rotation,"img/ai_bot.png");
            break;

        }        
    }

public: 
    Scene(QObject *parent = 0):QGraphicsScene(parent) {

        this->setSceneRect(-BOT_SIZE/2, -BOT_SIZE/2, ARENA_SIZE_X + BOT_SIZE, ARENA_SIZE_Y + BOT_SIZE);
        this->setItemIndexMethod(QGraphicsScene::NoIndex);

        QBrush trBrush(Qt::transparent);
        QPen outlinePen(Qt::blue);
        outlinePen.setWidth(5);

        rectangle = this->addRect(this->sceneRect(), outlinePen, trBrush);

        box_cursor = new QGraphicsPixmapItem(QPixmap("img/box.png").scaled(QSize(BOX_SIZE, BOX_SIZE)));
        box_cursor->setOffset(-BOX_SIZE/2,-BOX_SIZE/2);

        bot_cursor  = new QGraphicsPixmapItem(QPixmap("img/bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE)));
        bot_cursor->setOffset(-BOT_SIZE/2,-BOT_SIZE/2);

        ai_bot_cursor  = new QGraphicsPixmapItem(QPixmap("img/ai_bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE)));
        ai_bot_cursor->setOffset(-BOT_SIZE/2,-BOT_SIZE/2);

        installEventFilter(this);

        Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(create_entyty(ObjectType, int, int, int , int)));
    }

private:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override{
        if(momental_cursor != nullptr){
            const QPointF p = e->scenePos();
            momental_cursor->setPos(p.x(),p.y());
        }

    }

    void mousePressEvent(QGraphicsSceneMouseEvent * e) override {
        //Mediator::get_instance().notify_registartion(BOX);
        const QPointF p = e->scenePos();

        switch (pickmode){
            case BOX_PICKING:
                Mediator::get_instance().notify_registartion(BOX, p.x(), p.y() , 0);
                break;
            case MAN_BOT_PICKING:
                Mediator::get_instance().notify_registartion(MAN_ROBOT, p.x(), p.y() , random()%360);
                break;
            case AI_BOT_PICKING:
                Mediator::get_instance().notify_registartion(AI_ROBOT, p.x(), p.y() , random()%360);
                break;
            case DELETING:
                //SceneEntity *item = itemAt(p, QTransform());
                //qDebug((QString("obj id ") + QString::number( item.get_id() )).toStdString().c_str());
                break;
            default:
                break;

        }


        qDebug((QString("click recorded ") + QString::number( p.x())  + QString(" ") +  QString::number( p.y())).toStdString().c_str());
    }

    // schovávání pick kurzoru když není ve scéně
    bool eventFilter(QObject *watched, QEvent *event) override{
        if(momental_cursor != nullptr){
            if(event->type() == QEvent::Enter){
                cursor_hiden = false;
                this->addItem(momental_cursor);
            }else if(event->type() == QEvent::Leave){
                cursor_hiden = true;
                this->removeItem(momental_cursor);
            }
        }
        return false;
    }

};