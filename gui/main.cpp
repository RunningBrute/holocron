#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>

#include "NodeManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    NodeManager nodeManager(&app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("nodeManager", &nodeManager);

    engine.load(QUrl(QStringLiteral("qrc:/HolocronGui/Main.qml")));

    return app.exec();
}