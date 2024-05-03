/*********************************************************************
 * @file list.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief List záznamů objektů které se nachází ve scéně
 *
*********************************************************************/

#include "libs.h"

#include "../link/mediator.hpp"
#include "entry.hpp"
#include "bot_entry.hpp"
#include "ai_entry.hpp"

/// makro prevence hlášení nepužité proměnné
#define UNUSED(x) (void)(x)
#define NONE -1

class List :public QScrollArea{ 
Q_OBJECT


private:
    QWidget * parent;
    QWidget* entryes;

public slots:

    /**
     * @brief Přidá záznam entity do listu
     * 
     * @param type typ objektu pro který vytváříme záznam (ovlivňuje jaký záznam bude vytvořen)
     * @param i id objektu kterému záznam patří
     * @param x [není použit]
     * @param y [není použit]
     * @param r [není použit]
     */
    void add_entry(ObjectType type, int i, int x, int y, int r){

        // protože jde o signál jsou zde navíc parametry
        UNUSED(x); UNUSED(y); UNUSED(r);

        switch (type) {
            case AI_ROBOT:
                entryes->layout()->addWidget(new AI_Entry(parent,i));
                break;
            case MAN_ROBOT:
                entryes->layout()->addWidget(new BOT_Entry(parent,i));
                break;
            case BOX:
                entryes->layout()->addWidget(new Entry(parent,i));
                break;
        } 
    }


public: 

    /**
     * @brief Vytvoří list a nastaví jeho vzhled
     * 
     * @param parent rodič kterému poté budou přiřazen záznamy
     */
    List(QWidget *parent = 0):QScrollArea(parent) {
        this->parent = parent;

        this->setMaximumSize(QSize(230, 16777215));
        this->setMinimumSize(QSize(220, 0));
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        this->setLineWidth(3);
        this->setWidgetResizable(true);

        entryes = new QWidget;
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        QVBoxLayout * layout = new QVBoxLayout(entryes);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(2);
        entryes->setLayout(layout);
        this->setWidget(entryes);

        Mediator::get_instance().subscribe_forvarded_registartion(this, SLOT(add_entry(ObjectType, int, int, int , int)));

    }

};