#include "employee.h"

Employee::Employee() : employee_id(0), groupId(0)
{
}

Employee::~Employee()
{
}

int Employee::getEmployeeId() const
{
    return employee_id;
}

void Employee::setEmployeeId(const int employee_id)
{
    this->employee_id = employee_id;
}

int Employee::getGroupId() const
{
    return groupId;
}

void Employee::setGroupId(const int groupId)
{
    this->groupId = groupId;
}

bool Employee::getGender() const
{
    return gender;
}

void Employee::setGender(bool gender)
{
    this->gender = gender;
}

QString Employee::getName() const
{
    return name;
}

void Employee::setName(const QString &name)
{
    this->name = name;
}

QString Employee::getAddress() const
{
    return address;
}

void Employee::setAddress(const QString &address)
{
    this->address = address;
}

QString Employee::getPhone() const
{
    return phone;
}

void Employee::setPhone(const QString &phone)
{
    this->phone = phone;
}

QString Employee::getEmail() const
{
    return email;
}

void Employee::setEmail(const QString &email)
{
    this->email = email;
}

QVariantList Employee::object2VariantList()
{//id(int),name,tel(string),address,isPosition(bool),email,sex(bool)
    QVariantList variantList;
    variantList << employee_id << name << phone << address << isWorking << email << gender;
    return variantList;
}

bool Employee::getIsWorking() const
{
    return isWorking;
}

void Employee::setIsWorking(bool value)
{
    isWorking = value;
}
