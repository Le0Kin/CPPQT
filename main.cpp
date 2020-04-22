#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("CppQtLearning");
    QCoreApplication::setOrganizationDomain("GB");
    QCoreApplication::setApplicationName("CppQt");

    MainWindow w;
    w.show();
    return a.exec();
}
