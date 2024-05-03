#include <QObject>

#pragma once

#define NONE -1

class FocusColector : public QObject {
Q_OBJECT
public:

    // disable copy/move -- this is a Singleton
    FocusColector(const FocusColector&) = delete;
    FocusColector(FocusColector&&) = delete;
    FocusColector& operator=(const FocusColector&) = delete;
    FocusColector& operator=(FocusColector&&) = delete;

    FocusColector() : QObject(){};

    virtual ~FocusColector(){
        this->disconnect();
    };;
        
    static FocusColector &get_instance() {
        static FocusColector instance;
        return instance;
    }

    // rregistrace pro odbět zmeny vybraného objektu
    void subscribe(QObject* subscriber, const char* slot){
        connect(this, SIGNAL( focus_object(int)), subscriber, slot);
    };   

    signals:
    //notifikace zmeny vybraného objektu
    void focus_object(int id);

};
