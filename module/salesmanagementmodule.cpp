#include "salesmanagementmodule.h"
#include "stockmanagementmodule.h"

SalesManagementModule* SalesManagementModule::sm = new SalesManagementModule();


SalesManagementModule::SalesManagementModule()
{
}

QByteArray SalesManagementModule::handleRequest(int methodName, QVariantList i)
{
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case QueryAllSales_Method:
        resultVector = queryAllSales(QDate::fromString(i[0].toString(), "yyyy-MM-dd"), QDate::fromString(i[1].toString(), "yyyy-MM-dd"));
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryProductAllSales_Method:
        resultVector = queryProductAllSales(i[0].toInt(), QDate::fromString(i[1].toString(), "yyyy-MM-dd"), QDate::fromString(i[2].toString(), "yyyy-MM-dd"));
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QuerySalesById_Method:
        resultVector = querySalesById(i[0].toInt());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QuerySalesByName_Method:
        resultVector = querySalesByName(i[0].toString());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case AddSales_Method:
        excuteResult = addSales(i[0].toInt(), i[1].toInt(), i[2].toDouble());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteSales_Method:
        excuteResult = deleteSales(i[0].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QuerySalesKindStatistic_Method:
        resultVector = querySalesKindStatistic(QDate::fromString(i[0].toString(), "yyyy-MM-dd"), QDate::fromString(i[1].toString(), "yyyy-MM-dd"));
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QuerySalesMonthStatistic_Method:
        resultVector = querySalesMonthStatistic();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    default:
        break;
    }
    sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

SalesManagementModule *SalesManagementModule::getSingleInstance()
{
    return sm;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::queryAllSales(QDate beginDate, QDate endDate)
{
    QVector<shared_ptr<AbstractObject> > sales;
    QString statement = QString("SELECT SalesRecord.product_id, Product.name, SalesRecord.quantity, "
                        "SalesRecord.time, SalesRecord.money_amout FROM Product INNER JOIN "
                        "SalesRecord ON SalesRecord.product_id = Product.product_id "
                        "WHERE SalesRecord.time >= \'%1\' AND SalesRecord.time <= \'%2\'").arg(
                beginDate.toString("yyyy-MM-dd") + " 00:00:00.000", endDate.toString("yyyy-MM-dd") + " 23:59:59.999");
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesVector(query, sales);
    return sales;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::queryProductAllSales(int productId, QDate beginDate, QDate endDate)
{
    QVector<shared_ptr<AbstractObject> > sales;
    QString statement = QString("SELECT SalesRecord.product_id, Product.name, SalesRecord.quantity, "
                                "SalesRecord.time, SalesRecord.money_amout FROM Product INNER JOIN "
                                "SalesRecord ON SalesRecord.product_id = Product.product_id "
                                "WHERE SalesRecord.time >= \'%1\' AND SalesRecord.time <= \'%2\' "
                                "AND Product.product_id = \'%3\'").arg(
                beginDate.toString("yyyy-MM-dd") + " 00:00:00.000", endDate.toString("yyyy-MM-dd") + " 23:59:59.999", QString::number(productId));
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesVector(query, sales);
    return sales;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::querySalesKindStatistic(QDate beginDate, QDate endDate)
{
    QVector<shared_ptr<AbstractObject> > salesKind;
    QString statement = QString("SELECT sum(SalesRecord.money_amout), Product.kind FROM SalesRecord "
                                "INNER JOIN Product ON SalesRecord.product_id = Product.product_id "
                                "WHERE SalesRecord.time >= \'%1\' AND SalesRecord.time <= \'%2\' "
                                "GROUP BY Product.kind").arg(beginDate.toString("yyyy-MM-dd") + " 00:00:00.000", endDate.toString("yyyy-MM-dd") + " 23:59:59.999");
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesKindVector(query, salesKind);
    return salesKind;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::querySalesMonthStatistic()
{
    QVector<shared_ptr<AbstractObject> > salesmonth;
    QDate i = QDate::currentDate();
    QString year = i.toString("yyyy");
    for(int j = 1; j < 12; ++j) {
        shared_ptr<AbstractObject> s;
        QString month = QString::number(j);
        QString month1 = QString::number(j + 1);
        if(j <= 9) {
            month = QString("0").append(month);
        }
        if(j + 1 <= 9) {
            month1 = QString("0").append(month1);
        }
        QString statement = QString("SELECT sum(SalesRecord.money_amout), \'%1\' FROM SalesRecord "
                                    "WHERE SalesRecord.time >= \'%2\' AND SalesRecord.time < \'%3\'"
                                    ).arg(year + "-" + month + "-01", year + "-" + month + "-01", year + "-" + month1 + "-01");
        qDebug() << statement;
        QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
        queryResult2SalesMonthStatisticObject(query, s);
        salesmonth.push_back(s);
    }
    shared_ptr<AbstractObject> ss;
    int y = year.toInt() + 1;
    QString statement = QString("SELECT sum(SalesRecord.money_amout), \'%1\' FROM SalesRecord "
                                "WHERE SalesRecord.time >= \'%2\' AND SalesRecord.time < \'%3\'"
                                ).arg(year + "-12-01" , y + "-01-01");
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesMonthStatisticObject(query, ss);
    salesmonth.push_back(ss);
    return salesmonth;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::querySalesById(int productId)
{
    QVector<shared_ptr<AbstractObject> > sales;
    QString statement = QString("SELECT * FROM SalesRecord WHERE product_id = \'%1\'").arg(productId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesVector(query, sales);
    return sales;
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::querySalesByName(const QString &productName)
{
    QVector<shared_ptr<AbstractObject> > sales;
    QString statement = QString("SELECT SalesRecord.sales_id, SalesRecord.product_id, "
                                "SalesRecord.money_amout, SalesRecord.time FROM SalesRecord "
                                "INNER JOIN Product ON SalesRecord.product_id = Product.product_id "
                                "WHERE Product.name = \'%1\'").arg(productName);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesVector(query, sales);
    return sales;
}

bool SalesManagementModule::addSales(int productId, int quantity, double moneyAmount)
{
    int id = 0;
    QString statement1 = "SELECT MAX(sales_id) AS LargestId FROM SalesRecord";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO SalesRecord VALUES (\'%1\', \'%2\', \'%3\', \'%4\',"
                                 " \'%5\')").arg(
                QString::number(id), QString::number(productId), QString::number(quantity),
                QString::number(moneyAmount),
                QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    StockManagementModule::getSingleInstance()->deleteStock(productId, quantity);
    return ok;//同上
}

bool SalesManagementModule::deleteSales(int salesId)
{
    QString statement = QString("DELETE FROM SalesRecord WHERE sales_id = \'%1\'").arg(salesId);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

QVector<shared_ptr<AbstractObject> > SalesManagementModule::viewSalesStatics(int productId)
{
    QVector<shared_ptr<AbstractObject> > sales;
    QString statement = QString("SELECT SalesRecord.product_id, sum(SalesRecord.money_amout), "
                                "SalesRecord.time FROM SalesRecord WHERE SalesRecord.time > \'%1\' "
                                "GROUP BY SalesRecord.product_id").arg(productId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SalesVector(query, sales);
    return sales;
}

void SalesManagementModule::queryResult2SalesObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    SalesRecord temp;
    if (query.next()) {
        temp.setSalesId(query.value(0).toInt());
        temp.setProductId(query.value(1).toInt());
        temp.setMoneyAmount(query.value(2).toDouble());
        temp.setTime(query.value(3).toDateTime());
    }
    obj = make_shared<SalesRecord>(temp);
}

void SalesManagementModule::queryResult2SalesKindVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    SalesKindStatistic temp;
    while (query.next()) {
        temp.setMoneyAmount(query.value(0).toDouble());
        temp.setKind(query.value(1).toString());
        vec.push_back(make_shared<SalesKindStatistic>(temp));
    }
}

void SalesManagementModule::queryResult2SalesMonthStatisticObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    SalesMonthStatistic temp;
    if (query.next()) {
        temp.setMoneyAmount(query.value(0).toDouble());
        temp.setMonth(query.value(1).toDate());
    }
    obj = make_shared<SalesMonthStatistic>(temp);
}

void SalesManagementModule::queryResult2SalesVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    SalesRecord temp;
    while (query.next()) {
        temp.setProductId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setQuantity(query.value(2).toInt());
        temp.setTime(query.value(3).toDateTime());
        temp.setMoneyAmount(query.value(4).toDouble());
        vec.push_back(make_shared<SalesRecord>(temp));
    }
}
