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

#include "entry.hpp"

#pragma once

//todo přidat přepínání a měnení tlařítek na základě state robota

class BOT_Entry :public Entry{ 
Q_OBJECT

public slots:
    void goButton_f(){
        Mediator::get_instance().notify_bot_controll(object_id , FORWARD);
    }

    void leftButton_f(){
        Mediator::get_instance().notify_bot_controll(object_id , LEFT);
    }

    void rightButton_f(){
        Mediator::get_instance().notify_bot_controll(object_id , RIGHT);
    }

public: 
    BOT_Entry(QWidget *parent = 0,int object_id = 0):Entry(parent,object_id) {

        entry_name->setText("Bot[" + QString::number(object_id) +"]");

        QPushButton * leftButton = new QPushButton(parent);
        leftButton->setIcon(QIcon("img/rleft.png"));
        leftButton->setFixedSize(QSize(24, 24));
        leftButton->setToolTip(QString("turn robot left"));
        layout->addWidget(leftButton);
        connect(leftButton, SIGNAL(clicked()), this,SLOT(leftButton_f()));

        QPushButton * goButton = new QPushButton(parent);
        goButton->setIcon(QIcon("img/go.png"));
        goButton->setFixedSize(QSize(24, 24));
        goButton->setToolTip(QString("go with robot"));
        layout->addWidget(goButton);
        connect(goButton, SIGNAL(clicked()), this,SLOT(goButton_f()));

        QPushButton * rightButton = new QPushButton(parent);
        rightButton->setIcon(QIcon("img/rright.png"));
        rightButton->setFixedSize(QSize(24, 24));
        rightButton->setToolTip(QString("turn robot right"));
        layout->addWidget(rightButton);
        connect(rightButton, SIGNAL(clicked()), this,SLOT(rightButton_f()));
    }

};