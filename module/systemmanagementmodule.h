#ifndef SYSTEMMANAGEMENTMODULE_H
#define SYSTEMMANAGEMENTMODULE_H

#include "abstractmodule.h"
#include "util/databasemediator.h"
#include <QSqlQuery>
#include "entity/user.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

class SystemManagementModule : AbstractModule
{
public:
    enum SystemManagementModule_Method {
        AddUser_Method,
        DeleteUser_Method,
        ChangePassword_Method,
        QueryUserByEmployeeId_Method,
        QueryUserByName_Method,
        QueryAllUser_Method,
        QueryAllUserDetail_Method,
        ModifyUser_Method
    };

   QByteArray handleRequest(int methodName, QVariantList i);
    static SystemManagementModule* getSingleInstance();
    //requesttype,employeeId,athority,sex,name,tel,address,email
    bool addUser(int employeeId, int groupId, bool gender, const QString &name,
                 const QString &tel, const QString &address, const QString &email);
    bool modifyUser(int employeeId, int groupId, bool gender, const QString &name,
                 const QString &tel, const QString &address, const QString &email);
    bool deleteUser(int employeeId);
    bool changePassword(int employeeId, const QString &password);
    shared_ptr<AbstractObject> queryUserByEmployeeId(int employeeId);
    QVector<shared_ptr<AbstractObject> > queryUserByName(const QString &name);
    QVector<shared_ptr<AbstractObject> > queryAllUser();
    QVector<shared_ptr<AbstractObject> > queryAllUserDetail();

private:
    static SystemManagementModule *sm;
    SystemManagementModule();
    SystemManagementModule(const SystemManagementModule&);
    void queryResult2UserVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2UserDetailVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2UserObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
};

#endif // SYSTEMMANAGEMENTMODULE_H
