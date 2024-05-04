/*********************************************************************
 * @file collision_administrator.cpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Implementace třídy ColisionAdministrator, která se stará o detekci kolizí.
 *********************************************************************/

#include "collision_administrator.hpp"
#include "bot.hpp"

using namespace std;

    bool ColisionAdministrator::collide(Bot * object){
        qDebug("co to je ");

        for (auto & element : list) {
            if(element->get_id() == object->get_id()){
                continue;
            }

            // kontrola se botovo tělo s jiným objektem, který není Box
            if((dynamic_cast<Box*>(element) == nullptr && CollisionEngine::does_collide(object->get_colider(),element->get_colider())) ||
                CollisionEngine::does_collide(object->get_radar(),element->get_colider()) ){
                #if DEBUG_DAW
                element->get_colider()->print();
                #endif
                return true;
            };
        }
        // kotrola jestli je v areně
        if(CollisionEngine::does_collide(object->get_radar(),&arena) ){
            return true;
        };
        // kotrola jestli je v areně
        if(CollisionEngine::does_collide(object->get_colider(),&arena) ){
            return true;
        };

        return false;
    };
