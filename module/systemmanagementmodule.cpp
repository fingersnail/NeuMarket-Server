#include "systemmanagementmodule.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"

using namespace QJson;

SystemManagementModule* SystemManagementModule::sm = new SystemManagementModule;

QByteArray SystemManagementModule::handleRequest(int methodName, const QString &parameter1, const QString &parameter2, const QString &parameter3, const QString &parameter4, const QString &parameter5, const QString &parameter6, const QString &parameter7)
{
    QByteArray sendMsg;
    bool excuteResult;
    QVector<shared_ptr<AbstractObject> > resultVector;
    shared_ptr<AbstractObject> resultObject;
    QVariantList variantList;
    Serializer serializer;
    switch (methodName) {
    case AddUser_Method:
        excuteResult = addUser(parameter1.toInt(), parameter2, parameter3.toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case DeleteUser_Method:
        excuteResult = deleteUser(parameter1.toInt());
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case ChangePassword_Method:
        excuteResult = changePassword(parameter1.toInt(), parameter2);
        variantList = Utilities::bool2VariantList(excuteResult);
        break;
    case QueryUserByEmployeeId_Method:
        resultObject = queryUserByEmployeeId(parameter1.toInt());
        variantList = Utilities::object2VariantList(resultObject);
        break;
    case QueryUserByName_Method:
        resultVector = queryUserByName(parameter1);
        variantList = Utilities::vector2VariantList(resultVector);
        break;
    case QueryAllUser_Method:
        resultVector = queryAllUser();
        variantList = Utilities::vector2VariantList(resultVector);
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

bool SystemManagementModule::addUser(int employeeId, const QString &password, int groupId)
{
    QString statement1 = QString("SELECT * FROM employee WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement1);
    if (query.next()) {
        QString name = query.value(3).toString();
        QString statement2 = QString("INSERT INTO user VALUES (\'%1\', \'%2\', \'%3\', \'%4\')").arg(
                    QString::number(employeeId), name, password, QString::number(groupId));
        DatabaseMediator::getSingleInstance()->executeSql(statement2);
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
