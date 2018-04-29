/*! \file      main.cpp
 *  \brief     BlockEditor application for creating and editing schemes
 *  \author    Matej Knazik
 *  \date      2018
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argv, char *args[])
{


    QApplication app(argv, args);
    MainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.show();

    return app.exec();
}
