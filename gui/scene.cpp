#include "scene.hpp"


void Scene::setClickAction(PickingCursor cursor){
    pickmode = cursor;
    if(!cursor_hiden){
        this->removeItem(momental_cursor);
    }
    switch (cursor){
        case MAN_BOT_PICKING:
            momental_cursor = bot_cursor;
            break;
        case AI_BOT_PICKING:
            momental_cursor = ai_bot_cursor;
            cursor_bot_vision->show();
            cursor_bot_rotation->show();
            break;
        case BOX_PICKING:
            momental_cursor = box_cursor;
            break;
        case SELECTING:
            momental_cursor = nullptr;
            break;
        case DELETING:
            momental_cursor = deleting_cursor;
            break;
    }

    if(momental_cursor != nullptr && !cursor_hiden){
        this->addItem(momental_cursor);
    }    

    if(cursor != AI_BOT_PICKING){
        cursor_bot_vision->hide();
        cursor_bot_rotation->hide();
    }

}


void Scene::create_entyty(ObjectType type,int id, int x , int y , int rotation){
    switch (type){
    case BOX:
        new SceneEntity(this,id,x,y,rotation);
        break;
        
    case MAN_ROBOT:
        new MovableEntity(this,id,x,y,rotation);
        break;
    
    case AI_ROBOT:
        new MovableEntity(this,id,x,y,rotation,"img/ai_bot.png","img/ai_bot-sel.png");
        break;

    }        
}

void Scene::DBG_draw_line(int x1, int y1, int x2,int y2, QColor color){ //dbg

    if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0){
        for (auto p : lines) {
            delete p;
        } 
        lines.clear();
    }else{
        QPen onepen(color);
        if(color == Qt::white || color == Qt::black){
            onepen.setWidth(2);
        }else{
            onepen.setWidth(4);
        }
        
        
        lines.push_back(this->addLine(x1, y1, x2, y2, onepen));
    }

    this->update();
};

