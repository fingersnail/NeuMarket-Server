#include "widget.h"
#include <QApplication>


using namespace QJson;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    QVariantList j;
//    auto i = SystemManagementModule::getSingleInstance()->handleRequest(SystemManagementModule::QueryAllUser_Method, j);
//qDebug() << i;
    //    auto i = StockManagementModule::getSingleInstance()->queryAllStock();
//    QVariantList j;
//    auto k = PurchaseManagementModule::getSingleInstance()->handleRequest(PurchaseManagementModule::QueryAllStockPlan_Method, j);
//    qDebug() << k;
//    auto i = PersonnelManagementModule::getSingleInstance()->addSupplier("qqqqq", "qqqqq", "qqqqq"
//                                                                         , "qqqqqqqqqqq", "file:///C:/Users/John/Pictures/DBDX.jpg");
//    qDebug() << i;
//    auto i = StockManagementModule::getSingleInstance()->queryStockProductKindStatistic();
//    qDebug() << Utilities::vector2VariantList(i)[0].toString();
//    QVariantList j;
//        auto i = StockManagementModule::getSingleInstance()->handleRequest(StockManagementModule::QueryStockProductKindStatistic_Method, j);
//qDebug() << i;
//    QVariantList i;
//    i << 19;
//    QJson::Serializer s;
//    auto j = s.serialize(i);
//    auto k = ServerThread::respondRequest(j);
//    qDebug() << k;
//    auto i = PersonnelManagementModule::getSingleInstance()->modifyEmployee(5, -1, "54325", "54325", "54325", "54325", "54325", "54325");
//    QVariantList ii;
//    ii << 5 << -1 << true << "999" << "5" << "5" << "5" << true << "5" << "55" << "5";
//    auto i = PersonnelManagementModule::getSingleInstance()->handleRequest(PersonnelManagementModule::ModifyEmployee_Method, ii);
//    qDebug() << "fin";

    return a.exec();
}
