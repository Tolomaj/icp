/*********************************************************************
 * @file  mediator.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief komunikace mezi gui a simulací
 * Objekt který zajištuje komunikcai mezi gui a simulací pomocí notify funkcí které když jsou zavolány tak se provedou všechny funkce které byli nastaveny pomocí subscribe funkcí.
 *********************************************************************/

#include <QObject>
#include <QColor>
#pragma once

#define ALL -1 // pro práci se všemi objekty
#define CLEAR_LINES 0,0,0,0,Qt::blue // pro zrušení všech linek

enum FileOP{ SAVE, LOAD };

enum RoboState{ STOPED, MOVING, ROTATING, COLIDED };

enum ObjectType{ AI_ROBOT,  MAN_ROBOT, BOX };

enum SimuControll{ RUN, STOP, STEP };

enum ControllComand{ TOGGLE_MOVE, LEFT, RIGHT };


/** @brief Mediator : singleton který zajituje komunikaci mezi gui a simulací
 *
 *  Je přístupný všude
 *  Některé notifikace jsou použity i pro vnitřní komunikaci. (Třeba notify_unregistration() se volá při kliknutí na tlačítko v GUI a to na tuto správu i reaguje)
 *
 */
class Mediator : public QObject {
Q_OBJECT
public:

    
    /// @cond z objektu vytvoří singletron
    Mediator(const Mediator&) = delete;
    Mediator(Mediator&&) = delete;
    Mediator& operator=(const Mediator&) = delete;
    Mediator& operator=(Mediator&&) = delete;

    Mediator() : QObject(){};

    virtual ~Mediator(){
        this->disconnect();
    };  
    /// @endcond


    /**
    * @brief    Vrací instanci přez krterou se přistupuje k metodám
    */
    static Mediator &get_instance();

    /**
     * @brief registrace robotů a objektů (přijímáno v seznamu, datech a scéně)
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(ObjectType type ,int x,int y,int rotation,colide_rotation ,int sence_lenght ,bool direction)
     */
    void subscribe_registartion(QObject* subscriber, const char* slot);      // funkce co spracuje požadavek na registraci robota


    /**
     * @brief funkce které mají zničit objěkt (-1 je vymazání všeho macro ALL)
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(int id)
     */
    void subscribe_unregistration(QObject* subscriber, const char* slot);  

    /**
     * @brief přidání robota do GUI
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(ObjectType type, int id,int x , int y , int rotation)
     */
    void subscribe_forvarded_registartion(QObject* subscriber, const char* slot); 


    /**
     * @brief změny stavů robotů je odebírano (bot_entry a [asi]Auto_bot_entry )
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(int id,RoboState state)
     */
    void subscribe_states_changes(QObject* subscriber, const char* slot);


    /**
     * @brief pohyb robotů odebíráno scénou
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(int id, int x, int y, int rotation)
     */
    void subscribe_move(QObject* subscriber, const char* slot);

    /**
     * @brief pohyb robotů odebíráno scénou 
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(int id, ControllComand command)
     */
    void subscribe_bot_controll(QObject* subscriber, const char* slot);

    /**
     * @brief ovládání simulace (voláno z gui do simulace)
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(SimuControll command)
     */
    void subscribe_simulation_controll(QObject* subscriber, const char* slot);

    /**
     * @brief  načtení nebo ukládíní simulace do souboru odebíráno v simulaci
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(FileOP file_operation,QString path)
     */
    void subscribe_load_save(QObject* subscriber, const char* slot);

    /**
     * @brief errová hláška zavolána odebíráno v gui
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(QString msg)
     */
    void subscribe_error_message(QObject* subscriber, const char* slot);

