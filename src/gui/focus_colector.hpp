/*********************************************************************
 * @file focus_colector.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief singleton který dává vědět scéně které objěkty a záznamy označit
*********************************************************************/
#include <QObject>

#pragma once

/// makro které říká že nic nemá být označeno
#define NONE -1

class FocusColector : public QObject {
Q_OBJECT
public:

    ///@cond z objektu vytvoří singletron 
    FocusColector(const FocusColector&) = delete;
    FocusColector(FocusColector&&) = delete;
    FocusColector& operator=(const FocusColector&) = delete;
    FocusColector& operator=(FocusColector&&) = delete;

    FocusColector() : QObject(){};

    virtual ~FocusColector(){
        this->disconnect();
    };
    /// @endcond
        
    /**
    * @brief    Vrací instanci přez krterou se přistupuje k metodám
    */
    static FocusColector &get_instance() {
        static FocusColector instance;
        return instance;
    }

    /**
     * @brief registrace pro odbět zmeny vybraného objektu
     * 
     * @param subscriber objekt který vlastní metodu
     * @param slot metoda volané při volání změny vybrání
     */
    void subscribe(QObject* subscriber, const char* slot){
        connect(this, SIGNAL( focus_object(int)), subscriber, slot);
    };   

    signals:
    /**
     * @brief notifikace zmeny vybraného objektu
     * 
     * @param id id entity která je vybrána
     */
    void focus_object(int id);

};
