#include "libs.h"

/*! objekt který rozšiřuje testutu o id ke které entitě patří */
class SignedTexture : public QGraphicsPixmapItem {

protected:
    int object_id = 0;
public:
    /** vrací id textury */
    int get_id(){
        return this->object_id;
    }

    SignedTexture(int id,const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap){
        this->object_id = id;
    };
    ~SignedTexture(){};
};