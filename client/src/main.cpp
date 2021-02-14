#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Organization");
    app.setOrganizationDomain("Some Domain");
    QQmlApplicationEngine engine;
    Client client;
    QQmlContext *context = engine.rootContext();
    context ->setContextProperty("client", &client);
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine.load(url);
    return app.exec();
}
