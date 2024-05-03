#include <QObject>

enum RESOURCE_INTERNAL_TYPE{
    AI_BOT_SELECTED_T,
    AI_BOT_T,
    MAN_BOT_SELECTED_T,
    MAN_BOT_T,
    BOX_SELECTED_T,
    BOX_T
};

// this is singleton fly wheel object containning all textures used by bots and boxes
class SceneResources : QObject {
private:
    QPixmap textures[6];
public:

    // disable copy/move -- this is a Singleton
    SceneResources(const SceneResources&) = delete;
    SceneResources(SceneResources&&) = delete;
    SceneResources& operator=(const SceneResources&) = delete;
    SceneResources& operator=(SceneResources&&) = delete;

    SceneResources() : QObject(){
        textures[AI_BOT_SELECTED_T] = QPixmap("img/ai_bot-sel.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[AI_BOT_T] = QPixmap("img/ai_bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[MAN_BOT_SELECTED_T] = QPixmap("img/bot-sel.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[MAN_BOT_T] = QPixmap("img/bot.png").scaled(QSize(BOT_SIZE, BOT_SIZE));
        textures[BOX_SELECTED_T] = QPixmap("img/box-sel.png").scaled(QSize(BOX_SIZE, BOX_SIZE));
        textures[BOX_T] = QPixmap("img/box.png").scaled(QSize(BOX_SIZE, BOX_SIZE));
        
    };

    QPixmap get_Texture(RESOURCE_INTERNAL_TYPE type){
        return textures[type];
    }

    virtual ~SceneResources(){};
        
    static SceneResources &get_instance() {
        static SceneResources instance;
        return instance;
    }



};