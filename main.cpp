/*
Name: Nate, Jake, Josh
Program: Card Game
Date: 6/6/25
Extra: GUI
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Collectable Card Game");
    // seed for random
    srand(time(NULL));
    return a.exec();
}
