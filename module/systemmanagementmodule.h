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
        QueryAllUser_Method
    };

    QByteArray handleRequest(int methodName,
                             const QString &parameter1 = "", const QString &parameter2 = "",
                             const QString &parameter3 = "", const QString &parameter4 = "",
                             const QString &parameter5 = "", const QString &parameter6 = "",
                             const QString &parameter7 = "") override;
    static SystemManagementModule* getSingleInstance();
    bool addUser(int employeeId, const QString &password, int groupId); //最开始的想法是返回成功和失败，但好像也可以返回添加后的主键
    bool deleteUser(int employeeId);
    bool changePassword(int employeeId, const QString &password);
    shared_ptr<AbstractObject> queryUserByEmployeeId(int employeeId);
    QVector<shared_ptr<AbstractObject> > queryUserByName(const QString &name);
    QVector<shared_ptr<AbstractObject> > queryAllUser();

private:
    static SystemManagementModule *sm;
    SystemManagementModule();
    SystemManagementModule(const SystemManagementModule&);
    void queryResult2UserVector(QSqlQuery &query, QVector<shared_ptr<AbstractObject> > &vec);
    void queryResult2UserObject(QSqlQuery &query, shared_ptr<AbstractObject> &obj);
};

#endif // SYSTEMMANAGEMENTMODULE_H
