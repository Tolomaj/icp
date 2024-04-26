#include "libs.h"

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
    QGraphicsPixmapItem* deleting_cursor = nullptr;

    QGraphicsPixmapItem* momental_cursor = nullptr; // actuali used cursor

    bool cursor_hiden = true;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * e) override;

    // schovávání pick kurzoru když není ve scéně
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:

    void create_entyty(ObjectType type,int id, int x , int y , int rotation);

   
public:

    void setClickAction(PickingCursor cursor);
    
    void select(int id);

    Scene(QObject *parent = 0);



};