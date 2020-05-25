#include "tcpserver.h"

tcpServer::tcpServer(int port, QObject *parent)
{
    server = new QTcpServer(this);
    if (server->listen(QHostAddress::Any, port)) {
        connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnect()));
    }
}

void tcpServer::slotNewConnect()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadData()));
}

void tcpServer::slotReadData()
{
    QDataStream input(socket);
    QByteArray ba;
    while (socket->bytesAvailable() > 0) {
        ba = socket->readAll();
    }
    QString command(ba);
    emit commandReady(command);
}
