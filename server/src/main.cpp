#include <QCoreApplication>
#include <QtDebug>
#include <iostream>

#include "http_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HttpServer server(8090); // do not change port number

    QMessageLogger().info() << "Server is running";

    return app.exec();
}