Scene::Scene(QWidget *parent, PropertyPicker * picker):QGraphicsScene(parent) {
    this->parent = parent;
    this->picker = picker;

    this->setSceneRect(-BOT_SIZE/2, -BOT_SIZE/2, ARENA_SIZE_X + BOT_SIZE, ARENA_SIZE_Y + BOT_SIZE);
    this->setItemIndexMethod(QGraphicsScene::NoIndex);


    QPen onepen1(Qt::green);
    onepen1.setWidth(6);
    QPen onepen2(Qt::yellow);
    onepen2.setWidth(4);
    cursor_bot_vision = this->addLine(0, 0, 0, 0, onepen1);
    cursor_bot_rotation = this->addLine(0, 0, 0, 0, onepen2);
    cursor_bot_vision->hide();
    cursor_bot_rotation->hide();


    QBrush trBrush(Qt::transparent);
    QPen outlinePen(Qt::blue);
    outlinePen.setWidth(5);

    rectangle = this->addRect(this->sceneRect(), outlinePen, trBrush);

    box_cursor = new QGraphicsPixmapItem(QPixmap("img/box.png").scaled(QSize(BOX_SIZE, BOX_SIZE)));
    box_cursor->setOffset(-BOX_SIZE/2,-BOX_SIZE/2);

    bot_cursor  = new QGraphicsPixmapItem(QPixmap("img/bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE)));
    bot_cursor->setOffset(-BOT_SIZE/2,-BOT_SIZE/2);

    ai_bot_cursor  = new QGraphicsPixmapItem(QPixmap("img/ai_bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE)));
    ai_bot_cursor->setOffset(-BOT_SIZE/2,-BOT_SIZE/2);

    deleting_cursor = new QGraphicsPixmapItem(QPixmap("img/delcross.png").scaled(QSize(70, 70)));
    deleting_cursor->setOffset(-(70/2),-(70/2));



    installEventFilter(this);


    Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(create_entyty(ObjectType, int, int, int , int)));
    Mediator::get_instance().subscribe_DBG_draw_line(this, SLOT(DBG_draw_line(int, int, int, int, QColor))); //dbg
}


void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    if(momental_cursor != nullptr){
        const QPointF p = e->scenePos();
        momental_cursor->setPos(p.x(),p.y());
        momental_cursor->setRotation(picker->get_rotation());
        int linesize = qSqrt((BOT_SIZE*BOT_SIZE)/2) + picker->get_bot_vision();
        
        int relative_rotation = (picker->get_colide_rotation()*(-2*(!picker->get_rotation_direction()) + 1) + picker->get_rotation());
        cursor_bot_vision->setLine(p.x(),p.y(),p.x() + qCos(picker->get_rotation()* (3.141592 / 180)) * linesize ,p.y() + qSin(picker->get_rotation()* (3.141592 / 180)) * linesize);
        cursor_bot_rotation->setLine(p.x(),p.y(),p.x() + qCos(relative_rotation* (3.141592 / 180)) * (qSqrt((BOT_SIZE*BOT_SIZE)/2) + 15) ,p.y() + qSin(relative_rotation * (3.141592 / 180)) * (qSqrt((BOT_SIZE*BOT_SIZE)/2) + 15));
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent * e)  {
    QPointF p = e->scenePos();

    // kontrola jestli je v aréně
    if(p.x() < 0){ p.setX(0); }
    if(p.y() < 0){ p.setY(0); }
    if(p.x() > ARENA_SIZE_X){ p.setX(ARENA_SIZE_X); }
    if(p.y() > ARENA_SIZE_Y){ p.setY(ARENA_SIZE_Y); }

    SignedTexture *texture_reference;
    QGraphicsItem * pttr;

    switch (pickmode){
        case BOX_PICKING:
            Mediator::get_instance().notify_registartion(BOX, p.x(), p.y() , picker->get_rotation(),picker->get_colide_rotation(),picker->get_bot_vision(),picker->get_rotation_direction());
            break;
        case MAN_BOT_PICKING:
            Mediator::get_instance().notify_registartion(MAN_ROBOT, p.x(), p.y() , picker->get_rotation(),picker->get_colide_rotation(),picker->get_bot_vision(),picker->get_rotation_direction());
            break;
        case AI_BOT_PICKING:
            Mediator::get_instance().notify_registartion(AI_ROBOT, p.x(), p.y() , picker->get_rotation(),picker->get_colide_rotation(),picker->get_bot_vision(),picker->get_rotation_direction());
            break;
        case DELETING:
        case SELECTING:
            if(momental_cursor != nullptr){ this->removeItem(momental_cursor); }; // ignorování kurzoru
            pttr = itemAt(p, QTransform());
            if(momental_cursor != nullptr){ this->addItem(momental_cursor); }; // ignorování kurzoru

            texture_reference = dynamic_cast<SignedTexture*>(pttr);
        
            if(pickmode == DELETING){
                // pro mód mazání //
                if(texture_reference == NULL){ return; }  // kontrola jestli objekt je klikatelný (má id)
                Mediator::get_instance().notify_unregistration(texture_reference->get_id());
            }else{
                // pro mód vybírání //
                if(texture_reference == NULL){
                    FocusColector::get_instance().focus_object(NONE);
                    return; // nevybrán platný objekt
                }
                FocusColector::get_instance().focus_object(texture_reference->get_id());
            }
                
        break;
    } 
}

// schovávání pick kurzoru když není ve scéně
bool Scene::eventFilter(QObject *watched, QEvent *event) {
    if(momental_cursor != nullptr){
        if(event->type() == QEvent::Enter){
            cursor_hiden = false;
            this->addItem(momental_cursor);
        }else if(event->type() == QEvent::Leave){
            cursor_hiden = true;
            this->removeItem(momental_cursor);
        }
    }
    return false;
}
