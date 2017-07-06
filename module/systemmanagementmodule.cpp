#include "systemmanagementmodule.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"
#include "entity/userdetail.h"

using namespace QJson;

SystemManagementModule* SystemManagementModule::sm = new SystemManagementModule;

QByteArray SystemManagementModule::handleRequest(int methodName, QVariantList i)
{
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case AddUser_Method:
//        addUser(int employeeId, int groupId, bool gender,
//                                             const QString &name, const QString &tel,
//                                             const QString &address, const QString &email)
        excuteResult = addUser(i[0].toInt(), i[1].toInt(), i[2].toBool(), i[3].toString(), i[4].toString(), i[5].toString(), i[6].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteUser_Method:
        excuteResult = deleteUser(i[0].toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ChangePassword_Method:
        excuteResult = changePassword(i[0].toInt(), i[1].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ModifyUser_Method:
        excuteResult = modifyUser(i[0].toInt(), i[1].toInt(), i[2].toBool(), i[3].toString(), i[4].toString(), i[5].toString(), i[6].toString());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QueryUserByEmployeeId_Method:
        resultObject = queryUserByEmployeeId(i[0].toInt());
        variantList = Utilities::object2VariantList(resultObject);
        break;
    case QueryUserByName_Method:
        resultVector = queryUserByName(i[0].toString());
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryAllUser_Method:
        resultVector = queryAllUser();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryAllUserDetail_Method:
        resultVector = queryAllUserDetail();
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    default:
        break;
    }
    sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

SystemManagementModule *SystemManagementModule::getSingleInstance()
{
    return sm;
}

bool SystemManagementModule::addUser(int employeeId, int groupId, bool gender,
                                     const QString &name, const QString &tel,
                                     const QString &address, const QString &email)
{
    QString statement1 = QString("SELECT * FROM employee WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query.next()) {
        QString statement2 = QString("INSERT INTO user VALUES (\'%1\', \'%2\', \'%3\', \'%4\')").arg(
                    QString::number(employeeId), name
                    , "", QString::number(groupId));
        DatabaseMediator::getSingleInstance()->executeSql(statement2);
        QString statement3 = QString("UPDATE employee SET name = \'%1\', gender = \'%2\', "
                                     "telephone = \'%3\', group_id = \'%4\', address = \'%5\', "
                                     "email = \'%6\' WHERE employee_id = \'%7\'").arg(name, (gender ? "1" : "0"), tel, QString::number(groupId), address, email, QString::number(employeeId));
        DatabaseMediator::getSingleInstance()->executeSql(statement3);
        return 1;
    }
    return 0;
}

bool SystemManagementModule::modifyUser(int employeeId, int groupId, bool gender,
                                        const QString &name, const QString &tel,
                                        const QString &address, const QString &email)
{
    QString statement1 = QString("SELECT * FROM employee WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query.next()) {
        QString statement2 = QString("UPDATE user SET uname = \'%1\', \"group\" = \'%2\' "
                                     "WHERE employee_id = \'%3\'").arg(
                    name, QString::number(groupId), QString::number(employeeId));
        DatabaseMediator::getSingleInstance()->executeSql(statement2);
        QString statement3 = QString("UPDATE employee SET name = \'%1\', gender = \'%2\', "
                                     "telephone = \'%3\', group_id = \'%4\', address = \'%5\', "
                                     "email = \'%6\' WHERE employee_id = \'%7\'").arg(name, (gender ? "1" : "0"), tel, QString::number(groupId), address, email, QString::number(employeeId));
        DatabaseMediator::getSingleInstance()->executeSql(statement3);
        return 1;
    }
    return 0;

}

bool SystemManagementModule::deleteUser(int employeeId)
{
    QString statement = QString("DELETE FROM user WHERE employee_id = \'%1\'").arg(employeeId);
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

bool SystemManagementModule::changePassword(int employeeId, const QString &password)
{
    QString statement = QString("UPDATE user SET passwd = \'%1\' WHERE employee_id = \'%2\'").arg(
                password, QString::number(employeeId));
    bool ok;
    DatabaseMediator::getSingleInstance()->executeSql(statement, ok);
    return ok;//同上
}

shared_ptr<AbstractObject> SystemManagementModule::queryUserByEmployeeId(int employeeId)
{
    shared_ptr<AbstractObject> user;
    QString statement = QString("SELECT * FROM user WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2UserObject(query, user);
    return user;

}

QVector<shared_ptr<AbstractObject> > SystemManagementModule::queryUserByName(const QString &name)
{
    QVector<shared_ptr<AbstractObject> > users;
    QString statement = QString("SELECT * FROM user WHERE uname = \'%1\'").arg(name);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2UserVector(query, users);
    return users;
}

QVector<shared_ptr<AbstractObject> > SystemManagementModule::queryAllUser()
{
    QVector<shared_ptr<AbstractObject> > users;
    QString statement = "SELECT * FROM user";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2UserVector(query, users);
    return users;
}

QVector<shared_ptr<AbstractObject> > SystemManagementModule::queryAllUserDetail()
{
    QVector<shared_ptr<AbstractObject> > users;
    QString statement = "SELECT User.employee_id, Employee.name, Employee.telephone, "
                        "Employee.address, User.\"group\", Employee.email, Employee.gender "
                        "FROM Employee INNER JOIN User ON User.employee_id = Employee.employee_id";
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    queryResult2UserDetailVector(query, users);
    return users;
}

SystemManagementModule::SystemManagementModule()
{
}

void SystemManagementModule::queryResult2UserVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    User temp;
    while (query.next()) {
        temp.setEmployeeId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setPassword(query.value(2).toString());
        temp.setGroupId(query.value(3).toInt());
        vec.push_back(make_shared<User>(temp));
    }
}

void SystemManagementModule::queryResult2UserDetailVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec)
{
    UserDetail i;
    while (query.next()) {
        i.setEmployeeId(query.value(0).toInt());
        i.setEmployeeName(query.value(1).toString());
        i.setTelephone(query.value(2).toString());
        i.setAddress(query.value(3).toString());
        i.setGroupId(query.value(4).toInt());
        i.setEmail(query.value(5).toString());
        i.setGender(query.value(6).toBool());
        vec.push_back(make_shared<UserDetail>(i));
    }
}

void SystemManagementModule::queryResult2UserObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj)
{
    User temp;
    if(query.next()) {
        temp.setEmployeeId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setPassword(query.value(2).toString());
        temp.setGroupId(query.value(3).toInt());
    }
    obj = make_shared<User>(temp);
}
