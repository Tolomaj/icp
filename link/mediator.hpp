#include <QObject>
#include <QColor>

#pragma once


#define ALL -1

#define CLEAR_LINES 0,0,0,0,Qt::blue

enum FileOP{
    SAVE,
    LOAD
};

enum RoboState{
    STOPED,
    MOVING,
    ROTATING,
    COLIDED
};

enum ObjectType{
    AI_ROBOT,
    MAN_ROBOT,
    BOX
};

enum SimuControll{
    RUN,
    STOP,
    STEP
};

enum ControllComand{
    FORWARD,
    LEFT,
    RIGHT
};

class Mediator : public QObject {
Q_OBJECT
public:

    // disable copy/move -- this is a Singleton
    Mediator(const Mediator&) = delete;
    Mediator(Mediator&&) = delete;
    Mediator& operator=(const Mediator&) = delete;
    Mediator& operator=(Mediator&&) = delete;

    Mediator() : QObject(){};

    virtual ~Mediator(){
        this->disconnect();
    };
        

    static Mediator &get_instance();

    // registrace robotů a objektů (přijímáno v seznamu, datech a scéně)
    void subscribe_registartion(QObject* subscriber, const char* slot);      // funkce co spracuje požadavek na registraci robota
    void subscribe_unregistration(QObject* subscriber, const char* slot);    // unkce které mají zničit objěkt (-1 je vymazání všeho)
    void subscribe_forvarded_registartion(QObject* subscriber, const char* slot); // přidání robota do všechy ui (přijímáno gui)

    //změny stavů robotů je odebírano (bot_entry a [asi]Auto_bot_entry )
    void subscribe_states_changes(QObject* subscriber, const char* slot);

    // pohyb robotů odebíráno scénou
    void subscribe_move(QObject* subscriber, const char* slot);

    // pohyb robotů odebíráno scénou
    void subscribe_bot_controll(QObject* subscriber, const char* slot);

    // ovládání simulace (voláno z gui do simulace)
    void subscribe_simulation_controll(QObject* subscriber, const char* slot);

    // načtení nebo ukládíní simulace do souboru odebíráno v data
    void subscribe_load_save(QObject* subscriber, const char* slot);

    void subscribe_DBG_draw_line(QObject* subscriber, const char* slot);

signals:
   // registrace robota, ovládáno z gui (pozadavek na vytvoření robota a přižazení id)
    void notify_registartion(ObjectType type,int x , int y , int rotation,int colide_rotation = 0,int sence_lenght = 0,bool rotation_direction = false);
    // potvrzení registrace robota od data pro gui (pravděpodobná reakce na registrateion)
    void notify_forvarded_registartion(ObjectType type, int id,int x , int y , int rotation);
    // zničení robota voláno z menu entry
    void notify_unregistration(int id);

    // mení stav daného robota voláno z simulace
    void notify_states_change(int id,RoboState state);

    // mění pozici a rotaci robota voláno ze simulace
    void notify_move(int id, int x, int y, int rotation);

    void notify_bot_controll(int id, ControllComand command);

    // ovládání simulace z gui
    void notify_simulation_controll(SimuControll command);

    // ovládání z ui pro naštení nebo uložení soubou
    void notify_send_save(FileOP file_operation,QString path);

    // ovládání z ui pro naštení nebo uložení soubou
    void notify_DBG_draw_line(int x1, int y1, int x2,int y2,QColor color);

};
