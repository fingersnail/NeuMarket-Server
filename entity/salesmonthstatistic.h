#ifndef SALESMONTHSTATISTIC_H
#define SALESMONTHSTATISTIC_H

#include "abstractobject.h"
#include <QDate>

class SalesMonthStatistic : public AbstractObject
{
public:
    SalesMonthStatistic();
    QDate getMonth() const;
    void setMonth(const QDate &value);

    double getMoneyAmount() const;
    void setMoneyAmount(double value);
    QVariantList object2VariantList();
private:
    QDate month;
    double moneyAmount;
};

#endif // SALESMONTHSTATISTIC_H
