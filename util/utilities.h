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
        rt_login,//0
        //requesttype,workernum,password
        //loginstate,workertype
        //人事管理相关控制层
        rt_listAllWorker,//1
        //requesttype
        //employee_id,group_id,gender,name,telephone,address,email
        rt_getSupplierList,//2
        //requesttype
        //suppliername,phone,pic,id,addr,descrip
        rt_getSupplierDetail,//3
        //requesttype,Supplierid
        //suppliername,phone,pic,id,addr,descrip
        rt_getWorkerDetail,//4
        //requesttype,Workerid
        //name,telephone,gender,employee_id,address,email,group_id
        rt_saveWorker,//5
        //requesttype,id,athority=-1,sex,name,tel,address,email,isPosition
        //ok
        rt_deleteWorker,//6
        //requesttype,Workerid
        //ok
        rt_addWorker,//7
        //requesttype,authority,sex,name,tel,address,email,isPosition
        //ok
        rt_saveSupplier,//8
        //requesttype,id,suppliername,addr,phone,descrip,pic
        //ok
        rt_deleteSupplier,//9
        //requesttype,Supplierid
        //ok
        rt_addSupplier,//10
        //requesttype,suppliername,addr,phone,descrip,pic
        //ok
        rt_changePositionState,//11
        //requesttype,userId,isPosition
        //ok
        //销售相关控制层
        rt_getSaleStatistic,//12
        //requesttype
        //年月，销售额
        rt_getSaleCatagoryStatistic,//13
        //requesttype,startYMD,endYMD
        //商品类别，库存
        rt_getSaleRecords,//14
        //requesttype,startYMD,endYMD
        //记录id，商品id，数量，销售额，时间
        rt_getSaleRecords2,//15
        //requesttype,product_id,startYMD,endYMD
        //product_id,product_name,price,num,sale_time(string)
        rt_getAllRecords,//16
        //requesttype
        //product_id product_name price num sale_time(string)
        rt_addSaleRecord,//17
        //requesttype,product_id,num,price
        //ok
        rt_getProductName,//18
        //requesttype,product_id
        //Qstring,
        //库存相关控制层
        rt_getRepertoryStatistic,//19
        //requesttype
        //商品类别，库存量
        rt_getAllProducts,//20
        //requesttype
        //id(int), name, catagory(string), num ,price ,info ,image(string)
        rt_saveProduct,//21
        //requesttype,id(int),name,catagory(string),num,price,info,image(string)
        //ok
        rt_deleteProduct,//22
        //requesttype,id
        //ok
        rt_addProduct,//23
        //name catagory(string) num price info image(string)
        //ok
        //进货相关控制层
        rt_getStockPlans,//24
        //requesttype
        //purchase_id，product_id，plan_employee_id，purchase_employee_id,supplier_name，purchase_date，quantity，money_amount，is_finish，comment,product_name
        rt_getSupplierNames,//25
        //requesttype
        //SupplierId,SupplierNames
        rt_savePlan,//26
        //requesttype,purchase_id，product_id，supplier_id，purchase_date,quantity，money_amount，comment
        //ok
        rt_addPlan,//27
        //product_id,makeplanworkerid,supplier_id，purchase_date,quantity，money_amount，comment(备注)
        //ok
        rt_deletePlan,//28
        //requesttype,planId
        //ok
        rt_changePlanState,//29
        //requesttype,planId,doplanworkerid,isfinished
        //ok
        //系统管理相关控制层
        rt_getStuffMainInfo,//30
        //requesttype
        //id(int) name password(string)
        rt_saveStuffMainInfo, //31
        //requesttype,id(int) password(string)
        //ok
        rt_getAllUsers,//32
        //requesttype
        //id(int) name tel(string) address authority(int) email sex(bool)
        rt_saveUser,//33
        //requesttype,id,athority,sex,name,tel,address,email
        //ok
        rt_addUser,//34
        //requesttype,employeeId, athority,sex,name,tel,address,email
        //ok
        rt_deleteUser,//35
        //requesttype,user_id
        //ok
        rt_getOneUser,//36
        //requesttype,user_id
        //id(int) name tel(string) address authority(int) email sex(bool)
    };

    Utilities();
    static QVariantList bool2VariantList(bool boolValue);
    static QVariantList vector2VariantList(QVector<shared_ptr<AbstractObject> > &ptrVector);
    static QVariantList object2VariantList(shared_ptr<AbstractObject> pointer);
    static void requstTypeConvertor(int requestType, int &moduleName, int &methodName);
    static void variantList2Parameter(QVariantList &variantList, int &moduleName, int &methodName,
                                      QVariantList &jj);
};

#endif // UTILITIES_H
