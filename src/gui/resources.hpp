/*********************************************************************
 * @file resources.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief objekt který načítá obrázky aby aplikace nezabírala tak moc paměti ram
 *
*********************************************************************/

#include <QObject>

/// enum typu zdroje (v tomto případe typ obrázku)
enum RESOURCE_INTERNAL_TYPE{
    AI_BOT_SELECTED_T,
    AI_BOT_T,
    MAN_BOT_SELECTED_T,
    MAN_BOT_T,
    BOX_SELECTED_T,
    BOX_T
};

/// SceneResources : Singleton obsahující načtené obrázky je implemntace flywheel. Obsahuje textury pro boty a bedny
class SceneResources : QObject {
private:
    QPixmap textures[6];
public:

    ///@cond z objektu vytvoří singletron 
    SceneResources(const SceneResources&) = delete;
    SceneResources(SceneResources&&) = delete;
    SceneResources& operator=(const SceneResources&) = delete;
    SceneResources& operator=(SceneResources&&) = delete;
    virtual ~SceneResources(){};
    /// @endcond

    /// konstruktor který načte všechy soubory a uloží si je
    SceneResources() : QObject(){
        textures[AI_BOT_SELECTED_T] = QPixmap("img/ai_bot-sel.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[AI_BOT_T] = QPixmap("img/ai_bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[MAN_BOT_SELECTED_T] = QPixmap("img/bot-sel.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[MAN_BOT_T] = QPixmap("img/bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[BOX_SELECTED_T] = QPixmap("img/box-sel.png").scaled(QSize(BOX_SIZE, BOX_SIZE));
        textures[BOX_T] = QPixmap("img/box.png").scaled(QSize(BOX_SIZE, BOX_SIZE));
        
    };

    /// vrátí texturu (protože QT textura je jen odkazem)
    QPixmap get_Texture(RESOURCE_INTERNAL_TYPE type){
        return textures[type];
    }

    /// vrátí instanci aby se dali volat funkce
    static SceneResources &get_instance() {
        static SceneResources instance;
        return instance;
    }

};