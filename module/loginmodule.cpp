#include "loginmodule.h"

LoginModule* LoginModule::loginModule = new LoginModule();

LoginModule::LoginModule()
{
}

QByteArray LoginModule::handleRequest(int methodName,
                                      const QString &parameter1, const QString &parameter2,
                                      const QString &parameter3, const QString &parameter4, const QString &parameter5, const QString &parameter6, const QString &parameter7)
{
    Serializer serializer;
    shared_ptr<AbstractObject> resultObject = validate(parameter1.toInt(), parameter2);
    QVariantList variantList = resultObject->object2VariantList();
    QByteArray sendMsg = serializer.serialize(variantList);
    return sendMsg;
}

shared_ptr<AbstractObject> LoginModule::validate(int employeeId, const QString &password)
{
    QString statement = QString("SELECT * FROM main.User WHERE employee_id = \'%1\'").arg(employeeId);
    QSqlQuery query = DatabaseMediator::getSingleInstance()->executeSql(statement);
    User temp;
    if (query.next()) {
        temp.setEmployeeId(query.value(0).toInt());
        temp.setName(query.value(1).toString());
        temp.setPassword(query.value(2).toString());
        temp.setGroupId(query.value(3).toInt());
    }
    LoginUser tempLoginUser;
    tempLoginUser.setGroupId(temp.getGroupId());
    tempLoginUser.setName(temp.getName());
    if(temp.getEmployeeId() == employeeId && temp.getPassword() == password)
        tempLoginUser.setStatus(SUCCESS);
    else if(temp.getEmployeeId() == 0)
        tempLoginUser.setStatus(USERNAME_WRONG);
    else
        tempLoginUser.setStatus(PASSWORD_WRONG);
    return make_shared<LoginUser>(tempLoginUser);
}

LoginModule* LoginModule::getSingletonInstance()
{
    return loginModule;
}
