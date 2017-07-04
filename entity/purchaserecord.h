#ifndef PURCHASERECORD_H
#define PURCHASERECORD_H

#include "abstractobject.h"
#include <QDate>

class PurchaseRecord : public AbstractObject
{

public:
    PurchaseRecord();

    int getPurchaseId() const;
    void setPurchaseId(int purchaseId);

    int getProductId() const;
    void setProductId(int productId);

    int getPlanEmployeeId() const;
    void setPlanEmployeeId(int planEmployeeId);

    int getPurchaseEmployeeId() const;
    void setPurchaseEmployeeId(int purchaseEmployeeId);

    int getSupplierId() const;
    void setSupplierId(int supplierId);

    int getQuantity() const;
    void setQuantity(int quantity);

    double getMoneyAmount() const;
    void setMoneyAmount(double moneyAmount);

    bool getIsFinish() const;
    void setIsFinish(bool isFinish);

    QDate getPurchaseDate() const;
    void setPurchaseDate(const QDate &purchaseDate);

    QString getComment() const;
    void setComment(const QString &comment);

    QVariantList object2VariantList();
private:
    int purchaseId;
    int productId;
    int planEmployeeId;
    int purchaseEmployeeId;
    int supplierId;
    int quantity;
    double moneyAmount;
    bool isFinish;
    QDate purchaseDate;
    QString comment;
};

#endif // STOCK_H
