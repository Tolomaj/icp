/*********************************************************************
 * @file collider.hpp
 * @author Ondřej Gross (xgross13)
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definuje třídu Colider, která je základní třídou pro všechny typy koliderů.
 *********************************************************************/

#ifndef COL_COLIDER_H
#define COL_COLIDER_H

/**
 * @enum ColiderType
 * @brief Enumerace typů kolizních objektů.
 */
enum ColiderType{
    RECT,
    CIRCLE,
    ARENA,
    UNDEFINED,
};

/**
 * @class Colider
 * @brief Základní kolizní objekt.
 *
 * Je základní třídou pro všechny typy koliderů.
 */
class Colider{
protected:
    /// Typ kolizního objektu.
    ColiderType type = UNDEFINED;
public:
    /**
     * @brief Získává typ kolizního objektu.
     * @return Typ kolizního objektu.
     */
    ColiderType getType(){
        return type;
    }

    /**
     * @brief Vypisuje informace o kolizním objektu.
     */
    virtual void print() {

    };
};

#endif