#include "userdetail.h"

UserDetail::UserDetail()
{

}

int UserDetail::getEmployeeId() const
{
    return employeeId;
}

void UserDetail::setEmployeeId(int value)
{
    employeeId = value;
}

QString UserDetail::getEmployeeName() const
{
    return employeeName;
}

void UserDetail::setEmployeeName(const QString &value)
{
    employeeName = value;
}

QString UserDetail::getTelephone() const
{
    return telephone;
}

void UserDetail::setTelephone(const QString &value)
{
    telephone = value;
}

QString UserDetail::getAddress() const
{
    return address;
}

void UserDetail::setAddress(const QString &value)
{
    address = value;
}

int UserDetail::getGroupId() const
{
    return groupId;
}

void UserDetail::setGroupId(int value)
{
    groupId = value;
}

QString UserDetail::getEmail() const
{
    return email;
}

void UserDetail::setEmail(const QString &value)
{
    email = value;
}

bool UserDetail::getGender() const
{
    return gender;
}

void UserDetail::setGender(bool value)
{
    gender = value;
}

QVariantList UserDetail::object2VariantList()
{
    QVariantList i;
    i << employeeId << employeeName << telephone << address << groupId << email << gender;
    return i;
}
