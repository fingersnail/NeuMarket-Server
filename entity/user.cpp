#include "user.h"

User::User() : employeeId(0), groupId(0)
{
}

User::~User()
{
}

int User::getEmployeeId() const
{
    return employeeId;
}

void User::setEmployeeId(const int employeeId)
{
    this->employeeId = employeeId;
}

int User::getGroupId() const
{
    return groupId;
}

void User::setGroupId(const int groupId)
{
    this->groupId = groupId;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &name)
{
    this->name = name;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &password)
{
    this->password = password;
}

QVariantList User::object2VariantList()
{
    QVariantList i;
    i << employeeId << name << password << groupId;
    return i;
}
