#include <QObject>
#include <vector>
#include "scene_object.hpp"
#include "collision_engine/collision_engine.hpp"

class Bot;

#pragma once
using namespace std;

class ColisionAdministrator : public QObject {
Q_OBJECT
    CollisionEngine engine = CollisionEngine();
    vector<SceneObject*> list;
    Arena arena = Arena(ARENA_SIZE_X,ARENA_SIZE_Y);

public:

    // disable copy/move -- this is a Singleton
    ColisionAdministrator(const ColisionAdministrator&) = delete;
    ColisionAdministrator(ColisionAdministrator&&) = delete;
    ColisionAdministrator& operator=(const ColisionAdministrator&) = delete;
    ColisionAdministrator& operator=(ColisionAdministrator&&) = delete;

    ColisionAdministrator() : QObject(){};

    virtual ~ColisionAdministrator(){
        this->disconnect();
    };;
        
    static ColisionAdministrator &get_instance() {
        static ColisionAdministrator instance;
        return instance;
    }

    void registerObject(SceneObject * object){
        list.push_back(object);
    }
    SceneObject * unregisterObject(int id){

        list.erase(remove_if(begin(list), end(list), [id](SceneObject * u){
            if(u->get_id() == id){
                return true;
            }
            return false;
        }), end(list));
        return nullptr;
    }

    bool collide(int id,Bot * object);

};
