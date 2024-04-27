#include "libs.h"

#include "scene.hpp"
#include "list.hpp"

#pragma once

class MainWindow: public QMainWindow{ 
Q_OBJECT

private:
    Scene *scene;
    List * techScroll;

    QGraphicsView *graphicsView;
public:

    virtual ~MainWindow() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

public slots:

    void open_file();

    void save_file();

    void message(QString ins);

    void stopButton_f();

    void stepButton_f();

    void runButton_f();
  
    void dropdown(QString string);

public: 

    void select_Object(int id);

    MainWindow(QMainWindow *parent = 0);

    void showEvent(QShowEvent *);

    void resizeEvent(QResizeEvent* event);


};