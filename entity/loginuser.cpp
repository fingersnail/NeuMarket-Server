#include "loginuser.h"

LoginUser::LoginUser() : groupId(0), status(0)
{
}

int LoginUser::getGroupId() const
{
    return groupId;
}

void LoginUser::setGroupId(int gruopId)
{
    this->groupId = gruopId;
}

QString LoginUser::getName() const
{
    return name;
}

void LoginUser::setName(const QString &name)
{
    this->name = name;
}

int LoginUser::getStatus() const
{
    return status;
}

void LoginUser::setStatus(int status)
{
    this->status = status;
}

QVariantList LoginUser::object2VariantList()
{
    QVariantList variantList;
    variantList << status << groupId;
    return variantList;
}
