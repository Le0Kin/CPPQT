#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include "tcpserver.h"

class listmodel : public QSqlQueryModel
{
    Q_OBJECT
public:
    listmodel(tcpServer *server, QObject *parent = 0);

    enum Roles {
        idRole = Qt::UserRole + 1,      // id
        nameRole,                       // название задачи
        descriptionRole,                // описание задачи
        dateStartRole,                  // дата начала
        dateEndRole,                    // дата окончания
        progressRole                    // прогресс
    };

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

public slots:
    void updateModel();
    int getid(int row);
};

#endif // LISTMODEL_H
