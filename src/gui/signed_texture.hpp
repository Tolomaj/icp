/*********************************************************************
 * @file signed_texture.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt který přidává k textury id
 *
*********************************************************************/

#include "libs.h"

/// SignedTexture : objekt který přidává k textury id aby bylo jednodušší zjisti na co se ve scéně kliknulo
class SignedTexture : public QGraphicsPixmapItem {

protected:
    /// id textury
    int object_id = 0;
public:
    
    
    /// vrací id textury
    int get_id(){
        return this->object_id;
    }

    /**
     * @brief vytvoří objekt a dá mu texturu a id
     * 
     * @param id id textury
     * @param pixmap textura (pokud není jedna v celé aplikaci, načítat z SceneResources)
     */
    SignedTexture(int id,const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap){
        this->object_id = id;
    };

};