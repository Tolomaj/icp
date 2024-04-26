QT += widgets

HEADERS += main_win.hpp
HEADERS += scene.hpp
HEADERS += list.hpp
HEADERS += entry.hpp
HEADERS += bot_entry.hpp
HEADERS += ai_entry.hpp
HEADERS += Testing_object.h
HEADERS += scene_entity.hpp
HEADERS += simulation.hpp
HEADERS += movable_entity.hpp
HEADERS += sim_data.hpp

HEADERS += mediator.hpp


CONFIG += c++17
SOURCES = main.cpp
SOURCES += mediator.cpp



