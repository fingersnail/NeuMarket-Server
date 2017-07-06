#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <QByteArray>
#include <QString>
#include <QVariantList>

class AbstractModule
{
public:
    AbstractModule();
    virtual QByteArray handleRequest(int methodName, QVariantList i) = 0;
};

#endif // ABSTRACTMODULE_H
