#include "salesmonthstatistic.h"

SalesMonthStatistic::SalesMonthStatistic()
{

}

QDate SalesMonthStatistic::getMonth() const
{
    return month;
}

void SalesMonthStatistic::setMonth(const QDate &value)
{
    month = value;
}

double SalesMonthStatistic::getMoneyAmount() const
{
    return moneyAmount;
}

void SalesMonthStatistic::setMoneyAmount(double value)
{
    moneyAmount = value;
}

QVariantList SalesMonthStatistic::object2VariantList()
{
    QVariantList i;
    i << month << moneyAmount;
    return i;
}
