#ifndef SALESKINDSTATISTIC_H
#define SALESKINDSTATISTIC_H

#include "abstractobject.h"

class SalesKindStatistic : public AbstractObject
{
public:
    SalesKindStatistic();

    QString getKind() const;
    void setKind(const QString &value);

    double getMoneyAmount() const;
    void setMoneyAmount(double value);

    QVariantList object2VariantList() override;
private:
    QString kind;
    double moneyAmount;
};

#endif // SALESKINDSTATISTIC_H
