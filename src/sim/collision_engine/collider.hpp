/*********************************************************************
 * @file collider.hpp
 * @author Ondřej Gross (xgross13)
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief komunikace mezi gui a simulací
 * Objekt který zajištuje komunikcai mezi gui a simulací pomocí notify funkcí které když jsou zavolány tak se provedou všechny funkce které byli nastaveny pomocí subscribe funkcí.
 *********************************************************************/

#ifndef COL_COLIDER_H
#define COL_COLIDER_H

enum ColiderType{
    RECT,
    CIRCLE,
    ARENA,
    UNDEFINED,
};

class Colider{
protected:
    ColiderType type = UNDEFINED;
public:
    ColiderType getType(){
        return type;
    }

    virtual void print() {

    };
};

#endif