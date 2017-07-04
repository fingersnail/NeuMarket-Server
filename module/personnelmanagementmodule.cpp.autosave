#include "personnelmanagementmodule.h"

PersonnelManagementModule* PersonnelManagementModule::pm = new PersonnelManagementModule;

PersonnelManagementModule::PersonnelManagementModule()
{
}

void PersonnelManagementModule::queryResult2SupplierVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    Supplier temp;
    while (query.next()) {
        temp.setSupplierId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setAddress(query.value(2).toString());
        temp.setPhone(query.value(3).toString());
        temp.setDescription(query.value(4).toString());
        temp.setPicutre(query.value(5).toString());
        vec.push_back(make_shared<Supplier>(temp));
    }
}

void PersonnelManagementModule::queryResult2SupplierObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    Supplier temp;
    if(query.next()) {
        temp.setSupplierId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setAddress(query.value(2).toString());
        temp.setPhone(query.value(3).toString());
        temp.setDescription(query.value(4).toString());
        temp.setPicutre(query.value(5).toString());
    }
    obj = make_shared<Supplier>(temp);
}

void PersonnelManagementModule::queryResult2EmployeeVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    Employee temp;
    while (query.next()) {
        temp.setEmployeeId(query.value(0).toInt());
        temp.setGroupId(query.value(1).toInt());
        temp.setGender(query.value(2).toString());
        temp.setName(query.value(3).toString());
        temp.setPhone(query.value(4).toString());
        temp.setAddress(query.value(5).toString());
        temp.setEmail(query.value(6).toString());
        vec.push_back(make_shared<Employee>(temp));
    }
}

void PersonnelManagementModule::queryResult2EmployeeObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    Employee temp;
    if (query.next()) {
        temp.setEmployeeId(query.value(0).toInt());
        temp.setGroupId(query.value(1).toInt());
        temp.setGender(query.value(2).toString());
        temp.setName(query.value(3).toString());
        temp.setPhone(query.value(4).toString());
        temp.setAddress(query.value(5).toString());
        temp.setEmail(query.value(6).toString());
    }
    obj = make_shared<Employee>(temp);
}

