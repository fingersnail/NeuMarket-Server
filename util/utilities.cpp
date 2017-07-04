#include "utilities.h"

Utilities::Utilities()
{
}

QVariantList Utilities::bool2VariantList(bool boolValue)
{
    QVariantList variantList;
    variantList << boolValue;
    return variantList;
}

QVariantList Utilities::vector2VariantList(QVector<shared_ptr<AbstractObject> > &ptrVector)
{
    QVariantList variantList;
    foreach (shared_ptr<AbstractObject> i, ptrVector) {
        variantList << i->object2VariantList();
    }
    return variantList;
}

QVariantList Utilities::object2VariantList(shared_ptr<AbstractObject> pointer)
{
    return pointer->object2VariantList();
}

void Utilities::requstTypeConvertor(int requestType, int &moduleName, int &methodName)
{
    switch (requestType) {
    case rt_addSupplier:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::AddSupplier_Method;
        break;
    case rt_deleteSupplier:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::DeleteSupplier_Method;
        break;
    case rt_getSupplierDetail:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::QueryEmployeeById_Method;
        break;
    case rt_getSupplierList:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::QueryAllSupplier_Method;
        break;
    case rt_listAllWorker:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::QueryAllEmployee_Method;
        break;
    case rt_login:
        moduleName = ServerThread::Login_Module;
        methodName = LoginModule::Validate_Method;
        break;
    case rt_getRepertoryStatistic:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::QueryStockProductKindStatistic_Method;
        break;
    case rt_getSaleCatagoryStatistic:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::QuerySalesKindStatistic_Method;
        break;
    case rt_getSaleRecords:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::QueryAllSales_Method;
        break;
    case rt_getSaleStatistic:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::QuerySalesMonthStatistic_Method;
        break;
    case rt_getStockPlans:
        moduleName = ServerThread::Purchase_Management_Module;
        methodName = PurchaseManagementModule::QueryAllStockPlan_Method;
        break;
    case rt_getSupplierNames:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::QueryAllSupplier_Method;
        break;
    case rt_savePlan:
        moduleName = ServerThread::Purchase_Management_Module;
        methodName = PurchaseManagementModule::AddStockPlan_Method;
        break;
    case rt_saveSupplier:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::ModifySupplier_Method;
        break;
    case rt_addPlan:
        moduleName = ServerThread::Purchase_Management_Module;
        methodName = PurchaseManagementModule::AddStockPlan_Method;
        break;
    case rt_deletePlan:
        moduleName = ServerThread::Purchase_Management_Module;
        methodName = PurchaseManagementModule::DeleteStockPlan_Method;
        break;
    case rt_changePlanState:
        moduleName = ServerThread::Purchase_Management_Module;
        methodName = PurchaseManagementModule::ExcutePurchaseStockPlan_Method;
        break;
    default:
        break;
    }
}

void Utilities::variantList2Parameter(QVariantList &variantList, int &moduleName, int &methodName,
                                      QString &parameter1, QString &parameter2, QString &parameter3,
                                      QString &parameter4, QString &parameter5, QString &parameter6,
                                      QString &parameter7)
{
    int i = variantList.size();
    for(int j = i + 1; j <= 8; ++j) {
        variantList << "";
    }
    int k = variantList[0].toInt();
    requstTypeConvertor(k, moduleName, methodName);
    parameter1 = variantList[1].toString();
    parameter2 = variantList[2].toString();
    parameter3 = variantList[3].toString();
    parameter4 = variantList[4].toString();
    parameter5 = variantList[5].toString();
    parameter6 = variantList[6].toString();
    parameter7 = variantList[7].toString();
}
