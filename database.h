#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#endif // DATABASE_H

#include "header.h"


class Database {

    public:

    void login_db();
    void datareq(QString command);
    QSqlQueryModel* get_table_full(QString get_req);
    void db_reader (int indexcols, int nexterdb);
    QString db_cell (int indexrow, int indexcols);
    void close();
    int dbrowsize();
    int dbcolsize();
    void db_getter_full (int indexrows, int indexcols);
private:

   };
