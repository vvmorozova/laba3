#include "mainwindow.h"

#include <QApplication>

#include "complexnumber.h"
#include "quaternion.h"
#include "collection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
