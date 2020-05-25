#include "listmodel.h"
#include <QSqlError>
#include <QDebug>

listmodel::listmodel(tcpServer *server, QObject *parent)
{
    Q_UNUSED(parent)
    this->updateModel();
    connect(server, SIGNAL(commandReady(QString)), this, SLOT(updateModel()));
}

QVariant listmodel::data(const QModelIndex &index, int role) const
{
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> listmodel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[nameRole] = "name";
    roles[descriptionRole] = "description";
    roles[dateStartRole] = "dateStart";
    roles[dateEndRole] = "dateEnd";
    roles[progressRole] = "progress";
    return roles;
}

void listmodel::updateModel()
{
    this->setQuery("SELECT * FROM tasks");
}

int listmodel::getid(int row)
{
    return this->data(this->index(row, 0), idRole).toInt();
}
