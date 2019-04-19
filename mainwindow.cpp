#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::starter()
{
    auth.show();
    this->hide();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QTimer *timer = new QTimer(this);
   timer->singleShot(1000, this, SLOT(starter()));
}
/////////////////
MainWindow::~MainWindow()
{
    delete ui;
}
/////////////////////////