QByteArray PersonnelManagementModule::handleRequest(int methodName,
                                                    const QString &parameter1, const QString &parameter2,
                                                    const QString &parameter3, const QString &parameter4,
                                                    const QString &parameter5, const QString &parameter6,
                                                    const QString &parameter7)
{
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case QueryAllSupplier_Method:
        resultVector = queryAllSupplier();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QuerySupplierById_Method:
        resultObject = querySupplierById(parameter1.toInt());
        variantList = Utilities::object2VariantList(resultObject);
        break;
    case QuerySupplierByName_Method:
        resultVector = querySupplierByName(parameter1);
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case ModifySupplier_Method:
        excuteResult = modifySupplier(parameter1.toInt(), parameter2, parameter3, parameter4, parameter5, parameter6);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteSupplier_Method:
        excuteResult = deleteSupplier(parameter1.toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case AddSupplier_Method:
        excuteResult = addSupplier(parameter1, parameter2, parameter3, parameter4);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QueryAllEmployee_Method:
        resultVector = queryAllEmployee();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryEmployeeById_Method:
        resultObject = queryEmployeeById(parameter1.toInt());
        variantList = Utilities::object2VariantList(resultObject);
        break;
    case QueryEmployeeByName_Method:
        resultVector = queryEmployeeByName(parameter1);
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case ModifyEmployee_Method:
        excuteResult = modifyEmployee(parameter1.toInt(), parameter2.toInt(), parameter3, parameter4,
                                      parameter5, parameter6, parameter7);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteEmployee_Method:
        excuteResult = deleteEmployee(parameter1.toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case AddEmployee_Method:
        excuteResult = addEmployee(parameter1.toInt(), parameter2, parameter3, parameter4, parameter5,
                                   parameter6);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    default:
        break;
    }
    sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

PersonnelManagementModule *PersonnelManagementModule::getSingleInstance()
{
    return pm;
}

QVector<shared_ptr<AbstractObject> > PersonnelManagementModule::queryAllSupplier()
{
    QVector<shared_ptr<AbstractObject> > suppliers;
    QString statement = "SELECT * FROM Supplier";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SupplierVector(query, suppliers);
    return suppliers;
}

shared_ptr<AbstractObject> PersonnelManagementModule::querySupplierById(int supplierId)
{
    QString statement = QString("SELECT * FROM Supplier WHERE supplier_id = \'%1\'").arg(supplierId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    shared_ptr<AbstractObject> supplier;
    queryResult2SupplierObject(query, supplier);
    return supplier;
}

QVector<shared_ptr<AbstractObject> > PersonnelManagementModule::querySupplierByName(const QString &supplierName)
{
    QVector<shared_ptr<AbstractObject> > suppliers;
    QString statement = QString("SELECT * FROM Supplier WHERE name = \'%1\'").arg(supplierName);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2SupplierVector(query, suppliers);
    return suppliers;
}

bool PersonnelManagementModule::modifySupplier(int supplierId, const QString &name,
                                               const QString &address, const QString &phone,
                                               const QString &description, const QString &picture)
{
    QString statement = QString("UPDATE Supplier SET name = \'%1\', address = \'%2\', "
                                "phone = \'%3\', description = \'%4\', picture = \'%6\' "
                                "WHERE supplier_id = \'%5\'").arg(
                name, address, phone, description, QString::number(supplierId), picture);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//可以加入判断该supplierId是否存在
}

bool PersonnelManagementModule::deleteSupplier(int supplierId)
{
    QString s = QString("DELETE FROM Supplier WHERE supplier_id = \'%1\'").arg(supplierId);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(s, ok);
    return ok;//同上
}

bool PersonnelManagementModule::addSupplier(const QString &name, const QString &address,
                                            const QString &phone, const QString &description)
{
    int id = 0;
    QString statement1 = "SELECT MAX(supplier_id) AS LargestId FROM Supplier";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO Supplier VALUES (\'%1\', \'%2\', \'%3\', \'%4\',"
                                 " \'%5\', \'%6\')").arg(
                QString::number(id), name, address, phone, description, "");
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    return ok;//同上
}

QVector<shared_ptr<AbstractObject> > PersonnelManagementModule::queryAllEmployee()
{
    QVector<shared_ptr<AbstractObject> > employees;
    QString statement = "SELECT * FROM Employee";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2EmployeeVector(query, employees);
    return employees;
}


shared_ptr<AbstractObject> PersonnelManagementModule::queryEmployeeById(int employeeId)
{
    QString statement = QString("SELECT * FROM Employee WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    shared_ptr<AbstractObject> employee;
    queryResult2EmployeeObject(query, employee);
    return employee;
}

QVector<shared_ptr<AbstractObject> > PersonnelManagementModule::queryEmployeeByName(const QString &employeeName)
{
    QVector<shared_ptr<AbstractObject> > employees;
    QString statement = QString("SELECT * FROM Employee WHERE name = \'%1\'").arg(employeeName);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2EmployeeVector(query, employees);
    return employees;
}

bool PersonnelManagementModule::modifyEmployee(int employeeId, int groupId, const QString &gender,
                                               const QString &name, const QString &phone,
                                               const QString &address, const QString &email)
{
    QString statement = QString("UPDATE Employee SET group_Id = \'%1\', gender = \'%2\', "
                                "name = \'%3\', telephone = \'%4\', address = \'%5\', "
                                "email = \'%6\' WHERE employee_id = \'%7\'").arg(
                QString::number(groupId), gender, name, phone, address, email, QString::number(employeeId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool PersonnelManagementModule::deleteEmployee(int employeeId)
{
    QString statement = QString("DELETE FROM employee WHERE employee_id = \'%1\'").arg(employeeId);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool PersonnelManagementModule::addEmployee(int groupId, const QString &gender, const QString &name,
                                            const QString &phone, const QString &address,
                                            const QString &email)
{
    int id = 0;
    QString statement1 = "SELECT MAX(employee_id) AS LargestId FROM employee";
    QSqlQuery query1 = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query1.next()) {
        id = query1.value(0).toInt() + 1;
    }
    QString statement2 = QString("INSERT INTO employee VALUES (\'%1\', \'%2\', \'%3\', \'%4\', \'%5\', "
                                 "\'%6\', \'%7\')").arg(
                QString::number(id), QString::number(groupId), gender, name, phone, address, email);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement2, ok);
    return ok;//同上
}
