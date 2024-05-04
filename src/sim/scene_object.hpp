/*********************************************************************
 * @file scene_object.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu SceneObject, která je základní třídou pro všechny objekty ve scéně.
 *********************************************************************/

#include "../link/mediator.hpp"
#include <QObject>
#include "collision_engine/b_shapes.h"
#include "collision_engine/collider.hpp"

#pragma once

/**
 * @class SceneObject
 * @brief Základní třída pro všechny objekty ve scéně.
 */
class SceneObject : public QObject{
protected:
    /// Identifikátor objektu.
    int id;
    /// Rotace objektu.
    int rotation;
    /// Pozice objektu.
    Point position;
    /// Typ objektu.
    ObjectType type;
public:
    /**
     * @brief Konstruktor třídy SceneObject.
     * @param id Identifikátor objektu.
     */
    SceneObject(int id) : QObject(){
        this->id = id;
    }

    /**
     * @brief Získává rotaci objektu.
     * @return Rotace objektu.
     */
    int get_rotation(){
        return rotation;
    }

    /**
     * @brief Získává pozici objektu.
     * @return Pozice objektu.
     */
    Point get_position(){
        return position;
    }

    /**
     * @brief Získává identifikátor objektu.
     * @return Identifikátor objektu.
     */
    int get_id(){
        return id;
    }

    /**
     * @brief Získává typ objektu.
     * @return Typ objektu.
     */
    ObjectType get_type(){
        return type;
    }
    
    virtual Colider * get_colider() = 0;
};

