#ifndef GUI_SCENE_H
#define GUI_SCENE_H

#include "libs.h"

#include "movable_entity.hpp"
#include "scene_entity.hpp"

#include <vector> 
using namespace std; 


//možné akce při kliknutí kurzorem do scény
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
    QWidget *parent;

    PickingCursor pickmode = SELECTING; // drží hodnotu co se má provédst po kliknutí

    QGraphicsRectItem *rectangle; // hranice arény

    // obrázky kurzoru pro jednotlivé módy
    QGraphicsPixmapItem* box_cursor = nullptr;
    QGraphicsPixmapItem* bot_cursor = nullptr;
    QGraphicsPixmapItem* ai_bot_cursor = nullptr;
    QGraphicsPixmapItem* deleting_cursor = nullptr;
    //aktuálně používaný kurzor
    QGraphicsPixmapItem* momental_cursor = nullptr; 

    // ukládá jestli je kurzor schovaný 
    bool cursor_hiden = true;

    // pole všech linek vykreslovyných debugovacím nástrojem 
    vector <QGraphicsLineItem* > lines; //dbg


    
    // poslech eventů kliknutí
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;  //posunutí obrázku pod kurzorem
    void mousePressEvent(QGraphicsSceneMouseEvent * e) override;

    // schovávání pick kurzoru když není ve scéně
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:

    // přidání vykreslovací linky do scéne (všechny koorináty na nule vymazají aktuálně vykreslené linky)
    void DBG_draw_line(int x1, int y1, int x2,int y2,QColor color);

    // vytvoření entity na daneém místě
    void create_entyty(ObjectType type,int id, int x , int y , int rotation);

   
public:

    Scene(QWidget * parent );

    // nastaví co se stane po kliknutí myší
    void setClickAction(PickingCursor cursor);

};

#endif