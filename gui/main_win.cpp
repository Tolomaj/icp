#include "main_win.hpp"

#pragma once

void MainWindow::open_file(){
    QString filename = QFileDialog::getOpenFileName( nullptr,
        QObject::tr("Open playground file"),
        QDir::currentPath(),
        QObject::tr("Playground file (*.playground);;All files (*.*)"));

    Mediator::get_instance().notify_send_save(LOAD,filename);
}

void MainWindow::save_file(){
    QString filename = QFileDialog::getSaveFileName(nullptr,
        QObject::tr("Save playground file"),
        QDir::currentPath(),
        QObject::tr("Playground file (*.playground);;All files (*.*)"));
    Mediator::get_instance().notify_send_save(SAVE,filename);
}

void MainWindow::message(QString ins){
    QMessageBox::about(this, tr("info"), ins);
}

void MainWindow::stopButton_f(){
    Mediator::get_instance().notify_simulation_controll(STOP);
}

void MainWindow::stepButton_f(){
    Mediator::get_instance().notify_simulation_controll(STEP);
}

void MainWindow::runButton_f(){
    Mediator::get_instance().notify_simulation_controll(RUN);
}
  
void MainWindow::dropdown(QString string){
    if(string == QLatin1String("BOT")){
        scene->setClickAction(AI_BOT_PICKING);

    }else if(string == QLatin1String("HUMAN_BOT")){
        scene->setClickAction(MAN_BOT_PICKING);

    }else if(string == QLatin1String("BOX")){
        scene->setClickAction(BOX_PICKING);
        
    }else if(string == QLatin1String("DELETE")){
        scene->setClickAction(DELETING);

    }else if(string == QLatin1String("SELECT")){
        scene->setClickAction(SELECTING);

    }else{
        qDebug("error state not picking option");
    }
}

void MainWindow::select_Object(int id){
    //scene->select(id);
    techScroll->select(id);
}

MainWindow::MainWindows(QMainWindow *parent):QMainWindow(parent) {

    //set title
    this->setWindowTitle("Robots");
    this->resize(750, 500);

    QWidget * centralWidget = new QWidget(this);
        
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
    QPushButton * run_button = new QPushButton(centralWidget);
    run_button->setText("RUN");
    run_button->setMaximumSize(QSize(50, 50));
    run_button->setToolTip(QString("Starts simulation"));
    horizontalLayout_3->addWidget(run_button);
    connect(run_button, SIGNAL(clicked()), this,SLOT(runButton_f()));

    QPushButton * step_button = new QPushButton(centralWidget);
    step_button->setText("STEP");
    run_button->setMaximumSize(QSize(70, 50));
    run_button->setToolTip(QString("Steps simulation one step and then stops"));
    horizontalLayout_3->addWidget(step_button);
    connect(step_button, SIGNAL(clicked()), this, SLOT(stepButton_f()));

    QPushButton * stop_button = new QPushButton(centralWidget);
    stop_button->setText("STOP");
    stop_button->setMaximumSize(QSize(50, 50));
    stop_button->setToolTip(QString("Stops simulation"));
    horizontalLayout_3->addWidget(stop_button);
    connect(stop_button, SIGNAL(clicked()), this, SLOT(stopButton_f()));

    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    horizontalLayout_3->addSpacerItem(item);

    QPushButton * load_button = new QPushButton(centralWidget);
    load_button->setText("LOAD");
    load_button->setMaximumSize(QSize(50, 50));
    load_button->setToolTip(QString("Loads sesion from file"));
    horizontalLayout_3->addWidget(load_button);
    connect(load_button, SIGNAL(clicked()), this, SLOT(open_file()));

    QPushButton * save_button = new QPushButton(centralWidget);
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

    techScroll = new List(this);

  

    verticalLayout->addWidget(techScroll);

    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(1);
    QLabel *label = new QLabel(verticalWidget_2);
    label->setText("Click action:");

    horizontalLayout_2->addWidget(label);

    QComboBox *comboBox = new QComboBox(verticalWidget_2);
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

void MainWindow::showEvent(QShowEvent *) {
    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent* event){
    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
