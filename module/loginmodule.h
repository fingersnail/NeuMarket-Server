#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "util/databasemediator.h"
#include "entity/user.h"
#include "abstractmodule.h"
#include "entity/loginuser.h"
#include <memory>
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"

using std::shared_ptr;
using std::make_shared;
using namespace QJson;

class LoginModule : public AbstractModule
{
public:
    enum LoginState {
        SUCCESS,
        USERNAME_WRONG,
        PASSWORD_WRONG,
    };
    enum LoginModule_Method {
        Validate_Method
    };
    QByteArray handleRequest(int methodName,
                             const QString &parameter1 = "", const QString &parameter2 = "",
                             const QString &parameter3 = "", const QString &parameter4 = "",
                             const QString &parameter5 = "", const QString &parameter6 = "",
                             const QString &parameter7 = "");
    shared_ptr<AbstractObject> validate(int employeeId, const QString &password);
    static LoginModule *getSingletonInstance();
private:
    LoginModule();
    LoginModule(const LoginModule&);
    static LoginModule *loginModule;
};

#endif // LOGINMODULE_H
