#include "auth.h"
#include "ui_auth.h"
#include "database.h"
static Database database;
//check if db exists
void Auth::chekex ()
{
    ui->comboBox->clear();
    QString req = "SELECT id, Username FROM Authorization ORDER BY id ASC";
    database.datareq(req);
    if (database.db_cell (0,0) == "")
    {
        MessageBox(nullptr,L"Ошибка, база данных отсутствует!",L"MySQL", MB_OK);
    }
    else
    {
        int rowsize = database.dbrowsize();
        for (int i=0; i <rowsize; i++) ui->comboBox->addItem(database.db_cell (i,1));
    }
}
//authloader
void Auth::authloader()
{
 if (adminex.authload)
 {
     chekex();
     this->show();
     adminex.authload = false;
 }
}
Auth::Auth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    setFixedSize(size());
    QTimer *timer = new QTimer(this);
    timer->singleShot(10, this, SLOT(chekex()));
    QTimer *timere = new QTimer(this);
    connect(timere, SIGNAL(timeout()), this, SLOT(authloader()));
    timere->start(500);
}
Auth::~Auth()
{
    delete ui;
}
//auth button
void Auth::on_pushButton_5_clicked()
{
        int numuser = ui->comboBox->currentIndex();
        QString usernamis = ui->comboBox->itemText(numuser);
        QString req = "SELECT id,Username,Password FROM Authorization ORDER BY id ASC";
        database.datareq(req);
        int comboindex = ui->comboBox->currentIndex();
        QString enterpass=ui->lineEdit_2->text();
        QByteArray passc = enterpass.toUtf8();
        enterpass = QString(QCryptographicHash::hash((passc),QCryptographicHash::Md5).toHex());
        QString dbpass = database.db_cell (comboindex,2);
        if (dbpass == enterpass)
        {
             form.usernamer = usernamis;
             form.setusr();
             form.showMaximized();
             this->hide();
        }
        else MessageBox(nullptr,L"Ошибка!",L"MySQL", MB_OK);
}
//admin form show
void Auth::on_pushButton_4_clicked()
{
    adminex.show();
    this->hide();
}
