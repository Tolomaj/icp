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