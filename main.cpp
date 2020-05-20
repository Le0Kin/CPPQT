#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tasksdatabase.h"
#include "listmodel.h"

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

    tasksDatabase database;
    database.connectToDatabase("db");

    listmodel *model = new listmodel();

    engine.rootContext()->setContextProperty("mymodel", model);
    engine.rootContext()->setContextProperty("database", &database);

    engine.load(url);

    return app.exec();
}
