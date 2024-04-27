#include <QtWidgets>
#include <QFileDialog>
#include <QString>

#include "gui/main_win.hpp"
#include "link/Testing_object.h"//dbg
#include "sim/simulation.hpp"



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   new GUI_Window(); // objekt který se stará o gui
   new Test_Probe(); // tento objekt monitoruje eventy střídané mezi GUI a simulace
   new Simulation();


   return app.exec();
}