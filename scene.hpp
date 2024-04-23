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

class Scene :public QGraphicsScene{ 
Q_OBJECT


public:

    virtual ~Scene() {}; // https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable

private:

    QGraphicsRectItem *rectangle;

public: 
    Scene(QMainWindow *parent = 0):QGraphicsScene(parent) {

        this->setSceneRect(0, 0, 1000, 1000);
        this->setItemIndexMethod(QGraphicsScene::NoIndex);
        
        QGraphicsPixmapItem* botIMG = new QGraphicsPixmapItem(QPixmap("bot.png"));
        botIMG->setTransformOriginPoint(5, 5);
        botIMG->setRotation(50);
        this->addItem(botIMG);
        //todo rotations

        QBrush trBrush(Qt::transparent);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);

        rectangle = this->addRect(this->sceneRect(), outlinePen, trBrush);
    }



};