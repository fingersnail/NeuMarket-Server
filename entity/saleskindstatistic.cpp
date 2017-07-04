#include "saleskindstatistic.h"

SalesKindStatistic::SalesKindStatistic()
{

}

QString SalesKindStatistic::getKind() const
{
    return kind;
}

void SalesKindStatistic::setKind(const QString &value)
{
    kind = value;
}

double SalesKindStatistic::getMoneyAmount() const
{
    return moneyAmount;
}

void SalesKindStatistic::setMoneyAmount(double value)
{
    moneyAmount = value;
}

QVariantList SalesKindStatistic::object2VariantList()
{
    QVariantList i;
    i << kind << moneyAmount;
    return i;
}
