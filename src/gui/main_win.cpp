
#include "main_win.hpp"

void GUI_Window::open_file(){
    QString filename = QFileDialog::getOpenFileName( nullptr,
        QObject::tr("Open playground file"),
        QDir::currentPath(),
        QObject::tr("Playground file (*.playground);;All files (*.*)"));

    if(filename == ""){ return; }
    Mediator::get_instance().notify_send_save(LOAD,filename);
}

void GUI_Window::save_file(){
    QString filename = QFileDialog::getSaveFileName(nullptr,
        QObject::tr("Save playground file"),
        QDir::currentPath(),
        QObject::tr("Playground file (*.playground);;All files (*.*)"));

    if(filename == ""){ return; }
    Mediator::get_instance().notify_send_save(SAVE,filename);
}

void GUI_Window::message(QString ins){
    QMessageBox::about(this, tr("info"), ins);
}

void GUI_Window::stopButton_f(){
    Mediator::get_instance().notify_simulation_controll(STOP);
}

void GUI_Window::stepButton_f(){
    Mediator::get_instance().notify_simulation_controll(STEP);
}

void GUI_Window::runButton_f(){
    Mediator::get_instance().notify_simulation_controll(RUN);
}
  
void GUI_Window::select(int id){
    scene->setClickAction(SELECTING);
    propertyPicker->hide(); 
    comboBox->setCurrentIndex(0);
}

void GUI_Window::dropdown(QString string){
    if(string == QLatin1String("BOT")){
        scene->setClickAction(AI_BOT_PICKING);
        propertyPicker->setFullMode(true);
        propertyPicker->show();

    }else if(string == QLatin1String("HUMAN_BOT")){
        scene->setClickAction(MAN_BOT_PICKING);
        propertyPicker->setFullMode(true,true);
        propertyPicker->show();
    }else if(string == QLatin1String("BOX")){
        scene->setClickAction(BOX_PICKING);
        propertyPicker->setFullMode(false);
        propertyPicker->show();    
    }else if(string == QLatin1String("DELETE")){
        scene->setClickAction(DELETING);
        propertyPicker->hide();
    }else{
        scene->setClickAction(SELECTING);
        propertyPicker->hide();
    }  
}

GUI_Window::GUI_Window(QMainWindow *parent):QMainWindow(parent) {

    //set title
    this->setWindowTitle("Robots");
    this->resize(750, 500);
    setMinimumSize(300, 400);

    QWidget * centralWidget = new QWidget(this);
        
    QHBoxLayout * horizontalLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout * verticalLayout_2 = new QVBoxLayout();

    propertyPicker = new PropertyPicker(centralWidget);
    propertyPicker->hide();

    scene = new Scene(this,propertyPicker);

    graphicsView = new QGraphicsView(centralWidget);
    graphicsView->viewport()->setCursor(Qt::BlankCursor);
    graphicsView->setMouseTracking(true);
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
    rightSide = new QVBoxLayout(verticalWidget_2);

    verticalWidget_2->setMaximumWidth(230);
    rightSide->setContentsMargins(0, 0, 0, 0);

    list = new List(this);
    rightSide->addWidget(list);


    rightSide->addWidget(propertyPicker);
    
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
    rightSide->addLayout(horizontalLayout_2);
    horizontalLayout->addWidget(verticalWidget_2);

    this->setCentralWidget(centralWidget);

    this->show();
    Mediator::get_instance().subscribe_error_message(this, SLOT(message(QString)));
    FocusColector::get_instance().subscribe(this, SLOT(select(int)));
}

void GUI_Window::showEvent(QShowEvent *) {
    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void GUI_Window::resizeEvent(QResizeEvent* event){
    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
