#ifndef TESTDATETIME_H
#define TESTDATETIME_H

#include <QObject>
#include <QtTest>
#include <QTextEdit>

class testDateTime : public QObject
{
    Q_OBJECT
public:
    explicit testDateTime(QObject *parent = nullptr);

private slots:
    void testDate();
};

#endif // TESTDATETIME_H
