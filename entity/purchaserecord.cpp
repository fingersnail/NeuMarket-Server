#include "purchaserecord.h"

PurchaseRecord::PurchaseRecord()
{
}

int PurchaseRecord::getPurchaseId() const
{
    return purchaseId;
}

void PurchaseRecord::setPurchaseId(int purchaseId)
{
    this->purchaseId = purchaseId;
}

int PurchaseRecord::getProductId() const
{
    return productId;
}

void PurchaseRecord::setProductId(int productId)
{
    this->productId = productId;
}

int PurchaseRecord::getPlanEmployeeId() const
{
    return planEmployeeId;
}

void PurchaseRecord::setPlanEmployeeId(int planEmployeeId)
{
    this->planEmployeeId = planEmployeeId;
}

int PurchaseRecord::getPurchaseEmployeeId() const
{
    return purchaseEmployeeId;
}

void PurchaseRecord::setPurchaseEmployeeId(int purchaseEmployeeId)
{
    this->purchaseEmployeeId = purchaseEmployeeId;
}

int PurchaseRecord::getSupplierId() const
{
    return supplierId;
}

void PurchaseRecord::setSupplierId(int supplierId)
{
    this->supplierId = supplierId;
}

int PurchaseRecord::getQuantity() const
{
    return quantity;
}

void PurchaseRecord::setQuantity(int quantity)
{
    this->quantity = quantity;
}

double PurchaseRecord::getMoneyAmount() const
{
    return moneyAmount;
}

void PurchaseRecord::setMoneyAmount(double moneyAmount)
{
    this->moneyAmount = moneyAmount;
}

bool PurchaseRecord::getIsFinish() const
{
    return isFinish;
}

void PurchaseRecord::setIsFinish(bool isFinish)
{
    this->isFinish = isFinish;
}

QDate PurchaseRecord::getPurchaseDate() const
{
    return purchaseDate;
}

void PurchaseRecord::setPurchaseDate(const QDate &purchaseDate)
{
    this->purchaseDate = purchaseDate;
}

QString PurchaseRecord::getComment() const
{
    return comment;
}

void PurchaseRecord::setComment(const QString &comment)
{
    this->comment = comment;
}

QVariantList PurchaseRecord::object2VariantList()
{
    QVariantList variantList;
    variantList << purchaseId << productId << planEmployeeId << purchaseEmployeeId << supplierId << purchaseDate
                << quantity << moneyAmount << isFinish << comment;
    return variantList;
}
