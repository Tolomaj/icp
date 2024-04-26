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
#include <QtGlobal>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QRadioButton>

#include "mediator.hpp"
#include "entry.hpp"
#include "bot_entry.hpp"
#include "ai_entry.hpp"

class List :public QScrollArea{ 
Q_OBJECT


public:

    virtual ~List() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

private:
    QWidget * parent;
    QWidget* entryes;
    Mediator mediator;

public slots:
    void add_entry(ObjectType type, int i, int x, int y, int r){
        qDebug("entry entering from widget");
       
        switch (type) {
            case AI_ROBOT:
                entryes->layout()->addWidget(new AI_Entry(parent,i));
                break;
            case MAN_ROBOT:
                entryes->layout()->addWidget(new BOT_Entry(parent,i));
                break;
            case BOX:
                entryes->layout()->addWidget(new Entry(parent,i));
                break;
        } 
    }


public: 
    List(QWidget *parent = 0):QScrollArea(parent) {

        this->parent = parent;

        this->setMaximumSize(QSize(250, 16777215));
        this->setMinimumSize(QSize(200, 0));
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        this->setWidgetResizable(true);

        entryes = new QWidget;
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        QVBoxLayout * layout = new QVBoxLayout(entryes);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(2);
        entryes->setLayout(layout);
        this->setWidget(entryes);


        Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(add_entry(ObjectType, int, int, int , int)));
    

        }

};