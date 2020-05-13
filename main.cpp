#include "mainwindow.h"

#include <QApplication>
#include <QtTest>
#include "testdatetime.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("CppQtLearning");
    QCoreApplication::setOrganizationDomain("GB");
    QCoreApplication::setApplicationName("CppQt");

    QTest::qExec(new testDateTime(), argc, argv);

//    MainWindow w;
//    w.show();
//    return a.exec();
}
