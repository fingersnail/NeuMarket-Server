#ifndef SALESMANAGEMENTMODULE_H
#define SALESMANAGEMENTMODULE_H

#include "abstractmodule.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "util/databasemediator.h"
#include "entity/user.h"
#include "abstractmodule.h"
#include "entity/loginuser.h"
#include <memory>
#include "entity/salesrecord.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"
#include "entity/saleskindstatistic.h"
#include "entity/salesmonthstatistic.h"

using std::shared_ptr;
using std::make_shared;
using namespace QJson;

class SalesManagementModule : public AbstractModule
{
public:
    enum SalesManagementModule_Method{
        QueryAllSales_Method,
        QuerySalesById_Method,
        QuerySalesByName_Method,
        AddSales_Method,
        DeleteSales_Method,
        ViewSalesStatics_Method,
        QuerySalesMonthStatistic_Method,
        QuerySalesKindStatistic_Method,
        QueryProductAllSales_Method
    };

    QByteArray handleRequest(int methodName, QVariantList i);
    static SalesManagementModule* getSingleInstance();
    QVector<shared_ptr<AbstractObject> > queryAllSales(QDate beginDate, QDate endDate);
    QVector<shared_ptr<AbstractObject> > queryProductAllSales(int productId, QDate beginDate, QDate endDate);
    QVector<shared_ptr<AbstractObject> > querySalesKindStatistic(QDate beginDate, QDate endDate);
    QVector<shared_ptr<AbstractObject> > querySalesMonthStatistic();
    QVector<shared_ptr<AbstractObject> > querySalesById(int productId);
    QVector<shared_ptr<AbstractObject> > querySalesByName(const QString &productName);
    bool addSales(int productId, int quantity, double moneyAmount);
    bool deleteSales(int salesId);

private:
    static SalesManagementModule *sm;
    SalesManagementModule(const SalesManagementModule&);
    SalesManagementModule();
    QVector<shared_ptr<AbstractObject> > viewSalesStatics(int productId);
    void queryResult2SalesVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2SalesObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
    void queryResult2SalesKindVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2SalesMonthStatisticObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
};

#endif // SALESMANAGEMENTMODULE_H
