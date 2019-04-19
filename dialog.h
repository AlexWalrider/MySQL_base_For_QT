#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>


namespace Ui {
class dialog;
}

class dialog : public QWidget
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();
    int digger = 0;
    QString usernamus = "";
    int tempvar = 0;
    QString qstemp = "";
    bool tabup = false;
    QString explz = "";
    void shower(int dig);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
