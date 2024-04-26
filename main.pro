# obecná konfigurace
QT += widgets

CONFIG += c++17
SOURCES = main.cpp



# objekt propojující gui i simulaci
HEADERS += link/mediator.hpp
HEADERS += link/Testing_object.h

SOURCES += link/mediator.cpp


# závislosti gui
HEADERS += gui/main_win.hpp
HEADERS += gui/scene.hpp
HEADERS += gui/list.hpp
HEADERS += gui/entry.hpp
HEADERS += gui/bot_entry.hpp
HEADERS += gui/ai_entry.hpp
HEADERS += gui/scene_entity.hpp
HEADERS += gui/movable_entity.hpp
HEADERS += gui/signed_texture.hpp
HEADERS += gui/libs.h

#SOURCES += gui/main_win.cpp
SOURCES += gui/scene.cpp


# závislosti simulace
HEADERS += sim/sim_data.hpp
HEADERS += sim/simulation.hpp











