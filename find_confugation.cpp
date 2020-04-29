#include "find_confugation.h"
#include <QDebug>

QFileInfoList find_confugation::drives = QDir::drives();

find_confugation::find_confugation(QObject *parent) : QObject(parent)
{

}

void find_confugation::check()
{
    QFileInfoList new_drives = QDir::drives();

    if (new_drives == drives) return;
    if (new_drives.size() < drives.size()) {
        drives = new_drives;
        return;
    }


    for (int i = 0; i < drives.size(); i++) {
        if (new_drives.at(i).filePath() == drives.at(i).filePath()) continue;
        drives = new_drives;
        QtConcurrent::run(this, &find_confugation::find, i);
        return;
    }

    drives = new_drives;
    QtConcurrent::run(this, &find_confugation::find, new_drives.size()-1);


}

void find_confugation::find(int index)
{
    QString path;

    QDirIterator it(drives.at(index).filePath(), QStringList() << "config.txt", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();

}
