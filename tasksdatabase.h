#ifndef TASKSDATABASE_H
#define TASKSDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "tcpserver.h"

class tasksDatabase : public QObject
{
    Q_OBJECT
public:
    explicit tasksDatabase(QObject *parent = nullptr);

    void connectToDatabase(QString nameDatabase, tcpServer *server);

private:
    QSqlDatabase db;

public slots:
    void insertDataToTable(QString name, QString description, QString dateStart, QString dateEnd, QString progress);
    void insertDataToTable(QString command);
    void removeRecord(const int id);

};

#endif // TASKSDATABASE_H
