#ifndef STOCKMANAGEMENTMODULE_H
#define STOCKMANAGEMENTMODULE_H

#include "abstractmodule.h"
#include "entity/product.h"
#include <memory>
#include <QSqlQuery>
#include "entity/salesrecord.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"
#include "entity/productkindstatistic.h"

using std::shared_ptr;
using std::make_shared;
using namespace QJson;

class StockManagementModule : AbstractModule
{
public:
    enum StockManagementModule_Method {
        QueryAllStock_Method,
        QueryStockByProductId_Method,
        QueryStockByProductName_Method,
        AddStock_Method,
        AddNewProduct_Method,
        DeleteStock_Method,
        ModifyStock_Method,
        DeleteProduct_Method,
        QueryStockProductKindStatistic_Method
    };
    QByteArray handleRequest(int methodName,
                             const QString &parameter1 = "", const QString &parameter2 = "",
                             const QString &parameter3 = "", const QString &parameter4 = "",
                             const QString &parameter5 = "", const QString &parameter6 = "",
                             const QString &parameter7 = "") override;
    static StockManagementModule* getSingleInstance();
    QVector<shared_ptr<AbstractObject> > queryAllStock();
    shared_ptr<AbstractObject> queryStockByProductId(int productId);
    QVector<shared_ptr<AbstractObject> > queryStockByProductName(const QString &productName);
    bool addStock(int productId, int quantity);
    bool addNewProduct(double price, const QString &name, const QString &picture, const QString &description, const QString &kind);
    bool deleteStock(int productId, int quantity);
    bool modifyStock(int productId, int quantity);
    bool deleteProduct(int productId);
    QVector<shared_ptr<AbstractObject> > queryStockProductKindStatistic();
private:
    StockManagementModule() = default;
    StockManagementModule(const StockManagementModule&);
    static StockManagementModule *sm;
    void queryResult2ProductVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2ProductObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
    void queryResult2ProductKindStatisticVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
};

#endif // STOCKMANAGEMENTMODULE_H
