#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>
#include "abstractobject.h"

class Supplier : public AbstractObject
{
public:
    Supplier();

    ~Supplier();

    int getSupplierId() const;
    void setSupplierId(const int supplierId);

    QString getName() const;
    void setName(const QString& name);

    QString getAddress() const;
    void setAddress(const QString& address);

    QString getPhone() const;
    void setPhone(const QString& phone);

    QString getDescription() const;
    void setDescription(const QString& description);

    QVariantList object2VariantList() override;

    QString getPicutre() const;
    void setPicutre(const QString &picutre);

private:
    int supplierId;
    QString name, address, phone, description, picutre;
};

#endif // SUPPLIER_H
