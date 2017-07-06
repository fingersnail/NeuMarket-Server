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
    case rt_getAllProducts:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::QueryAllStock_Method;
        break;
    case rt_addWorker:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::AddEmployee_Method;
        break;
    case rt_changePositionState:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::ChangePositionState_Method;
        break;
    case rt_deleteWorker:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::DeleteEmployee_Method;
        break;
    case rt_saveWorker:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::ModifyEmployee_Method;
        break;
    case rt_addProduct:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::AddProduct_Method;
        break;
    case rt_saveProduct:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::ModifyProduct_Method;
        break;
    case rt_deleteProduct:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::DeleteProduct_Method;
        break;
    case rt_getAllRecords:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::QueryAllSales_Method;
        break;
    case rt_getSaleRecords2:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::QueryProductAllSales_Method;
        break;
    case rt_getProductName:
        moduleName = ServerThread::Stock_Management_Module;
        methodName = StockManagementModule::QueryStockByProductId_Method;
        break;
    case rt_addSaleRecord:
        moduleName = ServerThread::Sales_Management_Module;
        methodName = SalesManagementModule::AddSales_Method;
        break;
    case rt_getStuffMainInfo:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::QueryAllUser_Method;
        break;
    case rt_saveStuffMainInfo:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::ChangePassword_Method;
        break;
    case rt_getAllUsers:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::QueryAllUserDetail_Method;
        break;
    case rt_addUser:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::AddUser_Method;
        break;
    case rt_getOneUser:
        moduleName = ServerThread::Personnel_Management_Module;
        methodName = PersonnelManagementModule::QueryEmployeeById_Method;
        break;
    case rt_deleteUser:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::DeleteUser_Method;
        break;
    case rt_saveUser:
        moduleName = ServerThread::System_Management_Module;
        methodName = SystemManagementModule::ModifyUser_Method;
        break;
    default:
        break;
    }
}

void Utilities::variantList2Parameter(QVariantList &variantList, int &moduleName, int &methodName,
                                     QVariantList &jj)
{
    int i = variantList.size();
    for(int j = i + 1; j <= 8; ++j) {
        variantList << "";
    }
    int k = variantList[0].toInt();
    requstTypeConvertor(k, moduleName, methodName);
    for(int xx = 1; xx < i; ++xx) {
        jj << variantList[xx];
    }
}
