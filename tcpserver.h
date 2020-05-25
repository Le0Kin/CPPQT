#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class tcpServer : public QObject
{
    Q_OBJECT
public:
    explicit tcpServer(int port, QObject *parent = nullptr);

private:
    QTcpServer* server;
    QTcpSocket* socket;

private slots:
    void slotNewConnect();
    void slotReadData();

signals:
    void commandReady(QString command);
};

#endif // TCPSERVER_H
