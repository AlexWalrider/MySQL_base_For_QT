#include "dialog.h"
#include "ui_dialog.h"
#include "database.h"
static Database database;
//show selected tab
void dialog::shower(int dig)
{
    ui->tabWidget->setCurrentIndex(dig);
    this->show();
}
dialog::dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    setWindowFlags(Qt::CustomizeWindowHint);
    setFixedSize(size());
}

dialog::~dialog()
{
    delete ui;
}

//hide button
void dialog::on_pushButton_clicked()
{
    this->hide();
}
//create request button
void dialog::on_pushButton_7_clicked()
{
    QString inter = QString::number(tempvar);
    QString state = "Введена";
    QString dateout = "Не выполнено";
    QString urgent = ui->comboBox_2->currentText();
    QString service = ui->comboBox->currentText();
    QString korpus = ui->comboBox_3->currentText();
    QString floor = ui->lineEdit_2->text();
    QString room = ui->lineEdit_3->text();
    QString issue = ui->lineEdit_5->text();
    QString explain = ui->lineEdit_7->text();
    QString invoker = usernamus;
    QString currentdat = QDateTime::currentDateTime().toString();
    QString rcomm =  "INSERT INTO TaskRequest (id,State,Urgent,JobService,Department,DepFloor,DepRoom,Issue,DateIn,DateOut,Invoker,Explainer) VALUES("+inter+", '"+state+"', '"+urgent+"', '"+service+"', '"+korpus+"', '"+floor+"', '"+room+"', '"+issue+"', '"+currentdat+"', '"+dateout+"', '"+invoker+"', '"+explain+"')";
    database.datareq(rcomm);
    this->hide();
    MessageBox(nullptr,L"Заявка размещена!",L"INFO", MB_OK);
    tabup = true;
}
//close request button
void dialog::on_pushButton_5_clicked()
{
    QString explzer = ui->lineEdit_8->text();
    if (explzer == "")explzer=explz;
    QString state = "Выполнено";
    QString invoker = usernamus;
    QString currentdat = QDateTime::currentDateTime().toString();
    QString rcomm =  "UPDATE TaskRequest SET JobCloser='"+invoker+"',Explainer='"+explzer+"',DateOut='"+currentdat+"',State='" + state + "' WHERE id = "+ qstemp;
    database.datareq(rcomm);
    this->hide();
    MessageBox(nullptr,L"Заявка закрыта!",L"INFO", MB_OK);
    tabup = true;
}
//problem request btton
void dialog::on_pushButton_8_clicked()
{
    QString explzer = ui->lineEdit_8->text();
    if (explzer == "")explzer=explz;
    QString state = "Проблема";
    QString invoker = usernamus;
    QString currentdat = QDateTime::currentDateTime().toString();
    QString rcomm =  "UPDATE TaskRequest SET JobCloser='"+invoker+"',Explainer='"+explzer+"',DateOut='"+currentdat+"',State='" + state + "' WHERE id = "+ qstemp;
    database.datareq(rcomm);
    this->hide();
    MessageBox(nullptr,L"Заявка закрыта!",L"INFO", MB_OK);
    tabup = true;
}
