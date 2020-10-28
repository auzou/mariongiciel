/**
 * \file main.cpp
 * \brief Run APP
 * \author Auzou
 * \version 0.1
 * \date last update : 28/09/2007
 *
 * Run QApplication singleton \link https://doc.qt.io/qt-5/qapplication.html \endlink
 * Run \link mariongiciel::core::DirManagement::initDirsEnv() \endlink to ensure that the folder environment exists
 *
 */

#include <QApplication>
#include "gui/mainwindow.h"

#include "core/iomanagement.h"

/**
 * \fn int main (int argc, char *argv[])
 * \brief start the main components
 *
 * \param The arguments passed by the system
 * \return int - comes from QApplication::exec() which is 0 if exit() is called via quit()
 */

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    mariongiciel::core::DirManagement::initDirsEnv();
    mariongiciel::gui::MainWindow mainWindow;
    mainWindow.showMaximized();
    return app.exec();
}
