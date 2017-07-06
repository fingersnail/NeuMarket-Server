#include "stockmanagementmodule.h"
#include <QVector>
#include "util/databasemediator.h"

StockManagementModule* StockManagementModule::sm = new StockManagementModule;

QByteArray StockManagementModule::handleRequest(int methodName, QVariantList i)
{
    qDebug() << "in";
    qDebug() << methodName;
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case QueryAllStock_Method:
        resultVector = queryAllStock();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryStockByProductId_Method:
        resultObject = queryStockByProductId(i[0].toInt());
        variantList = Utilities::object2VariantList(resultObject);
        break;
    case QueryStockByProductName_Method:
        resultVector = queryStockByProductName(i[0].toString());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case AddStock_Method:
        excuteResult = addStock(i[0].toInt(), i[1].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case AddNewProduct_Method:
        excuteResult = addNewProduct(i[0].toDouble(), i[1].toString(), i[2].toString(), i[3].toString(), i[4].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteStock_Method:
        excuteResult = deleteStock(i[0].toInt(), i[1].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ModifyStock_Method:
        excuteResult = modifyStock(i[0].toInt(), i[1].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteProduct_Method:
        excuteResult = deleteProduct(i[0].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QueryStockProductKindStatistic_Method:
        resultVector = queryStockProductKindStatistic();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case AddProduct_Method:
        excuteResult = addProduct(i[0].toDouble(), i[1].toString(), i[2].toString(), i[3].toString(), i[4].toInt(), i[5].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ModifyProduct_Method:
        excuteResult = modifyProduct(i[0].toInt(), i[1].toDouble(), i[2].toString(), i[3].toString(), i[4].toString(), i[5].toInt(), i[6].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    default:
        break;
    }
    sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

StockManagementModule *StockManagementModule::getSingleInstance()
{
    return sm;
}

QVector<shared_ptr<AbstractObject> > StockManagementModule::queryAllStock()
{
    QVector<shared_ptr<AbstractObject> > stocks;
    QString statement = "SELECT * FROM Product";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2ProductVector(query, stocks);
    return stocks;
}

shared_ptr<AbstractObject> StockManagementModule::queryStockByProductId(int productId)
{
    QString statement = QString("SELECT * FROM Product WHERE product_id = \'%1\'").arg(productId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    shared_ptr<AbstractObject> stock;
    queryResult2ProductObject(query, stock);
    return stock;
}

QVector<shared_ptr<AbstractObject> > StockManagementModule::queryStockByProductName(const QString &productName)
{
    QVector<shared_ptr<AbstractObject> > stocks;
    QString statement = QString("SELECT * FROM Product WHERE name = \'%1\'").arg(productName);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2ProductVector(query, stocks);
    return stocks;
}

bool StockManagementModule::addStock(int productId, int quantity)
{
    QString statement = QString("UPDATE Product SET instock_quantity = instock_quantity + %1 WHERE product_id = \'%2\'").arg(
                QString::number(quantity), QString::number(productId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool StockManagementModule::addNewProduct(double price, const QString &name, const QString &picture, const QString &description, const QString &kind)
{
    int id = 0;
    QString statement1 = "SELECT MAX(product_id) AS LargestId FROM Product";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO Product VALUES (\'%1\', \'%2\', \'%3\', \'%4\', \'%5\', "
                                 "\'%6\', \'%7\')").arg(
                QString::number(id), QString::number(price), name, picture, description, QString::number(0), kind);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    return ok;//同上
}

bool StockManagementModule::deleteStock(int productId, int quantity)
{
    QString statement = QString("UPDATE Product SET instock_quantity = instock_quantity - %1 WHERE product_id = \'%2\'").arg(
                QString::number(quantity), QString::number(productId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool StockManagementModule::modifyStock(int productId, int quantity)
{
    QString statement = QString("UPDATE Product SET instock_quantity = %1 WHERE product_id = \'%2\'").arg(
                QString::number(quantity), QString::number(productId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool StockManagementModule::deleteProduct(int productId)
{
    QString statement = QString("DELETE FROM Product WHERE product_id = \'%1\'").arg(productId);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool StockManagementModule::addProduct(double price, const QString &name, const QString &picture, const QString &description, int instockQuantity, const QString &kind)
{
    int id = 0;
    QString statement1 = "SELECT MAX(product_id) AS LargestId FROM Product";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO Product VALUES (\'%1\', \'%2\', \'%3\', \'%4\', \'%5\', "
                                 "\'%6\', \'%7\')").arg(
                QString::number(id), QString::number(price), name, picture, description, QString::number(instockQuantity), kind);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    return ok;//同上
}

bool StockManagementModule::modifyProduct(int productId, double price, const QString &name, const QString &picture, const QString &description, int instockQuantity, const QString &kind)
{
    QString statement = QString("UPDATE Product SET price = \'%1\', name = \'%2\', picture = \'%3\' "
                                ", description = \'%4\', instock_quantity = \'%5\', kind = \'%6\' "
                                "WHERE product_id = \'%7\'").arg(
               QString::number(price), name, picture, description, QString::number(instockQuantity), kind, QString::number(productId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

QVector<shared_ptr<AbstractObject> > StockManagementModule::queryStockProductKindStatistic()
{
    QVector<shared_ptr<AbstractObject> > j;
    QString statement = "SELECT Product.kind, sum(Product.instock_quantity) FROM Product GROUP BY Product.kind";
    QSqlQuery i = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2ProductKindStatisticVector(i, j);
    return j;
}

void StockManagementModule::queryResult2ProductVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    Product temp;
    while (query.next()) {
        temp.setProductId(query.value(0).toInt());
        temp.setPrice(query.value(1).toDouble());
        temp.setName(query.value(2).toString());
        temp.setPicture(query.value(3).toString());
        temp.setDescription(query.value(4).toString());
        temp.setInstockQuantity(query.value(5).toInt());\
        temp.setKind(query.value(6).toString());
        vec.push_back(make_shared<Product>(temp));
    }
}

void StockManagementModule::queryResult2ProductObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    Product temp;
    if (query.next()) {
        temp.setProductId(query.value(0).toInt());
        temp.setPrice(query.value(1).toDouble());
        temp.setName(query.value(2).toString());
        temp.setPicture(query.value(3).toString());
        temp.setDescription(query.value(4).toString());
        temp.setInstockQuantity(query.value(5).toInt());
        temp.setKind(query.value(6).toString());
    }
    obj = make_shared<Product>(temp);
}

void StockManagementModule::queryResult2ProductKindStatisticVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    ProductKindStatistic temp;
    while (query.next()) {
        temp.setKind(query.value(0).toString());
        temp.setQuantity(query.value(1).toInt());
        vec.push_back(make_shared<ProductKindStatistic>(temp));
    }
}
