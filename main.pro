# -------- obecná konfigurace ----------------- #
QT += widgets

CONFIG += c++17
SOURCES = main.cpp


# ----- objekt propojující gui i simulaci ----- #
HEADERS += link/mediator.hpp
HEADERS += link/Testing_object.h

SOURCES += link/mediator.cpp


# --------------- závislosti gui -------------- #
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
HEADERS += gui/focus_colector.hpp
HEADERS += gui/property_picker.hpp
HEADERS += gui/signed_slider.hpp

SOURCES += gui/scene.cpp
SOURCES += gui/main_win.cpp

#------------ collision_engine ----------------- #

HEADERS += sim/collision_engine/b_shapes.h
HEADERS += sim/collision_engine/arena.hpp
HEADERS += sim/collision_engine/circle.hpp
HEADERS += sim/collision_engine/arena.hpp
HEADERS += sim/collision_engine/rect.hpp
HEADERS += sim/collision_engine/collider.hpp
HEADERS += sim/collision_engine/collision_engine.hpp




# ------------ závislosti simulace ------------ #
HEADERS += sim/simulation.hpp











