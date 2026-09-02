#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "NodeManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/HolocronGui/Main.qml")));

    NodeManager nodeManager;

    return app.exec();
}