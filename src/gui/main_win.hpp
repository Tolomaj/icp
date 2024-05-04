/*********************************************************************
 * @file main_win.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
 *
*********************************************************************/


#ifndef GUI_MAIN_WIN_H
#define GUI_MAIN_WIN_H

#include "libs.h"

#include "scene.hpp"
#include "list.hpp"
#include "property_picker.hpp"
#include "focus_colector.hpp"

class Scene;

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class GUI_Window: public QMainWindow { 
Q_OBJECT

private:
    /// odkaz na scénu kde se odehrává práce s roboty
    Scene * scene;
    /// odkaz na list kde jsou vedeni všichni roboti
    List * list;

    //ovladací prvky okna
    QComboBox *comboBox ;
    QGraphicsView *graphicsView;
    PropertyPicker * propertyPicker;
    QVBoxLayout * rightSide; 

protected slots:

    /**
     * @brief  Odběratel vybrání prvku
     *
     * Při vybrání jakéhokli prvku nastaví odno do režimu vybírání aby se uživately dalo najevo že už položené entity nelze editovat
     * 
     * @param i [není požit]
     */
    void select(int i);

public slots:
        
    /**
     * @brief funkce volaná když užiovatel klikne na tlačítko otevření soboru
     * 
     * Otevře okno výběru souboru a pošle uřivatelem vybranou cestu mediátorem simulaci 
     */
    void open_file();

    /**
     * @brief funkce volaná když užiovatel klikne na tlačítko uložení soboru
     * 
     * Otevře okno výběru souboru a pošle uřivatelem vybranou cestu mediátorem simulaci 
     */
    void save_file();

    /**
     * @brief zobrazí uživateli okno s inforamcemi
     * 
     * Je napojené na signál z mediátoru 
     *
     * @param ins hlášení které se zobrazí uživateli
     */
    void message(QString ins);

    /// handler tlačítka zastavení simulace (posle přez mediatora povel simulaci)
    void stopButton_f();

    /// handler tlačítka krokování simulace (pošle přez mediatora simualci)
    void stepButton_f();

    /// handler tlačítka pro spustění simulace (pošle přez mediatora simualci)
    void runButton_f();
  
    /**
     * @brief handler vybírání akce kterou uživatel chce dělat 
     * 
     * Nastaví okno tak aby ukazovalovybírání parametrů nebo neukazovalo a ve scéně nastaví kurzor podle vybrané akce
     *
     * @param string název vybírané akce (bráno z &comboBox)
     */
    void dropdown(QString string);

public: 

    /**
     * @brief Vytvoří layout okna 
     * 
     * @param parent objekt hlavního okna kam se layout vyrbí
     */
    GUI_Window(QMainWindow *parent = 0);

    /// event když okno je vytvořeno / řeší zvětšování a zmenšování objektů okna
    void showEvent(QShowEvent *);

    /// event když okno je zmenšeno nebo zvětšeno / řeší zvětšování a zmenšování objektů okna
    void resizeEvent(QResizeEvent* event);


};

#endif