#ifndef USERDETAIL_H
#define USERDETAIL_H

#include "abstractobject.h"

class UserDetail : public AbstractObject
{
public:
    UserDetail();
    int getEmployeeId() const;
    void setEmployeeId(int value);

    QString getEmployeeName() const;
    void setEmployeeName(const QString &value);

    QString getTelephone() const;
    void setTelephone(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    int getGroupId() const;
    void setGroupId(int value);

    QString getEmail() const;
    void setEmail(const QString &value);

    bool getGender() const;
    void setGender(bool value);

    QVariantList object2VariantList();
private:
    int employeeId;
    QString employeeName;
    QString telephone;
    QString address;
    int groupId;
    QString email;
    bool gender;
};

#endif // USERDETAIL_H
