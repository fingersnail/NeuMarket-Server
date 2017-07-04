#ifndef DATABASEMEDIATOR_H
#define DATABASEMEDIATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

class DatabaseMediator
{
public:
    static DatabaseMediator* getSingleInstance();
    QSqlQuery executeSql(const QString &sqlStatement);
    QSqlQuery executeSql(const QString &sqlStatement, bool &ok);

private:
    static DatabaseMediator *databaseMediator;
    QSqlDatabase db;
    DatabaseMediator();
    DatabaseMediator(const DatabaseMediator&);
};

#endif // DATABASEMEDIATOR_H
