#include "mediator.hpp"



Mediator &Mediator::get_instance() {
    static Mediator instance;
    return instance;
}

void Mediator::subscribe_registartion(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_registartion(ObjectType)), subscriber, slot);
}

void Mediator::subscribe_load_save(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_send_save(FileOP ,QString)), subscriber, slot);
}


void Mediator::subscribe_unregistration(QObject* subscriber, const char* slot){
    connect(this, SIGNAL( notify_unregistration(int )), subscriber, slot);
}

void Mediator::subscribe_forvarded_registartion(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_forvarded_registartion(ObjectType , int )), subscriber, slot);
}

void Mediator::subscribe_states_changes(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_states_change(int ,RoboState)), subscriber, slot);
}

void Mediator::subscribe_move(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_move(int, int, int, int)), subscriber, slot);
}

void Mediator::subscribe_simulation_controll(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_simulation_controll(SimuControll)), subscriber, slot);
}

void Mediator::subscribe_bot_controll(QObject* subscriber, const char* slot){
    connect(this, SIGNAL(notify_bot_controll(int , ControllComand)), subscriber, slot);
}