#include "mainwindow.h"
#include <QApplication>
#include "global.h"

bool mode = false;
QString cur_file_name;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