    /**
     * @brief vykreslení linky
     * 
     * @param subscriber objekt ve kterém je funkce
     * @param slot slot v objěktu. Slot musí odpovídat funkci(int x1, int y1, int x2,int y2,QColor color
     */
    void subscribe_DBG_draw_line(QObject* subscriber, const char* slot);

signals:
   /**
    * @brief požadavek registrace robota/bedny
    *
    *   posíláno z gui -> Požadavek na přidání robota / bedny s vlastnostmi do scény
    *
    * @param type typ objektu ktrý vytvéříme AI_ROBOT | MAN_ROBOT | BOX
    * @param x pozice X ve scéně
    * @param y pozice Y ve scéně
    * @param rotation rotace ve scéně
    * @param colide_rotation o kolik se robot má otočit při kolizi (volitelné  MAN_ROBOT a BOX toto nastavení nepoužívají)
    * @param sence_lenght délka dohledu robota (Pro BOX není potřeba zadávat)
    * @param rotation_direction směr kterým se robot otočí při nárazu ( zadává se jen pro AI_ROBOT)
    */
    void notify_registartion(ObjectType type,int x , int y , int rotation,int colide_rotation = 0,int sence_lenght = 0,bool rotation_direction = false);


    /**
     * @brief potvrzení registrace robota/bedny
     *
     *   posíláno z simulace -> Potvrzuje uspěšnou registraci robota/ bedny do simulace, odpovídá příslušným přiděleným id a pozicí na mapě
     *
     * @param type typ objektu ktrý vytvéříme AI_ROBOT | MAN_ROBOT | BOX
     * @param id přiřazené id robota/bedny. používá se na jakoukoli další interakci s robotem/bednou
     * @param x pozice X ve scéně 
     * @param y pozice Y ve scéně
     * @param rotation rotace ve scéně
     */
    void notify_forvarded_registartion(ObjectType type, int id,int x , int y , int rotation);


    /**
     * @brief zničení robota/bedny
     *
     *  voláno z menu entry (gui) -> 
     *  
     * @param id id robota na zničení
     */
    void notify_unregistration(int id);


    /**
     * @brief mení stav daného robota voláno z simulace
     * 
     *  posíláno ze simulace -> 
     *
     * @param id id robota
     * @param state stav robota STOPED | MOVING | ROTATING | COLIDED
     */
    void notify_states_change(int id,RoboState state);


    /**
     * @brief mění pozici a rotaci robota voláno ze simulace
     * 
     * posíláno ze simulace -> 
     *
     * @param id id robota
     * @param x pozice X ve scéně 
     * @param y pozice Y ve scéně
     * @param rotation rotace ve scéně
     */
    void notify_move(int id, int x, int y, int rotation);


    /**
     * @brief poslání příkazu človekem ovládanému robotovy
     *  
     *  posíláno z gui -> 
     *
     * @param id id robota
     * @param command příkaz robotu TOGGLE_MOVE | LEFT | RIGHT
     */
    void notify_bot_controll(int id, ControllComand command);


    /**
     * @brief ovládání simulace
     *  
     *  posíláno z gui -> 
     *
     * @param command  požadovaný stav simulace RUN | STOP | STEP 
     */
    void notify_simulation_controll(SimuControll command);


    /**
     * @brief ovládání z ui pro naštení nebo uložení soubou
     *  
     *  posíláno z gui -> 
     *
     * @param file_operation o jakou operaci se jedná (uložení/načtení)  SAVE | LOAD 
     * @param path cesta k souboru se kterým se pracuje
     */
    void notify_send_save(FileOP file_operation,QString path);


    /**
     * @brief ukáže zprávu uživateli o chybě 
     *
     * např: při nepovedeném načtení souboru
     * posíláno z gui -> 
     * 
     * @param msg zpráva na zobrazení
     */
    void notify_error_message(QString msg);


    /**
     * @brief ladící funkce pro vykreslení linky ve scéně
     * 
     * pokud chceme obnovit linky použijeme makro CLEAR_LINES které obsahuje kompinaci paramterů tak aby se linky vymazali (0,0,0,0,0)
     *
     * @param x1 pozice X začátku linky
     * @param y1 pozice Y začátku linky
     * @param x2 pozice X konce linky
     * @param y2 pozice Y konce linky
     * @param color barva linky
     */
    void notify_DBG_draw_line(int x1, int y1, int x2,int y2,QColor color);

};
