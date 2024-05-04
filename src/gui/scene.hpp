#ifndef GUI_SCENE_H
#define GUI_SCENE_H

#include "libs.h"

#include "property_picker.hpp"
#include "movable_entity.hpp"
#include "scene_entity.hpp"
#include "focus_colector.hpp"

#include <vector> 
using namespace std; 


///možné akce při kliknutí kurzorem do scény | lehce nevhodně pojmenované 
enum PickingCursor{
    MAN_BOT_PICKING,
    AI_BOT_PICKING,
    BOX_PICKING,
    SELECTING,
    DELETING
};
/// Scene : je objekt scény která je v hlavním okně, obsahuje všechny objekty jako boxy / roboty a zařizuje obstarávání klikání do scény
class Scene :public QGraphicsScene{ 
Q_OBJECT
    PropertyPicker *picker;

    QWidget *parent;

    /// drží hodnotu co se má provédst po kliknutí
    PickingCursor pickmode = SELECTING;

    /// hranice arény
    QGraphicsRectItem *rectangle; 

    /// obrázky kurzoru pro jednotlivé módy
    QGraphicsPixmapItem* box_cursor = nullptr;
    /// obrázky kurzoru pro jednotlivé módy
    QGraphicsPixmapItem* bot_cursor = nullptr;
    /// obrázky kurzoru pro jednotlivé módy
    QGraphicsPixmapItem* ai_bot_cursor = nullptr;
    /// obrázky kurzoru pro jednotlivé módy
    QGraphicsPixmapItem* deleting_cursor = nullptr;

    /// aktuálně používaný kurzor
    QGraphicsPixmapItem* momental_cursor = nullptr;

    ///Linka zobrazující kam až robot vidí
    QGraphicsLineItem * cursor_bot_vision;
    ///Linka zobrazující kam se robot otočí když narazí
    QGraphicsLineItem * cursor_bot_rotation;

    // ukládá jestli je kurzor schovaný 
    bool cursor_hiden = true;

    // pole všech linek vykreslovyných debugovacím nástrojem 
    vector <QGraphicsLineItem* > lines;

    
    /// poslech eventu posunutí myši a posunutí obrázku pod kurzorem
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
    /// poslech eventů kliknutí
    void mousePressEvent(QGraphicsSceneMouseEvent * e) override;

    /// schovávání pick kurzoru když není ve scéně
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:

    /**
     * @brief přidání vykreslovací linky do scéne pro debugovací účeli
     * 
     * pokud všechny koordináty jsou 0 poté vymaže všechny linky ve scéně
     *
     * @param x1 pozice prvního bodu v X
     * @param y1 pozice prvního bodu v Y
     * @param x2 pozice druhého bodu v X
     * @param y2 pozice druhého bodu v Y
     * @param color barva linky
     */
    void DBG_draw_line(int x1, int y1, int x2,int y2,QColor color);

    /**
     * @brief vytvoření entity na daném místě
     * 
     * je spojený se signálem z mediatoru
     *
     * @param type typ objektu k vytvoření
     * @param id id objektu k vytvoření
     * @param x místo X ve scéně
     * @param y místo Y ve scéně
     * @param rotation Rotace ve scéně
     */
    void create_entyty(ObjectType type,int id, int x , int y , int rotation);

   
public:
    /**
     * @brief vytvoří scénu
     * 
     * @param parent rodič pod kterým se vytvoří scéna
     * @param picker picker hodnot ze kterého se berou hodnoty přidaného objektu
     */
    Scene(QWidget * parent ,PropertyPicker * picker);

    /// nastaví co se stane po kliknutí myší
    
    /**
     * @brief Set the Click Action object
     * 
     * @param cursor akce která se provede po kliknutí reprezentovaná typem kurzoru
     */
    void setClickAction(PickingCursor cursor);

};

#endif