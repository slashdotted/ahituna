// This code is released in the Public Domain
// The Ahi Tuna! logo and icon (c)2017 Amos Brocco, amos.brocco@supsi.ch
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
