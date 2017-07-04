#ifndef UTILITIES_H
#define UTILITIES_H

#include <QVariantList>
#include <QVector>
#include "entity/abstractobject.h"
#include <memory>
#include "module/loginmodule.h"
#include "module/personnelmanagementmodule.h"
#include "serverthread.h"

using std::shared_ptr;

class Utilities
{
public:
    enum RequestType{
            //登陆相关控制层
            rt_login,//loginstate,workertype
            //人事管理相关控制层
            rt_listAllWorker,//employee_id,group_id,gender,name,telephone,address,email
            rt_getSupplierList,//suppliername,phone,pic,id,addr,descrip
            rt_getSupplierDetail,//suppliername,phone,pic,id,addr,descrip
            rt_getWorkerDetail,//name,telephone,gender,employee_id,address,email,group_id
            rt_saveWorker,
            rt_deleteWorker,
            rt_addWorker,
            rt_saveSupplier,
            rt_deleteSupplier,
            rt_addSupplier,
            //销售相关控制层
            rt_getSaleStatistic,//年月，销售额
            rt_getSaleCatagoryStatistic,//商品类别，库存
            rt_getSaleRecords,//记录id，商品id，数量，销售额，时间
            //库存相关控制层
            rt_getRepertoryStatistic,//商品类别，库存量
            //进货相关控制层
            rt_getStockPlans,//purchase_id，product_id，plan_employee_id，purchase_employee_id，
                            //supplier_name，purchase_date，quantity，money_amount，is_finish，comment,product_name
            rt_getSupplierNames,//SupplierId,SupplierNames
            rt_savePlan,
            rt_addPlan,
            rt_deletePlan,
            rt_changePlanState,
        };


    Utilities();
    static QVariantList bool2VariantList(bool boolValue);
    static QVariantList vector2VariantList(QVector<shared_ptr<AbstractObject> > &ptrVector);
    static QVariantList object2VariantList(shared_ptr<AbstractObject> pointer);
    static void requstTypeConvertor(int requestType, int &moduleName, int &methodName);
    static void variantList2Parameter(QVariantList &variantList, int &moduleName, int &methodName,
                                      QString &parameter1, QString &parameter2,
                                      QString &parameter3, QString &parameter4,
                                      QString &parameter5, QString &parameter6,
                                      QString &parameter7);
};

#endif // UTILITIES_H
