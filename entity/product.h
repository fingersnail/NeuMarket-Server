#ifndef PRODUCT_H
#define PRODUCT_H

#include "abstractobject.h"

class Product : public AbstractObject
{
public:
    Product();
    int getProductId() const;
    void setProductId(int productId);

    double getPrice() const;
    void setPrice(double price);

    QString getName() const;
    void setName(const QString &name);

    QString getPicture() const;
    void setPicture(const QString &picture);

    QString getDescription() const;
    void setDescription(const QString &description);

    QString getKind() const;
    void setKind(const QString &kind);

    int getInstockQuantity() const;
    void setInstockQuantity(int instockQuantity);

    QVariantList object2VariantList() override;

private:
    int productId;
    int instockQuantity;
    double price;
    QString name;
    QString picture;
    QString description;
    QString kind;
};

#endif // PRODUCT_H
