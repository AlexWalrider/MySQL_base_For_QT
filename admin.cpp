#include "admin.h"
#include "ui_admin.h"
#include "database.h"

static Database database;
//md5 gen string
QString Admin::md5er(QString getter)
{
    QByteArray passc = getter.toUtf8();
    QString passer = QString(QCryptographicHash::hash((passc),QCryptographicHash::Md5).toHex());
    return passer;
}
//load users
void Admin::loadusr()
{
    QString req = "SELECT id, Username FROM Authorization ORDER BY id ASC";
    database.datareq(req);
    int rowsize = database.dbrowsize();
    ui->comboBox->clear();
    for (int i=0; i <rowsize; i++)
    {
        ider[i] = database.db_cell(i,0).toInt();
        ui->comboBox->addItem(database.db_cell (i,1));
    }
    ui->comboBox->setCurrentIndex(0);
}
Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    ui->widget->hide();
    loadusr();
    if (database.db_cell (0,0) != "")ui->pushButton->setEnabled(false);
}

Admin::~Admin()
{
    delete ui;
}
//create db if nonex
void Admin::on_pushButton_clicked()
{
   QString req = "CREATE TABLE IF NOT EXISTS Authorization (id INTEGER UNIQUE PRIMARY KEY, Username VARCHAR(99), Password VARCHAR(99))";
   database.datareq(req);
   QString passer= md5er(ui->lineEdit->text());
   QString rcomm =  "INSERT INTO Authorization (id, Username, Password) VALUES(1, 'Admin','"+ passer +"')";
   database.datareq(rcomm);
   MessageBox(nullptr,L"Завершено!",L"INFO", MB_OK);
   loadusr();
}
//auth button
void Admin::on_pushButton_2_clicked()
{
    authload = true;
    this->hide();
}
//form button
void Admin::on_pushButton_3_clicked()
{
    form.usernamer = "Admin";
    form.setusr();
    form.showMaximized();
    this->hide();
}
//open admin form auth
void Admin::on_pushButton_4_clicked()
{
    QString passing = md5er(ui->lineEdit_2->text());
    QString req = "SELECT id,Username,Password FROM Authorization ORDER BY id ASC";
    database.datareq(req);
    QString passdbad = "202cb962ac59075b964b07152d234b70";
    if (database.db_cell (0,0) != "") passdbad = database.db_cell (0,2);
    if (passing == passdbad)
    {
        ui->widget->show();
        ui->lineEdit_2->hide();
        ui->pushButton_4->hide();
    }
    else MessageBox(nullptr,L"Ошибка!",L"INFO", MB_OK);
}
//add user btn
void Admin::on_pushButton_5_clicked()
{
    int combox = ui->comboBox->count();
    QString cominx = QString::number(ider[combox-1]+1);
    QString user= ui->lineEdit_3->text();
    user = user.toUtf8();
    bool chex = false;
    ////////////////////
    QString req = "SELECT id,Username FROM Authorization";
    database.datareq(req);
    int rowsize = database.dbrowsize();
    for (int i=0; i<rowsize; i++)
    {
       if (database.db_cell (i,1) == user)chex = true;
    }
    ////////////////////
    QString passer= md5er(ui->lineEdit_4->text());
    QString rcomm =  "INSERT INTO Authorization (id, Username, Password) VALUES("+cominx+", '"+user+"','"+ passer +"')";
    if (!chex)
    {
        database.datareq(rcomm);
        MessageBox(nullptr,L"Завершено!",L"INFO", MB_OK);
    }
    else MessageBox(nullptr,L"Пользователь уже существует!",L"INFO", MB_OK);
    loadusr();
}
//delete user
void Admin::on_pushButton_6_clicked()
{
    int combox = ui->comboBox->currentIndex();
    combox = ider[combox];
    QString cominx = QString::number(combox);
    QString rcomm = "DELETE FROM Authorization WHERE id="+ cominx;
    database.datareq(rcomm);
    MessageBox(nullptr,L"Завершено!",L"INFO", MB_OK);
    loadusr();
}
//update password
void Admin::on_pushButton_7_clicked()
{
    int combox = ui->comboBox->currentIndex();
    combox = ider[combox];
    QString cominx = QString::number(combox);
    QString passer= md5er(ui->lineEdit_5->text());
    QString rcomm =  "UPDATE Authorization SET Password='" + passer + "' WHERE id = "+ cominx;
    database.datareq(rcomm);
    MessageBox(nullptr,L"Завершено!",L"INFO", MB_OK);
    loadusr();
}
//create request table
void Admin::on_pushButton_8_clicked()
{
    QString req = "CREATE TABLE IF NOT EXISTS TaskRequest (id INTEGER UNIQUE PRIMARY KEY, State VARCHAR(50), Urgent VARCHAR(50), JobService VARCHAR(50), Department VARCHAR(50), DepFloor VARCHAR(50), DepRoom VARCHAR(50), Issue VARCHAR(300), DateIn VARCHAR(50), DateOut VARCHAR(50), Invoker VARCHAR(50), Explainer VARCHAR(50),JobCloser VARCHAR(50))";
    database.datareq(req);
    MessageBox(nullptr,L"Завершено!",L"INFO", MB_OK);
}
