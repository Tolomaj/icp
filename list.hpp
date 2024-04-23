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
    void add_entry(ObjectType type, int i){
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

    void remove_entry(int id){
        for (size_t i = 0; i < entryes->layout()->count(); i++){
            QWidget *widget = entryes->layout()->itemAt(i)->widget();
            if(((Entry * )widget)->get_id() == id){
                entryes->layout()->removeWidget(widget);
                delete widget;
                return;
            }
        }
    }


public: 
    List(QWidget *parent = 0):QScrollArea(parent) {

        this->parent = parent;

        this->setMaximumSize(QSize(250, 16777215));
        this->setMinimumSize(QSize(200, 0));
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        //this->setBackgroundRole(QPalette::Window);
        //this->setFrameShadow(QFrame::Plain);
        this->setWidgetResizable(true);

        entryes = new QWidget;
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        QVBoxLayout * layout = new QVBoxLayout(entryes);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(2);
        entryes->setLayout(layout);
        this->setWidget(entryes);


        Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(add_entry(ObjectType, int)));
        Mediator::get_instance().subscribe_unregistration(this, SLOT(remove_entry(int)));

        entryes->layout()->addWidget(new Entry(parent,1));
        entryes->layout()->addWidget(new Entry(parent,2));
        entryes->layout()->addWidget(new Entry(parent,3));
        entryes->layout()->addWidget(new Entry(parent,4));
        entryes->layout()->addWidget(new BOT_Entry(parent,5));
        entryes->layout()->addWidget(new Entry(parent,6));
        entryes->layout()->addWidget(new Entry(parent,7));
        entryes->layout()->addWidget(new Entry(parent,8));

        entryes->layout()->addWidget(new AI_Entry(parent,9));
        entryes->layout()->addWidget(new AI_Entry(parent,10));



        }


/*//todo
    add (BOT/HUMAN/OBSTICLE,ID)
    remove (ID)
*/


};