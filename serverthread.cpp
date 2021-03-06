#include "serverthread.h"

int ServerThread::methodName = 0;
int ServerThread::moduleName = 0;
QString ServerThread::parameter1 = "";
QString ServerThread::parameter2 = "";
QString ServerThread::parameter3 = "";
QString ServerThread::parameter4 = "";
QString ServerThread::parameter5 = "";
QString ServerThread::parameter6 = "";
QString ServerThread::parameter7 = "";

ServerThread::ServerThread(int socketDecription, QObject *parent) : QThread(parent)
{
    tcpSocket.setSocketDescriptor(socketDecription);
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(handleRequest()));
}

void ServerThread::run()
{
    exec();
}

QByteArray ServerThread:: respondRequest(QByteArray &receivedMsg)
{
    QByteArray sendMsg;
    Parser p;
    QVariantList i = p.parse(receivedMsg).toList();
    QVariantList j;
    Utilities::variantList2Parameter(i, moduleName, methodName, j);
    qDebug() << moduleName;
    qDebug() << methodName;

    switch (moduleName) {
    case ModuleName::Login_Module:
        sendMsg = LoginModule::getSingletonInstance()->handleRequest(methodName, j);
        break;
    case ModuleName::Personnel_Management_Module:
        sendMsg = PersonnelManagementModule::getSingleInstance()->handleRequest(methodName, j);
        break;
    case ModuleName::Sales_Management_Module:
        sendMsg = SalesManagementModule::getSingleInstance()->handleRequest(methodName, j);
        break;
    case ModuleName::Purchase_Management_Module:
        sendMsg = PurchaseManagementModule::getSingleInstance()->handleRequest(methodName, j);
        break;
    case ModuleName::System_Management_Module:
        sendMsg = SystemManagementModule::getSingleInstance()->handleRequest(methodName, j);
        break;
    case ModuleName::Stock_Management_Module:
        sendMsg = StockManagementModule::getSingleInstance()->handleRequest(methodName, j);
        break;
    default:
        break;
    }
    return sendMsg;
}

void ServerThread::handleRequest()
{
    qDebug() << "handle";
    QByteArray receivedMsg = tcpSocket.readAll();
    qDebug() << "receivedMsg: " << receivedMsg;
    QByteArray sendMsg = respondRequest(receivedMsg);
    qDebug() << "sendMsg: " << sendMsg;
    tcpSocket.write(sendMsg);
}
