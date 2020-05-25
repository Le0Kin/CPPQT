#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tasksdatabase.h"
#include "listmodel.h"
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // БД и сервер
    tasksDatabase database;
    tcpServer server(8080);
    database.connectToDatabase("db", &server);

    // Модель
    listmodel *model = new listmodel(&server);

    engine.rootContext()->setContextProperty("mymodel", model);
    engine.rootContext()->setContextProperty("database", &database);

    engine.load(url);

    return app.exec();
}
