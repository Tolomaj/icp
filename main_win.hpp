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
#include <QBitmap>

#include "mediator.hpp"
#include "scene.hpp"
#include "list.hpp"

class MainWindows:public QMainWindow{ 
Q_OBJECT

private:
    Scene *scene;

    QWidget *centralWidget;
    QGraphicsView *graphicsView;

    QPushButton *run_button;
    QPushButton *stop_button;
    QPushButton *step_button;
    QPushButton *load_button;
    QPushButton *save_button;
    
    QListWidget *listWidget;
    QComboBox *comboBox;

public:

    virtual ~MainWindows() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

public slots:


    void open_file(){
        QString filename = QFileDialog::getOpenFileName(
                nullptr,
                QObject::tr("Open playground file"),
                QDir::currentPath(),
                QObject::tr("Playground file (*.playground);;All files (*.*)"));
         Mediator::get_instance().notify_send_save(LOAD,filename);
    }

    void save_file(){
        QString filename = QFileDialog::getSaveFileName(
                nullptr,
                QObject::tr("Save playground file"),
                QDir::currentPath(),
                QObject::tr("Playground file (*.playground);;All files (*.*)"));
        Mediator::get_instance().notify_send_save(SAVE,filename);
    }

    void message(QString ins){
        QMessageBox::about(this, tr("info"), ins);
    }

    void stopButton_f(){
        Mediator::get_instance().notify_simulation_controll(STOP);
    }
    void stepButton_f(){
        Mediator::get_instance().notify_simulation_controll(STEP);
    }
    void runButton_f(){
        Mediator::get_instance().notify_simulation_controll(RUN);
    }
  
    void dropdown(QString string){
        if(string == QLatin1String("BOT")){
            scene->setClickAction(AI_BOT_PICKING);
        }else
        if(string == QLatin1String("HUMAN_BOT")){
            scene->setClickAction(MAN_BOT_PICKING);
        }else
        if(string == QLatin1String("BOX")){
            scene->setClickAction(BOX_PICKING);
        }else
        if(string == QLatin1String("DELETE")){
            scene->setClickAction(DELETING);
        }else
        if(string == QLatin1String("SELECT")){
            scene->setClickAction(SELECTING);
        }else{
            qDebug("error state not picking option");
        }
    }
public: 
    MainWindows(QMainWindow *parent = 0):QMainWindow(parent) {

        //set title
        this->setWindowTitle("Robots");
        this->resize(750, 500);

        centralWidget = new QWidget(this);
        
        QHBoxLayout * horizontalLayout = new QHBoxLayout(centralWidget);
        QVBoxLayout * verticalLayout_2 = new QVBoxLayout();

        scene = new Scene(this);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->viewport()->setCursor(Qt::BlankCursor);
        graphicsView->setMouseTracking(true);
        //graphicsView->setAcceptHoverEvents(true);
        graphicsView->setScene(scene);
        graphicsView->setRenderHint(QPainter::Antialiasing);
        graphicsView->setBackgroundBrush(QPixmap("img/floor.jpg"));



        verticalLayout_2->addWidget(graphicsView);

        QHBoxLayout * horizontalLayout_3 = new QHBoxLayout();
        // simulation controlls buttons
        run_button = new QPushButton(centralWidget);
        run_button->setText("RUN");
        run_button->setMaximumSize(QSize(50, 50));
        run_button->setToolTip(QString("Starts simulation"));
        horizontalLayout_3->addWidget(run_button);
        connect(run_button, SIGNAL(clicked()), this,SLOT(runButton_f()));

        step_button = new QPushButton(centralWidget);
        step_button->setText("STEP");
        run_button->setMaximumSize(QSize(70, 50));
        run_button->setToolTip(QString("Steps simulation one step and then stops"));
        horizontalLayout_3->addWidget(step_button);
        connect(step_button, SIGNAL(clicked()), this, SLOT(stepButton_f()));

        stop_button = new QPushButton(centralWidget);
        stop_button->setText("STOP");
        stop_button->setMaximumSize(QSize(50, 50));
        stop_button->setToolTip(QString("Stops simulation"));
        horizontalLayout_3->addWidget(stop_button);
        connect(stop_button, SIGNAL(clicked()), this, SLOT(stopButton_f()));

        QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        horizontalLayout_3->addSpacerItem(item);

        load_button = new QPushButton(centralWidget);
        load_button->setText("LOAD");
        load_button->setMaximumSize(QSize(50, 50));
        load_button->setToolTip(QString("Loads sesion from file"));
        horizontalLayout_3->addWidget(load_button);
        connect(load_button, SIGNAL(clicked()), this, SLOT(open_file()));

        save_button = new QPushButton(centralWidget);
        save_button->setText("SAVE");
        save_button->setMaximumSize(QSize(50, 50));
        save_button->setToolTip(QString("Saves actual sesion to file"));
        horizontalLayout_3->addWidget(save_button);
        connect(save_button, SIGNAL(clicked()), this, SLOT(save_file()));



        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        QWidget * verticalWidget_2 = new QWidget(centralWidget);
        QVBoxLayout * verticalLayout = new QVBoxLayout(verticalWidget_2);
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        QScrollArea* techScroll = new List(verticalWidget_2);

  

        verticalLayout->addWidget(techScroll);

        QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        QLabel *label = new QLabel(verticalWidget_2);
        label->setText("Click action:");

        horizontalLayout_2->addWidget(label);


        comboBox = new QComboBox(verticalWidget_2);
        comboBox->addItem(QString("SELECT"));
        comboBox->addItem(QString("BOT"));
        comboBox->addItem(QString("HUMAN_BOT"));
        comboBox->addItem(QString("BOX"));
        comboBox->addItem(QString("DELETE"));
        connect(comboBox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(dropdown(const QString)));




        horizontalLayout_2->addWidget(comboBox);
        verticalLayout->addLayout(horizontalLayout_2);
        horizontalLayout->addWidget(verticalWidget_2);

        this->setCentralWidget(centralWidget);
        

        this->show();
    }

    void showEvent(QShowEvent *) {
        graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
        
    }

    void resizeEvent(QResizeEvent* event){
        
       graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
        
    }


};