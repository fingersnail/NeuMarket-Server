#include "purchasemanagementmodule.h"
#include "stockmanagementmodule.h"

PurchaseManagementModule* PurchaseManagementModule::pm = new PurchaseManagementModule;

QByteArray PurchaseManagementModule::handleRequest(int methodName, QVariantList i)
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
        resultVector = queryStockPlanByProductId(i[0].toInt());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case AddStockPlan_Method:
        excuteResult = addStockPlan(i[0].toInt(), i[1].toInt(), i[2].toInt(),
                i[3].toInt(), i[4].toDate(), i[5].toInt(), i[6].toDouble(),
                i[7].toBool(), i[8].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteStockPlan_Method:
        excuteResult = deleteStockPlan(i[0].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ExcutePurchaseStockPlan_Method:
        excuteResult = excutePurchaseStockPlan(i[0].toInt(), i[1].toInt(), i[2].toBool());
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
    QString statement = "SELECT PurchaseRecord.purchase_id, PurchaseRecord.product_id, PurchaseRecord.plan_employee_id, PurchaseRecord.purchase_employee_id, Supplier.name, PurchaseRecord.purchase_date, PurchaseRecord.quantity, PurchaseRecord.money_amount, PurchaseRecord.is_finish, PurchaseRecord.comment, Product.name FROM PurchaseRecord INNER JOIN Supplier ON PurchaseRecord.supplier_id = Supplier.supplier_id INNER JOIN Product ON PurchaseRecord.product_id = Product.product_id";
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

bool PurchaseManagementModule::addStockPlan(int productId, int planEmployeeId,
                                            int purchaseEmployeeId, int supplierId,
                                            QDate time, int quantity, double moneyAmount,
                                            bool isFinished, QString comment)
{
    int id = 0;
    QString statement1 = "SELECT MAX(purchase_id) AS LargestId FROM PurchaseRecord";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO PurchaseRecord "
                                 "VALUES (\'%1\', \'%2\', \'%3\', \'%4\', \'%5\', \'%6\', \'%7\', \'%8\', \'%9\', ").arg(
                QString::number(id), QString::number(productId), QString::number(planEmployeeId),
                QString::number(purchaseEmployeeId), QString::number(supplierId), time.toString("yyyy-MM-dd"),
                QString::number(quantity), QString::number(moneyAmount), (isFinished ? "1" : "0"))
            + QString("\'%1\')").arg(comment);
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

bool PurchaseManagementModule::excutePurchaseStockPlan(int purchaseId, int purchaseEmployeeId, bool isFinished)
{
    QString statement = QString("UPDATE PurchaseRecord SET purchase_employee_id = \'%1\', "
                                "is_finish = \'%2\' WHERE purchase_id = \'%3\'").arg(
                QString::number(purchaseEmployeeId),  (isFinished ? "1" : "0"), QString::number(purchaseId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    QString statement1 = QString("SELECT product_id, quantity FROM PurchaseRecord where purchase_id = \'%1\'").arg(purchaseId);
    auto i = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if(i.next()) {
        int productId = i.value(0).toInt();
        int quantity = i.value(1).toInt();
        if(isFinished) {
            StockManagementModule::getSingleInstance()->addStock(productId, quantity);
        } else {
            StockManagementModule::getSingleInstance()->deleteStock(productId, quantity);
        }
    }
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
        temp.setSupplierName(query.value(4).toString());
        temp.setPurchaseDate(query.value(5).toDate());
        temp.setQuantity(query.value(6).toInt());
        temp.setMoneyAmount(query.value(7).toDouble());
        temp.setIsFinish(query.value(8).toInt());
        temp.setComment(query.value(9).toString());
        temp.setProductName(query.value(10).toString());
        vec.push_back(make_shared<PurchaseRecord>(temp));
    }
}
