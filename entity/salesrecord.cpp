#include "salesrecord.h"

int SalesRecord::getSalesId() const
{
    return salesId;
}

void SalesRecord::setSalesId(int salesId)
{
    this->salesId = salesId;
}

int SalesRecord::getProductId() const
{
    return productId;
}

void SalesRecord::setProductId(int productId)
{
    this->productId = productId;
}

double SalesRecord::getMoneyAmount() const
{
    return moneyAmount;
}

void SalesRecord::setMoneyAmount(double moneyAmount)
{
    this->moneyAmount = moneyAmount;
}

QDateTime SalesRecord::getTime() const
{
    return time;
}

void SalesRecord::setTime(const QDateTime &time)
{
    this->time = time;
}

int SalesRecord::getQuantity() const
{
    return quantity;
}

void SalesRecord::setQuantity(int quantity)
{
    this->quantity = quantity;
}

QVariantList SalesRecord::object2VariantList()
{
    QVariantList variantList;
    variantList << salesId << productId << quantity << moneyAmount << time.toString("yyyy-MM-dd HH:mm:ss.zzz");
    return variantList;
}

SalesRecord::SalesRecord()
{
}
