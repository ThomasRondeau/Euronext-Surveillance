#include "mainwindow.h"
#include "multipleViewsWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultipleViewsWindow w;
    w.show();
    return a.exec();
}