#ifndef USER_H
#define USER_H

#include <QString>
#include "abstractobject.h"

class User : public AbstractObject
{
public:
    User();

    ~User();

    int getEmployeeId() const;
    void setEmployeeId(const int employeeId);

    int getGroupId() const;
    void setGroupId(const int groupId);

    QString getName() const;
    void setName(const QString& name);

    QString getPassword() const;
    void setPassword(const QString& password);

    QVariantList object2VariantList() override;

private:
    int employeeId, groupId;
    QString name, password;
};
#endif // USER_H
