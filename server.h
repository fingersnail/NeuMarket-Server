#ifndef MAINSERVER_H
#define MAINSERVER_H

#include "serverthread.h"
#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // MAINSERVER_H
