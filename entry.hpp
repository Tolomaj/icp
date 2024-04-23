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

#include "mediator.hpp"

#pragma once

class Entry :public QFrame{ 
Q_OBJECT

protected:
    QLabel *entry_name;
    QHBoxLayout* layout;
    int object_id = 0;

protected slots:

    void removeButton_f(){
        Mediator::get_instance().notify_unregistration(object_id);
    }

public: 

    int get_id(){
        return object_id;
    }

    Entry(QWidget *parent = 0,int object_id = 0):QFrame(parent) {
        this->object_id = object_id;
        layout = new QHBoxLayout(this);
        layout->setContentsMargins(2, 2, 2, 2);

        QPushButton * delButton = new QPushButton(parent);
        delButton->setIcon(QIcon("img/wbasket.png"));
        delButton->setFixedSize(QSize(24, 24));
        delButton->setToolTip(QString("Remove object from scene"));
        layout->addWidget(delButton);
        connect(delButton, SIGNAL(clicked()), this,SLOT(removeButton_f()));

        entry_name = new QLabel;
        entry_name->setText("Obsticle[" + QString::number(object_id) +"]");
        layout->addWidget(entry_name);

        this->setFrameStyle(QFrame::Panel | QFrame::Raised);
        
    }

};