/*********************************************************************
 * @file libs.h
 * @author Ondřej Gross (xgross13)
 *
 * @brief Tento soubor obsahuje veškeré externí zavyslosti.
 *
 * je to jediný soubor ve kterém provádějte změny když dojde k porušení závyslostí knihoven
*********************************************************************/

#ifndef GUI_LIBS_FILE_WIN_H
#define GUI_LIBS_FILE_WIN_H

// knihovny mediatoru a zakladní vlastzosti simulace
#include "../link/simu_info.hpp"
#include "../link/mediator.hpp"

//qt knihovny
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QSlider>
#include <QtMath>

#endif