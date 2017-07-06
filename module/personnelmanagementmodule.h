#ifndef PERSONNELMANAGEMENTMODULE_H
#define PERSONNELMANAGEMENTMODULE_H

#include <QTcpSocket>
#include <QVector>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <memory>
#include <QString>
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/databasemediator.h"
#include "entity/supplier.h"
#include "entity/employee.h"
#include "entity/abstractobject.h"
#include "util/utilities.h"
#include "abstractmodule.h"

using namespace QJson;
using std::shared_ptr;
using std::make_shared;

class PersonnelManagementModule : public AbstractModule
{
public:
    enum PersonnelManagementModule_Method {
        QueryAllSupplier_Method,
        QuerySupplierById_Method,
        QuerySupplierByName_Method,
        ModifySupplier_Method,
        DeleteSupplier_Method,
        AddSupplier_Method,
        QueryAllEmployee_Method,
        QueryEmployeeById_Method,
        QueryEmployeeByName_Method,
        ModifyEmployee_Method,
        DeleteEmployee_Method,
        AddEmployee_Method,
        ChangePositionState_Method
    };
    QByteArray handleRequest(int methodName, QVariantList i);
    static PersonnelManagementModule* getSingleInstance();
    QVector<shared_ptr<AbstractObject> > queryAllSupplier();
    shared_ptr<AbstractObject> querySupplierById(int supplierId);
    QVector<shared_ptr<AbstractObject> > querySupplierByName(const QString &supplierName);
    bool modifySupplier(int supplierId, const QString &name, const QString &address, const QString &phone,
                        const QString &description, const QString &picture);
    bool deleteSupplier(int supplierId);
    bool addSupplier(const QString &name, const QString &address, const QString &phone,
                     const QString &description, const QString &picture);
    QVector<shared_ptr<AbstractObject> > queryAllEmployee();
    shared_ptr<AbstractObject> queryEmployeeById(int employeeId);
    QVector<shared_ptr<AbstractObject> > queryEmployeeByName(const QString &employeeName);
    bool modifyEmployee(int employeeId, int groupId, const QString &gender, const QString &name,
                        const QString &phone, const QString &address, const QString &email, const QString &isWorking);
    bool deleteEmployee(int employeeId);
    bool addEmployee(const QString &gender, const QString &name,
                     const QString &phone, const QString &address, const QString &email, const QString &isWorking);
    bool changePositionState(int employeeId, int status);
private:
    static PersonnelManagementModule *pm;
    PersonnelManagementModule();
    PersonnelManagementModule(const PersonnelManagementModule&);
    void queryResult2SupplierVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2SupplierObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
    void queryResult2EmployeeVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2EmployeeObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
};

#endif // PERSONNELMANAGEMENTMODULE_H
