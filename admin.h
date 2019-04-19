#ifndef ADMIN_H
#define ADMIN_H

#include "header.h"
#include "form.h"

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    int ider[50];
    bool authload = false;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void loadusr();
    void on_pushButton_5_clicked();
    QString md5er(QString getter);
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

private:
    Ui::Admin *ui;
    Form form;
};

#endif // ADMIN_H
