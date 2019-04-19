#include "database.h"

static QSqlDatabase datb = QSqlDatabase::addDatabase("QMYSQL", "datab");
static QSqlQuery    query(datb);

static QString host = "";
static QString namedb = "";
static QString nameusr = "";
static QString passdb = "";
//db login & open
void Database::login_db()
{
    datb.setHostName(host);
    datb.setDatabaseName(namedb);
    datb.setUserName(nameusr);
    datb.setPassword(passdb);
    if (!datb.open())MessageBox(nullptr,L"База данных недоступна!",L"MySQL", MB_OK);
}
//execute request
void Database::datareq(QString command)//
{
   query.exec(command);
}
//all table in 1 var(model)
QSqlQueryModel* Database::get_table_full(QString get_req)
{
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(get_req);
        query.exec(get_req);
        return model;
}
//idk what is dis
void Database::db_reader (int indexcols, int nexterdb)//int indexrows,
{

       if (nexterdb == 0)
       {
           query.first();
           for (int ct = 0; ct <= indexcols; ct++)
           {
               QString getreq = query.value(ct).toString();
           }
       }
       else
       {
           query.next();
           for (int ct = 0; ct <= indexcols; ct++)
           {
               QString getreq = query.value(ct).toString();
           }
       }

}
//database specified cell
QString Database::db_cell (int indexrow, int indexcols)
{
           query.first();
           for (int ct = 0; ct <= indexrow-1; ct++)
           {
               query.next();
           }
           QString getreq = query.value(indexcols).toString();
           return getreq;
}
//close database
void Database::close()
{
    datb.close();
}
//get row size of table in memory
int Database::dbrowsize()
{
    return query.size();
}
//get col size of table in memory
int Database::dbcolsize()
{
    int first = query.record().count();
    int second = first-1;
    return second;
}
//idk what is dis
void Database::db_getter_full (int indexrows, int indexcols)
{
    db_reader (indexcols,0);
    for (int ct = 0; ct <= indexrows-1; ct++)
    {
        db_reader (indexcols,1);
    }
}
