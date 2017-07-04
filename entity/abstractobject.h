#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QVariantList>

class AbstractObject
{
public:
    AbstractObject();
    //抽象接口提供对象与QVariantList的转换
    virtual QVariantList object2VariantList() = 0;
};

#endif // BASE_H
