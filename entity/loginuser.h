#ifndef LOGINUSER_H
#define LOGINUSER_H

#include "abstractobject.h"

class LoginUser : public AbstractObject
{
public:
    LoginUser();
    int getGroupId() const;
    void setGroupId(int gruopId);

    QString getName() const;
    void setName(const QString &name);

    int getStatus() const;
    void setStatus(int status);

    QVariantList object2VariantList() override;
private:
    int groupId, status;
    QString name;
};

#endif // LOGINUSER_H
