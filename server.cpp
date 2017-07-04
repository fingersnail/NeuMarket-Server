#include "server.h"

Server::Server()
{
}

void Server::incomingConnection(int socketDescriptor)
{
    ServerThread *thread = new ServerThread(socketDescriptor, this);
    thread->start();
}
