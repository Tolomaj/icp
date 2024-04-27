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
#include <QTimer>

#include "../link/mediator.hpp"

#pragma once


class SimulationData : public QObject {
Q_OBJECT

//todo zde bude pole objektů pro simulaci


private slots:
    // prozba o regstraci entity. je zadán typ a pozice kam je objekt požadován
    // aby se ovšem objekt zaregistroval je nuté aby byl poslán forvarded_registration signal
    


public:

    SimulationData() : QObject(){
       
       
    }


};
