#include <QtWidgets>
#include <QFileDialog>
#include <QString>
#include "main_win.hpp"

#include "Testing_object.h" //dbg
#include "simulation.hpp"



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   MainWindows window;

   new Test_Probe(); // tento objekt monitoruje eventy střídané mezi GUI a simulace


   new Simulation();



   return app.exec();
}