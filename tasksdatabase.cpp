#include "tasksdatabase.h"
#include <QDebug>
#include <QSqlError>

tasksDatabase::tasksDatabase(QObject *parent) : QObject(parent)
{

}

void tasksDatabase::connectToDatabase(QString nameDatabase)
{
    // Создание/открытие базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nameDatabase);
    if (!db.open()){
        qDebug() << "Can't open database";
        return;
    }

    // Создание таблицы если ее нет
    if (db.tables().size() == 0) {
        QSqlQuery *query = new QSqlQuery();
        QString str = "CREATE TABLE tasks ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "name VARCHAR(255),"
                      "description VARCHAR(255),"
                      "datestart VARCHAR(10),"
                      "dateend VARCHAR(10),"
                      "progress VARCHAR(4) );";
        if (!query->exec(str)) {
            qDebug() << "Unable to create a table";
        }
    }

    this->insertDataToTable("So", "sad", "11.11.1111", "22.22.2222", "0");
}

void tasksDatabase::insertDataToTable(QString name, QString description, QString dateStart, QString dateEnd, QString progress)
{
    QRegExp dateStartRX("[0-3][0-9]\.[0-1][0-9]\.[0-9][0-9][0-9][0-9]");
    QRegExp dateEndRX("[0-3][0-9]\.[0-1][0-9]\.[0-9][0-9][0-9][0-9]");
    QRegExp progRX("[0-1]?[0-9]?[0-9]%");
    if (!dateStartRX.exactMatch(dateStart)) dateStart = "00.00.0000";
    if (!dateEndRX.exactMatch(dateStart)) dateEnd = "00.00.0000";
    if (!progRX.exactMatch(progress)) progress = "0";

    QSqlQuery query;
    QString str = "INSERT INTO tasks (name, description, datestart, dateend, progress)"
                  "VALUES ( '" + name + "', '" + description + "', '" + dateStart + "', '" + dateEnd + "', '" + progress + "' )";
    if (!query.exec(str)) {
        qDebug() << "Unable insert data to database";
        qDebug() << query.lastError().text();
    }
}

void tasksDatabase::removeRecord(const int id)
{
    QSqlTableModel table(this);
    table.removeRow(id);
}
