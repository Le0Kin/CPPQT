#include "testdatetime.h"
#include "mainwindow.h"
#include <QDebug>

testDateTime::testDateTime(QObject *parent) : QObject(parent)
{

}

void testDateTime::testDate()
{
    MainWindow mw;
    mw.show();
    mw.getNewFileButton().trigger();

    mw.getAddDateButton().trigger();
    QCOMPARE(mw.getTextEditor().toPlainText(), "13.05.2020");

    mw.getAddDateButton().trigger();
    QCOMPARE(mw.getTextEditor().toPlainText(), "13.05.202013.05.2020");
}
