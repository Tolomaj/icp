#include "bot.hpp"

class MANBot : public Bot{
private:
    
public:
    MANBot(int id, Point position, int rotation, int view) : Bot(id,position,rotation,view){};
    ~MANBot(){

    };

    void update() override {
        move_and_colide();
        //todo
    };

};

