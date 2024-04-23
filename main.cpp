#include <QtWidgets>
#include <QFileDialog>
#include <QString>
#include "main_win.hpp"

#include "Testing_object.h" //dbg



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   MainWindows window;

   Test_Probe * obj = new Test_Probe(); // tento objekt monitoruje eventy střídané mezi GUI a simulace

   return app.exec();
}