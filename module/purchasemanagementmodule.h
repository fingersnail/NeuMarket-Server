#ifndef PURCHASEMANAGEMENTMODULE_H
#define PURCHASEMANAGEMENTMODULE_H

#include "abstractmodule.h"
#include <memory>
#include "entity/purchaserecord.h"
#include <QSqlQuery>
#include <QVector>
#include "entity/abstractobject.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"

using std::shared_ptr;
using std::make_shared;
using namespace QJson;

class PurchaseManagementModule : public AbstractModule
{
public:
    enum PurchaseManagementModule_Method {
        QueryAllStockPlan_Method,
        QueryStockPlanByProductId_Method,
        AddStockPlan_Method,
        DeleteStockPlan_Method,
        ExcutePurchaseStockPlan_Method,
        QueryAllIsFinish_Method
    };
   QByteArray handleRequest(int methodName, QVariantList i);
    static PurchaseManagementModule* getSingleInstance();
    QVector<shared_ptr<AbstractObject> > queryAllStockPlan();
    QVector<shared_ptr<AbstractObject> > queryStockPlanByProductId(int productId);
    bool addStockPlan(int productId, int planEmployeeId, int purchaseEmployeeId, int supplierId,
                      QDate time, int quantity, double moneyAmount, bool isFinished,
                      QString comment);
    bool deleteStockPlan(int stockId);
    bool excutePurchaseStockPlan(int purchaseId, int purchaseEmployeeId, bool isFinished);
    QVector<shared_ptr<AbstractObject> > queryAllIsFinish();

private:
    static PurchaseManagementModule *pm;
    PurchaseManagementModule();
    PurchaseManagementModule(const PurchaseManagementModule&);
    void queryResult2PurchaseRecordVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2PurchaseRecordObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
};

#endif // PURCHASEMANAGEMENTMODULE_H
