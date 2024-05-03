#include "collision_administrator.hpp"
#include "bot.hpp"

using namespace std;

    bool ColisionAdministrator::collide(int id,Bot * object){
        qDebug("co to je ");

        for (auto & element : list) {
            if(element->get_id() == id){
                continue;
            }

            if( engine.collide(object->get_colider(),element->get_colider()) || engine.collide(object->get_radar(),element->get_colider()) ){
                #if DEBUG_DAW
                element->get_colider()->print();
                #endif
                return true;
            };
        }
        // kotrola jestli je v areně
        if( engine.collide(object->get_radar(),&arena) ){
            return true;
        };
        // kotrola jestli je v areně
        if( engine.collide(object->get_colider(),&arena) ){
            return true;
        };

        return false;
    };
