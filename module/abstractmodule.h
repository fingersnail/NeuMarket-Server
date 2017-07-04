#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <QByteArray>
#include <QString>

class AbstractModule
{
public:
    AbstractModule();
    virtual QByteArray handleRequest(int methodName,
                                     const QString &parameter1 = "", const QString &parameter2 = "",
                                     const QString &parameter3 = "", const QString &parameter4 = "",
                                     const QString &parameter5 = "", const QString &parameter6 = "",
                                     const QString &parameter7 = "") = 0;
};

#endif // ABSTRACTMODULE_H
