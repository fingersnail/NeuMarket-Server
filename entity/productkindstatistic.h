#ifndef PRODUCTKINDSTATISTIC_H
#define PRODUCTKINDSTATISTIC_H

#include "abstractobject.h"

class ProductKindStatistic : public AbstractObject
{
public:
    ProductKindStatistic();
    QString getKind() const;
    void setKind(const QString &value);

    int getQuantity() const;
    void setQuantity(int value);
    QVariantList object2VariantList();
private:
    QString kind;
    int quantity;
};

#endif // PRODUCTKINDSTATISTIC_H
