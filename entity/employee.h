#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include "abstractobject.h"

class Employee : public AbstractObject
{
public:
    Employee();

    ~Employee();

    int getEmployeeId() const;
    void setEmployeeId(const int employee_id);

    int getGroupId() const;
    void setGroupId(const int groupId);

    bool getGender() const;
    void setGender(bool gender);

    QString getName() const;
    void setName(const QString& name);
    QString getAddress() const;
    void setAddress(const QString& address);

    QString getPhone() const;
    void setPhone(const QString& phone);

    QString getEmail() const;
    void setEmail(const QString& email);

    QVariantList object2VariantList() override;
    bool getIsWorking() const;
    void setIsWorking(bool value);

private:
    int employee_id, groupId;
    QString name, address, phone, email;
   bool gender, isWorking;
};
#endif // EMPLOYEE_H
