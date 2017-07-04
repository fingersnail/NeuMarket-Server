#include "purchasemanagementmodule.h"

PurchaseManagementModule* PurchaseManagementModule::pm = new PurchaseManagementModule;

QByteArray PurchaseManagementModule::handleRequest(int methodName, const QString &parameter1, const QString &parameter2, const QString &parameter3, const QString &parameter4, const QString &parameter5, const QString &parameter6, const QString &parameter7)
{
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case QueryAllStockPlan_Method:
        resultVector = queryAllStockPlan();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryStockPlanByProductId_Method:
        resultVector = queryStockPlanByProductId(parameter1.toInt());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case AddStockPlan_Method:
        excuteResult = addStockPlan(parameter1.toInt(), parameter2.toInt(), parameter3.toInt(),
                                    parameter4.toInt(), parameter5.toDouble());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteStockPlan_Method:
        excuteResult = deleteStockPlan(parameter1.toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ExcutePurchaseStockPlan_Method:
        excuteResult = excutePurchaseStockPlan(parameter1.toInt(), parameter2.toInt(), parameter3);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QueryAllIsFinish_Method:
        resultVector = queryAllIsFinish();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    default:
        break;
    }
    sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

PurchaseManagementModule *PurchaseManagementModule::getSingleInstance()
{
    return pm;
}

QVector<shared_ptr<AbstractObject> > PurchaseManagementModule::queryAllStockPlan()
{
    QVector<shared_ptr<AbstractObject> > stockPlan;
    QString statement = "SELECT * FROM PurchaseRecord";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2PurchaseRecordVector(query, stockPlan);
    return stockPlan;
}

QVector<shared_ptr<AbstractObject> > PurchaseManagementModule::queryStockPlanByProductId(int productId)
{
    QVector<shared_ptr<AbstractObject> > stockPlan;
    QString statement = QString("SELECT * FROM PurchaseRecord WHERE PurchaseRecord.product_id = \'%1\'").arg(productId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2PurchaseRecordVector(query, stockPlan);
    return stockPlan;
}

bool PurchaseManagementModule::addStockPlan(int productId, int planEmployeeId, int supplierId,
                                            int quantity, double moneyAmount)
{
    int id = 0;
    QString statement1 = "SELECT MAX(purchase_id) AS LargestId FROM PurchaseRecord";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO PurchaseRecord(purchase_id, product_id, "
                                 "plan_employee_id, supplier_id, quantity, money_amount) "
                                 "VALUES (\'%1\', \'%2\', \'%3\', \'%4\', \'%5\', \'%6\')").arg(
                QString::number(id), QString::number(productId), QString::number(planEmployeeId),
                QString::number(supplierId), QString::number(quantity), QString::number(moneyAmount));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    return ok;//同上
}

bool PurchaseManagementModule::deleteStockPlan(int stockId)
{
    QString statement = QString("DELETE FROM PurchaseRecord WHERE purchase_id = \'%1\'").arg(stockId);
   bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return 1;//同上
}

bool PurchaseManagementModule::excutePurchaseStockPlan(int purchaseId, int purchaseEmployeeId, const QString &comment)
{
    QString statement = QString("UPDATE PurchaseRecord SET purchase_employee_id = \'%1\', purchase_date = \'%2\', "
                                "is_finish = \'%3\', comment = \'%4\' WHERE purchase_id = \'%5\'").arg(
                QString::number(purchaseEmployeeId),  QDate::currentDate().toString("yyyy-MM-dd"), "1", comment, QString::number(purchaseId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

QVector<shared_ptr<AbstractObject> > PurchaseManagementModule::queryAllIsFinish()
{
    QVector<shared_ptr<AbstractObject> > stockPlan;
    QString statement = "SELECT * FROM PurchaseRecord WHERE PurchaseRecord.is_finish = 1";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2PurchaseRecordVector(query, stockPlan);
    return stockPlan;
}

PurchaseManagementModule::PurchaseManagementModule()
{
}

void PurchaseManagementModule::queryResult2PurchaseRecordObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    PurchaseRecord temp;
    if (query.next()) {
        temp.setPurchaseId(query.value(0).toInt());
        temp.setProductId(query.value(1).toInt());
        temp.setPlanEmployeeId(query.value(2).toInt());
        temp.setPurchaseEmployeeId(query.value(3).toInt());
        temp.setSupplierId(query.value(4).toInt());
        temp.setPurchaseDate(query.value(5).toDate());
        temp.setQuantity(query.value(6).toInt());
        temp.setMoneyAmount(query.value(7).toDouble());
        temp.setIsFinish(query.value(8).toInt());
        temp.setComment(query.value(9).toString());
    }
    obj = make_shared<PurchaseRecord>(temp);
}

void PurchaseManagementModule::queryResult2PurchaseRecordVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    PurchaseRecord temp;
    while (query.next()) {
        temp.setPurchaseId(query.value(0).toInt());
        temp.setProductId(query.value(1).toInt());
        temp.setPlanEmployeeId(query.value(2).toInt());
        temp.setPurchaseEmployeeId(query.value(3).toInt());
        temp.setSupplierId(query.value(4).toInt());
        temp.setPurchaseDate(query.value(5).toDate());
        temp.setQuantity(query.value(6).toInt());
        temp.setMoneyAmount(query.value(7).toDouble());
        temp.setIsFinish(query.value(8).toInt());
        temp.setComment(query.value(9).toString());
        vec.push_back(make_shared<PurchaseRecord>(temp));
    }
}
