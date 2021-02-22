#include <QDebug>
#include <QApplication>

#include "include/mainwindow.h"
#include <unicorn/unicorn.h>
#include <capstone/capstone.h>
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    return 0;
}
