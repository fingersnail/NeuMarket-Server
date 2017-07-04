#ifndef SALESRECORD_H
#define SALESRECORD_H

#include "abstractobject.h"
#include <QDateTime>

class SalesRecord : public AbstractObject
{
public:
    SalesRecord();

    int getSalesId() const;
    void setSalesId(int salesId);

    int getProductId() const;
    void setProductId(int productId);

    double getMoneyAmount() const;
    void setMoneyAmount(double moneyAmount);

    QDateTime getTime() const;
    void setTime(const QDateTime &time);

    int getQuantity() const;
    void setQuantity(int quantity);

    QVariantList object2VariantList();

private:
    int salesId, productId, quantity;
    double moneyAmount;
    QDateTime time;
};

#endif // SALESRECORD_H
