#include "databasemediator.h"

DatabaseMediator* DatabaseMediator::databaseMediator = new DatabaseMediator();

DatabaseMediator::DatabaseMediator()
{
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("C:\\Users\\Kevin\\Desktop\\server\\supermarket.db");
     if(!db.open()) {
         qDebug() << "Cannot open Database: supermarket.db";
     }
}

DatabaseMediator *DatabaseMediator::getSingleInstance()
{
    return databaseMediator;
}

QSqlQuery DatabaseMediator::executeSql(const QString &sqlStatement)
{
    QSqlQuery query;
    query.exec(sqlStatement);
    return query;
}

QSqlQuery DatabaseMediator::executeSql(const QString &sqlStatement, bool &ok)
{
    QSqlQuery query;
    ok = query.exec(sqlStatement);
    return query;
}
