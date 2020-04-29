#ifndef FIND_CONFUGATION_H
#define FIND_CONFUGATION_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QtConcurrent>

class find_confugation : public QObject
{
    Q_OBJECT
public:
    explicit find_confugation(QObject *parent = nullptr);
    static QFileInfoList drives;

public slots:
    void check();

private:
    void find(int);

};

#endif // FIND_CONFUGATION_H
