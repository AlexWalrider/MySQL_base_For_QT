#ifndef AUTH_H
#define AUTH_H

#include "header.h"
#include "admin.h"
#include "form.h"

namespace Ui {
class Auth;
}

class Auth : public QWidget
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void chekex ();
    void authloader ();
private:
    Ui::Auth *ui;
    Admin adminex;
    Form form;
};

#endif // AUTH_H
