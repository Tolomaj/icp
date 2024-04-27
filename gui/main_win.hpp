#ifndef GUI_MAIN_WIN_H
#define GUI_MAIN_WIN_H

#include "libs.h"

#include "scene.hpp"
#include "list.hpp"
#include "property_picker.hpp"
#include "focus_colector.hpp"

class Scene;

class GUI_Window: public QMainWindow { 
Q_OBJECT

private:
    Scene * scene;
    List * list;

    QComboBox *comboBox ;
    QGraphicsView *graphicsView;
    PropertyPicker * propertyPicker;
    QVBoxLayout * rightSide; 
public:

    virtual ~GUI_Window() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

protected slots:
    // když je něco vybráno zruší se vkládání
    void select(int i);

public slots:
        


    void open_file();

    void save_file();

    void message(QString ins);

    void stopButton_f();

    void stepButton_f();

    void runButton_f();
  
    void dropdown(QString string);

public: 


    GUI_Window(QMainWindow *parent = 0);

    void showEvent(QShowEvent *);

    void resizeEvent(QResizeEvent* event);


};

#endif