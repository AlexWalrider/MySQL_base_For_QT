#ifndef FORM_H
#define FORM_H
#include "header.h"
#include "dialog.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(QWidget *parent = nullptr);
    bool press = false;
    bool tabler = false;
    int indegz = 0;
    int indey = 0;
    QString usernamer = "";
    ~Form();
    void setusr();

private slots:
    void formupdater();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //////press/////
    void tableincr()
    {
       tableupd(indegz,indey,false);
    }
    void tabledecr()
    {
        tableupd(indegz,indey,true);
    }
    void contextable(const QPoint &pos)
    {
        if (true)
        {
        QMenu contextMenu(("Context menu"), this);
        QAction action1("Increment", this);
        QAction action2("Decrement", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(tableincr()));
        connect(&action2, SIGNAL(triggered()), this, SLOT(tabledecr()));
        contextMenu.addAction(&action1);
        contextMenu.addAction(&action2);
        contextMenu.exec(mapToGlobal(pos));
        }
    }

    ///////////////////////
    void on_tableView_pressed(const QModelIndex &index);
    void tableupd(int indexer1, int indexer2, bool incr);
    void tablegetterTR();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_tableView_2_pressed(const QModelIndex &index);
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Form *ui;
    dialog dig;
};

#endif // FORM_H
