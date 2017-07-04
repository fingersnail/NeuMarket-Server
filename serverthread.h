#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include "module/loginmodule.h"
#include "module/personnelmanagementmodule.h"
#include "qjson/include/qjson-qt5/parser.h"
#include "qjson/include/qjson-qt5/serializer.h"
#include "qjson/include/qjson-qt5/qobjecthelper.h"
#include "util/utilities.h"
#include "module/salesmanagementmodule.h"
#include "module/stockmanagementmodule.h"
#include "module/systemmanagementmodule.h"
#include "module/purchasemanagementmodule.h"

using namespace QJson;

class ServerThread : public QThread
{
    Q_OBJECT
public:
    enum ModuleName {
        Login_Module,
        Personnel_Management_Module,
        Sales_Management_Module,
        Purchase_Management_Module,
        System_Management_Module,
        Stock_Management_Module
    };
    ServerThread(int socketDecription, QObject *parent);
    void run();
    static QByteArray respondRequest(QByteArray &receivedMsg);
private:
    static QString parameter1;
    static QString parameter2;
    static QString parameter3;
    static QString parameter4;
    static QString parameter5;
    static QString parameter6;
    static QString parameter7;
    static int moduleName;
    static int methodName;
    QTcpSocket tcpSocket;
private slots:
    void handleRequest();
};

#endif // SERVERTHREAD_H
