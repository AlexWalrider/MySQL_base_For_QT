#include "form.h"
#include "ui_form.h"
#include "database.h"
static Database database;
//timer for upd
void Form::formupdater()
{
  if (dig.tabup)
  {
      tablegetterTR();
      dig.tabup = false;
  }
}
//set user field
void Form::setusr()
{
    ui->usernams->setText(usernamer);
    dig.usernamus = usernamer;
}
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(contextable(const QPoint &)));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(formupdater()));
    timer->start(500);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
}
Form::~Form()
{
    delete ui;
}
//get table 2
void Form::tablegetterTR()
{
    //////////////////////
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    QStringList verticalHeader;
    QString req = "SELECT * FROM TaskRequest ORDER BY id DESC";
    database.datareq(req);
    int iterb=0;
    int rowsize = database.dbrowsize();
    int colsize = database.dbcolsize();
    while (iterb != rowsize)
    {
            for (int itera=0;itera <= colsize;itera++)
                {
                QString zz = database.db_cell(iterb,itera);
                item = new QStandardItem(QString(zz));
                model->setItem(iterb, itera, item);
                ui->tableView_2->setModel(model);
                if (zz == "Выполнено") ui->tableView_2->model()->setData(ui->tableView_2->model()->index(iterb, 1, QModelIndex()), QBrush(Qt::green),Qt::BackgroundRole);
                if (zz == "Введена") ui->tableView_2->model()->setData(ui->tableView_2->model()->index(iterb, 1, QModelIndex()), QBrush(Qt::yellow),Qt::BackgroundRole);
                if (zz == "Проблема") ui->tableView_2->model()->setData(ui->tableView_2->model()->index(iterb, 1, QModelIndex()), QBrush(Qt::red),Qt::BackgroundRole);
                }
            iterb++;
    }
        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);
        model->setHeaderData(0,Qt::Horizontal, "№");
        model->setHeaderData(1,Qt::Horizontal, "Состояние");
        model->setHeaderData(2,Qt::Horizontal, "Срочность");
        model->setHeaderData(3,Qt::Horizontal, "Служба");
        model->setHeaderData(4,Qt::Horizontal, "Корпус");
        model->setHeaderData(5,Qt::Horizontal, "Этаж");
        model->setHeaderData(6,Qt::Horizontal, "Место");
        model->setHeaderData(7,Qt::Horizontal, "Неисправность");
        model->setHeaderData(8,Qt::Horizontal, "Дата ввода");
        model->setHeaderData(9,Qt::Horizontal, "Дата исполнения");
        model->setHeaderData(10,Qt::Horizontal, "Ввел");
        model->setHeaderData(11,Qt::Horizontal, "Примечание");
        model->setHeaderData(12,Qt::Horizontal, "Закрыл");
        ui->tableView_2->setModel(model);
        ui->tableView_2->resizeRowsToContents();
        ui->tableView_2->resizeColumnsToContents();
        ui->tableView_2->verticalHeader()->hide();

}
//tab0 table 0 update func
void Form::tableupd(int indexer1,int indexer2,bool incr)
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    int index1 = indexer1;
    int index2 = indexer2;
    QString row = QString::number(index1);
    QString col = QString::number(index2);
    QString value =  ui->tableView->model()->data(ui->tableView->model()->index(index1,index2)).toString();
    int valuer =  value.toInt();
    if (incr == false)valuer++;
    if (incr == true)valuer--;
    QString replacer = QString::number(valuer);
    int rowforstr = index1+1;
    QString rowcom = QString::number(rowforstr);
    QString rcomm =  "UPDATE TableCount SET "+ col +"q='" + replacer + "' WHERE id = "+ rowcom +"";
    database.datareq(rcomm);
    on_pushButton_clicked();
}
//tab0 table 0
void Form::on_pushButton_clicked()
{
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    QStringList verticalHeader;
    QString req = "SELECT * FROM TableCount";
    database.datareq(req);
    int iterb=0;
    int rowsize = database.dbrowsize();
    int colsize = database.dbcolsize();
    while (iterb != rowsize)
    {
            for (int itera=0;itera <= colsize;itera++)
                {
                QString zz = database.db_cell(iterb,itera);
                int chez = zz.toInt();
                item = new QStandardItem(QString(zz));
                model->setItem(iterb, itera, item);
                ui->tableView->setModel(model);
                if (chez >= 10)
                {
                    ui->tableView->model()->setData(ui->tableView->model()->index(iterb, itera,  QModelIndex()), QBrush(QColor(137, 237, 184)),Qt::BackgroundRole);
                }
                else
                {
                    ui->tableView->model()->setData(ui->tableView->model()->index(iterb, itera,  QModelIndex()), QBrush(Qt::green),Qt::BackgroundRole);
                }
                if (chez == 0)
                {
                    ui->tableView->model()->setData(ui->tableView->model()->index(iterb, itera,  QModelIndex()), QBrush(Qt::cyan),Qt::BackgroundRole);
                }
                ui->tableView->model()->setData(ui->tableView->model()->index(iterb, itera,  QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
               }
            iterb++;
    }
        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);
        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->hide();
        ui->tableView->verticalHeader()->hide();
}
//empty
void Form::on_pushButton_2_clicked()
{
}
//table index press
void Form::on_tableView_pressed(const QModelIndex &index)
{ 
indegz = index.row();
indey = index.column();
}
//1 tab
void Form::on_pushButton_3_clicked()
{
   QWidget::setWindowTitle ("Модуль размещения заявок");
   ui->tabWidget->setCurrentIndex(1);
   tablegetterTR();
}
//zero tab
void Form::on_pushButton_4_clicked()
{
    QWidget::setWindowTitle ("Test window");
    ui->tabWidget->setCurrentIndex(0);
}
//request reg
void Form::on_pushButton_7_clicked()
{
    QString needrow = ui->tableView_2->model()->data(ui->tableView_2->model()->index(0,0)).toString();
    int chex = needrow.toInt();
    dig.tempvar = chex+1;
    dig.shower(0);
}
//tab1 table1 index press
void Form::on_tableView_2_pressed(const QModelIndex &index)
{
    indegz = index.row();
    indey = index.column();
}
//remove request
void Form::on_pushButton_6_clicked()
{
    QString rownum = ui->tableView_2->model()->data(ui->tableView_2->model()->index(indegz,0)).toString();
    QString rcomm = "DELETE FROM TaskRequest WHERE id="+ rownum;
    database.datareq(rcomm);
    MessageBox(nullptr,L"Заявка удалена!",L"INFO", MB_OK);
    tablegetterTR();
}
//call close-problem form
void Form::on_pushButton_5_clicked()
{
    QString needID = ui->tableView_2->model()->data(ui->tableView_2->model()->index(indegz,0)).toString();
    dig.qstemp = needID;
    dig.explz = ui->tableView_2->model()->data(ui->tableView_2->model()->index(indegz,11)).toString();
    dig.shower(1);
}
