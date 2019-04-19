#include "mainwindow.h"
#include <QApplication>
#include "database.h"
static Database database;
int main(int argc, char *argv[])
{
    database.login_db();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
