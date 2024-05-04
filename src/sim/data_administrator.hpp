/*********************************************************************
 * @file data_administrator.hpp
 * @author Tomáš Foltyn (xfolty21)
 *
 * @brief Definice třídy DataAdministrator, která se stará o ukládání a načítání scény.
 *********************************************************************/

#include <QObject>
#include <vector>
#include "scene_object.hpp"
#include "box.hpp"
#include "AI_bot.hpp"
#include "MAN_Bot.hpp"
#include "collision_engine/collision_engine.hpp"
#include <fstream>

class Bot;

#pragma once
using namespace std;

/**
 * @class DataAdministrator
 * @brief Stará se o ukládání a načítání scény.
 * 
 * Udržuje seznam všech objektů. Umožňuje zaregistrovat nový objekt a načíst nebo uložit scénu.
 */
class DataAdministrator : public QObject {
Q_OBJECT
    /// Seznam všech objektů.
    vector<SceneObject*> list;

private:
    /**
     * @brief Odstraní mezery ze začátku řetězce.
     * @param s Řetězec, ze kterého se mají odstranit mezery.
     */
    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }


public:
    /**
     * @brief Registruje nový objekt.
     * @param Instance Objekt, který se má zaregistrovat.
     */
    void registerObject(SceneObject * object){
        for(SceneObject * u : list) {
            if(u->get_id() == object->get_id()){ 
                #if DEBUG_SAY
                qDebug("nelze pridat"); 
                #endif
                return; 
            } // id already used
        }
        list.push_back(object);
    }

    /**
     * @brief Odregistruje objekt.
     * @param id ID objektu, který se má odregistrovat. Pokud je ALL, odregistruje všechny objekty.
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
     * @brief Převede parametr na číslo.
     * @param str Parametr.
     * @return Číslo.
     */
    int resolveParam(string str){
        if(str.substr(0, 4) == "LEFT"){
            return 0;
        }else if(str.substr(0, 5) == "RIGHT"){
            return 1;
        }else{
            try {
                return std::stoi(str);
            }
            catch (...) {
                throw -1;
            }
        }
    }

    /**
     * @brief Načte scénu ze souboru.
     * @param path Cesta k souboru.
     * @return True, pokud se podařilo načíst scénu, jinak false.
     */
    bool load(std::string path){
        Mediator::get_instance().notify_simulation_controll(STOP);
        Mediator::get_instance().notify_DBG_draw_line(CLEAR_LINES);
        
        ifstream inputFile(path); 
        if(inputFile.fail()){
            Mediator::get_instance().notify_error_message(QString("Nemohu načíst soubor"));
            return false;
        }

        Mediator::get_instance().notify_unregistration(ALL);
        string line;
        try{
            // pro každou linku
            while (getline(inputFile, line)) { 
                ltrim(line);
                if(line == "" || line[0] == '#'){ continue; }

                size_t pos = 0;
                int iter = 0; 
                int param_num = 0;
                int param[10] = {0};
                ObjectType type;

                // pro každé slovo na lince
                while ((pos = line.find(" ")) != string::npos) {
                    string arg = line.substr(0, pos);
                    // první pozice je vždy typ
                    if(iter == 0){
                        if(arg == "AI_BOT"){ 
                            param_num = 6; // kolik chceme argumentů
                            type = AI_ROBOT;
                        }else if(arg == "MAN_BOT"){ 
                            param_num = 4;  // kolik chceme argumentů
                            type = MAN_ROBOT;
                        }else if(arg == "BOX"){ 
                            param_num = 3;  // kolik chceme argumentů
                            type = BOX;
                        }else{
                            throw -1;
                        }
                    }else{
                        if(iter > param_num ){ throw -1; } // chyba moc parametrů
                        param[iter-1] = resolveParam(arg); // načteme parametr
                    }

                    line.erase(0, pos + 1);
                    ltrim(line);

                    iter++;
                }
                param[iter-1] = resolveParam(line);
                if(iter != param_num){ throw -1; }
                Mediator::get_instance().notify_registartion(type, param[0], param[1] , param[2],param[3],param[4],param[5]);
            } 
        } catch(int e) {
            inputFile.close(); 
            Mediator::get_instance().notify_error_message(QString("Poškozený soubor!"));
        }
       
        inputFile.close(); 
        return true;
    }

    /**
     * @brief Uloží scénu do souboru.
     * @param path Cesta k souboru.
     * @return True, pokud se podařilo uložit scénu, jinak false.
     */
    bool save(std::string path){
        ofstream myfile;
        myfile.open(path);
        if (!myfile.is_open()) {
            Mediator::get_instance().notify_error_message(QString("Cant Save to File"));
            return false;
        }

        myfile << "#tento soubor obsahuje uloženou scénu, každý řádek reprezentuje jednu entitu ve formátu:" << endl;
        myfile << "#AI_BOT {X} {Y} {ROTATION} {SENCE_LENGHT} {COLIDE_ROTATION} {ROTATION_DIRECTION}" << endl;
        myfile << "#MAN_BOT {X} {Y} {ROTATION} {SENCE_LENGHT}" << endl;
        myfile << "#BOX {X} {Y} {ROTATION}" << endl;
        myfile << "# a samosebou řádek začínající # je ignorovaný, stejně jako řádek prázdný" << endl << endl;

        for(SceneObject * u : list) {

            switch (u->get_type()){
            case AI_ROBOT:
                myfile << "AI_BOT " << ((AIBot*)u)->get_position().x << " " << ((AIBot*)u)->get_position().y << " "
                       << ((AIBot*)u)->get_rotation() << " " << ((AIBot*)u)->get_collide_rotation_angle() << " " << ((AIBot*)u)->get_view() << " "
                       << (((AIBot*)u)->get_rotation_direction() ? "RIGHT" : "LEFT")<< endl;
                break;
            case MAN_ROBOT:
                myfile << "MAN_BOT " << ((MANBot*)u)->get_position().x << " " << ((MANBot*)u)->get_position().y << " " << ((MANBot*)u)->get_rotation()<< " " << ((MANBot*)u)->get_view() << endl;
                break;          
            case BOX:
                myfile << "BOX " << ((Box*)u)->get_position().x << " " << ((Box*)u)->get_position().y << " " << ((Box*)u)->get_rotation() << endl;
                break;
            }
        }
        myfile.close();
        return true;
    }

public slots:
    
    /**
     * @brief Provede operaci souboru.
     * @param file_operation Operace.
     * @param path Cesta k souboru.
     */
    void file_op(FileOP file_operation,QString path){
        if(file_operation == SAVE){
            save(path.toStdString());
        }else{
            load(path.toStdString());
        }
    };

public:

    DataAdministrator() : QObject(){
        Mediator::get_instance().subscribe_load_save(this, SLOT(file_op(FileOP, QString)));
    }
};
