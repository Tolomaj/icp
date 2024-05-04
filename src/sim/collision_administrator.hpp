/*********************************************************************
 * @file collision_administrator.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu ColisionAdministrator, která spravuje kolize.
 *********************************************************************/

#include <QObject>
#include <vector>
#include "scene_object.hpp"
#include "box.hpp"
#include "collision_engine/collision_engine.hpp"

class Bot;

#pragma once
using namespace std;

/**
 * @class ColisionAdministrator
 * @brief Spravuje kolize mezi objekty.
 * 
 * Udržuje seznam všech kozovatelných objektů. Umožňuje zaregistrovat nový objekt a zjistit, zda došlo ke kolizi s jiným objektem.
 */
class ColisionAdministrator : public QObject {
Q_OBJECT
    /// Seznam všech objektů.
    vector<SceneObject*> list;
    Arena arena = Arena(ARENA_SIZE_X,ARENA_SIZE_Y);

public:

    /// Zakáže kopírování a přesouvání -- třída je Jedináček.
    ColisionAdministrator(const ColisionAdministrator&) = delete;
    ColisionAdministrator(ColisionAdministrator&&) = delete;
    ColisionAdministrator& operator=(const ColisionAdministrator&) = delete;
    ColisionAdministrator& operator=(ColisionAdministrator&&) = delete;

    ColisionAdministrator() : QObject(){};

    virtual ~ColisionAdministrator(){
        this->disconnect();
    };;
        
    /**
     * @brief Získává instanci třídy.
     * @return Instance třídy.
     */
    static ColisionAdministrator &get_instance() {
        static ColisionAdministrator instance;
        return instance;
    }

    /**
     * @brief Registruje nový objekt.
     * @param object Objekt, který se má zaregistrovat.
     */
    void registerObject(SceneObject * object){
        for(SceneObject * u : list) {
            if(u->get_id() == object->get_id()){
                qDebug("nelze pridat");
                return; // id already used
            }
        }

        list.push_back(object);
    }

    /**
     * @brief Odregistruje objekt.
     * @param id Id objektu, který se má odregistrovat. Pokud je ALL, odregistruje všechny objekty.
     * @param delete_all Pokud je true, dealokuje všechny objekty.
     * @return Odregistrovaný objekt.
     */
    SceneObject * unregisterObject(int id, bool delete_all = false){
        SceneObject * returnVal = nullptr;
        list.erase(remove_if(begin(list), end(list), [id,&returnVal,delete_all](SceneObject * u){
            if(id == ALL){
                if(delete_all){
                    delete u;
                }
                return true;
            }
            if(u->get_id() == id){
                returnVal = u;
                return true;
            }
            return false;
        }), end(list));
        return returnVal;
    }

    /**
     * @brief Zjistí, zda došlo ke kolizi s jiným objektem.
     * @param object Bot, který se má testovat.
     * @return True, pokud došlo ke kolizi.
     */
    bool collide(Bot * object);
};
