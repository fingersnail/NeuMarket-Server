#include "productkindstatistic.h"

ProductKindStatistic::ProductKindStatistic()
{

}

QString ProductKindStatistic::getKind() const
{
    return kind;
}

void ProductKindStatistic::setKind(const QString &value)
{
    kind = value;
}

int ProductKindStatistic::getQuantity() const
{
    return quantity;
}

void ProductKindStatistic::setQuantity(int value)
{
    quantity = value;
}

QVariantList ProductKindStatistic::object2VariantList()
{
    QVariantList i;
    i << kind << quantity;
    return i;
}
